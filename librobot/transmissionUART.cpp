/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * William Glazer Cavanagh, Elion Rushiti, Diana Kouakam, Bouchra Dahamni
 * 2018
 *
 */
#include "transmissionUART.h"

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void initialisationUART ()
//
// DESCRIPTION:        	Initialise la transmission
//                          
// MATERIEL:            Cable USB et serieViaUSB -l sur terminal
//            
////////////////////////////////////////////////////////////////////////////////////////////

void initialisationUART () {

	// 2400 bauds. Nous vous donnons la valeur des deux

	// premier registres pour vous éviter des complications

	UBRR0H = 0;

	UBRR0L = 0xCF;

	// permettre la reception et la transmission par le UART0

	UCSR0A |= (1 << UDRE0);

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// Format des trames: 8 bits, 1 stop bits, none parity

	UCSR0C =  (1 << UCSZ10) | (1 << UCSZ11);
};

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void transmissionUART (const uint8_t donnee )
//
// DESCRIPTION:        	transmets un caractere
//
// PARAMETRES:          donnee -> const uint8_t, un caractere a afficher
//                          
// MATERIEL:            Cable USB et serieViaUSB -l sur terminal
//            
////////////////////////////////////////////////////////////////////////////////////////////

void transmissionUART (const uint8_t donnee ) {

	while ( !( UCSR0A & (1<<UDRE1)));
	UCSR0B &= ~(1<<TXB80);
	if ( donnee & 0x0100)
	UCSR0B |= (1<<TXB80);
	/* Put data into buffer, sends the data */
	UDR0 = donnee;
}

////////////////////////////////////////////////////////////////////////////////////////////
// FONCTION:            void UARTmot(const char* chaineCar, uint8_t size)
//
// DESCRIPTION:        	transmets une chaine de caracteres
//
// PARAMETRES:          chaineCar -> const char*, ptr vers un string a afficher
//                      size      -> taille de la chaine
//                          
// MATERIEL:            Cable USB et serieViaUSB -l sur terminal
//            
////////////////////////////////////////////////////////////////////////////////////////////

void UARTmot(const char* chaineCar, uint8_t size) {
    
	//call transmissionUART pour tous les caracteres
	for (uint8_t  i=0; i < size; i++ ) {
        	transmissionUART(*(chaineCar+i) );
	}
}

