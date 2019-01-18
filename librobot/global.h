#ifndef GLOBAL_H
#define GLOBAL_H
/*regroupement de certain include et define qui vont être utile tout au long 
du projet. Egalement les varible const et extern qui circule dans beaucoup de fichier*/
#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
using namespace std;

//capteur definie dans main.cpp mais accessible aux autres classes grace a ceci
extern volatile uint8_t capteur;
extern volatile bool bouton;

//valeur du compteur
extern volatile bool minuterieExpiree;
extern volatile uint8_t compteur;
extern volatile uint8_t delaisDesire;
extern volatile bool clignoterVert;

//Delay mesure experimentale
const uint16_t DELAIS_1s    = 8000000/128/1024;
const uint16_t DELAIS = DELAIS_1s / 14; //delay de prise de mesure experimental

//conversion INCH -> Cm
const double CmParPouce = 2.54;

//definition de gauche et droite pour nos arrays de mesures
const uint8_t LEFT  = 0;
const uint8_t RIGHT = 1;

//Ajout Valeur de Del
const uint8_t ROUGE    = (1 << 1);
const uint8_t VERT     = (1 << 0);
const uint8_t ETEINT   = (1 << 0) & (1 << 1);

//definition des cateurs avec leure pin associée
const uint8_t CAPTEUR1 = 0b00000001;
const uint8_t CAPTEUR2 = 0b00000010;
const uint8_t CAPTEUR3 = 0b00001000;
const uint8_t CAPTEUR4 = 0b00000100;
const uint8_t CAPTEUR5 = 0b00010000;

//definition des differentes combinaisons de detecteur de lignes
const uint8_t CENTRE   =  0b00100;
const uint8_t MARQUEUR =  0b11111;
const uint8_t VIDE     =  0b00000;

const uint8_t RIGHT0    =  0b11100;
const uint8_t RIGHT1   =  0b01100;
const uint8_t RIGHT2   =  0b01000;
const uint8_t RIGHT3   =  0b11000;
const uint8_t RIGHT4   =  0b10000;
const uint8_t RIGHT5   =  0b11110;

const uint8_t LEFT0     =  0b00111; 
const uint8_t LEFT1    =  0b00110;
const uint8_t LEFT2    =  0b00010;
const uint8_t LEFT3    =  0b00011;
const uint8_t LEFT4    =  0b00001;
const uint8_t LEFT5    =  0b01111;

//Valeur de OCR0A pour la sonorite
//Mesurees experimentalement pour avoir le bon delay avec prescaler 256
const uint8_t valeursOCR0A [37] = {141,133,126,118,112,105,99,94,88,83,79,74,70,66,62,59,55,52,49,46,44,42,39,37,35,32,30,29,27,26,24,23,21,20,19,18}; // OCR0A calcule pour chaque note //

//Creation des segments ou:
//      A = 1er droit
//      B = 2e droit
//      C = 3e droit
enum Segment {A,B,C};

//Fonction qui initialise tous les params
void initialisationGlobale();
#endif