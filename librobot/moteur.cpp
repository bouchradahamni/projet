/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Elion Rushiti
 * 2018
 *
 */
#include "moteur.h"


void initialisationPWM(){
	//Port D en sortie
	DDRD = 0xF0;
	// mise � un des sorties OC1A et OC1B sur comparaison

	// r�ussie en mode PWM 8 bits, phase correcte

	// et valeur de TOP fixe � 0xFF (mode #1 de la table 17-6

	// page 177 de la description technique du ATmega324PA)
	
	// mise a un des sorties OC1A et OC1B sur comparaison
	TCCR1A |= (1 << COM1A0) | (1 << COM1A1) | (1 << COM1B0) | (1 << COM1B1);
	TCCR1A |= (1 << WGM10);

	// division d'horloge par 8 � implique une frequence de PWM fixe
	TCCR1B |= (1 << CS11);
}

void disablePWM(){

	TCCR1A &= ~((1 << COM1A0) | (1 << COM1A1) | (1 << COM1B0) | (1 << COM1B1));
	TCCR1A &= ~(1 << WGM10);
	TCCR1B &= ~(1 << CS11);
}


////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void ajusterLePWM(uint8_t val1, uint8_t val2) 
// DESCRIPTION:        	Cette fonction permet d'ajuster le signal PWM des moteurs.
// PARAMETRES:			Les 2 entr�es sont OCR1A et OCR1B sur 8 bits 
//
// VALEUR DE RETOUR :	Aucune.
////////////////////////////////////////////////////////////////////////////////////////////
void ajusterLePWM(uint8_t gauche, uint8_t droite)
{
	uint8_t Ngauche,  Ndroite;
	
	Ndroite = 100 - droite;
	Ngauche = 100 - gauche;
	
	OCR1A = 0x00ff*(Ndroite/100.0);         					              					 
	OCR1B = 0x00ff*(Ngauche/100.0);
	
	

  }

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTIONS:           void avancer(), void reculer()
//						 
// DESCRIPTION:        	Ces fonctions permettent de faire bouger(avancer et reculer) 
//						le robot en modiffiant les ports qui sont mis à 1 selon 
//						la logique suivante:
//		PORT pour  avancer = roue droite == 6  
//					   		 roue gauche == 5
//			 	   reculer = roue droite == 8
//			 				 roue gauche == 7
//
// VALEUR DE RETOUR :	Aucune.
////////////////////////////////////////////////////////////////////////////////////////////
void avancer(){	
	PORTD = (1<<5) | (1<<4);
	ajusterLePWM( 42, 45);
};

void boost(){
	PORTD = (1<<5) | (1<<4);
	ajusterLePWM( 99, 99);
	_delay_ms(30);
}

void boostArriere(){
	PORTD = (1<<7) | (1<<6);
	ajusterLePWM(99, 99);
	_delay_ms(30);
}
void reculer(){
	PORTD = (1<<7) | (1<<6);
	ajusterLePWM(45, 45);
}

void arreterM(){
	PORTD = (0<<7) | (0<<6) | (0<<5)| (0<<4);
	ajusterLePWM(0,0);
}

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTIONS:           void tournerGauche(int dir), void tournerDroite(int dir)
//						 
// DESCRIPTION:        	Ces fonctions permettent de faire tourner(droite et gauche) 
//						le robot  de 2 maniere en modiffiant les ports qui sont mis 
//   					à 1 selon. Les deux manières sont en faisant avancer la roue 
//						à l'opposé ou reculer la roue du bord qu'on tourne. Ça permet
//						d'ajuster le robot apres le virage.
//						La logique est la suivante(pour "int dir"):
//								dir 1->tourne avec reculon
//								dir 2->tourne en avancant
//
// VALEUR DE RETOUR :	Aucune.
////////////////////////////////////////////////////////////////////////////////////////////

void tournerGauche(int dir){
	PORTD=(1<<5) | (1<<6);
	if (dir==1)
	{
		ajusterLePWM(53,0);
	}
	else 
	{
		ajusterLePWM(0,50);
	}
}

void tournerDroite(int dir){
	PORTD =  (1<<4) | (1<<7);
	if (dir==1)
	{
		ajusterLePWM(0,55);
	}
	else 
	{
		ajusterLePWM(50,0);
	}	
}

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTIONS:           void legerD(uint8_t increaseD), void legerD(uint8_t increaseD)
//						 
// DESCRIPTION:        	Ces fonctions permettent d'ajouter du pwm à la roue qui
//						qui pousse moins fort. Plus le robot se déclale, plus le
//						pwm ajouté est grand.
//
// VALEUR DE RETOUR :	Aucune.
////////////////////////////////////////////////////////////////////////////////////////////
void legerG(uint8_t increaseG){
	//trouver les valeurs pour quil retourne tout droit 

	uint8_t nouvelleVG;
	nouvelleVG = 42 + increaseG;
	PORTD = (1<<5) | (1<<4);
	ajusterLePWM(nouvelleVG, 45);
}

void legerD(uint8_t increaseD){
	//torouver les valeurs pour quil retourne tout droit 
	uint8_t nouvelleVD;
	nouvelleVD = 45 + increaseD;
	PORTD = (1<<5) | (1<<4);
	ajusterLePWM( 42,  nouvelleVD);
}

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void reajustementAvantTourner()	 
// DESCRIPTION:        	Cette fonction permet de faire reculer le robot pour lui 
//						donner un meilleur angle pour tourner
// VALEUR DE RETOUR :	Aucune.
////////////////////////////////////////////////////////////////////////////////////////////
void reajustementAvantTourner(){
	boostArriere();
    reculer();
	_delay_ms(600);
}
////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void reajustementArriere()	 
// DESCRIPTION:        	Cette fonction permet de faire reculer le robot pour qu'on 
//						puisse récupérer toute les données après le virage.  
// VALEUR DE RETOUR :	Aucune.
////////////////////////////////////////////////////////////////////////////////////////////
void reajustementArriere(){
	//APRES LE VIRAGE
	//le robot avancre pour trouver le centre
	boost();
    avanceDroit();
    while (capteur!=CENTRE){
        updateCapteurLigne();
        avanceDroit();
    }
    arreterM();
    _delay_ms(200);
	//une fois aligner, il reculer se reset jusqu'au vide
	boostArriere();
    reculer();
    while (capteur!=VIDE){
        updateCapteurLigne();
        reculer();
    }
    arreterM();
    _delay_ms(200);
	//Puis il reprend son chemin normal et continu le parcours
	boost();
    avancer();
	
    while (capteur==VIDE){
        updateCapteurLigne();
        avancer();
    }
}
