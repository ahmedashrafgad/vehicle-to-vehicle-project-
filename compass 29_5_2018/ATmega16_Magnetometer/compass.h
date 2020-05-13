/*
 * compass.h
 *
 * Created: 29/05/2018 05:17:51 م
 *  Author: DELL
 */ 

#ifndef COMPASS_H_
#define COMPASS_H_
#include <math.h>
#include "I2C_Master_H_file.h"
typedef enum{north,south,east,west,non}compass;

void Magneto_init();
int Magneto_GetHeading();
int compass_direction();



#endif /* COMPASS_H_ */