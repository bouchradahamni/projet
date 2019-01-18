/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * William Glazer Cavanagh
 * 2018
 *
 */
#include "minuterie.h"


//Fonction Interrupt qui a deux modes
//  on set minuterieExpiree a true si le interrupt se produit
//  si clignoterVert est true -> on clignote vert a raison d'un quart delay
////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            ISR( TIMER0_COMPA_vect )
//
// DESCRIPTION:        	Fonction Interrupt qui a deux modes
//                          on set minuterieExpiree a true si le interrupt se produit
//                          si clignoterVert est true -> on clignote vert a raison d'un quart delay
//                
////////////////////////////////////////////////////////////////////////////////////////////

ISR( TIMER0_COMPA_vect ) {

    //set bool et incremente compteur pour match daly experimental
	if (compteur > delaisDesire){
		minuterieExpiree = true;
		compteur=0;
	}
	else{
		compteur++;
	}

    // option pour clignoterVert
	if (clignoterVert){
		if(compteur > delaisDesire){
			vert();
		}
		else if(compteur > delaisDesire / 4){
			eteindre();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void partirMinuterie()
//
// DESCRIPTION:        	Fonction qui debute la minuterie et appele ISR(timer0) sur CTC
//                          Sert au inputDist et clignotement lors du transfert de donnees
//                
////////////////////////////////////////////////////////////////////////////////////////////

void partirMinuterie() {
	TCNT0 = 0; 
	OCR0A = 0xFF;
	TCCR0A = 0;
	TCCR0B |= (1 << WGM02) | (1 << CS02) | (1 << CS00);
	TIMSK0 |= (1 << OCIE0A);
}

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void initialisationMinuterie()
//
// DESCRIPTION:        	Fonction qui initialise la minuterie et appele ISR(timer0) sur CTC
//                
////////////////////////////////////////////////////////////////////////////////////////////

void initialisationMinuterie(){
	minuterieExpiree = true;
	cli();
	EICRA |= (1 << ISC01);	
	sei ();
}

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void diseableMinuterie()
//
// DESCRIPTION:        	Fonction ferme la minuterie
//                
////////////////////////////////////////////////////////////////////////////////////////////

void diseableMinuterie(){
	TCCR0B &= ~((1 << WGM02) | (1 << CS02) | (1 << CS00));
	TIMSK0 &= ~(1 << OCIE0A);
}