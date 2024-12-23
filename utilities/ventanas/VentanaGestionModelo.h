//
// Created by secre on 23/12/2024.
//

#ifndef PROYECTO_ESPADA_VENTANAGESTIONMODELO_H
#define PROYECTO_ESPADA_VENTANAGESTIONMODELO_H

#include "Ventana.h"

namespace IGV{
    /**
     * Ventana para gestionar el modelo a visualizar en la escena!
     */
    class VentanaGestionModelo: public Ventana {
    public:
        void refrescarVentana() override;
    };
}

#endif //PROYECTO_ESPADA_VENTANAGESTIONMODELO_H
