#ifndef MOTEUR_h
#define MOTEUR_h

#include "global.h"
#include "ligneDroite.h"
#include "etats.h"
#include "minuterie.h"

void initialisationPWM();
void disablePWM();

void ajusterLePWM(uint8_t gauche, uint8_t droite);
void avancer();
void reculer();
void arreterM();
void tournerGauche(int dir);
void tournerDroite(int dir);
void legerG(uint8_t increaseG);
void legerD(uint8_t increaseD);
void reajustementAvantTourner();
void reajustementArriere();
void disablePWM();
void boost();
void boostArriere();

#endif