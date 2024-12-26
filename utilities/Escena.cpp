//
// Created by secre on 22/12/2024.
//

#include <glm/gtc/type_ptr.hpp>
#include "Escena.h"

/**
 * Metodo para pintar los ejes X,Y,Z
 */
void IGV::Escena::pintar_ejes() {
    GLfloat rojo[] = { 1,0,0,1.0 };
    GLfloat verde[] = { 0, 1, 0, 1.0 };
    GLfloat azul[] = { 0, 0, 1, 1.0 };
    GLfloat negro[] = { 0, 0, 0, 1.0};

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

    glMaterialfv ( GL_FRONT, GL_EMISSION, negro );
}

/**
 * Constructor de la escena
 */
IGV::Escena::Escena() {
    luzPuntual = new FuenteLuz(0,
                               igvPunto3D(1,1,1),
                               Color(0.1, 0.1, 0.1, 1.0),
                               Color(0.6, 0.6, 0.6, 1),
                               Color(1, 1, 1, 1),
                               1,
                               0,
                               0
    );

    //modelo = new Modelo();
}

/**
 * Destructor de la escena
 */
IGV::Escena::~Escena() {
    delete modelo;
    delete luzPuntual;
}

/**
 * Metodo para visualizar la escena
 */
void IGV::Escena::visualizar() {
    glPushMatrix();

    seleccionMalla();

    if( ejes )
    {
        pintar_ejes();
    }

    if( luzPuntual )
    {
        luzPuntual->aplicar();
    }

    if ( modelo )
    {
        glm::mat4 matModelado = modelo->getMatrizModelado();
        glMatrixMode(GL_MODELVIEW);
        // A la matriz de vision, proyeccion de la camara, se le multiplica ( por la derecha ;3 ) la matriz de modelado del modelo
        glMultMatrixf(glm::value_ptr(matModelado));

        std::vector<IGV::Malla> *mallas = modelo->getMallas();
        for(int i = 0 ; i < mallas->size() ; i++)
        {
            std::vector<GLfloat> pos = mallas->data()[i].getPosicionesVertices();
            std::vector<GLfloat> norm = mallas->data()[i].getNormales();
            std::vector<GLuint> indices = mallas->data()[i].getIndices();
            Material *material = mallas->data()[i].getMaterial();

            GLfloat Es = material->getEs();

             //ToDo Ver porque no se actualiza el Kd en este material desde la GUI, porque estoy usando referencias!!!

            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &material->getKd()[0]);
            glMaterialfv(GL_FRONT, GL_SPECULAR, &material->getKs()[0]);
            glMaterialfv(GL_FRONT, GL_SHININESS, &Es);
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, pos.data());
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, 0, norm.data());
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
        }
    }

    glPopMatrix();
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

void IGV::Escena::agregarModelo(std::string rutaArchivo) {
    delete modelo;
    modelo = new Modelo(rutaArchivo);
    rutaModelo = rutaArchivo;
}

IGV::Modelo& IGV::Escena::getModelo() {
    return *modelo;
}

/**
 * Metodo para eliminar el modelo actual, si existe
 */
void IGV::Escena::eliminarModelo() {
    delete modelo;
    modelo = nullptr;
    rutaModelo = "";
}

/**
 * Metodo para consultar la ruta al modelo cargado en escena ;)
 * @return La ruta al modelo cargado en escena, desde la raiz del proyecto, o "" si no hay un modelo cargado
 */
std::string IGV::Escena::getRutaModelo(){
    return rutaModelo;
}

/**
 * Metodo para obtener los colores, con los que se pintara cada malla en el buffer de color
 * @param size El numero de mallas
 * @return Un vector con un color para cada malla
 */
std::vector<glm::vec3> IGV::Escena::creaVectorColores(unsigned long long int size) {
    std::vector<glm::vec3> colores;

    for(int i = 0 ; i < size ; i++)
    {
        float color = float(i)/float(size) + 0.1f;
        colores.push_back(glm::vec3(color, 0, color));
    }

    return colores;
}

void IGV::Escena::comprobarSiHayMalla() {
    consultarMalla = true;
}

/**
 * Metodo auxiliar para comprobar si dos flotantes son iguales
 * @param a
 * @param b
 * @return
 */
bool IGV::Escena::flotantesIguales(float a, float b) {
    return ( abs(a-b) < 0.1 );
}

/**
 * Metodo auxiliar para comprobar si se ha seleccionado una malla con el raton, usando un buffer de color
 */
void IGV::Escena::seleccionMalla() {
// Si se quiere comprobar si hay una malla donde se ha clicado:
    if ( modelo && consultarMalla)
    {
        glDisable ( GL_LIGHTING ); // desactiva la iluminaci�n de la escena
        // Se desactiva la luz para el buffer de color

        glm::mat4 matModelado = modelo->getMatrizModelado();
        glMatrixMode(GL_MODELVIEW);
        // A la matriz de vision, proyeccion de la camara, se le multiplica ( por la derecha ;3 ) la matriz de modelado del modelo
        glMultMatrixf(glm::value_ptr(matModelado));

        std::vector<IGV::Malla> *mallas = modelo->getMallas();
        std::vector<glm::vec3> colores = creaVectorColores(mallas->size());
        for(int i = 0 ; i < mallas->size() ; i++)
        {
            std::vector<GLfloat> pos = mallas->data()[i].getPosicionesVertices();
            std::vector<GLuint> indices = mallas->data()[i].getIndices();

            float colorNegro[3] = {0,0,0};
            glMaterialfv(GL_FRONT, GL_EMISSION, &colores[i][0]);
            glColor3fv(&colores[i][0]);
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, pos.data());
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
            glDisableClientState(GL_VERTEX_ARRAY);
            glMaterialfv(GL_FRONT, GL_EMISSION, colorNegro); /// Importante desactivar el emision!!!
            glColor3fv(colorNegro);
        }

        float colorLeido[3];
        glReadPixels(xpos, ypos, 1, 1, GL_RGB, GL_FLOAT, colorLeido);

        bool encontrado = false;
        for(int i = 0 ; i < mallas->size(); i++)
        {
            if( flotantesIguales(colorLeido[0], colores[i][0]) && flotantesIguales(colorLeido[1], colores[i][1]) && flotantesIguales(colorLeido[2], colores[i][2]))
            {
                mallaElegida = &mallas->data()[i];
                encontrado = true;
            }
        }
        if(!encontrado)
        {
            mallaElegida = nullptr;
        }
        consultarMalla = false;

        glEnable ( GL_LIGHTING ); // desactiva la iluminaci�n de la escena
    }
}

/**
 * Getter para obtener la malla elegida si la hay
 * @return La malla elegida, o nullptr si no hay ninguna
 */
IGV::Malla *IGV::Escena::getMallaElegida() {
    return mallaElegida;
}

/**
 * Metodo para notificar a la escena donde se encuentra el cursor en la ventana
 * @param x
 * @param y
 */
void IGV::Escena::pasarPosicionCursor(int x, int y) {
    xpos = x;
    ypos = y;
}

void IGV::Escena::deseleccionarMalla() {
    mallaElegida = nullptr;
}

