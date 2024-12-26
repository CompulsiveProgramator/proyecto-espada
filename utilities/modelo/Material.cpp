//
// Created by secre on 23/12/2024.
//

#include <iostream>
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

glm::vec3 &IGV::Material::getKa(){
    return Ka;
}

glm::vec3 &IGV::Material::getKd(){
    return Kd;
}

glm::vec3 &IGV::Material::getKs(){
    return Ks;
}

GLfloat IGV::Material::getEs(){
    return Es;
}

/**
 * Setter del color difuso
 * @param _Kd
 */
void IGV::Material::setKd(glm::vec3 &Kd1) {
    Kd = Kd1;
}

void IGV::Material::setKs(glm::vec3 &Ks1) {
    Ks = Ks1;
}
