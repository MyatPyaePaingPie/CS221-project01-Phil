
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "passwords.h"
#include "sha256.h"

#define DIG_BIN_LEN 32
#define DIG_STR_LEN ((DIG_BIN_LEN * 2) + 1)

void sha256(char *dest, char *src) {	
    // zero out the sha256 context
    struct sha256_ctx ctx;
    memset(&ctx, 0, sizeof(ctx));

    // zero out the binary version of the hash digest
    unsigned char dig_bin[DIG_BIN_LEN];
    memset(dig_bin, 0, DIG_BIN_LEN);

    // zero out the string version of the hash digest
    memset(dest, 0, DIG_STR_LEN);

    // compute the binary hash digest
    __sha256_init_ctx(&ctx);
    __sha256_process_bytes(src, strlen(src), &ctx);
    __sha256_finish_ctx(&ctx, dig_bin);

    // convert it into a string of hexadecimal digits
    for (int i = 0; i < DIG_BIN_LEN; i++) {
        snprintf(dest, 3, "%02x", dig_bin[i]);
        dest += 2;
    }
}

int tenK(char *dig_str, int lenP, char *pwd){
	//for 10k tests
	for (int i = 0; i < lenP; i++) {
		sha256(dig_str, passwords[i]);

		if(strcmp(dig_str, pwd) == 0){
			printf("%s\n", passwords[i]);
			return 0;
		}	
	}
	return 1;
}

char leet(char strP){

		switch(strP){
					case 'o':
						return '0';
			
					case 'e':
						return '3';
						
					case 'i':
						return '!';
						
					case 'a':
						return '@';
						
					case 'h':
						return '#';
						
					case 's':
						return '$';
						
					case 't':
						 return'+';
						
					default:
						return strP;
			}				
}

void temp(char* wordStr, char* pwd);
int returnLeet(char *final_str, int lenP, char *pwd){
	//for 10k l33t-speak tests

		char wordStr[64];
		for(int i = 0; i < 10000; i++){
			int lenPword = strlen(passwords[i]);

			temp(wordStr, passwords[i]);
			
			sha256(final_str, wordStr);

			if(strcmp(final_str, pwd) == 0){
				printf("%s\n", wordStr);
				return 0;
			}
		}
		return 1;
		
}

void temp(char*wordStr, char* pwd){
	for(int i = 0; i < 64; i++){
		wordStr[i] = leet(pwd[i]);
		
	}
}

int tenKpOne(char* pwd){
	char wordPlusOne[64];
	for(int i = 0; i < 10000; i++){
		strncat(wordPlusOne, "1", 2);

		if(strcmp(wordPlusOne, pwd) == 0){
			printf("%s\n", wordPlusOne[i]);
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[]) {
	char dig_str[DIG_STR_LEN];
	int lenP = sizeof(passwords)/sizeof(passwords[0]);//found the size of passwords[]
	char final_str[DIG_STR_LEN];//empty to put in the hashed versions
	

	int tenK_result = tenK(dig_str, lenP, argv[1]);
	//int returnLeet_result = returnLeet(final_str, lenP, argv[1]);
	//int wordPlusOne_result = tenKpOne(argv[1]);

	if(tenK_result == 0){//if tenK == 0 return 0
		return 0;
		exit(-1);
		}
	int returnLeet_result = returnLeet(final_str, lenP, argv[1]);

	if(returnLeet_result == 0){
		return 0;
		exit(-1);
	}
	
	int wordPlusOne_result = tenKpOne(argv[1]);
	if(wordPlusOne_result == 0){
		return 0;
		exit(-1);
	}

	else{
		printf("not found\n");
		return 0;
	}
	return 0;
	
}
