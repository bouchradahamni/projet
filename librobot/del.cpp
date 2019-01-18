/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * William Glazer Cavanagh, Elion Rushiti, Diana Kouakam, Bouchra Dahamni
 * 2018
 *
 */
#include "del.h"

//ETEINT, ROUGE, VERT def dans global.h

#define F_CPU 8000000UL

//Fonction qui initialise Del
void initialisationDel(){
    //on connecte del sur D bits 0-1
	DDRB |= 0b00000011;
}

//fonction qui eteins del
void eteindre(){
	PORTB &= ETEINT;
}

//fonction qui mets del rouge
void rouge(){
    eteindre();
	PORTB |= ROUGE;
}

//fonction qui mets del vert
void vert(){
    eteindre();
	PORTB  |= VERT;
}

//fonction pour couleur ambre
//fonction doit etre appelee a repetition
void ambre(){
	for(uint16_t j = 0; j<2800; j++){
		rouge();
		_delay_us(2);
		vert();
		_delay_us(3);
	}
}