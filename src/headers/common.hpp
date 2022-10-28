#pragma once

#include <cstddef>

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

void report_assertion_failure(char const *prefix, char const *filename, std::size_t line_number,
                              char const *function_name, char const *cond, char *msg, ...);
