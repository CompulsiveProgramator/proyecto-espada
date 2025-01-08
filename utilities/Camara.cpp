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
 * @param _posicion La posicionPuntual de la camara
 * @param _lookAt El punto al que mira la camara
 * @param _vectorVertical El vector vertical a la camara
 */
IGV::Camara::Camara(GLdouble _xmin, GLdouble _xmax, GLdouble _ymin, GLdouble _ymax, GLdouble _znear, GLdouble _zfar,
                    glm::vec3 _posicion, glm::vec3 _lookAt, glm::vec3 _vectorVertical): xwmin(_xmin), xwmax(_xmax), ywmin(_ymin), ywmax(_ymax),
                    znear(_znear), zfar(_zfar),
                    posicionCamara(_posicion), lookAt(_lookAt), vectorVertical(_vectorVertical){
    tipo = IGV_PARALELA;
}

/**
 * Constructor de la camara en perspectiva
 * @param _angulo
 * @param _raspecto
 * @param _znear
 * @param _zfar
 * @param _posicion
 * @param _lookAt
 * @param _vectorVertical
 */
IGV::Camara::Camara(GLdouble _angulo, GLdouble _raspecto, GLdouble _znear, GLdouble _zfar, glm::vec3 _posicion,
                    glm::vec3 _lookAt, glm::vec3 _vectorVertical):angulo(_angulo), raspecto(_raspecto),
                                                                  znear(_znear), zfar(_zfar), posicionCamara(_posicion), lookAt(_lookAt), vectorVertical(_vectorVertical){
    tipo = IGV_PERSPECTIVA;
}

/**
 * Devuelve la matriz de la transformación de visión de la cámara, para llevarla al origen de coordenadas
 * @return La matriz de visión
 */
glm::mat4 IGV::Camara::getMatrizVision() {
    return glm::lookAt(posicionCamara, lookAt, vectorVertical);
}

/**
 * Devuelve la matriz de la transformación de proyección, para llevar las coordenadas de los objetos 3D a el plano 2D
 * @return La matriz de proyección
 */
glm::mat4 IGV::Camara::getMatrizPerspectiva() {
    return glm::perspective(angulo, raspecto, znear, zfar);
}

/**
 * Para hacer el movimiento de camara orbit
 * @param antihorario True si queremos girar antihorario o false si queremos ir horario
 */
void IGV::Camara::rotarSobreLookAtEjeX(bool antihorario) {
    if(antihorario){
        glm::mat4 rotacionSobrePosicionLookAt = glm::translate(lookAt) * glm::rotate(glm::radians(10.0f), glm::vec3(1,0,0)) * glm::translate(-lookAt);
        posicionCamara = rotacionSobrePosicionLookAt * glm::vec4(posicionCamara, 1);
    }else{
        glm::mat4 rotacionSobrePosicionLookAt = glm::translate(lookAt) * glm::rotate(glm::radians(-10.0f), glm::vec3(1,0,0)) * glm::translate(-lookAt);
        posicionCamara = rotacionSobrePosicionLookAt * glm::vec4(posicionCamara, 1);
    }
}

/**
 * Para hacer el movimiento de camara orbit
 * @param antihorario True si queremos girar antihorario o false si queremos ir horario
 */
void IGV::Camara::rotarSobreLookAtEjeY(bool antihorario) {
    if(antihorario){
        glm::mat4 rotacionSobrePosicionLookAt = glm::translate(lookAt) * glm::rotate(glm::radians(10.0f), glm::vec3(0,1,0)) * glm::translate(-lookAt);
        posicionCamara = rotacionSobrePosicionLookAt * glm::vec4(posicionCamara, 1);
    }else{
        glm::mat4 rotacionSobrePosicionLookAt = glm::translate(lookAt) * glm::rotate(glm::radians(-10.0f), glm::vec3(0,1,0)) * glm::translate(-lookAt);
        posicionCamara = rotacionSobrePosicionLookAt * glm::vec4(posicionCamara, 1);
    }
}

/**
 * Metodo para hacer zoom con la camara
 * @param positivo true si aumentamos el angulo de vision, false si lo disminuimos
 */
void IGV::Camara::zoom(bool positivo) {
    if(positivo){
        angulo += 5.0;
    }else{
        if((angulo - 5) > 0){
            angulo -= 5.0;
        }
    }
}

/**
 * Metodo para desplazar sobre el ejeY la camara
 * @param desplazamiento El desplazamiento
 */
void IGV::Camara::desplazarSobreEjeY(float desplazamiento) {
        posicionCamara[Y] += desplazamiento;
}
