//
// Created by secre on 22/12/2024.
//

#ifndef PROYECTO_ESPADA_CAMARA_H
#define PROYECTO_ESPADA_CAMARA_H

#include <GL/gl.h>
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
        igvPunto3D posicionCamara;
        igvPunto3D lookAt;
        igvPunto3D vectorVertical;
    public:
        Camara(GLdouble _xmin, GLdouble _xmax,
               GLdouble _ymin, GLdouble _ymax,
               GLdouble _znear, GLdouble _zfar,
               igvPunto3D _posicion,
               igvPunto3D _lookAt,
               igvPunto3D _vectorVertical);

        void aplicar();
    };
}


#endif //PROYECTO_ESPADA_CAMARA_H
