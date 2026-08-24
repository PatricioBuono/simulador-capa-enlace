#include <iostream>
#include "capa_enlace.h"
#include "medio_fisico.h"

using namespace std;

bool receptor(Marco marco_entrante) {
    cout << "[RECEPTOR] Marco recibido. Revisando errores..." << endl;
    
    int calc = calcular_checksum(marco_entrante.info.datos);
    
    if (calc != marco_entrante.checksum) {
        cout << "[RECEPTOR] Error: El marco esta danado. Descartando..." << endl;
        return false;
    }
    
    if (simular_perdida()) {
        cout << "[MEDIO FISICO] Uy! El ACK se perdio en el camino de vuelta." << endl;
        return false; // Pierde ACK
    }
    
    cout << "[RECEPTOR] Marco perfecto. Datos entregados: " << marco_entrante.info.datos << endl;
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
            cout << "[MEDIO FISICO] Uy! El marco se perdio en el cable." << endl;
            cout << "[EMISOR] Timeout... Reenviando marco " << secuencia << endl;
            continue; // Pierde marco y reintenta
        }
        
        ack = receptor(m);
        
        if (!ack) {
            cout << "[EMISOR] ACK no llego o fue erroneo. Reenviando marco..." << endl;
        }
    }
    
    cout << "[EMISOR] ACK recibido correctamente. Exito." << endl << endl;
    secuencia = 1 - secuencia; // Intercala entre 0 y 1
}