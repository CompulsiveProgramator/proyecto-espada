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
    Modelo::Modelo():matrizModelado(glm::translate(glm::vec3(0,0,0))), mallas(), materiales(), texturas() {}

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
            std::vector<GLfloat> coordenadasTextura; // (U, V)
            std::vector<GLuint> indices;

            for(int j = 0 ; j < mesh->Vertices.size() ; j++)
            {
                posicionesVertices.push_back(mesh->Vertices[j].Position.X);
                posicionesVertices.push_back(mesh->Vertices[j].Position.Y);
                posicionesVertices.push_back(mesh->Vertices[j].Position.Z);

                normales.push_back(mesh->Vertices[j].Normal.X);
                normales.push_back(mesh->Vertices[j].Normal.Y);
                normales.push_back(mesh->Vertices[j].Normal.Z);

                coordenadasTextura.push_back(mesh->Vertices[j].TextureCoordinate.X);
                coordenadasTextura.push_back(mesh->Vertices[j].TextureCoordinate.Y);
            }

            for(int j = 0 ; j < mesh->Indices.size() ; j++)
            {
                indices.push_back(mesh->Indices[j]);
            }

            int posicionMaterial = buscaMaterial(mesh->MeshMaterial.name);
            if(posicionMaterial == -1)
            {
                glm::vec3 ka = glm::vec3(mesh->MeshMaterial.Ka.X, mesh->MeshMaterial.Ka.Y, mesh->MeshMaterial.Ka.Z);
                glm::vec3 kd = glm::vec3(mesh->MeshMaterial.Kd.X, mesh->MeshMaterial.Kd.Y, mesh->MeshMaterial.Kd.Z);
                glm::vec3 ks = glm::vec3(mesh->MeshMaterial.Ks.X, mesh->MeshMaterial.Ks.Y, mesh->MeshMaterial.Ks.Z);
                GLfloat exponenteEspecular = mesh->MeshMaterial.Ns;
                std::string nombreMat = mesh->MeshMaterial.name;
                Material material(ka, kd, ks, exponenteEspecular, nombreMat);
                materiales.push_back(material);
            }

            bool usaTextura;
            if(mesh->MeshMaterial.map_Kd.empty())
            {
                usaTextura = false;
            }else{
                usaTextura = true;
            }

            int posicionTextura;
            if(usaTextura)
            {
                posicionTextura = buscaTextura(mesh->MeshMaterial.map_Kd);
                if(posicionTextura == -1) // Si no se ha credo la textura, la creamos ;)
                {
                    Textura textura(mesh->MeshMaterial.map_Kd);
                    texturas.push_back(textura);
                }
            }

            posicionMaterial = buscaMaterial(mesh->MeshMaterial.name);
            if(usaTextura)
            {
                posicionTextura = buscaTextura(mesh->MeshMaterial.map_Kd);
                Malla nuevaMalla(posicionesVertices, normales, coordenadasTextura, indices, posicionMaterial, posicionTextura, this);
                mallas.push_back(nuevaMalla);
            }else{
                Malla nuevaMalla(posicionesVertices, normales, coordenadasTextura, indices, posicionMaterial, -1, this);
                mallas.push_back(nuevaMalla);
            }
        }
    }

    std::vector<Malla>* IGV::Modelo::getMallas() {
        return &mallas;
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

    void Modelo::aplicarEscaladoEjeZ(float proporcion) {
        matrizModelado = glm::scale(glm::vec3(1,1,proporcion)) * matrizModelado;
    }

    /**
     * Metodo auxiliar para que cada malla pueda consultar su material
     * @param i La posicionPuntual en el vector de materiales [0, n-1]
     * @return La direccion del material
     */
    Material *Modelo::getMaterial(int i) {
        return &materiales[i];
    }

    /**
     * Metodo auxiliar, para ver si un material leido ya esta creado o no
     * @param nombreMat El nombre del material a buscar
     * @return La posicionPuntual del material si se ha encontrado, o -1 si no existe
     */
    int Modelo::buscaMaterial(std::string nombreMat) {
        for(int i = 0 ; i < materiales.size() ; i++)
        {
            if(materiales[i].getNombreMaterial() == nombreMat)
            {
                return i;
            }
        }

        return -1;
    }

    /**
     * Metodo auxiliar, para ver si una textura ya ha sido creada o no
     * @param nombreTex El nombre de la textura a buscar en "texturas"
     * @return La posicion de la textura si se ha encontrado, o -1 si no existe
     */
    int Modelo::buscaTextura(std::string nombreTex) {
        for(int i = 0 ; i < texturas.size() ; i++)
        {
            if(texturas[i].getNombreTextura() == nombreTex)
            {
                return i;
            }
        }

        return -1;
    }

    /**
     * Metodo auxiliar para que cada malla pueda consultar su textura
     * @param i La posicion de la textura [0, n-1] n = numero de texturas
     * @return Un puntero a la textura
     */
    Textura *Modelo::getTextura(int i) {
        return &texturas[i];
    }
}
