//
// Created by secre on 27/12/2024.
//

#ifndef PROYECTO_ESPADA_TEXTURA_H
#define PROYECTO_ESPADA_TEXTURA_H

#include <string>
#include "GL/gl.h"

namespace IGV {
    /**
     * Clase que contiene una textura de color con su imagen
     */
    class Textura {
    private:
        unsigned int idTextura = 0; //< Id de la textura
        unsigned ancho = 0, alto = 0; // Ancho y alto de la textura
        std::string nombreTextura;
    public:
        Textura( std::string fichero );
        ~Textura();
        void aplicar();
        std::string getNombreTextura();
    };

} // IGV

#endif //PROYECTO_ESPADA_TEXTURA_H
