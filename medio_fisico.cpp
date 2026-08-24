#include "medio_fisico.h"
#include <cstdlib>
bool simular_perdida() {
  //return false; // Escenario sin pérdida de datos
  return (rand() % 100) < 30; // 30% de probabilidad de fallo
}
int calcular_checksum(std::string datos) {
int suma = 0;
for (char c : datos) {
suma += c;
}
return suma;
}