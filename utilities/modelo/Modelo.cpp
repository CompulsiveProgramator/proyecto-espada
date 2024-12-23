//
// Created by secre on 23/12/2024.
//

#include "OBJ_Loader.h"
#include "Modelo.h"

namespace IGV
{
    /**
    * Constructor del modelo
    * @param rutaArchivo La ruta hacia el archivo OBJ
    */
    IGV::Modelo::Modelo(std::string rutaArchivo) {
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

            std::cout << mesh->MeshMaterial.Ka.X << " " << mesh->MeshMaterial.Ka.Y << " " << mesh->MeshMaterial.Ka.Z << "\n";
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
}
