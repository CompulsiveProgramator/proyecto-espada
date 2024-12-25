//
// Created by secre on 25/12/2024.
//

#include "../../Renderer.h"
#include "MenuMaterial.h"

/**
 * Metodo para visualizar el menu de gestion de material
 */
void IGV::MenuMaterial::refrescarMenu() {
   if( ImGui::CollapsingHeader("Material"))
   {
       ImGui::Checkbox("Activar seleccion de malla", &seleccionMalla);

       if(malla != nullptr)
       {
           float a = malla->getMaterial().getKd()[0];
           std::string mensajeVictoria = std::to_string(a);
           ImGui::Text(mensajeVictoria.c_str());

           if(ImGui::Button("Deseleccionar malla"))
           {
               malla = nullptr;
               IGV::Renderer::getInstancia().deseleccionarMalla();
           }
       }
   }
}

/**
 * Setter del atributo de malla
 * @param malla1
 */
void IGV::MenuMaterial::setMalla(IGV::Malla *malla1) {
    malla = malla1;
}

/**
 * Getter para consultar si estamos en modo de seleccion de malla o no
 * @return
 */
bool IGV::MenuMaterial::getSeleccionMalla() {
    return seleccionMalla;
}
