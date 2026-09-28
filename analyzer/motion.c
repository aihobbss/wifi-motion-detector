/* Detects motion from packet input
 * CSC 2050, Assignment X
 * coded, Fall '26 */

#include "csi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char *end;
	int threshold;

	/* Declare CSI Varaibles*/
	char line[MAXLINE] = {0};

	int k = 0;
	int first_pairs = 0;
	long ts = 0;
	int re[MAXSUB] = {0};
	int im[MAXSUB] = {0};
	int magnitudes[MAXSUB] = {0};

	int first = 0;
	int prev[MAXSUB] = {0};
	int pairs = 0;

	int score = 0;
	int win[WINDOW] = {0};
	int next = 0;
	int avg = 0;

	if (argc != 2) {
		printf("usage: ./motion THRESHOLD\n");
		return 3;
	}

	threshold = strtol(argv[1], &end, 10);

	if (*end != '\0' || threshold < 0) {
		printf("usage: ./motion THRESHOLD\n");
		return 3;
	}

	while (fgets(line, MAXLINE, stdin) != NULL) {
		pairs = parse_line(line, &ts, re, im);
		/*packet error checks*/
		if (pairs == -1 ) {
			printf("./motion: Malformed line\n");
                        return 2;
		}

		if (first == 0) {
			first_pairs = pairs;
		}

		else if (pairs != first_pairs) {
			printf("./motion: Mismatched subcarriers\n");
			return 1;
		}

		/*Get packet magnitudes*/
		for(k=0; k<pairs; k++) {
			magnitudes[k] = magnitude(re[k], im[k]);
		}

		/* Get difference from current to previous packet's magnitudes, determine score,
		 * then smooth score */
		if (first == 0) {
			score = 0;
		}

		else {
			score = diff_score(prev, magnitudes, pairs);
		}

		avg = moving_avg(score, win, &next);

		for (k = 0; k<pairs; k++) {
			prev[k] = magnitudes[k];
                }

		first = 1;

		/* Print results, TIMESTAMP SCORE SMOOTHED, AND IF SMOOTH>THRESHOLD: MOTION*/
		printf("%ld %d %d", ts, score, avg);

		if (avg >= threshold) {
			printf(" MOTION");
		}

		printf("\n");
	}

	return 0;
}
