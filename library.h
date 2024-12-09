#ifndef _LIBRARY_H_
#define _LIBRARY_H_
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define CLIENT 0
#define ADMIN 1
typedef struct client{
	int id;
	char password[50];
	char name[30];
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
	char isAvailable;
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
//메모리 로드 함수
ClientNode load_client(char* );
BookNode load_book(char* );
BorrowNode load_borrow(char* );

//auth
void sign_up();
ClientNode get_client_info();
int save_client_info(ClientNode);
int sign_in();
ClientNode search_by_id(ClientNode, int);

//client
void menu_client();

//admin
void menu_admin();
void menu_clients_list();
void search_client_by_name(ClientNode);
void search_client_by_id(ClientNode);
void search_client_all(ClientNode);

//utils
void print_menu_name();
void get_string(char *, char []);
void sort_client(ClientNode);
ClientNode insert_client(ClientNode, ClientNode);
void debug_pring_client(ClientNode);
void wait_enter();
#endif
