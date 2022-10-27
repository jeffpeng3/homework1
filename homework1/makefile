SRCS	= $(wildcard ./*.c)
OBJS	= $(patsubst ./%.c, ./%.o, $(SRCS))
CFLAGS	= -Wall -O0 -std=c11 -g -c
CC		= gcc

default: $(OBJS)
	$(CC) $^ -o out/main
	cp number.txt ./out/number.txt
	./out/main

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
