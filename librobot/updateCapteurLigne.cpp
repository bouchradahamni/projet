/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Elion Rushiti
 * 2018
 *
 */
#include "updateCapteurLigne.h"


////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void updateCapteurLigne()
//
// DESCRIPTION:        	Update les capteur avec une valeur, chaque etat (VIDE DROIT GAUCHE etc.)
//                          Defini dans global.h. On fait une double verif du capteur pour s'assurer
//                          de ne pas avoir de faux negatifs. On ajuste aussi le capteur qui ne suit
//                          pas l'ordre des bits
//                          
// MATERIEL:            Capteur de ligne sur PORTA PIN 1-6 (sachant pin vont de 1 -> 8)
//            
////////////////////////////////////////////////////////////////////////////////////////////

void updateCapteurLigne(){

    bool boolConstant=false;

    //on procede a une double verification de la lecture de la PINA avec un intervalle de 10ms 
    while(!boolConstant)
    {
        capteur=PINA;
        _delay_ms(15);
        if (capteur  == PINA){
            boolConstant =true;
        }
    }

    //eliminer bits non necessaires
    capteur &= 0b11111;

    //Tenir compte de linversion
    uint8_t capteur3 = (capteur & 0b00100) << 1;
    capteur &= ~0b00100;
    uint8_t capteur4 = (capteur & 0b01000) >> 1;
    capteur &= ~0b01000;
    capteur |= capteur3 | capteur4;
}

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void initialisationLect()
//
// DESCRIPTION:        	Initialise la lecture des ports pour pouvoir appeler update capteurs
//                          
// MATERIEL:            Capteur de ligne sur PORTA PIN 1-6 (sachant pin vont de 1 -> 8)
//            
////////////////////////////////////////////////////////////////////////////////////////////

void initialisationLect(){
    DDRA = 0x00;                //PA as input
    PORTA |= 0b00011111;        //enable pull ups for
    updateCapteurLigne();
}