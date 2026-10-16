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

gen: gen.c
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -o gen gen.c

test:
	gcc -Wall -Wextra -Werror -std=c89 -pedantic csi.c csitests.c -lm
	./a.out
	./motion 10 < in1.txt | diff - out1.txt
	./motion 10 < in2.txt | diff - out2.txt
	./motion 10 < in3.txt | diff - out3.txt
	./motion 10 < in4.txt | diff - out4.txt
	./motion 10 < in5.txt | diff - out5.txt
	./motion 100 < in6.txt | diff - out6.txt
	./motion 100 < in7.txt | diff - out7.txt
	./motion 100 < in8.txt | diff - out8.txt

clean:
	rm -f *.o a.out motion gen
