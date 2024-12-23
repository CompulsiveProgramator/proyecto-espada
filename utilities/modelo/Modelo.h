//
// Created by secre on 23/12/2024.
//

#ifndef PROYECTO_ESPADA_MODELO_H
#define PROYECTO_ESPADA_MODELO_H

#include <iostream>
#include <vector>
#include "Malla.h"

namespace IGV{
    /**
     * Clase que contiene un modelo 3D, con sus mallas de triangulos y materiales
     */
    class Modelo {
    private:
        std::vector<Malla> mallas; /// Las mallas de triangulos
    public:
        Modelo(std::string rutaArchivo);
        std::vector<Malla> getMallas();
    };
}



#endif //PROYECTO_ESPADA_MODELO_H
