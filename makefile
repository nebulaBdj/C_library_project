CC = gcc
OBJS = main.o auth.o client.o admin.o utils.o

library: $(OBJS)
	@echo "linking..."
	@gcc -o library $(OBJS)

$(OBJS): library.h
		 gcc -c $*.c
