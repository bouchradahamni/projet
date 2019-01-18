/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * William Glazer Cavanagh
 * 2018
 *
 */
#include "mesurerPerimetre.h"


////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void mesurerPerimetres( uint8_t (&mesuresA)[128][2], uint8_t (&mesuresB)[128][2], uint8_t (&mesuresC)[128][2], double (&perimetre)[2])
//                              reference pour eviter temps de copie
//
// DESCRIPTION:        	Apeller cette fct apres que les arrays aient etes fit sur [32]
//                          Donne un array [2] de double de perimetres selon pythagore
//                          FCT appele mesurerPerimetre() pour chaque array et incremente le perimetre
//                          
//  PARAMETRES:         mesuresA, mesuresB, mesuresC -> uint8_t[128][2]
//                          valeurs donnt doit trouver les pythagores
//
//                      perimetre -> double de perimetres qui est incremente de la valeur de perimetre du segment
//                
////////////////////////////////////////////////////////////////////////////////////////////

void mesurerPerimetres( uint8_t (&mesuresA)[128][2], uint8_t (&mesuresB)[128][2], uint8_t (&mesuresC)[128][2], double (&perimetre)[2])
{
	mesurerPerimetre(mesuresA,perimetre);
	mesurerPerimetre(mesuresB,perimetre);
	mesurerPerimetre(mesuresC,perimetre);
}



////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void mesurerPerimetre( uint8_t (&mesures)[128][2], double (&perimetre)[2],  uint8_t arraySize)
//                              reference pour eviter temps de copie
//
// DESCRIPTION:        	mesure le perimetre d'un array fit a [32][2] valeurs
//                          Donne un array [2] de double de perimetres selon pythagore
//          `   
//          `                                 |\.
//          `                                 | \  Perimetre 
//          `                         Mesure  |  \.
//          `                                 |___\.
//          `                                   
//          `                               LongueurParMesure
//         
//  PARAMETRES:         mesures -> uint8_t[128][2], seulement 32 valeurs sont utiles
//                          valeurs donnt doit trouver les pythagores
//
//                      perimetre -> double de perimetres qui est incremente de la valeur de perimetre du segment
//
//                      arraySize -> par defaut 32
//                
////////////////////////////////////////////////////////////////////////////////////////////

void mesurerPerimetre( uint8_t (&mesures)[128][2], double (&perimetre)[2],  uint8_t arraySize)
{
	//valeur en Pc
	double segment = 16.0;

    //Delta X par mesure
	double longueurParMesure = segment * CmParPouce / (arraySize-1);
	
	double perimetreTemp[2] = {0.0, 0.0};
	double delta[2];

	//Avec pythagore, on calcule la longueur de l'hypothenuse entre la 
	//distance entre chaque mesure et le Delta en Y mesure par le capteur
	// SQRT ( Delta Y ^2 + Delta X ^2 )
	for (uint8_t i=0; i < (arraySize-1); i++)
	{	
		delta[LEFT]  = mesures[i][LEFT]  - mesures[i+1][LEFT];
        delta[RIGHT] = mesures[i][RIGHT] - mesures[i+1][RIGHT];

        perimetreTemp[LEFT]  += sqrt( delta[LEFT] *delta[LEFT]  + longueurParMesure*longueurParMesure );
        perimetreTemp[RIGHT] += sqrt( delta[RIGHT]*delta[RIGHT] + longueurParMesure*longueurParMesure );
	}

	//On retourne perimetre en int en sachant qu'on perds de la precision
	//Puisqu'on doit arrondir a un entier de toute maniere
	perimetre[LEFT]  += round(perimetreTemp[LEFT]);
	perimetre[RIGHT] += round(perimetreTemp[RIGHT]);
}
