#include "utf.h"

#ifdef _WIN32
#include <Windows.h>
const char *_locale = ".utf-8";
#define set() SetConsoleOutputCP(CP_UTF8);
#else
const char *_locale = "";
#endif

int __validate(uchr_t c)
{
    if (c <= 0x7f) return 1;

    if (0xC280 <= c && c <= 0xDFBF)
        return ((c & 0xE0C0) == 0xC080);
    
    if (0xEDA080 <= c && c <= 0xEDBFBF)
        return 0;

    if (0xE0A080 <= c && c <= 0xEFBFBF)
        return ((c & 0xF0C0C0) == 0xE08080);
    
    if (0xF0908080 <= c && c <= 0xF48FBFBF)
        return ((c & 0xF8C0C0C0) == 0xF0808080);

    return 0;
}

int u_next(char *txt, uchr_t *ch)
{
    uchr_t encoding = 0;
    int len = length(txt);

    for (int i = 0; i < len && txt[i] != '\0'; i++)
    {
        encoding = (encoding << 8) | txt[i];
    }

    errno = 0;
    if (len == 0 || !__validate(encoding))
    {
        encoding = txt[0];
        len = 1;
        errno = EINVAL;
    }

    if (ch) *ch = encoding;

    return encoding ? len : 0;
}

uchr_t u_encode(uint32_t codepoint)
{
    uchr_t c = codepoint;

    if (codepoint > 0x7F)
    {
        c =   (codepoint & 0x000003F) 
            | (codepoint & 0x0000FC0) << 2 
            | (codepoint & 0x003F000) << 4 
            | (codepoint & 0x01C0000) << 6;
        
        if (codepoint < 0x0000800) c |= 0x0000C080;
        else if (codepoint < 0x0010000) c |= 0x00E08080;
        else c |= 0xF0808080;
    }

    return c;
}

uint32_t u_decode(uchr_t ch)
{
    uint32_t mask;

    if (ch > 0x7F)
    {
        mask = (ch <= 0x00EFBFBF) ? 0x000F0000 : 0x003F0000;
        ch =  ((ch & 0x07000000) >> 6) 
            | ((ch & mask) >> 4)
            | ((ch & 0x00003F00) >> 2)
            | (ch & 0x0000003F);
    }

    return ch;
}

int ulen(uint32_t ch)
{
    if(ch & 0xf0000000)
        return 4;

    if(ch & 0x700000)
        return 3;

    if(ch & 0xc000)
        return 2;

    if (!(ch & 0x80))
        return 1;

    return -1;
}

void uputc(uint32_t ch)
{
    //Make sure output uses utf-8
    setlocale(LC_ALL, _locale);
    set();

    int size = ulen(ch);

    //create buffer to hold all the characters
    char *buff = (char *)malloc(sizeof(char) * (size + 1));
    // printf("%d\n", size);

    uint8_t j = 0;
    for(int i = 0; i < size; i++)
    {
        int shifter = (size - (i + 1)) * 8;
        uint8_t c = ((ch >> shifter) & 0xFF);
        if(c == 0)
            continue;
        
        printf("0x%X ", c);
        buff[j++] = c;
    }
    buff[j] = '\0';

    // printf("%x\n", buff[2]);
    puts(buff);
}