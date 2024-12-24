//
// Created by secre on 22/12/2024.
//

#include "GUI.h"

namespace IGV{
    GUI* GUI::instancia = nullptr;

    /**
     * Constructor de la GUI
     */
    GUI::GUI(): ventanaGestionModelo() {

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

        ventanaGestionModelo.refrescarVentana();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );
    }

    /**
     * Para consultar a la ventana de gestion, si tenemos que seguir el movimiento del raton
     * @return
     */
    bool GUI::getSeguirMovimientoRaton() {
        return ventanaGestionModelo.getSeguirRaton();
    }
}

