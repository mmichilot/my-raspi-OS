char *itoa(int value) {
   int neg = (value < 0);
   static char numbers[] = "0123456789";
   static char buffer[50];
   char *ptr = &buffer[49];

   *ptr = '\0';
   
   // Ensure that when we use value, it's not negative
   if (neg)
      value *= -1;

   do {
      *--ptr = numbers[value%10];
      
      value /= 10;

   } while (value != 0);

   // Don't forget the negative sign
   if (neg)
      *--ptr = '-';

   return ptr;
}
