#include "library.h"

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
				break;
			case 2:
				//도서 삭제
				break;
			case 3:
				//도서 대여
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
				search_client_by_name(NULL);//리스트
				break;
			case 2:
				//학번 검색
				search_client_by_id(NULL);//리스트
				break;
			case 3:
				//전체 검색
				search_client_all(NULL);//리스트
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
	char name[10];
	get_string("이름 : ", name);
	while(head != NULL){
		if(strcmp(name, head->name) == 0){
			printf("%d %s %s %s\n", head->id, head->name, head->address, head->phoneNumber);
		}
		head = head->next;
	}
}

void search_client_by_id(ClientNode head){
	int id;
	printf("학번 : ");
	scanf("%d", &id);
	getchar();
	while(head != NULL){
		if(id, head->id){
			printf("%d %s %s %s\n", head->id, head->name, head->address, head->phoneNumber);
			break;
		}
		head = head->next;
	}
}

void search_client_all(ClientNode head){
	while(head != NULL){
		printf("%d %s %s %s\n", head->id, head->name, head->address, head->phoneNumber);
		head = head->next;
	}
}
