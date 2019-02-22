/**********************************************************************
 * Copyright (c) 2013-2015 Pieter Wuille, Gregory Maxwell             *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#ifndef _SECP256K1_UTIL_H_
#define _SECP256K1_UTIL_H_

#define HAVE_CONFIG_H 1

#if defined HAVE_CONFIG_H
#include "libsecp256k1-config.h"
#endif

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include "secp256k1_zkp.h"

#ifdef DETERMINISTIC
#define TEST_FAILURE(msg) do { \
    fprintf(stderr, "%s\n", msg); \
    abort(); \
} while(0);
#else
#define TEST_FAILURE(msg) do { \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, msg); \
    abort(); \
} while(0)
#endif

#ifdef HAVE_BUILTIN_EXPECT
#define EXPECT(x,c) __builtin_expect((x),(c))
#else
#define EXPECT(x,c) (x)
#endif

#ifdef DETERMINISTIC
#define CHECK(cond) do { \
    if (EXPECT(!(cond), 0)) { \
        TEST_FAILURE("test condition failed"); \
    } \
} while(0)
#else
#define CHECK(cond) do { \
    if (EXPECT(!(cond), 0)) { \
        TEST_FAILURE("test condition failed: " #cond); \
    } \
} while(0)
#endif

/* Like assert(), but safe to use on expressions with side effects. */
#ifndef NDEBUG
#define DEBUG_CHECK CHECK
#else
#define DEBUG_CHECK(cond) do { (void)(cond); } while(0)
#endif

/* Like DEBUG_CHECK(), but when VERIFY is defined instead of NDEBUG not defined. */
#ifdef VERIFY
#define VERIFY_CHECK CHECK
#else
#define VERIFY_CHECK(cond) do { (void)(cond); } while(0)
#endif

static SECP256K1_INLINE void *checked_malloc(size_t size) {
    void *ret = malloc(size);
    CHECK(ret != NULL);
    return ret;
}

/* Macro for restrict, when available and not in a VERIFY build. */
#if defined(SECP256K1_BUILD) && defined(VERIFY)
# define SECP256K1_RESTRICT
#else
# if (!defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L) )
#  if SECP256K1_GNUC_PREREQ(3,0)
#   define SECP256K1_RESTRICT __restrict__
#  elif (defined(_MSC_VER) && _MSC_VER >= 1400)
#   define SECP256K1_RESTRICT __restrict
#  else
#   define SECP256K1_RESTRICT
#  endif
# else
#  define SECP256K1_RESTRICT restrict
# endif
#endif

#if defined(_WIN32)
# define I64FORMAT "I64d"
# define I64uFORMAT "I64u"
#else
# define I64FORMAT "lld"
# define I64uFORMAT "llu"
#endif

#if defined(HAVE___INT128)
# if defined(__GNUC__)
#  define SECP256K1_GNUC_EXT __extension__
# else
#  define SECP256K1_GNUC_EXT
# endif
SECP256K1_GNUC_EXT typedef unsigned __int128 uint128_t;
//SECP256K1_GNUC_EXT typedef unsigned char[16] uint128_t;
#endif

/* Extract the sign of an int64, take the abs and return a uint64, constant time. */
SECP256K1_INLINE static int secp256k1_sign_and_abs64(uint64_t *out, int64_t in) {
    uint64_t mask0, mask1;
    int ret;
    ret = in < 0;
    mask0 = ret + ~((uint64_t)0);
    mask1 = ~mask0;
    *out = (uint64_t)in;
    *out = (*out & mask0) | ((~*out + 1) & mask1);
    return ret;
}

SECP256K1_INLINE static int secp256k1_clz64_var(uint64_t x) {
    int ret;
    if (!x) {
        return 64;
    }
# if defined(HAVE_BUILTIN_CLZLL)
    ret = __builtin_clzll(x);
# else
    /*FIXME: debruijn fallback. */
    for (ret = 0; ((x & (1ULL << 63)) == 0); x <<= 1, ret++);
# endif
    return ret;

}


#endif
