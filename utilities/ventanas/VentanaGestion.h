//
// Created by secre on 23/12/2024.
//

#ifndef PROYECTO_ESPADA_VENTANAGESTION_H
#define PROYECTO_ESPADA_VENTANAGESTION_H

#include <iostream>
#include "Ventana.h"
#include "../Renderer.h"

namespace IGV{
    /**
     * Ventana para gestionar la aplicacion entera, incluyendo:
     * - Modelo a visualizar
     * - Transformaciones al modelo
     * - Camara
     * - Material de cada malla de triangulos
     * - Iluminacion
     * - Si se ve la textura del modelo o no
     * - Modo de visualizacion ( Alambre o Solido )
     */
    class VentanaGestion: public Ventana {
    private:
        std::string nombreModelo;

        void visualizarMenuModelo();
        void visualizarMenuTransformaciones();
        void visualizarMenuCamara();
    public:
        void refrescarVentana() override;
    };
}

#endif //PROYECTO_ESPADA_VENTANAGESTION_H
