/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * William Glazer Cavanagh
 * 2018
 *
 */
#include "format32.h"

/*
On prends au maximum 64 donnees par 16cm mais on veut les faire rentrer dans 32 donnees

Si on obtiens trop de donnees (mesure pour que ce soit le cas) -> On les formatte sur 32 valeurs
      On choisis de sauter une valeur sur 2 plutot que de faire une moyenne pour avoir des "pics" nets
      De plus, lors de la prise de donnees, on fait une moyenne de 5 valeurs ce qui assure que nos donnees soit bonnes

Le probleme est le long segment de 32cm -> on doit enlever l'exces avant et apres celui-ci

SOIT PARCOURS SUIVANT:

EXCES               ->   XXXX
VALEURS DESIREES    ->   ----

        I------A-------             -------C------I   
DBT             |                   |                FIN
                XXXXXXX------B------XXXXXXX

*/




////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void shift32(uint8_t (&distances)[128][2], uint8_t & arraySize)
//                              Passe array par reference pour temps sauver execution
//
// DESCRIPTION:        	Prends la taille des donnees et les arrays de distances
//                          formatte les donnees en array de [32][2] puis appelle shift32() sur chaque array
//                          
// PARAMETRES:          distancesA, distancesB, distancesC -> uint8_t[128][2]
//                          distancesA, distancesC ont 64 valeurs pertinantes de mesurees
//                          tandisque distancesB en a 128, dont plusieurs en double
//                          on les a mis en array[128][2] pour pouvoir appeler shift32() avec toutes le fcts
//                          et sauver de l'espace memoire
//                
////////////////////////////////////////////////////////////////////////////////////////////

void format32(uint8_t (&distancesA)[128][2],uint8_t & arraySizeA,uint8_t (&distancesB)[128][2],uint8_t & arraySizeB,uint8_t (&distancesC)[128][2],uint8_t & arraySizeC){
    
    //au lieur de mettre 6/16 comme facteur de dedoublement, on mets un facteur 1/3 pour s'assurer d'avoir assez de valeurs 

	//Trouver la taille des doubles (XXX)
	uint8_t duplicateSizeAB = arraySizeA/3 +1;
	uint8_t duplicateSizeCB = arraySizeC/3 -1;

	//Modifier la taille du array
	arraySizeB = arraySizeB - duplicateSizeAB - duplicateSizeCB;
	
	//sauter les double du debut de array B (ceux arrieres sont sautees par la taille du array)
    for (uint8_t oldPos = duplicateSizeAB, newPos = 0; newPos<arraySizeB; oldPos++, newPos++){
		distancesB[newPos][LEFT]  = distancesB[oldPos][LEFT];
        distancesB[newPos][RIGHT] = distancesB[oldPos][RIGHT];
	}
	
    //formatter les array
	shift32(distancesA, arraySizeA);
    shift32(distancesB, arraySizeB);
    shift32(distancesC, arraySizeC);
}



////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void shift32(uint8_t (&distances)[128][2], uint8_t & arraySize)
//                              Passe array par reference pour temps sauver execution
//
// DESCRIPTION:        	Fonction qui prends des array de taille [128][2] formattes a un maximum de [32][2]
//                          On prends les valeurs de trop du array[64][2] et on en saute 1/2 jusqu'a ce que
//                          l'array rentre dans un array[32][2] (les autres valeurs ne seront plus pertinantes)
//                          
// PARAMETRES:          distances -> un uint8_t[128][2] qui a ete formatte pour avoir seulement 64 valeurs pertinantes
//                      
//                      arraySize -> arraySize variable qui est le nombre de valeurs significatives du array
//                          Si aucun parametres, par defaut 32
//                
////////////////////////////////////////////////////////////////////////////////////////////

void shift32(uint8_t (&distances)[128][2], uint8_t & arraySize){

    //trouver combien de valeur eviter pour rentrer dans 32
    int8_t excess = arraySize-32;

    //seulement si on a plus de valeurs que 32
    if(excess>0){
        
        //avec les valeurs en exces, on en saute 1/2 jusqu'a ce qu'on en aie 32

        //pour chaque valeur
        for (uint8_t i = 0; i<excess; i++)
        {
            //shifter 1/2 vers la droite
            for (uint8_t j = i; j<arraySize  ; j++)
            {
                distances[j][LEFT]  = distances[j+1][LEFT];
                distances[j][RIGHT] = distances[j+1][RIGHT];
            }
        }
    }
}