//
// Created by secre on 23/12/2024.
//

#include "Malla.h"

#include <utility>

IGV::Malla::Malla(std::vector<GLfloat> pos, std::vector<GLuint> ind, Material mat):material(mat) {
    posicionesVertices = std::move(pos);
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
