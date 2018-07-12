/*
 * utils_test.cpp
 *
 *  Created on: Jul 10, 2018
 *      Author: usrc
 */


#include "utils.h"

using namespace RB_ROBOT_UTILS;

int main(int argc, char **argv) {

	Squeezer *p = Squeezer::Instance();
	p->Test();
	return 0;

}

