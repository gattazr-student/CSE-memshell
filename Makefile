##################################################
#        Makefile automatically generated        #
# Brought to you by Jules HABLOT and Rémi GATTAZ #
##################################################

#-------------------------------------------------
#                    VARIABLES
#-------------------------------------------------
CC=gcc
CFLAGS= -Wall
LIBRARIES=
EXECS=memshell

SRCS_0=memshell.c alloc.c
OBJS_0=${SRCS_0:.c=.o}

#-------------------------------------------------
#                     LINKINGS
#-------------------------------------------------
all: $(EXECS)

memshell: $(OBJS_0)
	$(CC) $(CFLAGS) -o memshell $(OBJS_0) $(LIBRARIES)

#-------------------------------------------------
#                   DEPENDENCIES
#-------------------------------------------------
memshell.o: memshell.c alloc.o

#-------------------------------------------------
#                     CLEANING
#-------------------------------------------------
clean_memshell:
	rm -f memshell $(OBJS_0)

clean: clean_memshell
