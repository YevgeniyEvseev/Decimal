#ifndef DEFINE_H
#define DEFINE_H

#define CRITICAL 1
#define WARNING 0

#define ERR_1(MSG) fprintf(stderr, "%s %d %s", __FILE__, __LINE__, MSG)
#define ERR_2(MSG, segv)                                  \
  do {                                                    \
    fprintf(stderr, "%s %d %s", __FILE__, __LINE__, MSG); \
    if (segv) {                                           \
      fprintf(stderr, "aborting...!");                    \
      abort();                                            \
    }                                                     \
  } while (0)

#define FUNC_3A_ARG(A1, A2, A3, ...) A3
#define MACRO_CHOOSER(...) FUNC_3A_ARG(__VA_ARGS__, ERR_2, ERR_1)
#define ERROR(...) MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define var1 0
#define var2 1
#endif