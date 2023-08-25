#include <stdio.h>

void deref(char *t[])
{
   	for(int count = 1; *t; count++)
		printf("variable: %s\ncount: %d\n\n", &**t++, count);
}
int main(void) 
{
    char *t[] = { "Program", "juyy", "this", "thee", "other", "next", "other"};
    deref(t);
}