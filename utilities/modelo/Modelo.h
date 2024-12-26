//
// Created by secre on 23/12/2024.
//

#ifndef PROYECTO_ESPADA_MODELO_H
#define PROYECTO_ESPADA_MODELO_H

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <vector>
#include <glm/gtx/transform.hpp>
#include "Material.h"

namespace IGV{
    class Malla;

    /**
     * Clase que contiene un modelo 3D, con sus mallas de triangulos y materiales
     */
    class Modelo {
    private:
        std::vector<Malla> mallas; /// Las mallas de triangulos
        std::vector<Material> materiales;
        glm::mat4 matrizModelado;
        int buscaMaterial(std::string nombreMat);
    public:
        Modelo();
        Modelo(std::string rutaArchivo);
        std::vector<Malla>* getMallas();
        glm::mat4 getMatrizModelado();
        Material* getMaterial(int i);
        void escalarUniforme(float i);
        void aplicarTraslacionEjeX(float distancia);
        void aplicarTraslacionEjeY(float distancia);
        void aplicarTraslacionEjeZ(float distancia);
        void aplicarRotacionEjeX(float angulo);
        void aplicarRotacionEjeY(float angulo);
        void aplicarRotacionEjeZ(float angulo);
        void aplicarEscaladoEjeX(float proporcion);
        void aplicarEscaladoEjeY(float proporcion);
        void aplicarEscaladoEjeZ(float proporcion);
        void resetearMatrizModelado();
    };

    class Malla {
    private:
        std::vector<GLfloat> posicionesVertices;
        std::vector<GLfloat> normales;
        std::vector<GLuint> indices;
        int indiceMaterial;
        IGV::Modelo *miModelo = nullptr;
    public:
        Malla(std::vector<GLfloat> pos, std::vector<GLfloat> norm, std::vector<GLuint> ind, int indiceMaterial, Modelo *miModelo1);
        const std::vector<GLfloat> &getPosicionesVertices() const;
        Material *getMaterial();
        const std::vector<GLuint> &getIndices() const;
        const std::vector<GLfloat> &getNormales() const;
    };
}



#endif //PROYECTO_ESPADA_MODELO_H
