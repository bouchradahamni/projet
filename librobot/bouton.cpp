/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * William Glazer Cavanagh
 * 2018
 *
 */
#include "bouton.h"


////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            ISR( INT0_vect  )
//
// DESCRIPTION:        	Fonction qui detecte Interrupt des boutons
//                          et set variable bool exeterne et volatile
//                          a true, ne pas oublier de reset a false
//
// MATERIEL:            Cavalier sur intEn
//                      Rien sur port D PIN 3-4
////////////////////////////////////////////////////////////////////////////////////////////

ISR( INT0_vect  ) {	
	//systeme antireonds?
	bouton = true;
}



////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void initialisationBouton()
//
// DESCRIPTION:        	Fonction qui initialise les interrupt de Boutons
//
// MATERIEL:            Cavalier sur intEn
//                      Rien sur port D PIN 3-4
////////////////////////////////////////////////////////////////////////////////////////////

void initialisationBouton()
{
	cli(); 					//stop iinterrupt
	DDRD &= ~0b00000010;	//PIND 2 est set en entree
	EIMSK |= (1 << INT0);	//scrutation sur falling edge
	EICRA |= (1 << ISC01);	
	sei ();					//repartir interrupt
}



////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void initialisationBouton()
//
// DESCRIPTION:        	Fonction qui initialise les interrupt de Boutons
//
// MATERIEL:            Cavalier sur intEn
//                      Rien sur port D PIN 3-4
////////////////////////////////////////////////////////////////////////////////////////////

void disableBouton(){
	cli(); 					//stop iinterrupt
	EIMSK &= ~(1 << INT0);	//scrutation sur falling edge
	EICRA &= ~(1 << ISC01);	
	sei ();	
}



////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void initialisationBouton()
//
// DESCRIPTION:        	Fonction qui attends un delais de bouton avant d'executer une autre commande
//
// MATERIEL:            Cavalier sur intEn
//                      Rien sur port D PIN 3-4
////////////////////////////////////////////////////////////////////////////////////////////

void waitBouton(){
	while(!bouton){};
    bouton = false;
}

