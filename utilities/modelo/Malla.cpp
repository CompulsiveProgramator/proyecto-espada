//
// Created by secre on 23/12/2024.
//

#include "Modelo.h"

#include <utility>

/**
 * Constructor de la malla
 * @param pos Las posiciones de todos los vertices de la malla
 * @param norm Las normales de cada vertice
 * @param ind Los indices de los triangulos
 * @param mat La direccion del material de la malla
 */
IGV::Malla::Malla(std::vector<GLfloat> pos, std::vector<GLfloat> norm, std::vector<GLuint> ind, int indiceMaterial, IGV::Modelo *_miModelo): indiceMaterial(indiceMaterial), miModelo(_miModelo){
    posicionesVertices = std::move(pos);
    normales = std::move(norm);
    indices = std::move(ind);
}

const std::vector<GLfloat> &IGV::Malla::getPosicionesVertices() const {
    return posicionesVertices;
}

const std::vector<GLuint> &IGV::Malla::getIndices() const {
    return indices;
}

const std::vector<GLfloat> &IGV::Malla::getNormales() const {
    return normales;
}

/**
 * Metodo para obtener el material de la malla
 * @return El material asignado a la malla, como puntero ;)
 */
IGV::Material *IGV::Malla::getMaterial() {
    return miModelo->getMaterial(indiceMaterial);
}
