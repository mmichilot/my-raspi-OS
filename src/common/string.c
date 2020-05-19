#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t n) {
   const uint8_t *s = (uint8_t*)src;
   uint8_t *d = (uint8_t*)dest;

   while (n--)   
      *d++ = *s++;

   return dest;
}

void memset(void *s, int c, size_t n) {
   uint8_t *byte = (uint8_t*)s;

   while (n--)
      *byte++ = c;
}

size_t strlen(const char *s) {
   size_t len = 0;
   while (*s++ != '\0')
      len++;
   return len;
}
