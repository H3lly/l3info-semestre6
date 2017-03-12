CC=g++
CFLAGS:= -std=c++11
LDFLAGS:= -lfl
SRCS = $(wildcard *.l)

PROGS = $(patsubst %.l,%,$(SRCS))

all: $(PROGS)

%: %.l
	flex -o $@.yy.cc $< 
	$(CC) $(CFLAGS) -o $@ $@.yy.cc $(LDFLAGS)

clean :
	rm *.cc $(PROGS)