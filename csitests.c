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
	long ts;
	int re[MAXSUB] = {0};
	int im[MAXSUB] = {0};

	assert(parse_line("100,1,2,3,4", &ts, re, im) == 2);
        assert(parse_line("100,1,2,3", &ts, re, im) == -1);
        assert(parse_line("100,1,2,,4", &ts, re, im) == -1);
	assert(parse_line("1x0,1,2,,4", &ts, re, im) == -1);
	assert(parse_line("100,     1, 2 ,3 ,4,5 ,  5", &ts, re, im) == 3);

}

/* Test 03 - tests magnitude*/
void test03(void) {

        printf("%d\n", magnitude(3, 4));
        assert(magnitude(3, 0) == 3);
	assert(magnitude(0, 4) == 4);

}

/* Test 04 - tests diff_scores*/
void test04(void) {
	int cur[] = {1,2,3,4};
        int prev[] = {4,3,2,1};

        printf("%d\n", diff_score(prev, cur, 4));
}

int main(void) {

	test01();
	test02();
	test03();
	test04();

	printf("All tests passed woohoo\n");

	return 0;
}
