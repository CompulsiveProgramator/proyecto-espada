//
// Created by secre on 07/01/2025.
//

#include <fstream>
#include <sstream>
#include <utility>
#include "../glad/include/glad/glad.h"
#include "ShaderProgram.h"

namespace IGV {
    /**
     * Constructor por defecto del shader program
     */
    ShaderProgram::ShaderProgram(std::string nombreShader) {
        creaShaderProgram(nombreShader);
    }

    /**
     * Métoodo para crear, compilar y enlazar el shader program
     * Con comprobacion de errores
     */
    void ShaderProgram::creaShaderProgram(std::string &nombreShader) {
        try{
            std::string contenido;
            std::string filename = nombreShader;
            GLuint vertexShaderId, fragmentShaderId;
            crearSP(idSP); //Fase 1

            vertexShaderId = creaShaderObject(GL_VERTEX_SHADER);
            contenido = leerShaderSource("../shader_files/"+filename+"-vs.glsl");
            compilarShaderObject(contenido, vertexShaderId, GL_VERTEX_SHADER);

            fragmentShaderId = creaShaderObject(GL_FRAGMENT_SHADER);
            contenido = leerShaderSource("../shader_files/"+filename+"-fs.glsl");
            compilarShaderObject(contenido, fragmentShaderId, GL_FRAGMENT_SHADER);

            glAttachShader(idSP, vertexShaderId);
            glAttachShader(idSP, fragmentShaderId);
            enlazarSP(idSP, filename);
        }
        catch(std::string &e)
        {
            std::cout << e << "\n";
        }
    }

/**
 * 1a fase del compilado del shader program
 * Crear el SP vacio
 * @return
 */
    void ShaderProgram::crearSP(GLuint &handler) {
        handler = glCreateProgram();
        if(handler == 0){
            throw std::string("Cannot create shader program\n");
        }
    }

/**
 * 2 fase del compilado del shader program
 * Abrir y leer el shader source
 * @param filename El nombre del archivo que queremos leer (pag03)
 * @return El string con el contenido del archivo
 */
    std::string ShaderProgram::leerShaderSource(std::string filename) {
        std::ifstream shaderSourceFile(filename);

        if(!shaderSourceFile.is_open()){
            throw std::string("Cannot open shader source file\n");
        }

        std::stringstream shaderSourceStream;
        shaderSourceStream << shaderSourceFile.rdbuf();
        std::string shaderSourceString = shaderSourceStream.str();

        shaderSourceFile.close();

        return shaderSourceString;
    }

/**
 * 3 fase del compilado del shader program
 * Crear el shader object
 * @param shaderType El tipo de objeto (vertex o fragment)
 * @return El id del objeto
 */
    GLuint ShaderProgram::creaShaderObject(GLenum shaderType) {
        GLuint shaderHandler = glCreateShader(shaderType);
        if(shaderHandler == 0){
            throw std::string("Cannot create shader object\n");
        }

        return shaderHandler;
    }

/**
 * 4 fase del compilado del shader program
 * Compilar el shader object
 * @param shaderSourceString El string con el archivo
 * @param shaderHandler El id del objeto
 * @param shaderType El tipo de objeto
 */
    void ShaderProgram::compilarShaderObject(std::string shaderSourceString, GLuint shaderHandler, GLenum shaderType) {
        const char * shaderSourceCString = shaderSourceString.c_str();
        glShaderSource(shaderHandler, 1, &shaderSourceCString, NULL);

        // - Compilar el shader object —————————————————————————
        glCompileShader(shaderHandler);
        GLint compileResult;
        glGetShaderiv(shaderHandler, GL_COMPILE_STATUS, &compileResult);
        if (compileResult == GL_FALSE) {
            GLint logLen = 0;
            std::string logString = "";
            glGetShaderiv(shaderHandler, GL_INFO_LOG_LENGTH, &logLen);
            if (logLen > 0) {
                char * cLogString = new char[logLen];
                GLint written = 0;
                glGetShaderInfoLog(shaderHandler, logLen, &written, cLogString);
                logString.assign(cLogString);
                delete[] cLogString;
                std::stringstream ss;
                ss << shaderType;
                throw std::string("Cannot compile shader " + ss.str() + logString + "\n");
            }
        }
    }


/**
 * 5 fase del compilado del shader program
 * Enlazar el shader program
 * @param handler El id del shader program
 * @param filename El nombre del shader
 */
    void ShaderProgram::enlazarSP(GLuint handler, std::string filename)
    {
        glLinkProgram(handler);
        GLint linkSuccess = 0;
        glGetProgramiv(handler, GL_LINK_STATUS, &linkSuccess);
        if (linkSuccess == GL_FALSE) {
            std::string logString = "";
            GLint logLen = 0;
            glGetProgramiv(handler, GL_INFO_LOG_LENGTH, &logLen);
            if (logLen > 0) {
                char * cLogString = new char[logLen];
                GLint written = 0;
                glGetProgramInfoLog(handler, logLen, &written, cLogString);
                logString.assign(cLogString);
                delete[] cLogString;
                throw std::string("Cannot link shader" + filename + "\n" + logString + "\n");
            }
        }
    }

