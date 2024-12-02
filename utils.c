#include "library.h"

void print_menu_name(char *str){
	printf(">> %s <<\n", str);
}

void get_string(char *text, char arr[]){
	printf("%s", text);
	scanf("%[^\n]", arr);
	getchar();
}
