#ifndef MINUTERIE_H
#define MINUTERIE_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "global.h"
#include "del.h"

//start Minuterie selon delay "delaisDesire" (extern volatile)
void partirMinuterie();

//initialise Minuterie
void initialisationMinuterie();

//Stop la minuterie
void diseableMinuterie();
#endif