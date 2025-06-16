#ifndef CONFIG_H
#define CONFIG_H

#define C23 (__STDC_VERSION__ >= 202311L)
#define clang_NOOPTIMIZE __attribute__((noinline)) __attribute__((optnone))
#define GCC_NOOPTIMIZE __attribute__((noinline)) __attribute__((optimize("-O0")))

#ifdef __GNUC__
    #define NOOPTIMIZE GCC_NOOPTIMIZE
#elif __clang__
    #define NOOPTIMIZE clang_NOOPTIMIZE
#endif

#define DATAPATH_MASTER_PASSWORD "data/mp.sha256"
#define DATAPATH_MASTER_SALT "data/mp.salt"

#endif

