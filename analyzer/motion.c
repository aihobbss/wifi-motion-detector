/* Detects motion from packet input
 * CSC 2050 x EE2328, Project Motion
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
	double prev[MAXSUB] = {0};
	int pairs = 0;

	double score = 0;
	double win[MAXSUB][WINDOW] = {0};
	int next = 0;
	int avg = 0;
	double gap,sum,total;
	int i;

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
            		continue;
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
			for (k= 0; k<pairs; k++) {
				prev[k] = magnitudes[k];
			}
		}

		/* Per subcarrier k, for one packet:
		 *   1. gap   = this packet minus the slow baseline
		 *   2. store the SIGNED gap in k's window (last WINDOW packets)
		 *   3. sum k's window: fuzz flips sign and cancels (+3, -3 -> 0),
		 *      a person holds one sign and survives (+4, +4 -> 8)
		 *   4. abs AFTER the sum, then add into the packet total
		 *   5. nudge the baseline toward this packet */

		total = 0;
		score = 0;
		for (k = 0; k<pairs; k++) {
			/* 1. x[n] - y[n-1], y = prev[k] (baseline, not last packet) */
			gap = magnitudes[k] - prev[k];
			score += fabs(gap);
			/* 2. win[subcarrier][slot]; next = oldest slot, overwritten */
			win[k][next]=gap;
			/* 3. signed sum = average * WINDOW (divide once, later,
			 *    so int division does not round small gaps to 0) */
			sum = 0;
			for (i = 0; i < (WINDOW); i++) { /*Sum each */
			        sum += win[k][i];
			}
			/* 4. abs after averaging, not before */
			total += fabs(sum);
			/* 5. BASELINE FILTER  y[n] = y[n-1] + (x[n] - y[n-1])/16 */
			prev[k] += gap/16;
                }
		avg = total/WINDOW; /*the average of the gaps*/
		next = (next + 1) % WINDOW; /* Move window index to next packet*/
		first = 1;

		/* Print results, TIMESTAMP SCORE SMOOTHED, AND IF SMOOTH>THRESHOLD: MOTION*/
		printf("%ld %d %d", ts, (int)score, avg);

		if (avg >= threshold) {
			printf(" MOTION");
		}

		printf("\n");
	}

	return 0;
}
