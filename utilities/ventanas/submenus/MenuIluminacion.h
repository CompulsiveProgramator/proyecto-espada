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
        glm::vec3 posicionPuntual;
        bool encendidaPuntual = true;

        FuenteLuz *luzFocal = nullptr;
        glm::vec3 posicionFocal;
        bool encendidaFocal = true;
    public:
        void refrescarMenu() override;
        void pasarLuzPuntual(FuenteLuz *pLuz);
        void pasarLuzFocal(FuenteLuz *pLuz);
    };
}

#endif //PROYECTO_ESPADA_MENUILUMINACION_H
