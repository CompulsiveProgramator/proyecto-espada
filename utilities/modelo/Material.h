//
// Created by secre on 23/12/2024.
//

#ifndef PROYECTO_ESPADA_MATERIAL_H
#define PROYECTO_ESPADA_MATERIAL_H

#include <GL/gl.h>
#include <glm/vec3.hpp>

namespace IGV{
    /**
     * Clase que contiene a un material, y las propiedades que lo definen:
     * - Color ambiente
     * - Color difuso
     * - Color especular
     * - Exponente especular
     */
    class Material {
    private:
        glm::vec3 Ka;
        glm::vec3 Kd;
        glm::vec3 Ks;
        GLfloat Es;
    public:
        Material(const glm::vec3 &ka, const glm::vec3 &kd, const glm::vec3 &ks, GLfloat es);

        const glm::vec3 &getKa() const;

        const glm::vec3 &getKd() const;

        const glm::vec3 &getKs() const;

        GLfloat getEs() const;
    };
}


#endif //PROYECTO_ESPADA_MATERIAL_H
