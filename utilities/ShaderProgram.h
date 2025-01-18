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

        void creaShaderProgram(std::string &nombreShader);
    public:
        ShaderProgram(std::string nombreShader);
        void ejecutarShaderProgram(Modelo *modelo, Camara *camara, FuenteLuz *luzPuntual);

        //Para compilar un shader al completo:
        void crearSP(GLuint &handler);
        std::string leerShaderSource(std::string filename);
        GLuint creaShaderObject(GLenum shaderType);
        void compilarShaderObject(std::string shaderSourceString, GLuint shaderHandler, GLenum shaderType);
        void enlazarSP(GLuint handler, std::string filename);

        void pasarUniformsLuzPuntual(FuenteLuz *luzPuntual, glm::mat4 matrizV);

        void pasarUniformsMaterial(Material *pMaterial);
    };

} // IGV

#endif //PROYECTO_ESPADA_SHADERPROGRAM_H
