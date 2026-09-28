# Builds targets for detecting motion through packets.
# CSC 2050 x EE2328, Assignment X
# Coded, Fall '26
# NOTE: Analyzes Signal Difference from motion.c.

motion: motion.o csi.o
	gcc -o motion motion.o csi.o -lm

motion.o: motion.c csi.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c motion.c

csi.o: csi.c csi.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c csi.c

test:
	gcc -Wall -Wextra -Werror -std=c89 -pedantic csi.c csitests.c -lm
	./a.out
