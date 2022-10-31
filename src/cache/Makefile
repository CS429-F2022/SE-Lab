# Modify these two lines to choose your compiler and compile time
# flags.

CC=gcc
CFLAGS= -Wall -Werror -O0 -ggdb
INC= -I../../include -I../../include/cache

##################################################
# You shouldn't need to modify anything below here
##################################################

LIBS= -lm

all: csim test-cache cache.o

cache.o: cache.c
	${CC} ${INC} ${CFLAGS} -c -o cache.o cache.c

se: all

csim: csim.c cache.c 
	$(CC) $(CFLAGS) $(INC) -o csim csim.c cache.c -lm

test-cache: csim test-csim.c
	$(CC) $(CFLAGS) -o test-csim test-csim.c

clean:
	rm -f test-csim csim *.o *.exe *~ 


