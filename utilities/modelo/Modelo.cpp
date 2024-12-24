//
// Created by secre on 23/12/2024.
//

#include "OBJ_Loader.h"
#include "Modelo.h"

namespace IGV
{
    /**
     * Constructor por defecto, que crea un modelo completamente vacio
     */
    Modelo::Modelo():matrizModelado(glm::translate(glm::vec3(0,0,0))), mallas() {}

    /**
    * Constructor del modelo
    * @param rutaArchivo La ruta hacia el archivo OBJ
    */
    IGV::Modelo::Modelo(std::string rutaArchivo):matrizModelado(glm::translate(glm::vec3(0,0,0))) {
        objl::Loader loader;

        if(!loader.LoadFile(rutaArchivo))
        {
            std::cout << "Error al leer el archivo del modelo" << std::endl;
        }

        /*
         * Recorremos cada malla y obtenemos todos sus datos, y los almacenamos para usarlos para pintarla luego
         */
        for(int i = 0 ; i < loader.LoadedMeshes.size() ; i++)
        {
            objl::Mesh *mesh = &loader.LoadedMeshes[i];

            std::vector<GLfloat> posicionesVertices;
            std::vector<GLfloat> normales;
            std::vector<GLuint> indices;

            for(int j = 0 ; j < mesh->Vertices.size() ; j++)
            {
                posicionesVertices.push_back(mesh->Vertices[j].Position.X);
                posicionesVertices.push_back(mesh->Vertices[j].Position.Y);
                posicionesVertices.push_back(mesh->Vertices[j].Position.Z);

                normales.push_back(mesh->Vertices[j].Normal.X);
                normales.push_back(mesh->Vertices[j].Normal.Y);
                normales.push_back(mesh->Vertices[j].Normal.Z);
            }

            for(int j = 0 ; j < mesh->Indices.size() ; j++)
            {
                indices.push_back(mesh->Indices[j]);
            }

            glm::vec3 ka = glm::vec3(mesh->MeshMaterial.Ka.X, mesh->MeshMaterial.Ka.Y, mesh->MeshMaterial.Ka.Z);
            glm::vec3 kd = glm::vec3(mesh->MeshMaterial.Kd.X, mesh->MeshMaterial.Kd.Y, mesh->MeshMaterial.Kd.Z);
            glm::vec3 ks = glm::vec3(mesh->MeshMaterial.Ks.X, mesh->MeshMaterial.Ks.Y, mesh->MeshMaterial.Ks.Z);
            GLfloat exponenteEspecular = mesh->MeshMaterial.Ns;
            Material material(ka, kd, ks, exponenteEspecular);

            Malla nuevaMalla(posicionesVertices, normales, indices, material);
            mallas.push_back(nuevaMalla);
        }
    }

    std::vector<Malla> IGV::Modelo::getMallas() {
        return mallas;
    }

    void Modelo::escalarUniforme(float i) {
        matrizModelado = glm::scale(glm::vec3(i,i,i)) * matrizModelado;
    }

    /**
     * Getter de la matriz de modelado del modelo
     * @return
     */
    glm::mat4 Modelo::getMatrizModelado() {
        return matrizModelado;
    }

    /**
     * Metodo para trasladar el modelo sobre el eje Y
     * @param distancia La distancia a trasladar
     */
    void Modelo::aplicarTraslacionEjeY(float distancia) {
        matrizModelado = glm::translate(glm::vec3(0, distancia, 0)) * matrizModelado;
    }

    /**
     * Metodo para trasladar el modelo sobre el eje X
     * @param distancia La distancia a trasladar
     */
    void Modelo::aplicarTraslacionEjeX(float distancia) {
        matrizModelado = glm::translate(glm::vec3(distancia, 0, 0)) * matrizModelado;
    }

    /**
     * Metodo para trasladar el modelo sobre el eje Z
     * @param distancia La distancia a trasladar
     */
    void Modelo::aplicarTraslacionEjeZ(float distancia) {
        matrizModelado = glm::translate(glm::vec3(0, 0, distancia)) * matrizModelado;
    }

    /**
     * Metodo para rotar el modelo respecto del eje X !!!
     * @param angulo El angulo en grados sexagesimales [-360, 360]
     */
    void Modelo::aplicarRotacionEjeX(float angulo) {
        matrizModelado = glm::rotate(glm::radians(angulo), glm::vec3(1, 0, 0)) * matrizModelado;
    }

    void Modelo::aplicarRotacionEjeY(float angulo) {
        matrizModelado = glm::rotate(glm::radians(angulo), glm::vec3(0, 1, 0)) * matrizModelado;
    }

    void Modelo::aplicarRotacionEjeZ(float angulo) {
        matrizModelado = glm::rotate(glm::radians(angulo), glm::vec3(0, 0, 1)) * matrizModelado;
    }

    /**
     * Metodo para devolver al origen al modelo ;)
     */
    void Modelo::resetearMatrizModelado() {
        matrizModelado = glm::translate(glm::vec3(0,0,0));
    }

    /**
     * Metodo para aplicar un escalado al modelo sobre el eje X
     * @param proporcion La proporcion de escalada ( Ej; 2 -> Duplicamos el tamaño en X , 0.5 -> Dividimos a la mitad el tamaño en X , 1 -> Se queda igual !!!
     */
    void Modelo::aplicarEscaladoEjeX(float proporcion) {
        matrizModelado = glm::scale(glm::vec3(proporcion, 1, 1)) * matrizModelado;
    }

    /**
     * Metodo para aplicar un escalado al modelo sobre el eje Y
     * @param proporcion
     */
    void Modelo::aplicarEscaladoEjeY(float proporcion) {
        matrizModelado = glm::scale(glm::vec3(1, proporcion, 1)) * matrizModelado;
    }
}
