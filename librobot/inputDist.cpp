/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * William Glazer Cavanagh
 * 2018
 *
 */
#include "inputDist.h"

const can ConvAnalogNum;	

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void inputDist(uint8_t (&distances)[128][2], uint8_t & arraySize, Segment segment)
//                              reference pour eviter temps de copie
//
// DESCRIPTION:        	fonction qui prends un array et ajoute des valeurs de distances selon le cote
//                          De la ligne
//
//  PARAMETRES:         distances -> array de distances dans lequel on rentre des valeurs
//                          
// MATERIEL:            Capteurs de dist sur PORT A bits 7-8
//                
////////////////////////////////////////////////////////////////////////////////////////////

void inputDist(uint8_t (&distances)[128][2], uint8_t & arraySize, Segment segment)
{
    if(arraySize>128){
        return;
    }

    //SEGMENT
    uint16_t distanceMoyenneL=0;
	uint16_t distanceMoyenneR=0;
            
    //Prendre Rapidement 5 mesures et storer dans distMoyenne
    for (uint8_t i=0; i<5; i++){
        //Conversion lecture 10 bits a 8 bits
        distanceMoyenneL += ConvAnalogNum.lecture(0x06) >> 2;
        distanceMoyenneR += ConvAnalogNum.lecture(0x07) >> 2;
        _delay_ms(5);
    }
            
    //Moyenne distancesMoyennes et convertir en cm
    distanceMoyenneL = conversionACM(distanceMoyenneL / 5);
    distanceMoyenneR = conversionACM(distanceMoyenneR / 5);
            
    //ajouter la distance dependemment du cote de la ligne
    switch (segment){
        case A:
            distanceMoyenneL+= 6 * CmParPouce / 2;
            distanceMoyenneR-= 6 * CmParPouce / 2;
        case B:
            distanceMoyenneL-= 6 * CmParPouce / 2;
            distanceMoyenneR+= 6 * CmParPouce / 2;
        case C:
            distanceMoyenneL+= 6 * CmParPouce / 2;
            distanceMoyenneR-= 6 * CmParPouce / 2;
    }
        
    //ajouter au array et incrementer sa taille
    distances[arraySize][LEFT]  = distanceMoyenneL;
    distances[arraySize][RIGHT] = distanceMoyenneR;
    arraySize++;
}
