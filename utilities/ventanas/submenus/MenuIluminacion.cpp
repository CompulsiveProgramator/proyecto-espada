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
            if(ImGui::TreeNode("Luz puntual"))
            {
                if(ImGui::TreeNode("Posicion"))
                {
                    ImGui::DragFloat("X", &posicionPuntual[0], 0.005f, -3, 3, "%.3f");
                    ImGui::DragFloat("Y", &posicionPuntual[1], 0.005f, -3, 3, "%.3f");
                    ImGui::DragFloat("Z", &posicionPuntual[2], 0.005f, -3, 3, "%.3f");

                    luzPuntual->setPosicion(posicionPuntual);

                    ImGui::TreePop();
                }

                ImGui::Checkbox("Activa", &encendidaPuntual);

                if(encendidaPuntual)
                {
                    luzPuntual->encender();
                }else{
                    luzPuntual->apagar();
                }

                ImGui::TreePop();
            }

        }

//        if(luzFocal)
//        {
//            if(ImGui::TreeNode("Luz focal"))
//            {
//                ImGui::Checkbox("Activa", &encendidaFocal);
//
//                if(encendidaFocal)
//                {
//                    luzFocal->encender();
//                }else{
//                    luzFocal->apagar();
//                }
//                ImGui::TreePop();
//            }
//        }
    }
}

/**
 * Funcion para asignar la luz puntual al menu
 * @param pLuz La luz puntual en la escena
 */
void IGV::MenuIluminacion::pasarLuzPuntual(FuenteLuz *pLuz) {
    luzPuntual = pLuz;
    posicionPuntual = luzPuntual->getPosicion();
}

/**
 * Funcion para asignar la luz focal al menu
 * @param pLuz La luz focal en la escena
 */
void IGV::MenuIluminacion::pasarLuzFocal(FuenteLuz *pLuz) {
    luzFocal = pLuz;
    posicionFocal = luzFocal->getPosicion();
}
