//
// Created by secre on 22/12/2024.
//

#ifndef PROYECTO_ESPADA_INTERFAZ_H
#define PROYECTO_ESPADA_INTERFAZ_H

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include <iostream>
#include "Escena.h"
#include "Camara.h"

namespace IGV{
    /**
     * Clase que contiene a la ventana de la aplicación
     *
     * Sigue el patron Singleton
     */
    class Interfaz {
    private:
        static Interfaz *instancia;
        Interfaz();

        int ancho_ventana = 0; ///< Ancho de la ventana de visualizaci�n
        int alto_ventana = 0;  ///< Alto de la ventana de visualizaci�n
        Escena *escena = nullptr;
        Camara *camara = nullptr;
    public:
        ~Interfaz();
        static Interfaz& getInstancia();
        void configurar_ventana( int argc, char **argv, int _ancho_ventana, int _alto_ventana, int _pos_X, int _pos_Y,
                                std::string _titulo );

        // Para los callbacks:
        static void keyboardFunc( unsigned char key, int x, int y );
        static void reshapeFunc( int w, int h );
        static void displayFunc();
        static void specialFunc( int key, int x, int y );
        void inicializa_callbacks();

        // Para el bucle de visualizacion:
        void inicia_bucle_visualizacion();
    };
}

#endif //PROYECTO_ESPADA_INTERFAZ_H
