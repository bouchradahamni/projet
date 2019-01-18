/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Bouchra Dahamni
 * 2018
 *
 */
#include "sonorite.h"

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void initialiseSonnerie()
//
// DESCRIPTION:        	initiliase la sonnerie avec prescaler de 256 en mode CTC
//
// MATERIEL:            PiezoElectrque sur PORTB PIN 3-4 (avec pin allant 1-8)
//                
////////////////////////////////////////////////////////////////////////////////////////////

void initialiseSonnerie(){
    DDRB = 0b00001100;
	TCCR0B |= (1 << CS02); // clk prescalar a 256 // 
	TCCR0A |= (1 << COM0A0) | (1 << WGM01);
	OCR0A = 0xFF;
	TIMSK0 = 0b1 << OCIE0A;
	TCNT0 = OCR0A;
}
 

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void choisirOCR0A(uint8_t note)()
//
// DESCRIPTION:        	reset le OCR0A pour reccomencer la sonnerie avec nouvelle frequence et don nouvelle note
//
// PARAMETRES:          note -> uint8_t qui set le TOP du CTC timer0
//
// MATERIEL:            PiezoElectrque sur PORTB PIN 3-4 (avec pin allant 1-8)
//            
////////////////////////////////////////////////////////////////////////////////////////////

void choisirOCR0A(uint8_t note){
	OCR0A = valeursOCR0A[note - 45];
}


////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void arreterSonnerie()
//
// DESCRIPTION:        	Arret de la sonoritee non-permanent
//                          
// MATERIEL:            PiezoElectrque sur PORTB PIN 3-4 (avec pin allant 1-8)
//            
////////////////////////////////////////////////////////////////////////////////////////////

void arreterSonnerie(){
	TIMSK1 &= ~(0b1 << OCIE1A);
	TCNT1 = OCR1A;
}


////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void diseableSonnerie()
//
// DESCRIPTION:        	Arret de la sonoritee permanent
//                          
// MATERIEL:            PiezoElectrque sur PORTB PIN 3-4 (avec pin allant 1-8)
//            
////////////////////////////////////////////////////////////////////////////////////////////

void diseableSonnerie(){
	TCCR0B &= ~(1 << CS02);  
	TCCR0A &= ~((1 << COM0A0) | (1 << WGM01)); 
}


////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void playSong(uint8_t note)()
//
// DESCRIPTION:        	joue une arpege de notes tout en mettant la DEL ambree
//                          chaque for loop est une serie de notes
//                          
// MATERIEL:            PiezoElectrque sur PORTB PIN 3-4 (avec pin allant 1-8)
//            
////////////////////////////////////////////////////////////////////////////////////////////

void playSong(){
    initialisationDel();
	//Arpege de notes de la gamme Pentatonique
	for (uint8_t i =0; i<10; i++)
	{
		choisirOCR0A(55);
		ambre();
		choisirOCR0A(59);
		ambre();
		choisirOCR0A(62);
		ambre();
		choisirOCR0A(67);
		ambre();
	}
	
	for (uint8_t i =0; i<10; i++)
	{
		choisirOCR0A(54);
		ambre();
		choisirOCR0A(57);
		ambre();
		choisirOCR0A(61);
		ambre();
		choisirOCR0A(64);
		ambre();
	}
	
	for (uint8_t i =0; i<10; i++)
	{
		choisirOCR0A(52);
		ambre();
		choisirOCR0A(55);
		ambre();
		choisirOCR0A(60);
		ambre();
		choisirOCR0A(62);
		ambre();
	}
	arreterSonnerie();
}

