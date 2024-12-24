//
// Created by secre on 23/12/2024.
//

#ifndef PROYECTO_ESPADA_MODELO_H
#define PROYECTO_ESPADA_MODELO_H

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <vector>
#include <glm/gtx/transform.hpp>
#include "Malla.h"

namespace IGV{
    /**
     * Clase que contiene un modelo 3D, con sus mallas de triangulos y materiales
     */
    class Modelo {
    private:
        std::vector<Malla> mallas; /// Las mallas de triangulos
        glm::mat4 matrizModelado;
    public:
        Modelo();
        Modelo(std::string rutaArchivo);
        std::vector<Malla> getMallas();
        glm::mat4 getMatrizModelado();
        void escalarUniforme(float i);
        void aplicarTraslacionEjeX(float distancia);
        void aplicarTraslacionEjeY(float distancia);
        void aplicarTraslacionEjeZ(float distancia);
        void aplicarRotacionEjeX(float angulo);
        void aplicarRotacionEjeY(float angulo);
        void aplicarRotacionEjeZ(float angulo);
        void resetearMatrizModelado();
    };
}



#endif //PROYECTO_ESPADA_MODELO_H
