#include "library.h"


void search_book_menu(BookNode headBook){
	int menuOption;
	char searchTerm[100];
	system("clear");
	do {
		printf("\n");
		print_menu_name("도서 검색");
		printf("1. 도서명 검색\t2. 출판사 검색\n");
		printf("3. ISBN 검색\t4. 저자명 검색\n");
		printf("5. 전체 검색\t6. 이전 메뉴\n\n");

		printf("번호를 선택하세요: ");
		scanf("%d", &menuOption);
		getchar();
		
		switch (menuOption) {
			case 1:
				printf("도서명을 입력하세요: ");
				scanf(" %[^\n]", searchTerm);
				search_by_attribute(headBook, searchTerm, 1);
				break;
			case 2:
				printf("출판사를 입력하세요: ");
				scanf(" %[^\n]", searchTerm);
				search_by_attribute(headBook, searchTerm, 2);
				break;
			case 3:
				printf("ISBN을 입력하세요: ");
				scanf(" %[^\n]", searchTerm);
				search_by_attribute(headBook, searchTerm, 3);
				break;
			case 4:
				printf("저자명을 입력하세요: ");
				scanf(" %[^\n]", searchTerm);
				search_by_attribute(headBook, searchTerm, 4);
				break;
			case 5:
				print_all_books(headBook);
				break;
			case 6:
				return;
			default:
				printf("잘못된 번호입니다. 다시 입력하세요.\n");
				sleep(1);
		}

	} while (menuOption != 6);
}

void print_all_books(BookNode headBook) {
	printf(">> 전체 도서 목록 <<\n");
	while (headBook != NULL) {
		printf("%s| %s| %s| %ld| %s| %c\n",
				headBook->name, headBook->publisher, headBook->author,
				headBook->ISBN, headBook->location, headBook->isAvailable);
		headBook = headBook->next;
	}
}


void search_by_attribute(BookNode headBook, const char* searchTerm, int searchMode) {
	bool found = false;
	printf("\n");
	printf(">> 검색 결과 <<\n");
	while (headBook != NULL) {
		if ((searchMode == 1 && strstr(headBook->name, searchTerm)) ||
				(searchMode == 2 && strstr(headBook->publisher, searchTerm)) ||
				(searchMode == 3 && headBook->ISBN == atoll(searchTerm)) ||
				(searchMode == 4 && strstr(headBook->author, searchTerm))) {
			printf("\n");
			printf("도서명: %s\n출판사: %s\n저자명: %s\nISBN: %ld\n소장처: %s\n대여가능 여부: %c\n",
					headBook->name, headBook->publisher, headBook->author,
					headBook->ISBN, headBook->location, headBook->isAvailable);
			found = true;
		}
		headBook = headBook->next;
	}

	if (!found) {
		printf("검색 결과가 없습니다.\n");
	}
}
