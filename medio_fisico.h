#ifndef MEDIO_FISICO_H
#define MEDIO_FISICO_H
#include "estructuras.h"
bool simular_perdida();
bool simular_corrupcion();
void corromper_datos(std::string &datos);
int calcular_checksum(const std::string &datos);
#endif