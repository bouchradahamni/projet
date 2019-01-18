/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * William Glazer Cavanagh
 * 2018
 *
 */
#include "conversionACM.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            uint8_t conversionACM(uint8_t data)
//
// DESCRIPTION:        	Fonction qui prends les conversions de donnees du CAN pour les outputs en cm
//                      
// EQUATION:            DIST = mesure * -1.1843 + 115.81
//                          R = 0.99 (trouve experimentalement)
//                          Sujet a changer avec le voltage de la batterie 9V
//
// PARAMETRES:          data -> un uint8_t qui a ete pris du CAN avec methode .lecture(),
//                           bitshifte >> 2. On le vonvertis en valeur de cm.
//                   
////////////////////////////////////////////////////////////////////////////////////////////

uint8_t conversionACM(uint8_t data)
{
	// coefficient de la formule qui converti la valeur retournee par le can en cm
	double coefficient = 1952.66;
	uint8_t result;
	//effectuer operation et convertir uint8_t
	result = coefficient*pow( data, -1.05714)+1;
	
	//De maniere arbitraire, 
    //      max = 56cm
    //      min = 10cm
	
	//ccorriger donnees trop loin (reads ~110)
    //      [56 , 130] -> 56
	if (result>56&& result<=130){
		result = 56;
	}
	//corriger donnees trop pres (reads ~200)
    //      [130 , 256] U [0 , 10] -> 10
	if (result>130 || result<10){
		result = 10;
	}
	
	return result;
	 
};
