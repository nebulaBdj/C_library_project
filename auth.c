#include "library.h"
extern ClientNode headClient;

void sign_up(){
	printf("\n");
	print_menu_name("회원 가입");
	printf("학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n\n");
	ClientNode newClient = get_client_info();
	printf("\n");

	if(search_by_id(headClient, newClient->id) == NULL){
		newClient->next = headClient;
		headClient = newClient;
		sort_client(headClient);
		if(save_client_info(headClient)){
			printf("저장에 실패했습니다.\n");
		}else{
			printf("회원가입이 되셨습니다.\n");
		}
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

	get_string("전화번호: ", newClient->phoneNumber);
	return newClient;
}

int save_client_info(ClientNode head){
	FILE *ifp;
	if((ifp = fopen("client.txt", "w")) == NULL){
		return -1;
	}

	while(head != NULL){
		fprintf(ifp, "%d | %s | %s | %s | %s\n", head -> id, head -> password, head -> name, head->address, head->phoneNumber);
		head = head -> next;		
	}
	fclose(ifp);
	return 0;
}

int sign_in(){
	bool isPwdValid = false;
	ClientNode findNode;
	while(!isPwdValid){
		system("clear");
		print_menu_name("로그인");
		char inputId[9], inputPwd[50];
		get_string("학번: ",inputId);

		get_string("비밀번호: ", inputPwd);
		if(strcmp(inputId, "admin") == 0){
			return 1;
		}

		findNode = search_by_id(headClient, atoi(inputId));

		if((findNode != NULL) && strcmp(inputPwd, findNode->password)){
			isPwdValid = true;
		}else{
			printf("정보가 일치하지 않습니다. 다시 입력해주세요.(ENTER 입력)");
			char ch;
			while((ch = getchar()) != '\n');
		}
	}
	return 0;
}

ClientNode search_by_id(ClientNode head, int id){
	ClientNode node = NULL;
	while(head != NULL){
		if(id == head->id){
			node = head;
			break;
		}
		head = head->next;
	}
	return node;
}
