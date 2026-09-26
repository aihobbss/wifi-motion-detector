/* Tests functions for detecting motion from packets
 * CSC - 2050 X EE 2328, Assignment X
 * Created Tests, Fall '26. */

#include <stdio.h>
#include <assert.h>
#include "csi.h"

/* Test 01 - tests count_pairs */
void test01(void) {

	assert(count_pairs("100,1,2,3,4") == 2);
	assert(count_pairs("100,1,2,3") == -1);
	assert(count_pairs("100,     1, 2 ,3 ,4,5 ,  5") == 3);
}

/* Test 02 - tests parse_line */
void test02(void) {

	assert(parse_line("100,1,2,3,4") == 2);
        printf("passes normal case\n");
        assert(parse_line("100,1,2,3") == -1);
        assert(parse_line("100,1,2,,4") == -1);
	printf("catches error\n");
        assert(parse_line("100,     1, 2 ,3 ,4,5 ,  5") == 3);

}

int main(void) {

	test01();
	test02();

	printf("All tests passed woohoo\n");

	return 0;
}
