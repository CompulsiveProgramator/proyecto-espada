//
// Created by secre on 22/12/2024.
//

#ifndef PROYECTO_ESPADA_ESCENA_H
#define PROYECTO_ESPADA_ESCENA_H

#include <GL/gl.h>
#include "modelo/Modelo.h"
#include "FuenteLuz.h"

namespace IGV{
    /**
     * Clase que dibuja el modelo en escena
     */
    class Escena {
    private:
        bool ejes = true; // Para dibujar los ejes de coordenadas X,Y,Z
        Modelo *modelo = nullptr;
        FuenteLuz *luzPuntual = nullptr;
        void pintar_ejes();
    public:
        Escena();
        ~Escena();

        void visualizar();
        bool getEjes();
        void setEjes(bool valor);
        void agregarModelo(std::string rutaArchivo);
    };
}

#endif //PROYECTO_ESPADA_ESCENA_H
