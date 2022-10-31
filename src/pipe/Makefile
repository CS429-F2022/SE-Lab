# Definitions

CC = gcc
CC_FLAGS = -Wall -ggdb -UDEBUG -I../../include  -I../../include/pipe
CC_OPTIONS = -c
CC_SO_OPTIONS = -shared -fpic
CC_DL_OPTIONS = -rdynamic
RM = /bin/rm -f
LD = gcc
LIBS = -ldl
MD = gccmakedep

SRCS := \
forward.c \
hazard_control.c \
select_pc.c

# SRCS := $(HDRS:%.h=%.c)
OBJS := $(SRCS:%.c=%.o)

# Generic rules

%.o: %.c
	${CC} ${CC_OPTIONS} ${CC_FLAGS} $<

# Targets

all: se clean

se: ${OBJS}

depend:
	${MD} -- ${CC_OPTIONS} ${CC_FLAGS} -- ${SRCS}

clean:
	${RM} *.o *.so *.bak
