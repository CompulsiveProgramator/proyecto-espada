//
// Created by secre on 22/12/2024.
//

#ifndef PROYECTO_ESPADA_CAMARA_H
#define PROYECTO_ESPADA_CAMARA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/gl.h>
#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>
#include "igvPunto3D.h"

enum tipoCamara
{
    IGV_PARALELA,
    IGV_PERSPECTIVA
};

namespace IGV{
    /**
     * Clase que contiene todos los parametros de la "camara" de escena
     */
    class Camara{
    private:
        tipoCamara tipo = IGV_PARALELA; // El tipo de la camara
        GLdouble xwmin, xwmax, ywmin, ywmax; // Las dimensiones de la camara, si usamos PARALELA
        GLdouble angulo, raspecto; // El angulo de apertura vertical y la relacion ancho/alto
        GLdouble znear, zfar;
        glm::vec3 posicionCamara;
        glm::vec3 lookAt;
        glm::vec3 vectorVertical;
    public:
        Camara(GLdouble _xmin, GLdouble _xmax,
               GLdouble _ymin, GLdouble _ymax,
               GLdouble _znear, GLdouble _zfar,
               glm::vec3 _posicion,
               glm::vec3 _lookAt,
               glm::vec3 _vectorVertical);

        void aplicar();
        void rotarSobreLookAtEjeX(bool antihorario);
        void rotarSobreLookAtEjeY(bool antihorario);
    };
}


#endif //PROYECTO_ESPADA_CAMARA_H