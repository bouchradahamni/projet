#ifndef TERMINALUART_H
#define TERMINAL_UART

#include "global.h"

#include "transmissionUART.h"
#include "del.h"
#include "sonorite.h"
#include "bouton.h"

//prends 3 arrays formattesc a [32][2] et appelle terminalUART(uint8_t (&mesures)[128][2]) pour chaque
void terminalUART(uint8_t (&mesuresA)[128][2], uint8_t (&mesuresB)[128][2], uint8_t (&mesuresC)[128][2]);

//affiche commee professeur
void terminalUART(uint8_t (&mesures)[128][2]);

//Loop de fin avec transmission bouton
void seuqenceFin(uint8_t (&distancesA)[128][2],uint8_t (&distancesB)[128][2],uint8_t (&distancesC)[128][2]);

#endif
