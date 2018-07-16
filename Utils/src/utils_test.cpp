/*
 * utils_test.cpp
 *
 *  Created on: Jul 10, 2018
 *      Author: usrc
 */


#include "utils.h"

#include <stdio.h>
#include <string.h>

using namespace std;
using namespace RB_ROBOT_UTILS;


int main(int argc, char **argv) {

	const char *str = "This is a test.This is a test.This is a test.1234567This is a test.This is a test.123456";
	Squeezer *p = Squeezer::Instance();

	
	size_t length = strlen(str);
	char dest[1024];
	size_t destLength = sizeof(dest);
	size_t decomSize = 1024;
	

	int ret = p->Initialize();
	if (ret != 0) {
		printf("Error in initializing...ret val %d \n", ret);
		return 0;
	}

	ret = p->Compress((lzham_uint8 *) dest, &destLength, (const lzham_uint8 *)str, length);

	printf("Length is %d ret value %d \n", destLength, ret);

	char temp[1024];
	char decom[1024];

	for (int i = 0; i<destLength + 1; i++)
		temp[i] = dest[i];

	
	ret = p->DeCompress((lzham_uint8 *)decom, &decomSize, (const lzham_uint8 *)temp, destLength);

	printf("Decom Length is %d ret value %d \n", decomSize, ret);
	for (int i = 0; i<decomSize; i++)
		printf("%c", decom[i]);
	printf("\n");

	return 0;

}

