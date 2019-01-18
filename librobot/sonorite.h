#ifndef SONORITE_H
#define SONORITE_H

#include "global.h"
#include "del.h"

//joue chanson
void playSong();

//arret bref sonnerie
void arreterSonnerie();

//Choisis frequence du son
void choisirOCR1A(uint8_t note);

//Initialise sonnerie
void initialiseSonnerie();

//diseable permanent de la sonnerie
void diseableSonnerie();

#endif
