#include "library.h"

void menu_client(){
	printf("\n");
	int num;
	do{
		print_menu_name("회원 메뉴");
		printf("1. 도서 검색\t\t2. 내 대여 목록\n");
		printf("3. 게인정보 수정\t4. 회원 탈퇴\n");
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
