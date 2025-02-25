//
// Created by secre on 22/12/2024.
//

#ifndef PROYECTO_ESPADA_GUI_H
#define PROYECTO_ESPADA_GUI_H

#include "ventanas/VentanaGestion.h"

namespace IGV{
    /**
     * Clase para pintar la GUI ( Graphical User Interface ) de la app
     * Sigue el patron Singleton
     */
    class GUI {
    private:
        static GUI *instancia;
        GUI();

        VentanaGestion ventanaGestion;
    public:
        static GUI& getInstancia();
        void refrescar();
        bool getSeguirMovimientoRaton();
        TipoMovimientoCamara getTipoMovimientoCamara();
        bool getModoSeleccion();
        void pasarMallaSeleccionada(Malla *Malla);
        void pasarLuzPuntual(FuenteLuz *luzP);
        void pasarLuzFocal(FuenteLuz *luzF);
        void pasarModelo(Modelo *modelo);
    };
}

#endif //PROYECTO_ESPADA_GUI_H
