#include "library.h"
ClientNode headClient; 
BookNode headBook;
BorrowNode headBorrow;

int main(void){
	headClient=load_client("client.txt");
	headBook=load_book("book.txt");
	headBorrow=load_borrow("borrow.txt");

	int num;
	while(num != 3){
		system("clear");
		print_main_menu();
		num = select_num();
		switch (num){
			case 1:
				//회원가입 
				sign_up();
				break;
			case 2:
				ClientNode signNode = sign_in();
				if(signNode == NULL){
			    	//관리자 메뉴 함수
					menu_admin();
				}else{
					//회원 메뉴 함수
					menu_client(signNode);
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
	getchar();
	return num;
}


//client파일 로드
ClientNode load_client(char* filename){
	FILE* fp=fopen(filename,"r");
	if(fp==NULL){
		printf("client 파일을 열 수 없습니다.\n");
		return NULL;
	}
	ClientNode head=NULL;
	ClientNode current=NULL;
	Client tmp;
	while(fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%s\n",&tmp.id,tmp.password,tmp.name,tmp.address, tmp.phoneNumber)!=EOF){

		ClientNode tmpp = malloc(sizeof(Client));
       		*tmpp = tmp;
        	tmpp->next = NULL;

        	if (head==NULL) {
               		head = tmpp;
            		current = tmpp;
		}
		else {
            		current->next = tmpp;
            		current = tmpp;
		}
	}

	fclose(fp);
    	return head;
}



//book파일 로드
BookNode load_book(char* filename){
	FILE* fp=fopen(filename,"r");
	if(fp==NULL){
		printf("book 파일을 열 수 없습니다.\n");
		return NULL;
	}
	BookNode head=NULL;
	BookNode current=NULL;
	Book tmp;
	while(fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%ld|%[^|]|%c\n",&tmp.bookId,tmp.name,tmp.publisher,tmp.author, &tmp.ISBN, tmp.location, &tmp.isAvailable)!=EOF){

		BookNode tmpp = malloc(sizeof(Book));
       		*tmpp = tmp;
        	tmpp->next = NULL;

        	if (head==NULL) {
               		head = tmpp;
            		current = tmpp;
		}
		else {
            		current->next = tmpp;
            		current = tmpp;
		}
	}

	fclose(fp);
    	return head;
}



//borrow파일 로드
BorrowNode load_borrow(char* filename){
	FILE* fp=fopen(filename,"r");
	if(fp==NULL){
		printf("borrow 파일을 열 수 없습니다.\n");
		return NULL;
	}
	BorrowNode head=NULL;
	BorrowNode current=NULL;
	Borrow tmp;
	while(fscanf(fp,"%d|%d|%ld|%ld\n",&tmp.id,&tmp.bookId,&tmp.borrowDate, &tmp.returnDate)!=EOF){

		BorrowNode tmpp = malloc(sizeof(Borrow));
       		*tmpp = tmp;
        	tmpp->next = NULL;

        	if (head==NULL) {
               		head = tmpp;
            		current = tmpp;
		}
		else {
            		current->next = tmpp;
            		current = tmpp;
		}
	}

	fclose(fp);
    	return head;
}


