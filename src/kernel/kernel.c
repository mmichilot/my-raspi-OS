#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <common/string.h>
#include <common/stdlib.h>
#include <common/stdio.h>

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
   (void) r0;
   (void) r1;
   (void) atags;
  
   char *msg = "Hello, kernel World!\n"; 
   char str[30];

   uart_init();
   puts(msg);

   while (1) {
      gets(str);
      puts("This is the word you entered: ");
      puts(str);
      putc('\n');
   }
}
