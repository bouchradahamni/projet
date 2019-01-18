/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * William Glazer Cavanagh
 * 2018
 *
 */
#include "terminalUART.h"

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void terminalUART(uint8_t (&mesuresA)[128][2],uint8_t (&mesuresB)[128][2],uint8_t (&mesuresC)[128][2])
//
// DESCRIPTION:        	Output tout le terminal et les valeurs du array
//                          appelle terminalUART() 3x
//                          
// MATERIEL:            Cable USB et serieViaUSB -l sur terminal
//            
////////////////////////////////////////////////////////////////////////////////////////////

void terminalUART(uint8_t (&mesuresA)[128][2],uint8_t (&mesuresB)[128][2],uint8_t (&mesuresC)[128][2])
{
	terminalUART(mesuresA);
	terminalUART(mesuresB);
	terminalUART(mesuresC);
    UARTmot("\n\n",2);
}

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void terminalUART(uint8_t (&mesures)[128][2])
//
// DESCRIPTION:        	Output au terminal 32 colonnes par 192 rangees
//                          Output relief
//                          
// MATERIEL:            Cable USB et serieViaUSB -l sur terminal
//            
////////////////////////////////////////////////////////////////////////////////////////////

void terminalUART(uint8_t (&mesures)[128][2])
{
	uint8_t numberOfA;
	uint8_t numberOfSpaces;
	
	//toutes les donnes dans l'array
	for (uint16_t i = 0; i<32; i++){		
        
        //Conversion  62cm (max) a 94 Atags (max)
        const float cmToA = 1.5;


        //si chiffre trop gros, restreindre
        if (mesures[i][RIGHT] * cmToA > 94){
            mesures[i][RIGHT] = 62;
        }
        if (mesures[i][LEFT]  * cmToA > 94){
            mesures[i][LEFT]  = 62;
        }


		//prends taille 192 et convertis en nombre de @ et ' '

		numberOfA = 94 - mesures[i][RIGHT] * cmToA;
		numberOfSpaces = 94 - numberOfA;
	
		//tranmets # and ' ' LEFT
		for (uint8_t j =0; j<numberOfA; j++){
			transmissionUART('@');
		}
		for (uint8_t j =0; j<numberOfSpaces; j++){
			transmissionUART(' ');
		}
		
		//transmets formattage voulu
		transmissionUART('|');
        transmissionUART('|');
		
		//prends taille 192 et convertis en nombre de @ et ' '
		numberOfA = 94 - mesures[i][LEFT] * cmToA;
		numberOfSpaces = 94 - numberOfA;
		
		//tranmets # and ' ' LEFT
		for (uint8_t j =0; j<numberOfSpaces; j++){
			transmissionUART(' ');
		}
		for (uint8_t j =0; j<numberOfA; j++){
			transmissionUART('@');
		}
		
		transmissionUART('\n');
	}
};

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            oid seuqenceFin(uint8_t (&distancesA)[128][2],uint8_t (&distancesB)[128][2],uint8_t (&distancesC)[128][2])
//
// DESCRIPTION:        	Output au terminal 32 colonnes par 192 rangees selon bouton, clignote en vert
//                          ensuite joue sonorite et couleur ambre
//                          
// MATERIEL:            Cable USB et serieViaUSB -l sur terminal
//                          Pizeo sur PORTB PIN 3-4 (pin allant 1 -> 8)
//                          Del   sur PORTB PIN 1-2        IDEM
//            
////////////////////////////////////////////////////////////////////////////////////////////

void seuqenceFin(uint8_t (&distancesA)[128][2],uint8_t (&distancesB)[128][2],uint8_t (&distancesC)[128][2]){
	
    //clignoter 2 fois par secondes
    delaisDesire = DELAIS_1s / 2;
	clignoterVert = true;
	
	//Sequence a repeter a l'infini
	while(true)
	{
        //attendre bouton
        bouton = false;
        waitBouton();

		//tranmission relief par terminal Avec clignotement
        initialisationMinuterie();
		partirMinuterie();
        
		terminalUART(distancesA,distancesB,distancesC);

		diseableMinuterie();
        
        //On mets une del ambree
        //on joue sonorite
		initialiseSonnerie();

		playSong();
		eteindre();
		
        diseableSonnerie();
	}
}