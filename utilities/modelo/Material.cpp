//
// Created by secre on 23/12/2024.
//

#include <iostream>
#include <utility>
#include "Material.h"

/**
 * Constructor del material
 * @param ka Color ambiente
 * @param kd Color difuso
 * @param ks Color especular
 * @param es Exponente especular
 */
IGV::Material::Material(const glm::vec3 &ka, const glm::vec3 &kd, const glm::vec3 &ks, GLfloat es, std::string nombreMat) : Ka(ka), Kd(kd),
                                                                                                     Ks(ks), Es(es), nombreMaterial(nombreMat) {}

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
 * Setter del color difuso del material
 * @param _Kd
 */
void IGV::Material::setKd(glm::vec3 &Kd1) {
    Kd = Kd1;
}

/**
 * Setter del color especular del material
 * @param Ks1
 */
void IGV::Material::setKs(glm::vec3 &Ks1) {
    Ks = Ks1;
}

/**
 * Metodo para consultar el nombre del material
 * @return
 */
std::string IGV::Material::getNombreMaterial() {
    return nombreMaterial;
}

/**
 * Setter del color ambiente
 * @param Ka1
 */
void IGV::Material::setKa(glm::vec3 &Ka1) {
    Ka = Ka1;
}

/**
 * Setter del exponente especular
 * @param Es1
 */
void IGV::Material::setEs(GLfloat Es1) {
    Es = Es1;
}
