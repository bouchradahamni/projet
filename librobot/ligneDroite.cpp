/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Elion Rushiti
 * 2018
 *
 */
#include "ligneDroite.h"



////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void avanceDroit()
//
// DESCRIPTION:        	Permet au robot de se réajuster pour suivre la ligne 
//                          
// MATERIEL:            Capteurs de ligne sur PORTA bits 1-6 (commencant a 1  ->  8)
//                
////////////////////////////////////////////////////////////////////////////////////////////

void avanceDroit()
{
    //centré
    if(capteur == CENTRE){
        avancer();
    }

    //trop a gauche
    else if (capteur == LEFT1)
    {
        legerD(5);
    }
    //trop a gauche
    else if (capteur == LEFT2)
    {
        legerD(8);
    }
    //trop a gauche
    else if (capteur == LEFT3)
    {
        legerD(11);
    }
    //trop a gauche
    else if (capteur == LEFT4)
    {
        legerD(13);
    }

    //trop a droite
    else if (capteur == RIGHT1)
    {
        legerG(5);
    }
    //trop a droite
    else if (capteur == RIGHT2)
    {
        legerG(7);
    }
    //trop a droite
    else if (capteur == RIGHT3)
    {
        legerG(9);
    }
    //trop a droite
    else if (capteur == RIGHT4)
    {
        legerG(11);
    }

    //Tout autre combinaison de capteurs
    else
    {
        avancer();
    }
}


