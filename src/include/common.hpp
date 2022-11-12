#pragma once

#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <string>

#ifndef DEBUG_TRAP
#define DEBUG_TRAP() __builtin_trap()
#endif

#ifndef ASSERT
#define ASSERT(cond)                                                                               \
  do {                                                                                             \
    if (!(cond)) {                                                                                 \
      report_assertion_failure("Assertion Failure", __FILE__, __LINE__, __func__, #cond, NULL);    \
      DEBUG_TRAP();                                                                                \
    }                                                                                              \
  } while (0);
#endif

#ifndef ASSERT_MESSAGE
#define ASSERT_MESSAGE(cond, msg)                                                                  \
  do {                                                                                             \
    if (!(cond)) {                                                                                 \
      report_assertion_failure("Assertion Failure", __FILE__, __LINE__, __func__, #cond, msg);     \
      DEBUG_TRAP();                                                                                \
    }                                                                                              \
  } while (0);
#endif

#ifndef DEBUG_ASSERT
#ifndef Debug
#define DEBUG_ASSERT(cond)
#else
#define DEBUG_ASSERT(cond)                                                                         \
  do {                                                                                             \
    if (!(cond)) {                                                                                 \
      report_assertion_failure("Debug Assert Failure", __FILE__, __LINE__, __func__, #cond, NULL); \
      DEBUG_TRAP();                                                                                \
    }                                                                                              \
  } while (0);
#endif
#endif

#ifndef DEBUG_ASSERT_MESSAGE
#ifndef Debug
#define DEBUG_ASSERT_MESSAGE(cond, msg)
#else
#define DEBUG_ASSERT_MESSAGE(cond, msg)                                                            \
  do {                                                                                             \
    if (!(cond)) {                                                                                 \
      report_assertion_failure("Debug Assert Failure", __FILE__, __LINE__, __func__, #cond, msg);  \
      DEBUG_TRAP();                                                                                \
    }                                                                                              \
  } while (0);
#endif
#endif

#ifndef UNREACHABLE
#define UNREACHABLE()                                                                              \
  do {                                                                                             \
    report_assertion_failure("Unreachable", __FILE__, __LINE__, __func__, NULL, NULL);             \
    DEBUG_TRAP();                                                                                  \
  } while (0);
#endif

#ifndef TODO
#define TODO()                                                                                     \
  do {                                                                                             \
    report_assertion_failure("TODO", __FILE__, __LINE__, __func__, NULL, NULL);                    \
    DEBUG_TRAP();                                                                                  \
  } while (0);
#endif

#ifndef TODO_MESSAGE
#define TODO_MESSAGE(...)                                                                          \
  do {                                                                                             \
    report_assertion_failure("TODO", __FILE__, __LINE__, __func__, NULL, __VA_ARGS__);             \
    DEBUG_TRAP();                                                                                  \
  } while (0);
#endif

#ifndef Debug
#define DEBUG(...)
#else
#define DEBUG(...) write_log("DEBUG", __VA_ARGS__)
#endif

#define INFO(...) write_log("INFO", __VA_ARGS__)
#define WARN(...) write_log("WARN", __VA_ARGS__)
#define ERR(...) write_log("ERR", __VA_ARGS__)

// Example log message
// [ERR] This is my error message
void write_log(char const *prefix, char const *msg, ...);

void report_assertion_failure(char const *prefix, char const *filename, std::size_t line_number,
                              char const *function_name, char const *cond, char *msg, ...);
