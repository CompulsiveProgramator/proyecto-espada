//
// Created by secre on 22/12/2024.
//

#include "Escena.h"

/**
 * Metodo para pintar los ejes X,Y,Z
 */
void IGV::Escena::pintar_ejes() {
    GLfloat rojo[] = { 1,0,0,1.0 };
    GLfloat verde[] = { 0, 1, 0, 1.0 };
    GLfloat azul[] = { 0, 0, 1, 1.0 };

    glMaterialfv ( GL_FRONT, GL_EMISSION, rojo );
    glBegin ( GL_LINES );
    glVertex3f ( 1000, 0, 0 );
    glVertex3f ( -1000, 0, 0 );
    glEnd ();

    glMaterialfv ( GL_FRONT, GL_EMISSION, verde );
    glBegin ( GL_LINES );
    glVertex3f ( 0, 1000, 0 );
    glVertex3f ( 0, -1000, 0 );
    glEnd ();

    glMaterialfv ( GL_FRONT, GL_EMISSION, azul );
    glBegin ( GL_LINES );
    glVertex3f ( 0, 0, 1000 );
    glVertex3f ( 0, 0, -1000 );
    glEnd ();
}

/**
 * Constructor de la escena
 */
IGV::Escena::Escena() {

}

/**
 * Destructor de la escena
 */
IGV::Escena::~Escena() {

}

/**
 * Metodo para visualizar la escena
 */
void IGV::Escena::visualizar() {
    glPushMatrix();

    if( ejes )
    {
        pintar_ejes();
    }

    glutWireTeapot(0.1);
}

/**
 * Setter del atributo ejes
 * @param valor El valor True o False
 */
void IGV::Escena::setEjes(bool valor) {
    ejes = valor;
}

/**
 * Getter del atributo ejes
 * @return El valor de ejes
 */
bool IGV::Escena::getEjes() {
    return ejes;
}
