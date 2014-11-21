//http://www.tutorialspoint.com/cprogramming/c_pointers.htm

#include <stdio.h>

int main ()
{
   char array[2] = {'a','b'}; 
   char *ptr;

   ptr = &array;/* store address of array in pointer variable*/
    
   printf("Address of array variable: %x\n", &array  );

   /* address stored in pointer variable */
   printf("Address stored in ptr variable: %x\n", ptr );

   /* access the value using the pointer */
   printf("Value of array[0]: %c\n", array[0] );
   ptr = ptr+1;
   printf("Value of *ptr variable: %c\n", *ptr );
   return 0;
}
