#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_64_ALPHABETH		64

const char table[BASE_64_ALPHABETH] = {'A', 'B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/',};

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

int get_index(const char* value){
	int idx;

	for(idx = 0; idx < BASE_64_ALPHABETH - 1; idx++){
		if(table[idx] == *value) break;
	}

	return idx;
}

int check_padding(const char* str){

	int padding = 0;
	int len = strlen(str);

	if( *(str+len) == '=') padding = 1;	// one '=' at the end
	if(padding == 1 && *(str+len-1) == '=') padding = 2; // two '=' at the end

	return padding;
}

char* base64_decode(const char* str){
	char* res = NULL;

	int len = strlen(str);
	res = malloc(len);
	
	int padding = check_padding(str);

	int i;
	if(padding == 0){
		int fours = len / 4;
		for(i = 0; i < fours; i++){
			char first =  get_index(str + i*4 + 0);
			char second = get_index(str + i*4 + 1);
			char third =  get_index(str + i*4 + 2);
			char fourth = get_index(str + i*4 + 3);

			res[0 + i*3] = (first << 2) | ( (second & 0x30) >> 4);
			res[1 + i*3] = (second << 4) | (third >> 2);
			res[2 + i*3] = ( (third & 0x03) << 6) | (fourth);
		}
	}
	
	res[3 + i*3] = '\0';

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
