#ifndef FORMAT64_H
#define FORMAT64_H

#include "global.h"


//fonction qui prends 3 array et formatte en size [32][2]
void format32(uint8_t (&distancesA)[128][2],uint8_t & arraySizeA,uint8_t (&distancesB)[128][2],uint8_t & arraySizeB,uint8_t (&distancesC)[128][2],uint8_t & arraySizeC);

//fonction qui prends des valeurs [64][2] et convertis en [32][2]
void shift32(uint8_t (&distances)[128][2], uint8_t & arraySize);
#endif