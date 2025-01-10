//
// Created by secre on 23/12/2024.
//

#include "glad/glad.h"
#include "Modelo.h"
#include <utility>

/**
 * Constructor de la malla
 * @param pos Las posiciones de todos los vertices de la malla
 * @param norm Las normales de cada vertice
 * @param ind Los indices de los triangulos
 * @param mat La direccion del material de la malla
 */
IGV::Malla::Malla(std::vector<GLfloat> pos, std::vector<GLfloat> norm, std::vector<GLfloat> text, std::vector<GLuint> ind, int _indiceMaterial, int _indiceTextura, IGV::Modelo *_miModelo): indiceMaterial(_indiceMaterial), indiceTextura(_indiceTextura), miModelo(_miModelo){
    posicionesVertices = std::move(pos);
    normales = std::move(norm);
    coordenadasTextura = std::move(text);
    indices = std::move(ind);
    numIndices = indices.size();
    crearVao();
}

const std::vector<GLfloat> &IGV::Malla::getPosicionesVertices() const {
    return posicionesVertices;
}

const std::vector<GLuint> &IGV::Malla::getIndices() const {
    return indices;
}

const std::vector<GLfloat> &IGV::Malla::getNormales() const {
    return normales;
}

/**
 * Getter de las coordenadas de textura
 * @return
 */
std::vector<GLfloat> &IGV::Malla::getCoordenadasTextura() {
    return coordenadasTextura;
}

/**
 * Metodo para obtener el material de la malla
 * @return El material asignado a la malla, como puntero ;)
 */
IGV::Material *IGV::Malla::getMaterial() {
    return miModelo->getMaterial(indiceMaterial);
}

/**
 * Metodo que devuelve un puntero a la textura, o nullptr si no tiene
 * @return
 */
IGV::Textura *IGV::Malla::getTextura() {
    if(indiceTextura == -1)
    {
        return nullptr;
    }else{
        return miModelo->getTextura(indiceTextura);
    }
}

/**
 * Metodo auxiliar para crear el VAO, con el que podre pintar mi espada!!!
 */
void IGV::Malla::crearVao() {
    // Generamos los buffers de OpenGL vacios:
    glGenVertexArrays(1, &idVAO);
    glGenBuffers(1, &idVBOpos);
    glGenBuffers(1, &idVBOnormal);
    glGenBuffers(1, &idVBOtext);
    glGenBuffers(1, &idIBO);

    glBindVertexArray(idVAO);

    glBindBuffer(GL_ARRAY_BUFFER, idVBOpos);
    glBufferData(GL_ARRAY_BUFFER, posicionesVertices.size() * sizeof(GLfloat), posicionesVertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0); //Esto es para decir que el contenido que vamos a leer para este VBO ira al "layout = 0" de nuestro vertex shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(GLfloat), nullptr); // index es para activar el layout

    glBindBuffer(GL_ARRAY_BUFFER, idVBOnormal);
    glBufferData(GL_ARRAY_BUFFER, normales.size() * sizeof(GLfloat), normales.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, idVBOtext);
    glBufferData(GL_ARRAY_BUFFER, coordenadasTextura.size() * sizeof(GLfloat), coordenadasTextura.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    //ToDo Ver porque salta el error 1280 de OpenGL
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << err << std::endl;
    }
}

/**
 * Metodo para obtener el id del VAO de la malla
 * @return El id del VAO
 */
GLuint IGV::Malla::getIdVao() {
    return idVAO;
}

/**
 * Metodo para obtener el id del IBO de la malla
 * @return El id del IBO
 */
GLuint IGV::Malla::getIdIbo() {
    return idIBO;
}

/**
 * Destructor de la clase
 */
IGV::Malla::~Malla() {
    std::cout << "Se destruye la malla" << "\n";
    glDeleteVertexArrays(1, &idVAO);
    glDeleteBuffers(1, &idIBO);
    glDeleteBuffers(1, &idVBOpos);
    glDeleteBuffers(1, &idVBOnormal);
}

unsigned long IGV::Malla::getNumIndices() {
    return numIndices;
}
