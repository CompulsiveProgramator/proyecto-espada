//
// Created by secre on 23/12/2024.
//

#include "Malla.h"

#include <utility>

IGV::Malla::Malla(std::vector<GLfloat> pos, std::vector<GLuint> ind, Material mat):material(mat) {
    posicionesVertices = std::move(pos);
    indices = std::move(ind);
}
