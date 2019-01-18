#ifndef BOUTON_H
#define BOUTON_H

//on inclue lib interrupt
#include "global.h"

//on ne mets pas ISR() dans .h car elle ne sera jamais appelee par autre fct

//Initialise Interrupt de Bouton et disable
void initialisationBouton();
void disableBouton();

//Stoppe programme tant que interrupt non-active
void waitBouton();

#endif
