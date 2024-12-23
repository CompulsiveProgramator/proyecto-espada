//
// Created by secre on 23/12/2024.
//

#ifndef PROYECTO_ESPADA_MALLA_H
#define PROYECTO_ESPADA_MALLA_H

#include <iostream>
#include <vector>
#include <GL/gl.h>
#include "Material.h" // Cada malla tiene un materiall asignado

namespace IGV{
    class Malla {
    private:
        std::vector<GLfloat> posicionesVertices;
        std::vector<GLfloat> normales;
        std::vector<GLuint> indices;
        Material material;
    public:
        Malla(std::vector<GLfloat> pos, std::vector<GLfloat> norm, std::vector<GLuint> ind, Material mat);

        const std::vector<GLfloat> &getPosicionesVertices() const;

        const Material &getMaterial() const;

        const std::vector<GLuint> &getIndices() const;

        const std::vector<GLfloat> &getNormales() const;
    };
}


#endif //PROYECTO_ESPADA_MALLA_H
