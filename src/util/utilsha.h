/* sha2 implementation by Aaron D. Gifford (http://www.aarongifford.com) */

#ifndef UTIL_SHA_H
#define UTIL_SHA_H

#include <stddef.h>
#include <stdint.h>
#include "utildecl.h"

/* begin of sha2.h */

/*
 * FILE:  sha2.h
 * AUTHOR:  Aaron D. Gifford - http://www.aarongifford.com/
 *
 * Copyright (c) 2000-2001, Aaron D. Gifford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTOR(S) ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTOR(S) BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: sha2.h,v 1.1 2001/11/08 00:02:01 adg Exp adg $
 */

/*** SHA-256/384/512 Various Length Definitions ***********************/

#define SHA256_BLOCK_LENGTH 64
#define SHA256_DIGEST_LENGTH 32
#define SHA256_DIGEST_STRING_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)
#define SHA384_BLOCK_LENGTH 128
#define SHA384_DIGEST_LENGTH 48
#define SHA384_DIGEST_STRING_LENGTH (SHA384_DIGEST_LENGTH * 2 + 1)
#define SHA512_BLOCK_LENGTH 128
#define SHA512_DIGEST_LENGTH 64
#define SHA512_DIGEST_STRING_LENGTH (SHA512_DIGEST_LENGTH * 2 + 1)

typedef struct _SHA256_CTX {
  uint32_t  state[8];
  uint64_t  bitcount;
  union { // to avoid warnings on pointer casts
    uint8_t buffer[SHA256_BLOCK_LENGTH];
    uint32_t buffer32[SHA256_BLOCK_LENGTH / sizeof(uint32_t)];
    uint64_t buffer64[SHA256_BLOCK_LENGTH / sizeof(uint64_t)];
  };
} SHA256_CTX;

typedef struct _SHA512_CTX {
  uint64_t  state[8];
  uint64_t  bitcount[2];
  union { // ditto
    uint8_t buffer[SHA512_BLOCK_LENGTH];
    uint64_t buffer64[SHA512_BLOCK_LENGTH / sizeof(uint64_t)];
  };
} SHA512_CTX;

typedef SHA512_CTX SHA384_CTX;

/*** SHA-256/384/512 Function Prototypes ******************************/

/*
void SHA256_Init(SHA256_CTX *);
void SHA256_Update(SHA256_CTX*, const u_int8_t*, size_t);
void SHA256_Final(u_int8_t[SHA256_DIGEST_LENGTH], SHA256_CTX*);
char* SHA256_End(SHA256_CTX*, char[SHA256_DIGEST_STRING_LENGTH]);
char* SHA256_Data(const u_int8_t*, size_t, char[SHA256_DIGEST_STRING_LENGTH]);

void SHA384_Init(SHA384_CTX*);
void SHA384_Update(SHA384_CTX*, const u_int8_t*, size_t);
void SHA384_Final(u_int8_t[SHA384_DIGEST_LENGTH], SHA384_CTX*);
char* SHA384_End(SHA384_CTX*, char[SHA384_DIGEST_STRING_LENGTH]);
char* SHA384_Data(const u_int8_t*, size_t, char[SHA384_DIGEST_STRING_LENGTH]);

void SHA512_Init(SHA512_CTX*);
void SHA512_Update(SHA512_CTX*, const u_int8_t*, size_t);
void SHA512_Final(u_int8_t[SHA512_DIGEST_LENGTH], SHA512_CTX*);
char* SHA512_End(SHA512_CTX*, char[SHA512_DIGEST_STRING_LENGTH]);
char* SHA512_Data(const u_int8_t*, size_t, char[SHA512_DIGEST_STRING_LENGTH]);
*/

/* end of sha2.h */

#ifndef sha256_func
#  define sha256_func(name) sha256_digest_ ## name
#endif
#ifndef sha384_func
#  define sha384_func(name) sha384_digest_ ## name
#endif
#ifndef sha512_func
#  define sha512_func(name) sha512_digest_ ## name
#endif

#define sha256_state SHA256_CTX
#define sha384_state SHA384_CTX
#define sha512_state SHA512_CTX

UTILAPI void sha256_func(init) (sha256_state *state);
UTILAPI void sha384_func(init) (sha384_state *state);
UTILAPI void sha512_func(init) (sha512_state *state);

UTILAPI void sha256_func(add) (sha256_state *state, const void *data, size_t size);
UTILAPI void sha384_func(add) (sha384_state *state, const void *data, size_t size);
UTILAPI void sha512_func(add) (sha512_state *state, const void *data, size_t size);

UTILAPI void sha256_func(put) (sha256_state *state, uint8_t digest[SHA256_DIGEST_LENGTH]);
UTILAPI void sha384_func(put) (sha384_state *state, uint8_t digest[SHA384_DIGEST_LENGTH]);
UTILAPI void sha512_func(put) (sha512_state *state, uint8_t digest[SHA512_DIGEST_LENGTH]);

UTILAPI void sha256_func(from) (const void *data, size_t size, uint8_t digest[SHA256_DIGEST_LENGTH]);
UTILAPI void sha384_func(from) (const void *data, size_t size, uint8_t digest[SHA384_DIGEST_LENGTH]);
UTILAPI void sha512_func(from) (const void *data, size_t size, uint8_t digest[SHA512_DIGEST_LENGTH]);

#endif