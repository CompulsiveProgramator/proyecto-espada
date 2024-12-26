//
// Created by secre on 23/12/2024.
//

#ifndef PROYECTO_ESPADA_VENTANAGESTION_H
#define PROYECTO_ESPADA_VENTANAGESTION_H

#include <iostream>
#include "Ventana.h"
#include "../Renderer.h"
#include "submenus/MenuTransformaciones.h"
#include "submenus/MenuCamara.h"
#include "submenus/MenuMaterial.h"
#include "submenus/MenuIluminacion.h"

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
        MenuTransformaciones menuTransformaciones; // El menu para aplicar transformaciones al modelo
        MenuCamara menuCamara;
        MenuMaterial menuMaterial;
        MenuIluminacion menuIluminacion;

        void visualizarMenuModelo();
    public:
        void refrescarVentana() override;
        bool getSeguirRaton();
        TipoMovimientoCamara getTipoMovimientoCamara();
        void pasarMallaSeleccionada(Malla *pMalla);
        bool getModoSeleccion();
        void pasarLuzPuntual(FuenteLuz *luzP);

        void pasarLuzFocal(FuenteLuz *luzF);
    };
}

#endif //PROYECTO_ESPADA_VENTANAGESTION_H
