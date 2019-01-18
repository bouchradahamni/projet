#ifndef TRANSMISSIONUART_H
#define TRANSMISSIONUART_H

#include "moteur.h"

//transmet seriaViaUsb un carctere
void transmissionUART (const uint8_t chaineCar) ;

//init transmission
void initialisationUART () ;

//transmets un mot serieViaUSB -l
void UARTmot(const char* chaineCar, uint8_t size) ;

#endif
