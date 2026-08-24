#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <string>
struct PaqueteRed {
std::string datos;
};
struct Marco {
int tipo; // 0: Datos, 1: ACK
int num_secuencia;
PaqueteRed info;
int checksum;
};
#endif