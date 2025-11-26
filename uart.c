#include <stdint.h>

/*  
 * CMSDK UART0 cho MPS2-AN505
 * Base address according to CoreLink SSE-200 / AN505 platform
 */
#define CMSDK_UART0_BASE   0x40004000UL

#define UART_DATA   (*(volatile uint32_t *)(CMSDK_UART0_BASE + 0x00))
#define UART_STATE  (*(volatile uint32_t *)(CMSDK_UART0_BASE + 0x04))
#define UART_CTRL   (*(volatile uint32_t *)(CMSDK_UART0_BASE + 0x08))
#define UART_BAUD   (*(volatile uint32_t *)(CMSDK_UART0_BASE + 0x0C))
#define UART_STATE_TXFULL   (1u << 0)


void uart_init(void)
{
    UART_CTRL = 0x01;   /* Enable TX */
    UART_BAUD = 16;     /* Baud divisor */
}

void uart_putc(char c)
{
    while (UART_STATE & UART_STATE_TXFULL) {
        /* wait until TX FIFO has space */
    }
    UART_DATA = (uint32_t)c;
}

void uart_puts(const char *s)
{
    while (*s) {
        if (*s == '\n')
            uart_putc('\r');
        uart_putc(*s++);
    }
}
