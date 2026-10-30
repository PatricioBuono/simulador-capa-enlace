#include <cstdlib>
#include <ctime>
#include "estructuras.h"
#include "capa_enlace.h"

int main() {
    srand(time(0)); // Inicializa la semilla aleatoria
    int secuencia = 0;
    
    PaqueteRed p1 = {"Primer paquete: 'Hola'"};
    PaqueteRed p2 = {"Segundo paquete: 'Redes de Datos'"};
    PaqueteRed p3 = {"Tercer paquete: 'Fin de transmision'"};
    
    emisor(p1, secuencia);
    emisor(p2, secuencia);
    emisor(p3, secuencia);
    
    return 0;
}