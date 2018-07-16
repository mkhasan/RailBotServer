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

	int length = strlen(str);
	char dest[1024];
	int destLength = sizeof(dest);

	int ret = p->Compress(dest, destLength, str, length);

	//cout << "Length is " << length << endl;

	printf("Length is %d ret value %d \n", destLength, ret);

	char temp[1024], decom[1024];

	for(int i=0; i<destLength+1; i++)
	 	temp[i] = dest[i];

	int decomSize = 1024;
	ret = p->DeCompress(decom, decomSize, temp, destLength);

	printf("Decom Length is %d ret value %d \n", decomSize, ret);
	for(int i=0; i<decomSize; i++)
		printf("%c", decom[i]);
	printf("\n");

	return 0;

}

