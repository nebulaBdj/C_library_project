CC = gcc
OBJS = main.o auth.o client.o admin.o utils.o search_book.o

library: $(OBJS)
	@echo "linking..."
	@$(CC) -o library $(OBJS)

main.o: main.c library.h
	$(CC) -c main.c

auth.o: auth.c library.h
	$(CC) -c auth.c

client.o: client.c library.h
	$(CC) -c client.c

admin.o: admin.c library.h
	$(CC) -c admin.c

utils.o: utils.c library.h
	$(CC) -c utils.c

search_book.o: search_book.c library.h
	$(CC) -c search_book.c

clean:
	rm $(OBJS) library
