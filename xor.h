#include <stdio.h>
#include <string.h>

void xor(char *input,int n){

	char xor_key[] = "A";

	for (int i = 0;i < n ;i++){
		input[i] = input[i] ^ xor_key[i % (sizeof(xor_key)/sizeof(xor_key[0]) - 1)];
	}
}
