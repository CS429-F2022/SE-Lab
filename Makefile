# Definitions

CC = gcc
CC_FLAGS = -Wall -ggdb -UDEBUG -Iinclude -Iinclude/pipe -Iinclude/cache
CC_OPTIONS = -c
CC_SO_OPTIONS = -shared -fpic
CC_DL_OPTIONS = -rdynamic
RM = /bin/rm -f
LD = gcc
LIBS = -ldl
MD = gccmakedep

# Generic rules

%.o: %.c
	${CC} ${CC_OPTIONS} ${CC_FLAGS} $<

# Targets

all: tidy se clean

se: 
	(cd src && make $@)
	${CC} ${CC_FLAGS} -I instr -o $@ `/bin/ls src/*.o src/pipe/*.o src/cache/*.o`

depend:
	(cd src && make $@)

clean:
	(cd src && make $@)
	${RM} *.o *.so *.bak

tidy:
	${RM} se

count:
	wc -l src/*.c src/pipe/*.c src/cache/*.c | tail -n 1
	wc -l include/*.h include/pipe/*.h include/cache/*.h | tail -n 1
