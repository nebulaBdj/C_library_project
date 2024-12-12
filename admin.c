#include "library.h"
extern ClientNode headClient;
extern BookNode headBook;
extern BorrowNode headBorrow;

void print_client(ClientNode);
void add_book(BookNode);
void update_book(BookNode, char*);
void borrowBook(BookNode, BorrowNode);
void update_borrow(BorrowNode,char*);



void menu_admin(){
	printf("\n");
	int num;
	do{
		print_menu_name("관리자 메뉴");
		printf("1. 도서 등록\t\t2. 도서 삭제\n");
		printf("3. 도서 대여\t\t4. 도서 반납\n");
		printf("5. 도서 검색\t\t6. 회원 목록\n");
		printf("7. 로그아웃\t\t8. 프로그램 종료\n\n");
		num = select_num();
		switch(num){
			case 1:
				//도서 등록
				add_book(headBook); 
				break;
			case 2:
				//도서 삭제
				delete_book();
				break;
			case 3:
				//도서 대여
				borrowBook(headBook,headBorrow);
				break;
			case 4:
				//도서 반남
				return_book();
				break;
			case 5:
				//도서 검색
				search_book_menu(headBook);
				break;
			case 6:
				//회원 목록
				menu_clients_list();
				break;
			case 7:
				//로그아웃
				break;
			case 8:
				//프로그램 종료
				exit(1);
			default:
				printf("잘못된 번호입니다. 2초후 다시 입력하세요.\n");
				sleep(2);
		}
		system("clear");
	}while(num != 7);
}


void menu_clients_list(){
	printf("\n");
	int num;
	do{
		print_menu_name("회원 목록");
		printf("1. 이름 검색\t\t2. 학번 검색\n");
		printf("3. 전체 검색\t\t4. 이전 메뉴\n\n");
		num = select_num();
		switch(num){
			case 1:
				//이름 검색 
				search_client_by_name(headClient);
				break;
			case 2:
				//학번 검색
				search_client_by_id(headClient);
				break;
			case 3:
				//전체 검색
				search_client_all(headClient);
				break;
			case 4:
				//이전 메뉴
				break;
			default:
				printf("잘못된 번호입니다. 2초후 다시 입력하세요.\n");
				sleep(2);
		}
		system("clear");
	}while(num != 4);
}

void search_client_by_name(ClientNode head){
	char name[50];
	get_string("이름 : ", name);
	bool isExist = false;
	while(head != NULL){
		if(strcmp(name, head->name) == 0){
			print_client(head);
			isExist = true;
		}
		head = head->next;
	}
	if(isExist == false)
		printf("%s은(는) 존재하지 않는 유저입니다.\n", name);
	wait_enter();
}

void search_client_by_id(ClientNode head){
	int id;
	printf("학번 : ");
	scanf("%d", &id);
	getchar();
	bool isExist = false;
	while(head != NULL){
		if(id == head->id){
			print_client(head);
			isExist = true;
			break;
		}
		head = head->next;
	}
	if(isExist == false)
		printf("%d은(는) 존재하지 않는 유저입니다.\n", id);
	wait_enter();
}

void search_client_all(ClientNode head){
	while(head != NULL){
		print_client(head);
		head = head->next;
	}
	wait_enter();
}

void print_client(ClientNode node){
	printf("%d | %s | %s | %s\n", node->id, node->name, node->address, node->phoneNumber);
}

