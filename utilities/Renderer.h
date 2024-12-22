//
// Created by secre on 22/12/2024.
//

#ifndef PROYECTO_ESPADA_RENDERER_H
#define PROYECTO_ESPADA_RENDERER_H

#include <iostream>
#include "Escena.h"
#include "GUI.h"
#include "Camara.h"

namespace IGV{
    /**
     * Clase que contiene a la ventana de la aplicación
     *
     * Sigue el patron Singleton
     */
    class Renderer {
    private:
        static Renderer *instancia;
        Renderer();

        Escena *escena = nullptr;
        Camara *camara = nullptr;
        void configuraOpenGL();
    public:
        ~Renderer();
        static Renderer& getInstancia();
        void refrescar();
        Escena& getEscena();
        static void modificarTamañoVentana(int ancho, int alto);
    };
}

#endif //PROYECTO_ESPADA_RENDERER_H
