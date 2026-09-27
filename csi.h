/* Declares functions and macros for taking input dataset and getting difference from previous input, then scoring and smoothing, and assessing against a threshold.
 * CSC 2050 X EE2328, Assignment X
 * coded, Fall '26. */

/* Worst case line: 10-digit timestamp + 256 pairs = 512 numbers,
 * each up to 5 chars ("-128,"), + '\n' = 10 + 512*5 + 1 = 2571.
 * Spec allows padding spaces, so it caps lines at 4096 instead.
 * +1 for the '\0' fgets appends. */
#define MAXLINE 4097

/* Max amount of Sub-Carriers one packet will have. Used for current packet's
 * Re, Im, and Magnitude Arrays. Also used for prev packet's Magnitude array
 * ESP-32 maxes at 64, but spec allows for 256 */
#define MAXSUB 256

/* Moving average window size */
#define WINDOW 4

/* Smoothed score at or above this prints MOTION; placeholder, tune later */
#define THRESHOLD 10

/* Counts the amount of pairs, if odd number of elements then 1 pair
 * is malformed, will return -1*/
int count_pairs(char *line);

/* Parses the input line, saves timestamp to ts, delegates real and
 * imaginary components to respective arrays, returns paircount if
 * success, -1 if fails */
int parse_line(char *line, long *ts,  int *re, int *im);

/* Returns (int) sqrt(re*re + im*im)*/
int magnitude(int re, int im);

/* Calculates difference between previous packets magnitudes and new
 * packets magnitudes and computes a score, with n being how many pairs
 * are actually in the packet, same magnitudes : score = 0 */
int diff_score(int *prev, int *cur, int pairs);

/* win is the pointer to the 4 slot array, it replaces the win[next] with
 * score, changes next to be the oldest index, then returns the average of
 * the 4 integers in that array*/
int moving_avg(int score, int *win, int *next);
