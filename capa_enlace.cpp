#include <iostream>
#include "capa_enlace.h"
#include "medio_fisico.h"

using namespace std;

bool receptor(Marco marco_entrante) {
    // Variable estatica para recordar que paquete esperamos (0 o 1)
    static int secuencia_esperada = 0;

    cout << "[RECEPTOR] Marco " << marco_entrante.num_secuencia << " recibido. Revisando errores..." << endl;

    if (calcular_checksum(marco_entrante.info.datos) != marco_entrante.checksum) {
        cout << "[RECEPTOR] Error: marco danado. Descartando (sin ACK)..." << endl;
        return false;
    }

    if (marco_entrante.num_secuencia == secuencia_esperada) {
        cout << "[RECEPTOR] Marco perfecto. Datos entregados: " << marco_entrante.info.datos << endl;
        secuencia_esperada = 1 - secuencia_esperada;
    } else {
        cout << "[RECEPTOR] Duplicado detectado (ya entregado). Se descarta y se reenvia ACK..." << endl;
    }

    if (simular_perdida()) {
        cout << "[MEDIO FISICO] El ACK " << marco_entrante.num_secuencia << " se perdio en el camino de vuelta." << endl;
        return false;
    }
    return true;
}

void emisor(PaqueteRed paquete, int &secuencia) {
    cout << "[EMISOR] Preparando marco con secuencia " << secuencia << "..." << endl;
    Marco m;
    m.tipo = 0;
    m.num_secuencia = secuencia;
    m.info = paquete;
    m.checksum = calcular_checksum(paquete.datos);
    
    bool ack = false;
    while (!ack) {
        if (simular_perdida()) {
            cout << "[MEDIO FISICO] El marco se perdio en el cable." << endl;
            cout << "[EMISOR] Timeout... Reenviando marco " << secuencia << endl;
            continue;
        }

        Marco enviado = m;
        if (simular_corrupcion()) {
            corromper_datos(enviado.info.datos);
            cout << "[MEDIO FISICO] El marco se corrompio en el camino." << endl;
        }

        ack = receptor(enviado);
        
        if (!ack) {
            cout << "[EMISOR] Timeout: ACK no llego. Reenviando marco " << secuencia << endl;
        }
    }
    
    cout << "[EMISOR] ACK " << secuencia << " recibido. Exito." << endl << endl;
    secuencia = 1 - secuencia;
}