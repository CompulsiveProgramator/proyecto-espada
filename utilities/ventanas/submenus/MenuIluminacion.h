//
// Created by secre on 26/12/2024.
//

#ifndef PROYECTO_ESPADA_MENUILUMINACION_H
#define PROYECTO_ESPADA_MENUILUMINACION_H

#include "Menu.h"
#include "../../FuenteLuz.h"

namespace IGV{
    class MenuIluminacion: public Menu {
    private:
        FuenteLuz *luzPuntual = nullptr;
        glm::vec3 posicion;
    public:
        void refrescarMenu() override;

        void pasarLuzPuntual(FuenteLuz *pLuz);
    };
}

#endif //PROYECTO_ESPADA_MENUILUMINACION_H
