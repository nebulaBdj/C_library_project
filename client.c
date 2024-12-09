#include "library.h"
extern ClientNode headClient;

void update_info(ClientNode);

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
				break;
			case 2:
				//내 대여 목록
				break;
			case 3:
				//개인정보 수정
				update_info(info);
				break;
			case 4:
				//회원 탈퇴 
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
