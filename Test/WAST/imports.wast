(module 
    (import $print_i32 "stdio" "print" (param i32))
    (import $print_i32_f32 "stdio" "print" (param i32 f32))
    (func $print (param $i i32)
        (call_import $print_i32 (get_local $i))
        (call_import $print_i32_f32
            (i32.add (get_local $i) (i32.const 1))
            (f32.const 42)
        )
    )
    (export "print" $print)
)

(invoke "print" (i32.const 13))
