//
// Created by secre on 23/12/2024.
//

#include "Material.h"

/**
 * Constructor del material!!!
 * @param ka Color ambiente
 * @param kd Color difuso
 * @param ks Color especular
 * @param es Exponente especular
 */
IGV::Material::Material(const glm::vec3 &ka, const glm::vec3 &kd, const glm::vec3 &ks, GLfloat es) : Ka(ka), Kd(kd),
                                                                                                     Ks(ks), Es(es) {}

const glm::vec3 &IGV::Material::getKa() const {
    return Ka;
}

const glm::vec3 &IGV::Material::getKd() const {
    return Kd;
}

const glm::vec3 &IGV::Material::getKs() const {
    return Ks;
}

GLfloat IGV::Material::getEs() const {
    return Es;
}
