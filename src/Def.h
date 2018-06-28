/*
 * Def.h
 *
 *  Created on: Jun 28, 2018
 *      Author: usrc
 */

#ifndef SRC_DEF_H_
#define SRC_DEF_H_

#include <sys/time.h>



#define RB_DEBUG(...) \
	gettimeofday(&now, NULL); \
	printf("[%Lu:%Lu] ", now.tv_sec-start_time.tv_sec, now.tv_usec); \
	printf(__VA_ARGS__)


extern timeval now;
extern timeval start_time;

#endif /* SRC_DEF_H_ */
