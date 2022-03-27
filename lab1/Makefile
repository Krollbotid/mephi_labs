CC=gcc

CFLAGS = -c -g -Wall

LDFLAGS = -lreadline
SRCS = main.c in.c out.c work.c useful.c

OBJS = $(SRCS:.c=.o)

EXE = lab1

all: $(SRCS) $(EXE)
	
$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)
