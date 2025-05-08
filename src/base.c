#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char table[] = {'A', 'B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/',};

typedef struct{
	char chunk[3];
} slot_t;

char* base64(const char* str){
	char* res = NULL;

	int len = strlen(str);
	res = malloc(len * 2);
	slot_t* slot = (slot_t*)str;
	printf("chunk to %d\n", slot[0]);
	
	for(int i = 0; i < (len / 3); i++){
		res[0 + i*4] =table[ ((*slot->chunk) & 0x0000FC) >> 0]; 	
		res[1 + i*4] =table[ ((*slot->chunk) & 0x000FC0) >> 6]; 	
	
//		printf("res0 =table[ %c\n", res[0]);
		res[2 + i*4] =table[ ((*slot->chunk) & 0x03F000) >> 12]; 	
		res[3 + i*4] =table[ ((*slot->chunk) & 0xFC0000) >> 18]; 	

		slot++;
	}

	res[len+5] = '\0';

	return res;
}

int main(){

	const char* txt = "foobar";

	int len = strlen(txt);
	char* res = base64(txt);

	printf("Lenght of %s is %d\n", txt, len);

	printf("String %s encoded using base64 is %s\n", txt, res);

	printf("size of %d\n", sizeof(table));

	return 0;
}
