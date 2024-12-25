//
// Created by secre on 22/12/2024.
//

#ifndef PROYECTO_ESPADA_RENDERER_H
#define PROYECTO_ESPADA_RENDERER_H

#include <iostream>
#include "Escena.h"
#include "Camara.h"
#include "../Constantes.h"

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
        int ancho_ventana = Constantes::anchoVentana, alto_ventana = Constantes::altoVentana;
        void configuraOpenGL();
    public:
        ~Renderer();
        static Renderer& getInstancia();
        void refrescar();
        Escena& getEscena();
        Camara& getCamara();
        static void modificarTamañoVentana(int ancho, int alto);
        void comprobarSiHayMalla();
        int getAnchoVentana() const;
        int getAltoVentana() const;
        Malla* getMallaSeleccionada();
        void pasarPosicionCursor(int x, int y);
        void deseleccionarMalla();
    };
}

#endif //PROYECTO_ESPADA_RENDERER_H
