CC=gcc

CFLAGS = -c -g -Wall

LDFLAGS = -lm

SRCS = main.c graph.c dgraph.c ind.c useful.c

OBJS = $(SRCS:.c=.o)

EXE = lab5

all: $(SRCS) $(EXE)
	
$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)
