//
// Created by secre on 22/12/2024.
//

#include "GUI.h"

namespace IGV{
    GUI* GUI::instancia = nullptr;

    /**
     * Constructor de la GUI
     */
    GUI::GUI(): ventanaGestion() {

    }

    /**
     * Metodo para obtener la instancia
     * @return
     */
    GUI &GUI::getInstancia() {
        if(instancia == nullptr)
        {
            instancia = new GUI();
        }

        return *instancia;
    }

    /**
     * Metodo que pinta la ventana la GUI
     */
    void GUI::refrescar() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ventanaGestion.refrescarVentana();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );
    }

    /**
     * Para consultar a la ventana de gestion, si tenemos que seguir el movimiento del raton
     * @return
     */
    bool GUI::getSeguirMovimientoRaton() {
        return ventanaGestion.getSeguirRaton();
    }

    /**
     * Metodo para obtener el tipo de movimiento de camara, seleccionado en la GUI
     * @return El tipo de movimiento ( Ej: Orbit )
     */
    TipoMovimientoCamara GUI::getTipoMovimientoCamara() {
        return ventanaGestion.getTipoMovimientoCamara();
    }

    /**
     * Metodo para pasarle a la GUI la malla seleccionada
     * @param pMalla La malla seleccionada
     */
    void GUI::pasarMallaSeleccionada(Malla *pMalla) {
        ventanaGestion.pasarMallaSeleccionada(pMalla);
    }

    /**
     * Metodo para obtener si estamos o no en modo de seleccion de malla ;)
     * @return True si estamos, y false si no
     */
    bool GUI::getModoSeleccion() {
        return ventanaGestion.getModoSeleccion();
    }

    /**
     * Metodo para pasar la luz puntual a la GUI
     * @param luzP La luz puntual
     */
    void GUI::pasarLuzPuntual(FuenteLuz *luzP) {
        ventanaGestion.pasarLuzPuntual(luzP);
    }

    /**
     * Metodo para pasar la luz focal a la GUI
     * @param luzF La luz focal
     */
    void GUI::pasarLuzFocal(FuenteLuz *luzF) {
        ventanaGestion.pasarLuzFocal(luzF);
    }
}

