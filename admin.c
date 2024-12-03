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
