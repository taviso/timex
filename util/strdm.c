#include <stddef.h>
#include <c88.h>
#include <stdint.h>
#include <timex.h>

#if 0
// This feels like it should be smaller, but I can't figure out an
// algorithm that beats the code size.
char _range_table[][] = {
    { '/', DM5_EXCLAMATION, '!' },
    { '9', DM5_0, '0' },
    { '@', DM5_COLON, ':' },
    { 'Z', DM5_A, 'A' },
    { '`', DM5_OPENSQBRACKET, '[' },
    { 'z', DM5_A, 'a' },
    { '~', DM5_OPENBRACE, '{'}
};
#endif

uint8_t _inline asciidm(uint8_t src)
{
    if (src == 0)
        return LCD_END_BANNER;
    if (src <= ' ')
        return DM5_SPACE;
    if (src <= '/')
        return DM5_EXCLAMATION + (src - '!');
    if (src <= '9')
        return DM5_0 + (src - '0');
    if (src <= '@')
        return DM5_COLON + (src - ':');
    if (src <= 'Z')
        return DM5_A + (src - 'A');
    if (src <= '`')
        return DM5_OPENSQBRACKET + (src - '[');
    if (src <= 'z')
        return DM5_A + (src - 'a');
    if (src <= '~')
        return DM5_OPENBRACE + (src - '{');
    return DM5_SPACE;
}

void strtodm(uint8_t col, char *dst, const char *src)
{
    *dst++ = LCDBANNER_COL(col);
    do {
        *dst++ = asciidm(*src);
    } while (*src++);
}
