#include <stdint.h>
#include <stddef.h>

/* Implement for memset */
void *memset(void *s, int c, size_t n)
{
    uint8_t *p = (uint8_t *)s;
    while (n--)
    {
        *p++ = (uint8_t)c;
    }
    return s;
}

/* Implement for memcpy */
void *memcpy(void *dest, const void *src, size_t n)
{
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    while (n--)
    {
        *d++ = *s++;
    }
    return dest;
}

/* link unwind with libgcc */
void __aeabi_unwind_cpp_pr0(void){}
