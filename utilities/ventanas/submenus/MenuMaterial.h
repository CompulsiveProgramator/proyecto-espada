//
// Created by secre on 25/12/2024.
//

#ifndef PROYECTO_ESPADA_MENUMATERIAL_H
#define PROYECTO_ESPADA_MENUMATERIAL_H

#include "Menu.h"
#include "../../modelo/Malla.h"

namespace IGV{
    class MenuMaterial: public Menu{
    private:
        Malla *malla = nullptr;
        bool seleccionMalla = false; // Para activar/desactivar el modo de seleccion de malla con el doble click
    public:
        void refrescarMenu() override;
        void setMalla(Malla *malla1);
        bool getSeleccionMalla();
    };
}

#endif //PROYECTO_ESPADA_MENUMATERIAL_H
