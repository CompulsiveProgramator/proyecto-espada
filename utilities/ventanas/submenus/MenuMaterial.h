//
// Created by secre on 25/12/2024.
//

#ifndef PROYECTO_ESPADA_MENUMATERIAL_H
#define PROYECTO_ESPADA_MENUMATERIAL_H

#include "Menu.h"
#include "../../modelo/Modelo.h"

namespace IGV{
    class MenuMaterial: public Menu{
    private:
        Malla *malla = nullptr;
        bool seleccionMalla = false; // Para activar/desactivar el modo de seleccion de malla con el doble click
//        glm::vec3 colorAmbiente;
        glm::vec3 colorDifuso;
        glm::vec3 colorEspecular;
        float exponenteEspecular;
    public:
        void refrescarMenu() override;
        void setMalla(Malla *malla1);
        bool getSeleccionMalla();
    };
}

#endif //PROYECTO_ESPADA_MENUMATERIAL_H
