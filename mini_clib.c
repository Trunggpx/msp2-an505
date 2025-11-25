#include <stdint.h>
#include <stddef.h>   // <-- bắt buộc để có size_t

void *memset(void *dest, int value, size_t n)
{
    uint8_t *p = (uint8_t *)dest;
    while (n--) {
        *p++ = (uint8_t)value;
    }
    return dest;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}
