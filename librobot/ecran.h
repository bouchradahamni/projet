#ifndef ECRAN_H
#define ECRAN_H

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

#include "global.h"

#define DDR	 DDRC // Data Direction Register' AVR occupé par l'aff.
#define PORT PORTC // Port AVR occupé par l'afficheur

//fonction pour afficher le nom du groupe
void afficherNom(const char* a); 

//fonction pour afficher le nom du groupe
void afficherMESURE(const uint16_t gauche , const uint16_t droite); 

#endif