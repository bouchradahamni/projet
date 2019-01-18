#ifndef MESURERPERIMETRE_H
#define MESURERPERIMETRE_H

#include "global.h"

//Mesure le perimetre de plusieurs array fitte a 32 valeurs
void mesurerPerimetres( uint8_t (&mesuresA)[128][2], uint8_t (&mesuresB)[128][2], uint8_t (&mesuresC)[128][2], double (&perimetre)[2]);

//Mesure le perimetre d'un array fitte a 32 valeurs
void mesurerPerimetre( uint8_t (&mesures)[128][2], double (&perimetre)[2], uint8_t arraySize = 32);

#endif
