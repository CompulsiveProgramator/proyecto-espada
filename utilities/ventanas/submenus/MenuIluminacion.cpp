//
// Created by secre on 26/12/2024.
//

#include <string>
#include "MenuIluminacion.h"

/**
 * Metodo para ver el menu de iluminacion
 */
void IGV::MenuIluminacion::refrescarMenu() {
    if(ImGui::CollapsingHeader("Iluminación"))
    {
        if(luzPuntual)
        {
            if(ImGui::TreeNode("LuzPuntual"))
            {
                if(ImGui::TreeNode("Posicion"))
                {
                    ImGui::DragFloat("X", &posicion[0], 0.005f, -3, 3, "%.3f");
                    ImGui::DragFloat("Y", &posicion[1], 0.005f, -3, 3, "%.3f");
                    ImGui::DragFloat("Z", &posicion[2], 0.005f, -3, 3, "%.3f");

                    luzPuntual->setPosicion(posicion);

                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }

        }
    }
}

/**
 * Funcion para asignar la luz puntual al menu
 * @param pLuz La luz puntual en la escena
 */
void IGV::MenuIluminacion::pasarLuzPuntual(FuenteLuz *pLuz) {
    luzPuntual = pLuz;
    posicion = luzPuntual->getPosicion();
}
