//
// Created by secre on 07/01/2025.
//

#ifndef PROYECTO_ESPADA_SHADERPROGRAM_H
#define PROYECTO_ESPADA_SHADERPROGRAM_H

#define GLM_ENABLE_EXPERIMENTAL

#include "Camara.h"
#include "modelo/Modelo.h"
#include "FuenteLuz.h"

namespace IGV {
    /**
     * Clase que contiene al Shader Program, que nos permite programar que se hace en el pipeline de rendering ;)
     */
    class ShaderProgram {
    private:
        GLuint idSP = 0; // El id del shader program

        void creaShaderProgram();
    public:
        ShaderProgram();
        void ejecutarShaderProgram(Modelo *modelo, Camara *camara, std::vector<FuenteLuz*> luces);

        //Para compilar un shader al completo:
        void crearSP(GLuint &handler);
        std::string leerShaderSource(std::string filename);
        GLuint creaShaderObject(GLenum shaderType);
        void compilarShaderObject(std::string shaderSourceString, GLuint shaderHandler, GLenum shaderType);
        void enlazarSP(GLuint handler, std::string filename);
    };

} // IGV

#endif //PROYECTO_ESPADA_SHADERPROGRAM_H
