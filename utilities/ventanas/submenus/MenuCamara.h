//
// Created by secre on 24/12/2024.
//

#ifndef PROYECTO_ESPADA_MENUCAMARA_H
#define PROYECTO_ESPADA_MENUCAMARA_H

#include "Menu.h"

/**
 * Enum para elegir el tipo de movimiento de la camara
 */
enum TipoMovimientoCamara{
    ORBIT,
    ZOOM,
    CRANE
};

namespace IGV{
    /**
     * Menu para seleccionar el tipo de movimiento de la camara
     */
    class MenuCamara: public Menu {
    private:
        TipoMovimientoCamara tipoMovimientoCamara = ORBIT;
        bool seguirRaton = false;

    public:
        void refrescarMenu() override;
        bool getSeguirRaton();
        TipoMovimientoCamara getTipoMovimiento();
    };
}



#endif //PROYECTO_ESPADA_MENUCAMARA_H
