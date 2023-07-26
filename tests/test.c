#include "../src/utf.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(){  
    uputc(u_encode(0x20ac));
    uputc(u_encode(0x0bb8));
    uputc(u_encode(0x61a8));
    uputc(u_encode(0x120ab));

    return 0;
}