void add_book(BookNode bookHead){
	BookNode newBook = malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("메모리 할당 실패.\n");
	printf("2초 후 돌아갑니다\n");
	sleep(2);
        return;
    }

    // 사용자로부터 도서 정보 입력 받기
    printf("\n\n>>도서등록<<\n");
    printf("도서명을 입력하세요: ");
    scanf(" %[^\n]", newBook->name);
    printf("출판사를 입력하세요: ");
    scanf(" %[^\n]", newBook->publisher);
    printf("저자명을 입력하세요: ");
    scanf(" %[^\n]", newBook->author);
    printf("ISBN을 입력하세요: ");
    int flag;
    long tmpISBN;
    do{
	flag = 0;
	scanf("%ld", &tmpISBN);
	BookNode tmp = bookHead;
	 while (tmp!= NULL) {
        if (tmp->ISBN == tmpISBN) {
            printf("이미 존재하는 ISBN입니다.\n 다시 입력해주세요:");
            flag = 1;
            break;
        	}
        tmp = tmp->next;
    	}
    }while(flag);


	newBook->ISBN = tmpISBN;

    	printf("소장처를 입력하세요: ");
    	scanf(" %[^\n]", newBook->location);


    // 대여 가능 여부 설정
    newBook->isAvailable = 'Y';
    int maxId = 1000000;
    BookNode current = bookHead;

    while (current != NULL) {
        if (current->bookId > maxId) {
            maxId = current->bookId; // 최대 ID 업데이트
        }
        current = current->next;
    }

    newBook->bookId = maxId + 1;
      char confirm;
        printf("\n\n자동입력사항\n\n");
        printf("대여가능 여부 %c\n",newBook->isAvailable);
        printf("도서번호 %d\n\n",newBook->bookId);
        printf("등록하시겠습니까? Y/N : ");
        getchar();
        scanf("%c",&confirm);
    current=bookHead;
    if(confirm=='Y' || confirm=='y'){
     if (bookHead == NULL || bookHead->ISBN > newBook->ISBN) {
        // 리스트가 비어있거나 첫 번째 노드의 ISBN이 새 도서의 ISBN보다 크면 맨 앞에 추가
        newBook->next = bookHead;
        bookHead = newBook;
     }
     else{
	    BookNode prev=NULL;
	   while(current!=NULL&&current->ISBN<newBook->ISBN){
		  prev=current;
		 current=current->next;
	   }
	  prev->next=newBook;
	 newBook->next=current;
     }
	update_book(bookHead,"book.txt");
	printf("도서 등록 성공,2초 후 돌아갑니다.\n");

	sleep(2);
    }
    else{
	    printf("도서등록 취소, 2초 후 돌아갑니다.\n");
	    free(newBook);
	    sleep(2);
    }

	return ;
}

void update_book(BookNode bookHead, char* filename){
	FILE* fp=fopen(filename,"w");
	if(fp==NULL){
		printf("book.txt 파일을 열 수 없습니다.\n");
		return ;}
	BookNode current=bookHead;
	while(current!=NULL){
		fprintf(fp,"%d | %s | %s | %s | %ld | %s | %c\n",current->bookId, current->name, current->publisher, current->author,current->ISBN, current->location,current->isAvailable);
		current=current->next;
		}
	fflush(fp);
	fclose(fp);
	return ;
}

