#include "library.h"

int main(void){
	int num;
	while(num != 3){ //조건 고민중.. 아예 이부분도 함수화해야하나?
		system("clear");
		print_main_menu();
		num = select_num();
		switch (num){
			case 1:
				//회원가입 
				sign_up();
				break;
			case 2:
				int signNum = sign_in();
				if(signNum == 1){
			    	//관리자 메뉴 함수	
				}else if(signNum == 0){
					//회원 메뉴 함수
				}
				//만약 로그아웃하면 함수 탈출, 프로그램 종료는 exit(1);
				break;
			case 3:
				break;
			default:
				printf("잘못된 번호입니다. 2초후 다시 입력하세요.\n");
				sleep(2);
				system("clear");
		}
	}
	return 0;
}

void print_main_menu(){
	print_menu_name("도서관 서비스");
	printf("1. 회원 가입\t\t2. 로그인\t\t3. 프로그램 종료\n\n");
}

int select_num(){
	printf("번호를 선택하세요: ");
	int num;
	scanf("%d", &num);
	return num;
}
