
# Make environment
CC=gcc
CFLAGS= -c -g -Wall $(INCLUDES)

# Files
OBJECT_FILES=	p2.o p2-support.o

# Productions
all : p2

p2 : $(OBJECT_FILES)
	$(CC)  $(OBJECT_FILES) -o $@ 

p2.o : cmsc257-p2.c p2-support.h
	$(CC) $(CFLAGS) $< -o $@

p2-support.o : p2-support.c p2-support.h 
	$(CC) $(CFLAGS) $< -o $@

clean : 
	rm -v cmsc257-p2 $(OBJECT_FILES)