void borrowBook(BookNode bookHead, BorrowNode borrowHead) {
    char search_num; //검색 방식을 위한 변수
    char search_term[100]; //도서명이나 ISBN을 입력받기 위한 변수
    int student_id, book_id; //학번과 도서번호를 임시로 저장하기 위한 변수
    time_t now;	  //대여, 반납일자를 위한 변수
    struct tm *t; //대여,반납일자를 위한 포인터,당장 이 함수에서는 필요 없네요. 나중에 time_t자료형을 받고 년 월 일 요일로 나타낼때 필요

    printf("\n>> 도서 대여 <<\n");
    printf("1. 도서명 검색\t");
    printf("2. ISBN 검색\n");
    printf("검색 번호를 입력하세요: ");
    scanf(" %c", &search_num);

    if (search_num == '1') {
        printf("도서명을 입력하세요: ");
    } else if (search_num == '2') {
        printf("ISBN을 입력하세요: ");
    } else {
        printf("잘못된 입력입니다. 2초 후 돌아갑니다.\n");
	sleep(2);
        return;
    }
    getchar();
    scanf("%[^\n]",search_term);

    BookNode book_current = bookHead;
    while (book_current != NULL) {
        if ((search_num == '1' && strstr(book_current->name, search_term) != NULL) ||
            (search_num == '2' && book_current->ISBN == atoll(search_term))) {
            printf(">> 검색 결과 <<\n");
            printf("도서번호: %d(대여 가능 여부: %c)\n", book_current->bookId, book_current->isAvailable);
            printf("도서명: %s\n", book_current->name);
            printf("출판사: %s\n", book_current->publisher);
            printf("저자명: %s\n", book_current->author);
            printf("ISBN: %ld\n", book_current->ISBN);
            printf("소장처: %s\n", book_current->location);

            if (book_current->isAvailable == 'Y') {
                printf("학번을 입력하세요: ");
                scanf("%d", &student_id);
                printf("도서번호를 입력하세요: ");
                scanf("%d", &book_id);

                if (book_id == book_current->bookId) {
                    printf("이 도서를 대여합니까? (Y/N): ");
                    char confirm;
                    scanf(" %c", &confirm);

                    if (confirm == 'Y' || confirm == 'y') {
                        book_current->isAvailable = 'N';

                        BorrowNode new_borrow = malloc(sizeof(Borrow));
                        new_borrow->id = student_id;
                        new_borrow->bookId = book_id;

                        now=time(NULL);
                        new_borrow->borrowDate = now;
                        t = localtime(&now);
                        now+=2592000;  //30일
                        new_borrow->returnDate = now;

                        if (t->tm_wday == 0) {
                            now += 86400; //하루:
                            new_borrow->returnDate = now;
                        }

                        new_borrow->next = borrowHead;
                        borrowHead = new_borrow;

			//book파일 업데이트
			update_book(bookHead,"book.txt");
			 //borrow파일 덮어쓰기
			 update_borrow(borrowHead,"borrow.txt");
                        printf("도서가 대여 되었습니다. 2초 후 돌아갑니다.\n");
			 sleep(2);
                        return;
                    }
		    else{
			    printf("도서대여를 취소합니다. 2초 후 돌아갑니다.\n");
			    sleep(2);
			    return;
		    }
		}


            } else {
                printf("이 도서는 대여되어 현재 대여할 수 없습니다. 2초 후 돌아갑니다.\n");
		sleep(2);
		return;
            	}
        }
        book_current = book_current->next;
    }

    printf("검색 결과가 없습니다. 2초 후 돌아갑니다.\n");
    sleep(2);
}

void update_borrow(BorrowNode borrowHead, char* filename){
        FILE* fp=fopen(filename,"w");
        if(fp==NULL){
                printf("borrow.txt 파일을 열 수 없습니다.\n");
                return ;}
        BorrowNode current=borrowHead;
        while(current!=NULL){
                fprintf(fp,"%d | %d | %ld | %ld\n",current->id, current->bookId, current->borrowDate, current->returnDate);
                current=current->next;
                }
	fflush(fp);
        fclose(fp);
        return ;
}


