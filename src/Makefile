# STUDENTS: DO NOT MODIFY.
#
# Definitions

CC = gcc
CC_FLAGS = -Wall -ggdb -UDEBUG -UCACHE -I../include -I../include/pipe
CC_OPTIONS = -c
CC_SO_OPTIONS = -shared -fpic
CC_DL_OPTIONS = -rdynamic
RM = /bin/rm -f
LD = gcc
LIBS = -ldl
MD = gccmakedep

SRCS := \
archsim.c \
elf_loader.c err_handler.c \
handle_args.c \
instr.c interface.c \
machine.c mem.c \
proc.c ptable.c \
reg.c hw_elts.c
OBJS := $(SRCS:%.c=%.o)

# Generic rules

%.o: %.c
	${CC} ${CC_OPTIONS} ${CC_FLAGS} $<

# Targets

all: se clean

se: ${OBJS}
	(cd pipe && make $@)
	(cd cache && make $@)

depend:
	${MD} -- ${CC_OPTIONS} ${CC_FLAGS} -- ${SRCS}

clean:
	(cd pipe && make $@)
	(cd cache && make $@)
	${RM} *.o *.so *.bak
