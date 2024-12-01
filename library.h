#ifndef _LIBRARY_H_
#define _LIBRARY_H_
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct client{
	int id;
	char *password;
	char *name;
	char *address;
	char *phoneNumber;
	struct client *next;
}Client;

typedef struct book{
	int bookId;
	char *name;
	char *publisher;
	char *author;
	long ISBN;
	char *location;
	char isAailable;
	struct book *next;
}Book;

typedef struct borrow{
	int id;
	int bookId;
	time_t borrowDate;
	time_t returnDate;
	struct borrow *next;
}Borrow;

//main
void print_main_menu();
int select_num();

//auth
void sign_up();
int sign_in();
#endif
