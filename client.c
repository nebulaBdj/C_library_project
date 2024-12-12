#include "library.h"
extern ClientNode headClient;
extern BorrowNode headBorrow;
extern BookNode headBook;

void update_info(ClientNode);
void updateClient(ClientNode, char*);
int isBorrow(BorrowNode, int );
void removeClient(ClientNode,BorrowNode ,int );

void menu_client(ClientNode info){
	printf("\n");
	int num;
	do{
		print_menu_name("회원 메뉴");
		printf("1. 도서 검색\t\t2. 내 대여 목록\n");
		printf("3. 개인정보 수정\t4. 회원 탈퇴\n");
		printf("5. 로그아웃\t\t6. 프로그램 종료\n\n");
		num = select_num();
		switch(num){
			case 1:
				//도서 검색
				search_book_menu(headBook);
				break;
			case 2:
				//내 대여 목록
				display_borrowed_books(info);
				break;
			case 3:
				//개인정보 수정
				update_info(info);
				break;
			case 4:
				//회원 탈퇴 
				removeClient(headClient, headBorrow,info->id);
				break;
			case 5:
				//로그아웃
				break;
			case 6:
				//프로그램 종료
				exit(1);
				break;
			default:
				printf("잘못된 번호입니다. 2초후 다시 입력하세요.\n");
				sleep(2);
		}
		system("clear");
	}while(num != 5);
}

void update_info(ClientNode info){
	printf("\n개인정보를 수정하기 위해선 비밀번호를 입력해야합니다.\n");
	char pwd[50];
	get_string("현재 비밀번호: ", pwd);
	if(strcmp(pwd, info->password)!= 0){
		printf("비밀번호가 일치하지 않습니다. 2초후 메뉴로 돌아갑니다.\n");
		sleep(2);
		return;
	}
	printf("\n");
	int num;
	do{
		bool isChange = false;
		print_menu_name("개인정보 수정");
		printf("1. 비밀번호 수정\t\t2. 주소 수정\n");
		printf("3. 전화번호 수정\t\t4. 이전 메뉴\n\n");
		num = select_num();
		switch(num){
			case 1:
				get_string("새 비밀번호: ", info->password);
				isChange = true;
				break;
			case 2:
				get_string("새 주소: ", info->address);
			   	isChange = true;	
				break;
			case 3:
				get_string("새 전화번호: ", info->phoneNumber);
			   	isChange = true;	
				break;
			case 4:
				break;
			default:
				printf("잘못된 번호입니다. 2초후 다시 입력하세요.\n");
				sleep(2);
		}
		if(isChange)
			save_client_info(headClient);
		system("clear");
	}while(num != 4);
}


void updateClient(ClientNode head, char* filename) {
    	FILE* fp=fopen(filename,"w");
    	if(fp==NULL){
        	printf("client.txt 파일을 열 수 없습니다.\n");
        	return;
	}

    	ClientNode current=head;
    	while(current!=NULL) {
        	fprintf(fp, "%d | %s | %s | %s | %s\n",current->id,current->password,current->name,current->address, current->phoneNumber);
        current = current->next;
    	}
	fflush(fp);
    	fclose(fp);
}

//대여목록 검사
int isBorrow(BorrowNode head, int id) {
    BorrowNode current=head;

    while (current != NULL) {
        if (current->id == id) {
            return 1;  // 학번이 존재하면 1 반환
        }
        current=current->next;
    }

    return 0;  // 학번이 존재하지 않으면 0 반환
}


void removeClient(ClientNode clientHead,BorrowNode borrowHead,int id){
	//대여한 도서가 있는경우
	if(isBorrow(borrowHead,id)){
		printf("대여한 도서가 있어 회원탈퇴가 불가능합니다. 2초 후 돌아갑니다.\n");
		sleep(2);
		return ;
	}


	//대여한 도서가 없는 경우 탈퇴 진행
	if(clientHead==NULL){
        	return ;  // 리스트가 비어있음
    	}

    	ClientNode current=clientHead;
    	ClientNode prev=NULL;

   	 // 삭제할 회원 찾기
    	while(current!=NULL&&current->id!=id) {
        	prev=current;
        	current=current->next;
    	}

    	// 첫 번째 노드를 삭제해야할 경우
    	if (prev==NULL) {
        	clientHead=current->next;
    	}
	else{
        	prev->next=current->next;
	}

    	free(current);
	updateClient(clientHead, "client.txt");
	printf("탈퇴가 완료되었습니다. 2초 후 돌아갑니다.\n");
	sleep(2);
    	return ;
}

void display_borrowed_books(ClientNode info) {
	printf("\n>> 내 대여 목록 <<\n");

	BorrowNode currentBorrow = headBorrow;
	bool found = false;

	while (currentBorrow != NULL) {
		if (currentBorrow->id == info->id) {
			found = true;

			BookNode currentBook = headBook;
			while (currentBook != NULL) {
				if (currentBook->bookId == currentBorrow->bookId) {
					char borrowDate[20], returnDate[20];

					calculate_date(currentBorrow->borrowDate, borrowDate);
					calculate_date(currentBorrow->returnDate, returnDate);

					printf("도서번호: %d\n", currentBook->bookId);
					printf("도서명: %s\n", currentBook->name);
					printf("대여일자: %s\n", borrowDate);
					printf("반납일자: %s\n\n", returnDate);
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

	printf("목록 확인 완료. 엔터를 누르면 돌아갑니다.\n");
	wait_enter();
}
