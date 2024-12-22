//
// Created by secre on 22/12/2024.
//

#include "Camara.h"

/**
 * Constructor de una camara paralela
 * @param _xmin
 * @param _xmax
 * @param _ymin
 * @param _ymax
 * @param _znear La distancia al plano de corte cercano
 * @param _zfar La distancia al plano de corte lejano
 * @param _posicion La posicion de la camara
 * @param _lookAt El punto al que mira la camara
 * @param _vectorVertical El vector vertical a la camara
 */
IGV::Camara::Camara(GLdouble _xmin, GLdouble _xmax, GLdouble _ymin, GLdouble _ymax, GLdouble _znear, GLdouble _zfar,
                    igvPunto3D _posicion, igvPunto3D _lookAt, igvPunto3D _vectorVertical): xwmin(_xmin), xwmax(_xmax), ywmin(_ymin), ywmax(_ymax),
                    znear(_znear), zfar(_zfar),
                    posicionCamara(_posicion), lookAt(_lookAt), vectorVertical(_vectorVertical){
    tipo = IGV_PARALELA;
}

/**
 * Metodo para aplicar la transformacion de vision, de esta bonita camara, a la escena
 */
void IGV::Camara::aplicar() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if( tipo == IGV_PARALELA )
    {
        glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posicionCamara[X], posicionCamara[Y], posicionCamara[Z], lookAt[X], lookAt[Y], lookAt[Z], vectorVertical[X], vectorVertical[Y], vectorVertical[Z]);
}
