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
	
	int tripples = len / 3;
	int rest = len % 3;

	int idx;
	for(idx = 0; idx < tripples; idx++){

		res[0 + idx * 4] = table[ (slot->chunk[0] >> 2) ]; 	

		char f = (slot->chunk[0] & 0x03) << 4;
		char s = (slot->chunk[1] >> 4);
		res[1 + idx*4] =table[ f | s ]; 	
	
		f = (slot->chunk[1] & 0x0F) << 2;
		s = (slot->chunk[2] >> 6);
		res[2 + idx*4] =table[ f | s ]; 	

		res[3 + idx*4] =table[ slot->chunk[2] & 0x3F ]; 	

		slot++;
	}
	if(rest == 1){
		int offset = (tripples * 3);

		res[offset + 1] = table[*(str+offset) >> 2];
		res[offset + 2] = table[(*(str+offset) & 0x03) << 4];
		res[offset + 3] = '=';
		res[offset + 4] = '=';
		res[offset + 5] = '\0';
	}
		
	if(rest == 2){
		int offset = (tripples * 3);
		res[offset + 1] = table[*(str+offset) >> 2];

		char f = (*(str+offset) & 0x03) << 4;
		char s = *(str+offset+1) >> 4;
		res[offset + 2] = table[f | s];

		res[offset + 3] = table[(*(str+offset+1) & 0x0F) << 2];
		res[offset + 4] = '=';
		res[offset + 5] = '\0';
	}
	return res;
}

int check_padding(const char* str){

	int padding = -1;
	int len = strlen(str);

	if( *(str+len) == '=') padding = 2;
	if(padding == 2 && *(str+len-1) == '=') padding = 1;

	for(int i = 0; i < len; i++){
		if(table[i] == *(str + len)){
			padding = 0;
			break;
		}else{
			padding = -1;
		}
	}
	return padding;
}

char* base64_decode(const char* str){
	char* res = NULL;

	int len = strlen(str);
	res = malloc(len);
	
	int padding = check_padding(str);
	if(padding == -1) exit(1);



	return res;
}

int main(){

	const char* txt = "foobar";

	int len = strlen(txt);
	char* res = base64(txt);

	printf("Lenght of %s is %d\n", txt, len);

	printf("String %s encoded using base64 is %s\n", txt, res);

	printf("String %s decoded using base64 is %s\n", res, base64_decode(res));

	free(res);

	return 0;
}
