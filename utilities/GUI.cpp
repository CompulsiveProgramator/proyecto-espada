//
// Created by secre on 22/12/2024.
//

#include "GUI.h"

namespace IGV{
    GUI* GUI::instancia = nullptr;

    /**
     * Constructor de la GUI
     */
    GUI::GUI() {

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

    void GUI::refrescar() {

    }
}

