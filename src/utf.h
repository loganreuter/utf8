#ifndef UTF_H
#define UTF_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <locale.h>

typedef uint32_t uchr_t;

static uint8_t const u8_length[] = {
//  0 1 2 3 4 5 6 7 8 9 A B C D E F
    1,1,1,1,1,1,1,1,0,0,0,0,2,2,3,4
};

#define length(s) u8_length[(((uint8_t *)(s))[0] & 0xFF) >> 4];

int u_strlen(const char *s);
char *u_strncpy(char *dest, const char *src, size_t n);

int u_next(char *txt, uchr_t *ch);

uchr_t u_encode(uint32_t codepoint);
uint32_t u_decode(uchr_t ch);

void uputc(uint32_t ch);

#endif