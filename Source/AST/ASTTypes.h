#pragma once

#include "Core/Core.h"

namespace AST
{
	// Forward declarations.
	template<typename TypeClass> struct Expression;
	enum class AnyOp : uint8;
	enum class IntOp : uint8;
	enum class FloatOp : uint8;
	enum class BoolOp : uint8;
	enum class VoidOp : uint8;

	#define ENUM_AST_TYPECLASSES_WITHOUT_ANY() AST_TYPECLASS(Int) AST_TYPECLASS(Float) AST_TYPECLASS(Bool) AST_TYPECLASS(Void)
	#define ENUM_AST_TYPECLASSES() AST_TYPECLASS(Any) ENUM_AST_TYPECLASSES_WITHOUT_ANY()
	
	#define ENUM_AST_TYPES_Int(callback,...) callback(I8,Int,__VA_ARGS__) callback(I16,Int,__VA_ARGS__) callback(I32,Int,__VA_ARGS__) callback(I64,Int,__VA_ARGS__)
	#define ENUM_AST_TYPES_Float(callback,...) callback(F32,Float,__VA_ARGS__) callback(F64,Float,__VA_ARGS__)
	#define ENUM_AST_TYPES_Bool(callback,...) callback(Bool,Bool,__VA_ARGS__)
	#define ENUM_AST_TYPES_Void(callback,...) callback(Void,Void,__VA_ARGS__)
	#define ENUM_AST_TYPES_Numeric(callback,...) ENUM_AST_TYPES_Int(callback,__VA_ARGS__) ENUM_AST_TYPES_Float(callback,__VA_ARGS__)
	#define ENUM_AST_TYPES_NonVoid(callback,...) ENUM_AST_TYPES_Numeric(callback,__VA_ARGS__) ENUM_AST_TYPES_Bool(callback,__VA_ARGS__)
	#define ENUM_AST_TYPES(callback,...) ENUM_AST_TYPES_NonVoid(callback,__VA_ARGS__) ENUM_AST_TYPES_Void(callback,__VA_ARGS__)

	// Can't recursively expand macros, so we have to manually enumerate one side of the pair.
    #define ENUM_AST_TYPE_PAIRS(callback,...) \
        callback(I8,I8,__VA_ARGS__)    callback(I16,I8,__VA_ARGS__)    callback(I32,I8,__VA_ARGS__)    callback(I64,I8,__VA_ARGS__)    callback(F32,I8,__VA_ARGS__)    callback(F64,I8,__VA_ARGS__)    callback(Bool,I8,__VA_ARGS__)    callback(Void,I8,__VA_ARGS__) \
        callback(I8,I16,__VA_ARGS__)    callback(I16,I16,__VA_ARGS__)    callback(I32,I16,__VA_ARGS__)    callback(I64,I16,__VA_ARGS__)    callback(F32,I16,__VA_ARGS__)    callback(F64,I16,__VA_ARGS__)    callback(Bool,I16,__VA_ARGS__)    callback(Void,I16,__VA_ARGS__) \
        callback(I8,I32,__VA_ARGS__)    callback(I16,I32,__VA_ARGS__)    callback(I32,I32,__VA_ARGS__)    callback(I64,I32,__VA_ARGS__)    callback(F32,I32,__VA_ARGS__)    callback(F64,I32,__VA_ARGS__)    callback(Bool,I32,__VA_ARGS__)    callback(Void,I32,__VA_ARGS__) \
        callback(I8,I64,__VA_ARGS__)    callback(I16,I64,__VA_ARGS__)    callback(I32,I64,__VA_ARGS__)    callback(I64,I64,__VA_ARGS__)    callback(F32,I64,__VA_ARGS__)    callback(F64,I64,__VA_ARGS__)    callback(Bool,I64,__VA_ARGS__)    callback(Void,I64,__VA_ARGS__) \
        callback(I8,F32,__VA_ARGS__)    callback(I16,F32,__VA_ARGS__)    callback(I32,F32,__VA_ARGS__)    callback(I64,F32,__VA_ARGS__)    callback(F32,F32,__VA_ARGS__)    callback(F64,F32,__VA_ARGS__)    callback(Bool,F32,__VA_ARGS__)    callback(Void,F32,__VA_ARGS__) \
        callback(I8,F64,__VA_ARGS__)    callback(I16,F64,__VA_ARGS__)    callback(I32,F64,__VA_ARGS__)    callback(I64,F64,__VA_ARGS__)    callback(F32,F64,__VA_ARGS__)    callback(F64,F64,__VA_ARGS__)    callback(Bool,F64,__VA_ARGS__)    callback(Void,F64,__VA_ARGS__) \
        callback(I8,Bool,__VA_ARGS__)    callback(I16,Bool,__VA_ARGS__)    callback(I32,Bool,__VA_ARGS__)    callback(I64,Bool,__VA_ARGS__)    callback(F32,Bool,__VA_ARGS__)    callback(F64,Bool,__VA_ARGS__)    callback(Bool,Bool,__VA_ARGS__)    callback(Void,Bool,__VA_ARGS__) \
        callback(I8,Void,__VA_ARGS__)    callback(I16,Void,__VA_ARGS__)    callback(I32,Void,__VA_ARGS__)    callback(I64,Void,__VA_ARGS__)    callback(F32,Void,__VA_ARGS__)    callback(F64,Void,__VA_ARGS__)    callback(Bool,Void,__VA_ARGS__)    callback(Void,Void,__VA_ARGS__)

