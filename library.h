#ifndef _LIBRARY_H_
#define _LIBRARY_H_
#include <stdio.h>
#include <time.h>

typedef struct client{
	int id;
	char *password;
	char *name;
	char *address;
	char *phoneNumber;
	struct client *next;
}client;

typedef struct book{
	int bookId;
	char *name;
	char *publisher;
	char *author;
	long ISBN;
	char *location;
	char isAailable;
	struct book *next;
}book;

typedef struct borrow{
	int id;
	int bookId;
	time_t borrowDate;
	time_t returnDate;
	struct borrow *next;
}borrow;
#endif
