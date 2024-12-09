#include "library.h"

void print_menu_name(char *str){
	printf(">> %s <<\n", str);
}

void get_string(char *text, char arr[]){
	printf("%s", text);
	scanf("%[^\n]", arr);
	getchar();
}

void sort_client(ClientNode head){
	ClientNode p, q;
	int checkSwap;
    do{
	    checkSwap = 0;
	    p = head;
	    q = head->next;
	    while(q != NULL){
		    if(p->id > q->id){
			    char temp[200];
				int tmp = p->id;
				p->id = q->id;
				q->id = tmp;
			    strcpy(temp, p->password);
			    strcpy(p->password, q->password);
			    strcpy(q->password, temp);

			    strcpy(temp, p->name);
			    strcpy(p->name, q->name);
			    strcpy(q->name, temp);

			    strcpy(temp, p->address);
			    strcpy(p->address, q->address);
			    strcpy(q->address, temp);
				
			    strcpy(temp, p->phoneNumber);
			    strcpy(p->phoneNumber, q->phoneNumber);
			    strcpy(q->phoneNumber, temp);
			    checkSwap = 1;
			}
			p = q;
			q = q->next;
	   }
	}while(checkSwap);
}

ClientNode insert_client(ClientNode head, ClientNode new){
	if(head == NULL || new->id < head->id){
		new->next = head;
		return new;
	}
	ClientNode p, q;
	p = head;
	q = head->next;
	while(q != NULL){
		if((p->id < new->id) && (q->id > new->id)){
			new->next = q;
			p->next = new;
			return head;
		}
		p = q;
		q = q->next;
	}
	p->next = new;
	return head;
}

void debug_print_client(ClientNode head){
	while(head!=NULL){
		fprintf(stdout, "%d|%s|%s|%s|%s|\n", head -> id, head -> password, head -> name, head->address, head->phoneNumber);
		head = head->next;
	}
}

void wait_enter(){
	printf("\n엔터를 누르면 이전화면으로 돌아갑니다.");
	char ch;
	while((ch = getchar()) != '\n');
}

