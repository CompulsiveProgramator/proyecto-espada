//
// Created by secre on 23/12/2024.
//

#include "Malla.h"

#include <utility>

/**
 * Constructor de la malla
 * @param pos Las posiciones de todos los vertices de la malla
 * @param norm Las normales de cada vertice
 * @param ind Los indices de los triangulos
 * @param mat EL material de la malla
 */
IGV::Malla::Malla(std::vector<GLfloat> pos, std::vector<GLfloat> norm, std::vector<GLuint> ind, Material mat):material(mat) {
    posicionesVertices = std::move(pos);
    normales = std::move(norm);
    indices = std::move(ind);
}

const std::vector<GLfloat> &IGV::Malla::getPosicionesVertices() const {
    return posicionesVertices;
}

const IGV::Material &IGV::Malla::getMaterial() const {
    return material;
}

const std::vector<GLuint> &IGV::Malla::getIndices() const {
    return indices;
}

const std::vector<GLfloat> &IGV::Malla::getNormales() const {
    return normales;
}
