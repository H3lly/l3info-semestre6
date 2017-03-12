CFLAGS= -std=c89
CLIBS=
CC= gcc

.PHONY: all clean

.SUFFIXES: .y .l .tab.h .tab.c .o .yy.c

all: programme

programme: ex4.yy.o
	$(CC) $(CLIBS) -o $@ $^
	
.y.tab.c:
	yacc --file-prefix=$* -d $<

.l.yy.c:
	lex -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -c $<

%:%.o
	$(CC) $(CLIBS) -o $% $<

clean:
	rm *yy.o programme