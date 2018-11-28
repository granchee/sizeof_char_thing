#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

void __assert(int line, const char *msg)
{
	printf("line=%d/ msg=%s\n", line, msg);
}

#define _assert(_exp) { if((_exp)==0) \
                        { __assert(__LINE__, (#_exp)); } \
                        else \
                        { printf("line=%d/ didn't assert\n", __LINE__); } }
#define _compile_assert(_exp) ((void) sizeof(char[(_exp) ? 1 : -1]))
#define ARRAYSIZE(arrayname) (sizeof(arrayname)/sizeof((arrayname)[0]))
#define CHAR_ARRAY_MAX (4)

char good_array[] = {1, 2, 3, 4};
char bad_array_1[] = {1, 2, 3};
char bad_array_2[] = {1, 2, 3, 4, 5};

int main()
{
	_assert(0);
	_assert(1);

	_assert(false);
	_assert(true);

	_assert(1>2);
	_assert(2>1);

	_compile_assert(ARRAYSIZE(good_array) == CHAR_ARRAY_MAX);
	_compile_assert(ARRAYSIZE(bad_array_1) == CHAR_ARRAY_MAX - 1); /* Compilation fails w/out '- 1'. */
	_compile_assert(ARRAYSIZE(bad_array_2) == CHAR_ARRAY_MAX + 1); /* W/out '+ 1'. */

	return 0;
}
