#ifndef CAPA_ENLACE_H
#define CAPA_ENLACE_H
#include "estructuras.h"
void emisor(PaqueteRed paquete_a_enviar, int &secuencia_actual);
bool receptor(Marco marco_entrante);
#endif