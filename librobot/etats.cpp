/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Elion Rushiti
 * 2018
 *
 */
#include "etats.h"
////////////////////////////////////////////////////////////////////////////////////////////
// FONCTIONS:           void etatRobot(uint8_t& etat)						 
// DESCRIPTION:         Les arrrets de moteur vont souvent etre utilisé dans cette  
//          fonction pour éviter que le robot perd la ligne à cause de son inertie
//          Nous utilisons les switch case pour simuler une machine à état et rendre notre 
//          code plus facile à lire, on sait que notre système possède 8 états alors on set
//          la limite du while en fonction
// VALEUR DE RETOUR :	Aucune.
// MATERIEL: Suiveur de ligne, Del, LCD, cavalier
////////////////////////////////////////////////////////////////////////////////////////////

void etatRobot(uint8_t& etat){
    
    delaisDesire = DELAIS;

    uint8_t distancesA[128][2];
    uint8_t distancesB[128][2];
    uint8_t distancesC[128][2];

    for (uint8_t i=0; i<128; i++){
        distancesA[i][RIGHT] = 0;
        distancesA[i][LEFT]  = 0;
        distancesB[i][RIGHT] = 0;
        distancesB[i][LEFT]  = 0;
        distancesC[i][RIGHT] = 0;
        distancesC[i][LEFT]  = 0;
    }

    uint8_t arraySizeA = 0;
    uint8_t arraySizeB = 0;
    uint8_t arraySizeC = 0;
    double  perimetre[2] = {0.0, 0.0};
    
    while(etat<=7){
            switch(etat){
            case 0: //AVANCE ET DETECT MARQUEUR
                arreterM();
                afficherNom("SUPER GENIUS"); // afficher le nom du robot
                waitBouton();
                _delay_ms(3000); //comme demande, on reste sur place 3seconde
                //le robot commence le parcours et cherche le marqueur
                boost();
                avanceDroit();
                afficherNom("Etat Un");
                while (capteur != MARQUEUR)
                {
                    updateCapteurLigne();
                    avanceDroit();
                }
                afficherNom("Etat Un fin");                
                rouge(); //on allume la del rouge
                etat++;
                break;

            case 1: /*Le robot avance jusqu'a ce qu'il arrive au bout de la ligne
                    on commence à prendre des mesures pour les murs*/
                avanceDroit();
                partirMinuterie();
                afficherNom("Etat deux");
                while (capteur != VIDE)
                {
                    updateCapteurLigne();
                    avanceDroit();
                    //pendant ce temps il prend des mesures sur un timer différent
                    if (minuterieExpiree)
                    {
                        inputDist(distancesA, arraySizeA, A);
                        minuterieExpiree = false;
                    }
                }
                afficherNom("Etat deux fin");
                //fin des mesures et arret au vide du robot
                diseableMinuterie();
                arreterM();
                _delay_ms(1000);
                etat++;
                break;

            case 2: /*le robot se reajuste d'abord pui tourne a droite pour 
                    continuer son parcours. 
                    La decription des manières de tourner expliqué dans moteur.cpp*/
                reajustementAvantTourner();
                tournerDroite(1);
                _delay_ms(700);
                updateCapteurLigne();

                afficherNom("Etat trois");
                while(capteur != RIGHT2){
                    updateCapteurLigne();
                    tournerDroite(1);
                }
                afficherNom("Etat trois fin");
                arreterM();
                _delay_ms(500);
                etat++;
                break;

            case 3: /*le robot avance jusqu'au virage gauche et trouve le vide
                     au bout du virage qui lui sert de signal pour tourner*/
                boost();
                avanceDroit();
                afficherNom("Etat quatre");
                while( (capteur != VIDE))
                {
                    updateCapteurLigne();
                    avanceDroit();
                    //pour avoir la ligne noire à peu près au même niveau que les roues
                    if(capteur==VIDE){
                        _delay_ms(1000);
                    }
                }
               
                arreterM();
                _delay_ms(200);
                /*commenece à tourner à gauche, jusqu'à ce que son 
                capteur le plus à gauche detect la ligne*/
                tournerGauche(2);
                while(capteur != CENTRE){
                    updateCapteurLigne();
                    tournerGauche(2);
                }
                arreterM();
                _delay_ms(200);
                afficherNom("Etat quatre fin");
                /*le robot va essayer de reajuster son parcours pour prendre toutes 
                les mesures qui sont au même niveau que la ligne noire*/
                reajustementArriere();
                etat++;
                break;

            case 4:/*Le robot avance jusqu'a ce qu'il arrive au bout de la ligne
                    on recommence à prendre des mesures pour les murs*/
                avanceDroit();
                partirMinuterie();
                afficherNom("Etat cinq");
                while (capteur!=VIDE){
                    updateCapteurLigne();
                    avanceDroit();

                    if (minuterieExpiree){
                        inputDist(distancesB,arraySizeB,B);
                        minuterieExpiree = false;
                    }

                }
                //fin des mesures pour ce segment et arrêt du robot
                diseableMinuterie();
                arreterM();
                _delay_ms(1000);
                afficherNom("Etat cinq fin");
                etat++;
                break;

            case 5: /*le robot se reajuste d'abord pui tourne a gauche pour 
                    continuer son parcours.*/
                reajustementAvantTourner();
                afficherNom("Etat six");
                tournerGauche(1);
                _delay_ms(350);
                updateCapteurLigne();
                while(capteur != LEFT3){
                    updateCapteurLigne();
                    tournerGauche(1);
                }
                arreterM();
                _delay_ms(500);
                afficherNom("Etat six fin");
                etat++;
                break;

            case 6:/*le robot avance jusqu'au virage gauche et trouve le vide
                     au bout du virage qui lui sert de signal pour tourner*/
                afficherNom("Etat sept");
                boost();
                avanceDroit();
                while(capteur != VIDE)
                {
                    updateCapteurLigne();
                    avanceDroit();
                    //pour avoir la ligne noire à peu près au même niveau que les roues
                    if(capteur==VIDE){
                        _delay_ms(1000);
                    }
                }
                
                arreterM();
                _delay_ms(200);
                tournerDroite(2);
                while(capteur != CENTRE){
                    updateCapteurLigne();
                    tournerDroite(2);
                }
                arreterM();
                _delay_ms(200);
                /*le robot va essayer de reajuster son parcours pour prendre toutes 
                les mesures qui sont au même niveau que la ligne noire*/
                reajustementArriere();
                afficherNom("Etat sept fin");
                etat++;
                break;

            case 7: /*le robot reprend son chemin droit et recommence à prendre
            les mesures sur les murs*/
                afficherNom("Etat huit");
                avanceDroit();
                partirMinuterie();

                while (capteur!=MARQUEUR){
                    updateCapteurLigne();
                    avanceDroit();

                    if (minuterieExpiree){
                        inputDist(distancesC,arraySizeC,C);
                        minuterieExpiree = false;
                    }

                }
                afficherNom("Etat huit fin");
                diseableMinuterie();

                arreterM();
                eteindre();
                
                //format arrays to length 64
	            format32(distancesA,arraySizeA,distancesB,arraySizeB,distancesC,arraySizeC);
                mesurerPerimetres(distancesA,distancesB,distancesC,perimetre);
                afficherMESURE(perimetre[LEFT] , perimetre[RIGHT]);
                seuqenceFin(distancesA,distancesB,distancesC);

                break;
            default:
                break;
        }
    }
}