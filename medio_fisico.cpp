#include "medio_fisico.h"
#include <cstdlib>

bool simular_perdida() {
  //return false; // Escenario sin perdida de datos
  return (rand() % 100) < 30; // 30% de probabilidad de fallo
}

bool simular_corrupcion() {
  return (rand() % 100) < 20; // 20% de probabilidad de que el marco llegue danado
}

void corromper_datos(std::string &datos) {
  if (!datos.empty()) datos[rand() % datos.size()] ^= 0x01; // cambia 1 bit de 1 caracter
}

int calcular_checksum(const std::string &datos) {
  int suma = 0;
  for (char c : datos) {
    suma += c;
  }
  return suma;
}