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
