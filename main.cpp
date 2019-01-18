#include "etats.h"

/*Déclaration des volatile de notre projet*/
volatile uint8_t capteur;
volatile bool bouton = false;
volatile bool minuterieExpiree;
volatile uint8_t compteur = 0;
volatile uint8_t delaisDesire;
volatile bool clignoterVert = false;

/*TOUTES LES VARIBLES QUI SONT UTILIES AU TRAVERS DU PROJET, SONT DÉFINIES
DANS LA FONCTION GLOBAL.CPP*/

int main(){
	
	uint8_t etatInit=0;
    initialisationGlobale();
	
	etatRobot(etatInit); 
	
	

}