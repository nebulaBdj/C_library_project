#include "library.h"

void sign_up(){
	printf("\n");
	print_menu_name("회원 가입");
	printf("학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n\n");
	ClientNode newClient = get_client_info();
	printf("\n");
	//정보에 학번 있나 체크
	if(1){
	// 불러온 정보에 끝에 붙이고
	// 정렬해주기
	// 파일에 저장하기
		printf("회원가입이 되셨습니다.\n");
	}else{
		printf("이미 존재하는 학번입니다.\n");
	}
	printf("2초후 메인화면으로 돌아갑니다\n");
	sleep(2);
}

ClientNode get_client_info(){
	ClientNode newClient = (ClientNode)malloc(sizeof(Client));
	printf("학번: ");
	scanf("%d", &newClient->id);
	getchar();

	get_string("비밀번호: ", newClient->password);

	get_string("이름: ", newClient->name);

	get_string("주소: ", newClient->address);

	get_string("전화번호: ", newClient->address);
	return newClient;
}

int sign_in(){
	bool isPwdValid = false;
	while(!isPwdValid){
		system("clear");
		print_menu_name("로그인");
		char inputId[9], inputPwd[50];
		get_string("학번: ",inputId);
		if(strcmp(inputId, "admin") == 0){
			return 1;
		}
		get_string("비밀번호: ", inputPwd);
			//검색 학번
			//비밀번호 일치
		if(0){
			isPwdValid = true;
		}else{
			printf("정보가 일치하지 않습니다. 다시 입력해주세요.(ENTER 입력)");
			char ch;
			while((ch = getchar()) != '\n');
		}
	}
	return 0;
}
