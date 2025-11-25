#include <stdint.h>
#include <stddef.h>

/* Implement tối giản cho memset */
void *memset(void *s, int c, size_t n)
{
    uint8_t *p = (uint8_t *)s;
    while (n--)
    {
        *p++ = (uint8_t)c;
    }
    return s;
}

/* Implement tối giản cho memcpy (FreeRTOS cũng hay dùng) */
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

/* Stub cho hàm unwind mà linker đòi khi không link libgcc */
void __aeabi_unwind_cpp_pr0(void)
{
    /* Không dùng C++ exception nên để trống */
}
