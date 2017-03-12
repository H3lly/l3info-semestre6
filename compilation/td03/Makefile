CFLAGS= -std=c89
LIBS=
CC= gcc

.PHONY: all clean

.SUFFIXES: .y .l .h .c .o

all: programme

programme: td3.3.o
	$(CC) $(CLIBS) -o $@ $^
	
.y.c:
	yacc --file-prefix=$* -d $<
	mv $*.tab.c $*.c
	mv $*.tab.h $*.h

.l.c:
	lex -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -c $<

%:%.o
	$(CC) $(CLIBS) -o $% $<

clean:
	rm *.o *.h programme