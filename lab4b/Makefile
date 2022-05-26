CC=gcc

CFLAGS = -c -g -Wall

LDFLAGS =

SRCS = main.c tree.c dtree.c timing.c useful.c

OBJS = $(SRCS:.c=.o)

EXE = lab4

all: $(SRCS) $(EXE)
	
$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)
