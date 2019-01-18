/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Elion Rushiti, William Glazer Cavanagh
 * 2018
 *
 */
#include "global.h"

//includes pour fcts init
#include "etats.h"
#include "del.h"
#include "bouton.h"
#include "moteur.h"
#include "transmissionUART.h"
#include "minuterie.h"
#include "updateCapteurLigne.h"

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void initialisationGlobale()
//
// DESCRIPTION:        	Call necessaire pour toutes les fcts qui necessitent de changer les registres ou PORTS
//                          (minuteries, Del, Bouton, Lecture, moteurs, transmission)
//                          
// MATERIEL:            Donne dans le fichier .txt Broches et materiel.txt
//                
////////////////////////////////////////////////////////////////////////////////////////////

void initialisationGlobale(){
    initialisationDel();
    initialisationBouton();
    initialisationLect();
    initialisationPWM();
	initialisationUART();
    initialisationMinuterie();
}