	// Provides typedefs that match the AST type names.
	namespace NativeTypes
	{
		typedef uint8 I8;
		typedef uint16 I16;
		typedef uint32_t I32;
		typedef uint64 I64;
		typedef float32 F32;
		typedef float64 F64;
		typedef bool Bool;
		typedef void Void;
	};

	// Define the TypeClassId enum: TypeClassId::Any, TypeClassId::Int, etc.
	enum class TypeClassId : uint8
	{
		Invalid = 0,
		#define AST_TYPECLASS(className) className,
			ENUM_AST_TYPECLASSES()
		#undef AST_TYPECLASS
	};

	// Define the TypeId enum: TypeId::I8, TypeId::I16, etc.
	enum class TypeId : uint8
	{
		None = 0,
		#define AST_TYPE(typeName,className,...) typeName,
		ENUM_AST_TYPES(AST_TYPE)
		#undef AST_TYPE
		num,
		max = num - 1
	};

	// Define the xClass types: AnyClass, IntClass, etc.
	template<TypeClassId typeClass> struct TypeClass;
	#define AST_TYPECLASS(className) \
		struct className##Class \
		{ \
			AST_API static TypeClassId id; \
			typedef className##Op Op; \
			typedef Expression<className##Class> ClassExpression; \
		}; \
		template<> struct TypeClass<TypeClassId::className> : public className##Class {};
	ENUM_AST_TYPECLASSES()
	#undef AST_TYPECLASS

	// Define the xType types: IntType, FloatType, etc.
	template<TypeId type> struct Type;
	#define AST_TYPE(typeName,className,...) \
		struct typeName##Type \
		{ \
			AST_API static TypeId id; \
			AST_API static TypeClassId classId; \
			AST_API static const char* name; \
			typedef className##Op Op; \
			typedef className##Class Class; \
			typedef Expression<Class> TypeExpression; \
			typedef NativeTypes::typeName NativeType; \
		}; \
		template<> struct Type<TypeId::typeName> : public typeName##Type {};
	ENUM_AST_TYPES(AST_TYPE)
	#undef AST_TYPE

	// Based on a TypeId, call a method with a template parameter for the type.
	template<typename Result,template<typename> class Visitor>
	Result dispatchByType(TypeId type,Result invalidResult)
	{
		switch(type)
		{
		#define AST_TYPE(typeName,className,...) case TypeId::typeName: return Visitor<typeName##Type>::visit();
		ENUM_AST_TYPES(AST_TYPE)
		#undef AST_TYPE
		default: return invalidResult;
		}
	}
	
	// Returns whether a type is part of a type class.
	AST_API bool isTypeClass(TypeId type,TypeClassId typeClass);

	// Returns the primary class for a type: Int, Float, Bool, Void.
	AST_API TypeClassId getPrimaryTypeClass(TypeId type);
	
	// Returns a string with the name of a type.
	AST_API const char* getTypeName(TypeId type);

	// Returns the number of bits in a value of a type.
	AST_API size_t getTypeBitWidth(TypeId type);

	// Returns the number of bytes in a value of a type.
	AST_API size_t getTypeByteWidth(TypeId type);

	// Returns the base 2 logarithm of the number of bytes in a value of a type.
	AST_API uint8 getTypeByteWidthLog2(TypeId type);
}
