#include <stdio.h>
struct test {
	unsigned int x : 2;
	unsigned int y : 2;
	unsigned int z : 2;
};
int main()
{
	struct test t;
	t.x = 7;
	printf("size of x is %d\n", t.x);
	printf("size of y is %d\n", t.x);
	printf("size of z is %d\n", t.x);

	return 0;
}

