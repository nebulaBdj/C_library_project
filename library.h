#ifndef _LIBRARY_H_
#define _LIBRARY_H_
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct client{
	int id;
	char password[50];
	char name[10];
	char address[200];
	char phoneNumber[12];
	struct client *next;
}Client;
typedef Client *ClientNode;

typedef struct book{
	int bookId;
	char name[50];
	char publisher[50];
	char author[10];
	long ISBN;
	char location[100];
	char isAailable;
	struct book *next;
}Book;
typedef Book *BookNode;

typedef struct borrow{
	int id;
	int bookId;
	time_t borrowDate;
	time_t returnDate;
	struct borrow *next;
}Borrow;
typedef Borrow *BorrowNode;

//main
void print_main_menu();
int select_num();

//auth
void sign_up();
ClientNode get_client_info();
int sign_in();

//utils
void print_menu_name();
void get_string(char *, char []);
#endif
