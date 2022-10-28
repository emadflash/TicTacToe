#include "headers/common.hpp"

#include <cstdio>

void report_assertion_failure(char const *prefix, char const *filename, std::size_t line_number,

                              char const *function_name, char const *cond, char *msg, ...) {
  fprintf(stderr, "%s:%zu: %s: %s: ", filename, line_number, prefix, function_name);
  if (cond) {
    fprintf(stderr, "`%s` ", cond);
  }

  if (msg) {
    va_list ap;
    va_start(ap, msg);
    vfprintf(stderr, msg, ap);
    va_end(ap);
  }

  fputc('\n', stderr);
}
