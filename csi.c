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

	char *end;
	*ts = strtol(line, &end, 10);

	if (*end != ',') {
		return -1;
	}
}
