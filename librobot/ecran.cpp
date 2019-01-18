/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Diana Kouakam
 * 2018
 *
 */
#include "ecran.h"

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void afficherNom(const char* word)
//
// DESCRIPTION:        	Fonction qui prends un string "VALUES" et affiche sur le LCD
//                          Efface les anciennes valeurs
//
// PARAMETRES:          word -> un const char*, sont un ptr vers un array de char
//
// MATERIEL:            Afficheur LCD branche sur le PORTC avec toutes les PIN, prises
//                   
////////////////////////////////////////////////////////////////////////////////////////////

void afficherNom(const char* word){
	DDRC = 0xFF ;                   //le port C est en sortie(utilise par le LCD)
	LCM LCD(&DDRC, &PORTC);         //cree un objet pour utiliser les methodes de la classe LCM
	LCD.clear();
    LCD.write(word, 2, true);       // ecrire le nom entrer a partir de la case 1 
}



////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void afficherMESURE(const uint16_t gauche , const uint16_t droite)
//
// DESCRIPTION:        	Fonction qui affiche au LCD: () efface l'ancien affichage
//                              GAUCHE: (gauche)
//                              DROITE: (droite)
//
// PARAMETRES:          gauche -> un uint16_t  representant une donne qui remplacera (value1 dans l'affichage)
//                      droite -> IDEM
//                   
////////////////////////////////////////////////////////////////////////////////////////////

void afficherMESURE(const uint16_t gauche , const uint16_t droite){
	DDRC = 0xFF ;
	LCM LCD(&DDRC, &PORTC);
	LCD.clear();                // efface tout ce qu'il y avait avant sur l'ecran

	LCD.write("GAUCHE: ", 1);
	LCD << gauche;               // ecrire a la suit de ce qui se trouve sur l ecran
	LCD[17] = "DROITE: ";        // ecrire le mot a partir de la case 17 
	LCD << droite;
}
