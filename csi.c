#include "csi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* count_pairs: takes in a line of input(packet from reciever) returns number of pairs, -1 if pair incomplete */

int count_pairs(char *line) {
	int count = 0;
        while (*line !='\0') {

                if (*line == ',') {
                        count++;
                }
                line++;
        }

	if (count % 2 !=0) {
		return -1;
	}

        return count/2;
}

int  parse_line(char *line, long *ts, int *re, int *im) {
	int count = 0;
	int countim = 0;
	/*get timestamp from the beginning of the input line, save it to global timestamp variable from main*/
	/*save address of first non-integer character*/
	char *end;
	*ts = strtol(line, &end, 10);
	while (*end == ' ') {
		end++;
	}

	/*if first non-integer is not ',' then input line was malformed, return -1*/
	if (*end != ',') {
		return -1;
	}
	line = end +1;
	while(*line != '\0') {
		/*if RE add to re array*/
		if (count % 2 == 0) {
			re[count/2] = strtol(line, &end, 10);

			while (*end == ' ') {
				end++;
			}

			count++;

			if(*end != ',' || end == line) {
				return -1;
			}

			line = end + 1;
			/*if count was even, belongs in Re[count/2], if first non-integer is not ',' then input line was malformed, return -1*/
		}
		/*it must be im, add to im*/
		else {
			im[countim] = strtol(line, &end, 10);
                        count++;
			countim++;

			if (*end == '\0') {
				return count/2;
			}

			else {
                        	while (*end == ' ') {
					end++;
				}

				if (*end != ',' || end == line) {
					return -1;
				}
			}

                        line = end + 1;
                        /*if count was odd, belongs in Im[countim], if first non-integer is not ',' then input line was malformed, return -1*/
		}
	}
	return count/2;
}

/*Get magnitude for each Re,Im pair and return the int*/
int magnitude(int re, int im) {
	int result = sqrt((re*re)+(im*im));
	return result;
}

/* Get difference of magnitudes between two packets, return score*/
int diff_score(int *prev, int *cur, int n) {
	int i = 0;
	int abs_difference = 0;

	for(i = 0; i < n-1; i++) {
		abs_difference += abs(cur[i] - prev[i]);
	}

	return abs_difference;
}
