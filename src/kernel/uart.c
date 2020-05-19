#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>

#define UART_FUNC 0x4

static inline void mmio_write(uint32_t reg, uint32_t data) {
   *(volatile uint32_t*)reg = data;
}

static inline uint32_t mmio_read(uint32_t reg) {
   return *(volatile uint32_t*)reg;
}

// Loop <delay> times in a way that the compiler won't optimize away
static inline void delay(uint32_t count) {
   asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
              : "=r" (count)
              : [count] "0" (count)
              : "cc");
};

void uart_init() {
   // Disable UART
   mmio_write(UART0_CR, 0x00000000);

   // Disable pull-down/up for pins 14 and 15
   mmio_write(GPPUD, 0x00000000);
   delay(150);

   mmio_write(GPPUDCLK0, (1 << 14) | (1 <<15));
   delay(150);

   mmio_write(GPPUDCLK0, 0x00000000);

#ifdef MODEL_2

   // Select UART function for pins 14 and 15
   mmio_write(GPFSEL1, (UART_FUNC << 15) | (UART_FUNC << 12));

#endif

   // Clear all pending interrupts
   mmio_write(UART0_ICR, 0x7FF);

   // Set baud rate to 115200
   mmio_write(UART0_IBRD, 312);
   mmio_write(UART0_FBRD, 0xFF);

   // Configure UART
   mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

   // Disable all interrupts
   mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

   // Enable UART
   mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));

};

void uart_putc(unsigned char c) {
   while (mmio_read(UART0_FR) & (1 << 5)) { }
   mmio_write(UART0_DR, c);
}

unsigned char uart_getc() {
   while (mmio_read(UART0_FR) & (1 << 4)) { }
   return mmio_read(UART0_DR);
}

void uart_puts(const char* str) {
   while (*str != '\0') {
      uart_putc(*str++);
   }
}

