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
#include "Textura.h"

namespace IGV{
    class Malla;

    /**
     * Clase que contiene un modelo 3D, con sus mallas de triangulos y materiales
     */
    class Modelo {
    private:
        std::vector<Malla> mallas; /// Las mallas de triangulos
        std::vector<Material> materiales;
        std::vector<Textura> texturas;
        glm::mat4 matrizModelado;
        int buscaMaterial(std::string nombreMat);
        int buscaTextura(std::string nombreTex);
    public:
        Modelo();
        Modelo(std::string rutaArchivo);
        std::vector<Malla>* getMallas();
        glm::mat4 getMatrizModelado();
        Material* getMaterial(int i);
        Textura* getTextura(int i);
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
        GLuint idVAO = 0; // Memoria dinamica disfrazada, ya que en el destructor se "liberan" el VAO, VBOs, e IBO
        GLuint idIBO = 0;
        GLuint idVBO1 = 0, idVBO2 = 0;
        std::vector<GLfloat> posicionesVertices;
        std::vector<GLfloat> normales;
        std::vector<GLfloat> coordenadasTextura;
        std::vector<GLuint> indices;
        int indiceMaterial;
        int indiceTextura;
        unsigned long numIndices;

        IGV::Modelo *miModelo = nullptr;
        void crearVao();
    public:
        Malla(std::vector<GLfloat> pos, std::vector<GLfloat> norm, std::vector<GLfloat> text, std::vector<GLuint> ind, int _indiceMaterial, int _indiceTextura, Modelo *miModelo1);
        ~Malla(); //Cuidado
        const std::vector<GLfloat> &getPosicionesVertices() const;
        Material *getMaterial();
        Textura *getTextura();
        const std::vector<GLuint> &getIndices() const;
        const std::vector<GLfloat> &getNormales() const;
        std::vector<GLfloat> &getCoordenadasTextura();
        GLuint getIdVao();
        GLuint getIdIbo();
        unsigned long getNumIndices();
    };
}



#endif //PROYECTO_ESPADA_MODELO_H
