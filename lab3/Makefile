CC=gcc

CFLAGS = -c -g -Wall

LDFLAGS =
SRCS = main.c item.c ks1.c ks2.c table.c dtable.c ftable.c

DATAS = lab3bINFODATA lab3bSTRUCTUREDATA

OBJS = $(SRCS:.c=.o)

EXE = lab3

all: $(SRCS) $(EXE)
	
$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)

cleandata:
	rm -rf $(DATAS)
