//
// Created by benja on 11/04/25.
//

#ifndef EVENTOS_HPP
#define EVENTOS_HPP
#include <ostream>

// Acá definís el enum de manera clara y exportable
enum class Evento {
    ATAQUE,
    DEFENSA,
    DESCANSO,
    COMERCIO,
    ALERTA,
    REPARACION
    // agregá más eventos si necesitás
};

#include <ostream>

inline std::ostream& operator<<(std::ostream& os, Evento evento) {
    switch (evento) {
        case Evento::ATAQUE: os << "ATAQUE"; break;
        case Evento::DEFENSA: os << "DEFENSA"; break;
        case Evento::DESCANSO: os << "DESCANSO"; break;
        case Evento::COMERCIO: os << "COMERCIO"; break;
        case Evento::ALERTA: os << "ALERTA"; break;
        case Evento::REPARACION: os << "REPARACION"; break;
        default: os << "DESCONOCIDO"; break;
    }
    return os;
}


#endif // EVENTOS_HPP