void delete_book() {
	int searchOption;
	char searchTerm[100];
	BookNode prev = NULL, current = headBook; 
	bool found = false;

	printf("\n>> 도서 삭제 <<\n");
	printf("1. 도서명 검색\t2. ISBN 검색\n");
	printf("검색 옵션을 선택하세요: ");
	scanf("%d", &searchOption);
	getchar();

	if (searchOption == 1) {
		printf("도서명을 입력하세요: ");
		scanf(" %[^\n]", searchTerm);
	} else if (searchOption == 2) {
		printf("ISBN을 입력하세요: ");
		scanf(" %[^\n]", searchTerm);
	} else {
		printf("잘못된 입력입니다. 2초 후 돌아갑니다.\n");
		sleep(2);
		return;
	}

	printf("\n>> 검색 결과 <<\n");
	while (current != NULL) {
		if ((searchOption == 1 && strstr(current->name, searchTerm)) ||
				(searchOption == 2 && current->ISBN == atoll(searchTerm))) {
			found = true;
			printf("\n");
			printf("도서번호: %d(삭제 가능 여부: %c)\n", current->bookId, current->isAvailable);
			printf("도서명: %s\n출판사: %s\n저자명: %s\nISBN: %ld\n소장처: %s\n",
					   current->name, current->publisher, current->author,
					      current->ISBN, current->location);
		}
		current = current->next;
	}

	if (!found) {
		printf("검색 결과가 없습니다. 2초 후 돌아갑니다.\n");
		sleep(2);
		return;
	}

	int deleteBookId;
	printf("\n삭제할 도서의 번호를 입력하세요: ");
	scanf("%d", &deleteBookId);

	current = headBook;
	while (current != NULL) {
		if (current->bookId == deleteBookId) {
			if (current->isAvailable == 'N') {
				printf("이 도서는 대여 중이므로 삭제할 수 없습니다. 2초 후 돌아갑니다.\n");
				sleep(2);
				return;
			}

			if (prev == NULL) {
				headBook = current->next;
			} else {
				prev->next = current->next;
			}
			free(current);
			update_book(headBook, "book.txt");
			printf("도서가 삭제되었습니다. 2초 후 돌아갑니다.\n");
			sleep(2);
			return;
		}
		prev = current;
		current = current->next;
	}

	printf("도서 번호를 찾을 수 없습니다. 2초 후 돌아갑니다.\n");
	sleep(2);
}







void return_book() {
	int studentId;
	printf("\n>> 도서 반납 <<\n");
	printf("학번을 입력하세요: ");
	scanf("%d", &studentId);

	BorrowNode currentBorrow = headBorrow;
	bool found = false;

	printf("\n>> 회원의 대여 목록 <<\n");
	while (currentBorrow != NULL) {
		if (currentBorrow->id == studentId) {
			found = true;

			BookNode currentBook = headBook;
			while (currentBook != NULL) {
				if (currentBook->bookId == currentBorrow->bookId) {
					char borrowDate[20], returnDate[20];
					calculate_date(currentBorrow->borrowDate, borrowDate);
					calculate_date(currentBorrow->returnDate, returnDate);

					printf("도서번호: %d\n도서명: %s\n대여일자: %s\n반납일자: %s\n\n",
							   currentBook->bookId, currentBook->name, borrowDate, returnDate);
					break;
				}
				currentBook = currentBook->next;
			}
		}
		currentBorrow = currentBorrow->next;
	}

	if (!found) {
		printf("대여 목록이 없습니다. 2초 후 돌아갑니다.\n");
		sleep(2);
		return;
	}

	int returnBookId;
	printf("반납할 도서번호를 입력하세요: ");
	scanf("%d", &returnBookId);

	BorrowNode prevBorrow = NULL;
	currentBorrow = headBorrow;
	found = false;

	while (currentBorrow != NULL) {
		if (currentBorrow->bookId == returnBookId && currentBorrow->id == studentId) {
			found = true;

			if (prevBorrow == NULL) {
				headBorrow = currentBorrow->next;
			} else {
				prevBorrow->next = currentBorrow->next;
			}
			free(currentBorrow);

			BookNode currentBook = headBook;
			while (currentBook != NULL) {
				if (currentBook->bookId == returnBookId) {
					currentBook->isAvailable = 'Y';
					break;
				}
				currentBook = currentBook->next;
			}

			update_borrow(headBorrow, "borrow.txt");
			update_book(headBook, "book.txt");

			printf("도서가 반납되었습니다. 2초 후 돌아갑니다.\n");
			sleep(2);
			return;
		}
		prevBorrow = currentBorrow;
		currentBorrow = currentBorrow->next;
	}

	if (!found) {
		printf("해당 도서번호를 찾을 수 없습니다. 2초 후 돌아갑니다.\n");
		sleep(2);
	}
}
