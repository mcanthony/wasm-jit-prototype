#pragma once
#include <stdint.h>
#include <stddef.h>
#include <memory>
#include <vector>
#include <map>
#include <chrono>
#include <algorithm>
#include <string>
#include <cstring>
#include <string.h>
#include <assert.h>

typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint64_t uint64;
typedef int64_t int64;
typedef uintptr_t uintptr;
typedef intptr_t intptr;
typedef float float32;
typedef double float64;

#ifndef CORE_API
	#define CORE_API DLL_EXPORT
#endif

namespace Core
{
	struct Timer
	{
		Timer(): startTime(std::chrono::high_resolution_clock::now()), isStopped(false) {}
		void stop() { endTime = std::chrono::high_resolution_clock::now(); }
		uint64 getMicroseconds()
		{
			if(!isStopped) { stop(); }
			return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		}
		float64 getMilliseconds() { return getMicroseconds() / 1000.0; }
		float64 getSeconds() { return getMicroseconds() / 1000000.0; }
	private:
		std::chrono::high_resolution_clock::time_point startTime;
		std::chrono::high_resolution_clock::time_point endTime;
		bool isStopped;
	};
	
	// A location in a text file.
	struct TextFileLocus
	{
		uint32 newlines;
		uint16 tabs;
		uint16 characters;

		TextFileLocus(): newlines(0), tabs(0), characters(0) {}

		std::string describe(uint32 spacesPerTab = 4) const
		{
			return "(" + std::to_string(newlines + 1) + ":" + std::to_string(tabs * spacesPerTab + characters + 1) + ")";
		}
	};
}
