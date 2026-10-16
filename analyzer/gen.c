/* ./gen MODE COUNT           MODE = quiet | bump | bad, COUNT = packets
 * base:   64 fixed RE,IM values
 * quiet:  every cell = base + rand() % 3 - 1
 * bump:   middle third of packets use base + rand() % 41 - 20, rest quiet
 * bad:    quiet stream, but one line in the middle is broken, ex. empty cell */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUBCARRIERS 64

void print_packet(long ts, int spread) {
	int k;
	printf("%ld", ts);
	for (k=0; k<SUBCARRIERS; k++) {
		printf(",%d,%d", k + (rand() % (2* spread + 1) - spread), k+(rand() % (2 * spread + 1) - spread));
	}
	printf("\n");
}
int main(int argc, char *argv[]) {

	int count = 0, k;
	char *end;
	long ts = 0;

	if (argc != 3) {
                printf("usage: ./gen MODE COUNT\n");
                return 3;
        }

	count = strtol(argv[2], &end, 10);

        if (*end != '\0' || count < 1) {
                printf("usage: ./gen MODE COUNT\n");
                return 3;
        }

	/* BUMP SIGNAL: Middle third of packets are randomly nudged by 0<x<20, other thirds are nudged by 0<x<1 */
	if (strcmp(argv[1], "bump") == 0) {
		for(k = 0; k<count; k++) {
			if ((k < count/3) || (k>= 2*count/3)) { /*if k is on first or last third of the packets*/
				print_packet(ts, 1);
				ts += 10000;
			}
			else {/*if k is is in the middle third of the packets*/
				print_packet(ts,20);
				ts += 10000;
			}
		}
	}
	/* QUIET SIGNAL: mimics slight noise, but not enough for motion*/
	else if (strcmp(argv[1], "quiet") == 0) { /*simulating quite signal, each packets subcarrier pairs only shifts -1 or 1*/
		for(k=0; k<count; k++){
			print_packet(ts, 1);
			ts += 10000;
		}
	}
	/* BAD SIGNAL: one malformed line about halfway through packets*/
	else if (strcmp(argv[1], "bad") == 0) {
		for(k = 0; k<count; k++) {
			if (k == count/2) {
				printf("%ld,,0", ts); /*empty cell is enough to trigger error*/
				ts += 10000;
			}
			else {
				print_packet(ts, 1);
				ts += 10000;
			}
		}
	}

	else {
		printf("usage: ./gen MODE COUNT\n");
		return 3;
	}
	return 0;
}
