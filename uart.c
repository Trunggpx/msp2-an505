#include <stdint.h>

#define UART0_BASE 0x40004000UL
#define UART_DR    (*(volatile uint32_t *)(UART0_BASE + 0x00))
#define UART_FR    (*(volatile uint32_t *)(UART0_BASE + 0x18))

void uart_init(void)
{
    // QEMU MPS2 PL011 reset default đã OK, không cần config
}

void uart_putc(char c)
{
    while (UART_FR & (1 << 5)) {
        // TXFF full, wait
    }
    UART_DR = c;
}

void uart_puts(const char *s)
{
    while (*s) {
        if (*s == '\n')
            uart_putc('\r');
        uart_putc(*s++);
    }
}
