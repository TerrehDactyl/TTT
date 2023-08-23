#include <stdio.h>
#define my_sizeof(X)  ((X*)0+1)
void deref(char *t[])
{
	size_t size = my_sizeof(t);
	printf("%d", size);
  //  	for(int count = 1; t; count++,  t++)
		// printf("variable: %s\ncount: %d\n\n", *t, count);
}
int main(void) 
{
    char *t[] = { "Program", "juyy", "this", "thee", "other", "next", "other"};
    deref(t);
}