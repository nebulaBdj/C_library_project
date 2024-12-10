#include "library.h"
extern ClientNode headClient;
extern BookNode headBook;
extern BorrowNode headBorrow;

void print_client(ClientNode);

BookNode add_book(BookNode head);
void borrowBook(BookNode,BorrowNode);

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
				headBook=add_book(headBook); 
				break;
			case 2:
				//도서 삭제
				break;
			case 3:
				//도서 대여
				borrowBook(headBook,headBorrow);
				break;
			case 4:
				//도서 반남
				break;
			case 5:
				//도서 검색
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


BookNode add_book(BookNode head) {
	//도서번호 설정용
	BookNode tmp=head;
	int tmpBookId=tmp->bookId;
	while(tmp!=NULL){
		if(tmpBookId<tmp->bookId)
			tmpBookId=tmp->bookId;
		tmp=tmp->next;
	}

    	BookNode new_book = malloc(sizeof(Book)); //임시 포인터
	if (new_book == NULL) {
        	printf("메모리 할당에 실패했습니다.\n");
        	return head;
    	}
	printf(">>도서등록<<\n");
    	printf("도서명: ");
    	scanf(" %[^\n]", new_book->name);

    	printf("출판사: ");
    	scanf(" %[^\n]", new_book->publisher);

    	printf("저자명: ");
    	scanf(" %[^\n]", new_book->author);

    	printf("ISBN: ");
    	scanf("%ld", &new_book->ISBN);

    	printf("소장처: ");
    	scanf(" %[^\n]", new_book->location);

    	new_book->isAvailable = 'Y';
    	// 도서번호 설정
    	if (head == NULL) {
        new_book->bookId = 1000000;
    	}
       	else {
		new_book->bookId = tmpBookId;
    	}

    	new_book->next = NULL;

	//최종 등록 여부
	char confirm;
	printf("\n\n자동입력사항\n\n");
	printf("대여가능 여부 %c\n",new_book->isAvailable);
	printf("도서번호 %d\n\n",new_book->bookId);
	printf("등록하시겠습니까? Y/N : ");
	getchar();
	scanf("%c",&confirm);


    	// 새로운 도서를 ISBN순으로 링크드리스트에 추가
	if(confirm=='Y' || confirm=='y'){
       		if (head == NULL || new_book->ISBN < head->ISBN) {
            		new_book->next = head;
            		head = new_book;
       		}
		else {
        		BookNode current = head;
        		while (current->next != NULL && current->next->ISBN<new_book->ISBN) {
            			current = current->next;
        		}
			new_book->next = current->next;
			current->next = new_book;
    		}

    		// ISBN순으로 정렬된 링크드리스트를 book.txt파일에 덮어쓰기
		//
    		FILE* fp = fopen("book.txt", "w");
    		if (fp == NULL) {
        		printf("book.txt 파일을 열 수 없습니다.\n");
        		free(new_book);
        		return head;
    		}

		BookNode current = head;
        		while (current != NULL) {
            		fprintf(fp, "%d | %s | %s | %s | %ld | %s | %c\n",current->bookId, current->name, current->publisher,current->author, current->ISBN, current->location, current->isAvailable);
            		current = current->next;
        		}
    		fclose(fp);

    		printf("도서 등록 성공.\n");
	}
	else{
		printf("도서 등록 취소\n");
		free(new_book);
	}
    	return head;
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
        printf("잘못된 입력입니다.\n");
        exit(1);
    }
    scanf("%[^\n]",search_term);

    BookNode book_current = bookHead;  //매개변수를 가리키기위한 임시 포인터
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

                        BorrowNode new_borrow = malloc(sizeof(Borrow));//borrow정보 저장을 위한 임시 포인터
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

                        printf("도서가 대여 되었습니다.\n");
			//book파일 업데이트
			FILE* fp=fopen("book.txt","w");
			if(fp==NULL)
				printf("book.txt 파일을 열 수 없습니다\n");
				
			BookNode tmp=bookHead;	
			while(tmp!=NULL){
				fprintf(fp, "%d | %s | %s | %s | %ld | %s | %c\n",tmp->bookId,tmp->name,tmp->publisher,tmp->author,tmp->ISBN, tmp->location, tmp->isAvailable);
				tmp=tmp->next;
			
			}
			fclose(fp);	

                        exit(1);
                    }
                }
            } else {
                printf("이 도서는 현재 대여할 수 없습니다.\n");
            	}	
        }
        book_current = book_current->next;
    }
	//borrow파일 덮어쓰기
        FILE* fp=fopen("borrow.txt","w");
        if(fp==NULL){
                printf("borrow.txt 파일을 열 수 없습니다.\n");
        }

        BorrowNode tmp=borrowHead;
        while(tmp!=NULL) {
                fprintf(fp, "%d | %d | %ld | %ld\n",tmp->id,tmp->bookId,tmp->borrowDate,tmp->returnDate);
        	tmp=tmp->next;
        }
        fclose(fp);
	
	
    printf("검색 결과가 없거나 대여할 수 없는 도서입니다.\n");
}

