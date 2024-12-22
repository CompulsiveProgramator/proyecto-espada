//
// Created by secre on 22/12/2024.
//

#ifndef PROYECTO_ESPADA_ESCENA_H
#define PROYECTO_ESPADA_ESCENA_H

#include <GL/gl.h>
#include <GL/glut.h>

namespace IGV{
    /**
     * Clase que dibuja el modelo en escena
     */
    class Escena {
    private:
        bool ejes = true; // Para dibujar los ejes de coordenadas X,Y,Z

        void pintar_ejes();
    public:
        Escena();
        ~Escena();

        void visualizar();
        bool getEjes();
        void setEjes(bool valor);
    };
}

#endif //PROYECTO_ESPADA_ESCENA_H
