#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef enum LOG_LEVEL_t
{
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
} LOG_LEVEL;

static const char* s_LogLevels[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL" };
static const char* s_LogColors[] = { "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m" };

#ifdef _WIN32
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#ifndef EX_RELEASE
	#define LOG_TRACE(...) { s_Log(LOG_TRACE, __FILENAME__, __LINE__, __TIME__); printf(__VA_ARGS__); printf("\n"); }
	#define LOG_DEBUG(...) { s_Log(LOG_DEBUG, __FILENAME__, __LINE__, __TIME__); printf(__VA_ARGS__); printf("\n"); }
	#define LOG_INFO(...)  { s_Log(LOG_INFO,  __FILENAME__, __LINE__, __TIME__); printf(__VA_ARGS__); printf("\n"); }
	#define LOG_WARN(...)  { s_Log(LOG_WARN,  __FILENAME__, __LINE__, __TIME__); printf(__VA_ARGS__); printf("\n"); }
	#define LOG_ERROR(...) { s_Log(LOG_ERROR, __FILENAME__, __LINE__, __TIME__); printf(__VA_ARGS__); printf("\n"); }
	#define LOG_FATAL(...) { s_Log(LOG_FATAL, __FILENAME__, __LINE__, __TIME__); printf(__VA_ARGS__); printf("\n"); }
#else
	#define LOG_TRACE(...)
	#define LOG_DEBUG(...)
	#define LOG_INFO(...)
	#define LOG_WARN(...)
	#define LOG_ERROR(...)
	#define LOG_FATAL(...)
#endif

static void s_Log(const uint8_t level, const char* file, const uint32_t line, const char* time)
{
	printf("(%s) %s [%s]\x1b[0m \x1b[90m%s:%d:\x1b[0m ", time, s_LogColors[level], s_LogLevels[level], file, line);
}
