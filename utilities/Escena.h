//
// Created by secre on 22/12/2024.
//

#ifndef PROYECTO_ESPADA_ESCENA_H
#define PROYECTO_ESPADA_ESCENA_H

/**
 * Para ver como visualizar la escena
 */
enum ModoVisualizacion{
    NORMAL, //Verla normal
    BUFFER_COLOR // Que las mallas de triangulos se pinten con un color asignado ;)
};

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
        std::string rutaModelo;
        FuenteLuz *luzPuntual = nullptr;
        FuenteLuz *luzFocal = nullptr;
        // Para elegir una malla
        bool consultarMalla = false;
        int xpos, ypos;
        Malla* mallaElegida = nullptr;

        void pintar_ejes();
        std::vector<glm::vec3> creaVectorColores(unsigned long long int size);
        bool flotantesIguales(float a, float b);
    public:
        Escena();
        ~Escena();

        void visualizar();
        bool getEjes();
        void setEjes(bool valor);
        void agregarModelo(std::string rutaArchivo);
        IGV::Modelo& getModelo();
        void eliminarModelo();
        std::string getRutaModelo();
        void comprobarSiHayMalla();
        void seleccionMalla();
        Malla* getMallaElegida();
        void pasarPosicionCursor(int x, int y);
        void deseleccionarMalla();
        FuenteLuz *getLuzPuntual();
    };
}

#endif //PROYECTO_ESPADA_ESCENA_H
