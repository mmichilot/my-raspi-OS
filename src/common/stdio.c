#include <kernel/uart.h>

char getc(void) {
   return uart_getc();
}

void putc(int c) {
   uart_putc(c);
}

void puts(const char *s) {
   while (*s != '\0')
      putc((int)*s++);
}

void gets(char *s) {
   char c;

   do {
      c = getc();
      putc(c);
      // Backspace
      if (c == 8 || c == 127) {
         putc(' ');
         putc(8);
         *s-- = c;
      }
      else
         *s++ = c;
   } while (c != '\r' || c == '\n');
   
   // Newline when input is finished
   putc('\n');
   *--s = '\0';
}
