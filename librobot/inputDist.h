#ifndef INPUTDIST_H
#define INPUTDIST_H

#include "global.h"

#include "can.h"	// Nécessaire pour effectuer une conversion analogique numérique
#include "conversionACM.h"
#include "bouton.h"

//fonction qui prends un array de distances et ajoute une distance
void inputDist(uint8_t (&distances)[128][2], uint8_t & arraySize, Segment segment);

#endif