    /**
     * Metodo para ejecutar el shader program con el modelo que se le pase, la camara y las luces respectivas
     * @param modelo El modelo a visualizar !
     * @param camara La camara con la que se ve el mundo
     * @param luzPuntual El vector con todas las luces, que iluminan al modelo
     */
    void ShaderProgram::ejecutarShaderProgram(Modelo *modelo, Camara *camara, FuenteLuz *luzPuntual) {
        glm::mat4 matrizModelado = modelo->getMatrizModelado();
        glm::mat4 matrizModeladoVision = camara->getMatrizVision() * matrizModelado;
        glm::mat4 matrizModeladoVisionPerspectiva = camara->getMatrizPerspectiva() * matrizModeladoVision;

        int pos;
        pos = glGetUniformLocation(idSP, "matrizMV");
        if(pos != -1)
        {
            glUniformMatrix4fv(pos, 1, GL_FALSE, &matrizModeladoVision[0][0]);
        }

        pos = glGetUniformLocation(idSP, "matrizMVP");
        if(pos != -1)
        {
            glUniformMatrix4fv(pos, 1, GL_FALSE, &matrizModeladoVisionPerspectiva[0][0]);
        }

        // Pasar uniforms de la luz puntual
        pasarUniformsLuzPuntual(luzPuntual, camara->getMatrizVision());

        try{
            glUseProgram(idSP);

            std::vector<Malla> *mallas = modelo->getMallas();
            for(int i = 0 ; i < mallas->size() ; i++)
            {
                pasarUniformsMaterial((*mallas)[i].getMaterial());
                if((*mallas)[i].getTextura())
                {
                    (*mallas)[i].getTextura()->aplicar(); // aqui se carga la imagen de textura en memoria
                    GLint posicion = glGetUniformLocation ( idSP, "muestreador" );
                    glUniform1i ( posicion, 0 );
                    glActiveTexture ( GL_TEXTURE0 ); // Activamos la unidad de textura 0, y le asociamos la textura que habíamos configurado
                }


                glBindVertexArray((*mallas)[i].getIdVao());
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*mallas)[i].getIdIbo());
                glDrawElements(GL_TRIANGLES, (*mallas)[i].getNumIndices(), GL_UNSIGNED_INT, nullptr);
            }
        }catch(std::exception &e)
        {
            std::cout << e.what();
        }
    }

    /**
     * Para pasarle al shader program, los uniforms de la luz
     */
    void ShaderProgram::pasarUniformsLuzPuntual(FuenteLuz *luzPuntual, glm::mat4 matrizV) {
        GLuint pos;
        pos = glGetUniformLocation(idSP, "posicionLuz");
        if(pos)
        {
            glm::vec3 posicionLuzEspacioVision = glm::vec3(matrizV * glm::vec4(luzPuntual->getPosicion(), 1));
            glUniform3fv(pos, 1, &posicionLuzEspacioVision[0]);
        }

        if(luzPuntual->esta_encendida())
        {
            pos = glGetUniformLocation(idSP, "Id");
            if(pos)
            {
                glUniform3fv(pos, 1, &luzPuntual->getDifuso()[0]);
            }

            pos = glGetUniformLocation(idSP, "Is");
            if(pos)
            {
                glUniform3fv(pos, 1, &luzPuntual->getEspecular()[0]);
            }
        }else{
            glm::vec3 ceros = {0,0,0};
            pos = glGetUniformLocation(idSP, "Id");
            if(pos)
            {
                glUniform3fv(pos, 1, &ceros[0]);
            }

            pos = glGetUniformLocation(idSP, "Is");
            if(pos)
            {
                glUniform3fv(pos, 1, &ceros[0]);
            }
        }

    }

    /**
     * Para pasarle los uniforms del material, al shader program
     * ( Color difuso, especular, exponente de phong, ... )
     * @param pMaterial Un puntero al material
     */
    void ShaderProgram::pasarUniformsMaterial(Material *pMaterial) {
        GLuint pos;
        pos = glGetUniformLocation(idSP, "Ks");
        if(pos)
        {
            glUniform3fv(pos, 1, &pMaterial->getKs()[0]);
        }

        pos = glGetUniformLocation(idSP, "Kd");
        if(pos)
        {
            glUniform3fv(pos, 1, &pMaterial->getKd()[0]);
        }
    }
} // IGV