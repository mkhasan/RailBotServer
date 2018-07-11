/*
 * util.h
 *
 *  Created on: Jul 9, 2018
 *      Author: usrc
 */

#ifndef UTILS_SRC_UTILS_H_
#define UTILS_SRC_UTILS_H_

namespace RB_ROBOT_UTILS {

class Squeezer {

private:
	Squeezer();
	~Squeezer();

	Squeezer(Squeezer & copy);

public:
	int Compress(char *dest, const char *src);
	int DeCompress(char *dest, const char *src);

	static Squeezer * Instance();
};



}



#endif /* UTILS_SRC_UTILS_H_ */
