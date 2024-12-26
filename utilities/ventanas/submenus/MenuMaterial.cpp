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
//           if(ImGui::TreeNode("Color ambiente"))
//           {
//               ImGui::DragFloat("R", &colorAmbiente[X], 0.005, 0.0f, 1.0f, "%.3f");
//               ImGui::DragFloat("G", &colorAmbiente[Y], 0.005, 0.0f, 1.0f, "%.3f");
//               ImGui::DragFloat("B", &colorAmbiente[Z], 0.005, 0.0f, 1.0f, "%.3f");
//
//               if(ImGui::Button("Aplicar"))
//               {
//                   malla->getMaterial()->setKa(colorAmbiente);
//               }
//
//               ImGui::TreePop();
//           }

           if(ImGui::TreeNode("Color difuso"))
           {
               ImGui::DragFloat("R", &colorDifuso[X], 0.005f, 0.0f, 1.0f, "%.3f");
               ImGui::DragFloat("G", &colorDifuso[Y], 0.005f, 0.0f, 1.0f, "%.3f");
               ImGui::DragFloat("B", &colorDifuso[Z], 0.005f, 0.0f, 1.0f, "%.3f");

               if(ImGui::Button("Aplicar")){
                   malla->getMaterial()->setKd(colorDifuso);
               }

               ImGui::TreePop();
           }

           if(ImGui::TreeNode("Color especular"))
           {
               ImGui::DragFloat("R", &colorEspecular[X], 0.005f, 0.0f, 1.0f, "%.3f");
               ImGui::DragFloat("G", &colorEspecular[Y], 0.005f, 0.0f, 1.0f, "%.3f");
               ImGui::DragFloat("B", &colorEspecular[Z], 0.005f, 0.0f, 1.0f, "%.3f");

               if (ImGui::Button("Aplicar")) {
                   malla->getMaterial()->setKs(colorEspecular);
               }

               ImGui::TreePop();
           }

           if(ImGui::TreeNode("Exponente especular"))
           {
               ImGui::DragFloat("Valor", &exponenteEspecular, 0.5f, 0.0f, 127.0f, "%.3f");

               if (ImGui::Button("Aplicar")) {
                   malla->getMaterial()->setEs(exponenteEspecular);
               }

               ImGui::TreePop();
           }

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
 * @param malla1 El puntero a la malla
 */
void IGV::MenuMaterial::setMalla(IGV::Malla *malla1) {
    if(malla != malla1)
    {
        malla = malla1;
        if(malla)
        {
            //colorAmbiente = malla->getMaterial()->getKa();
            colorDifuso = malla->getMaterial()->getKd();
            colorEspecular = malla->getMaterial()->getKs();
            exponenteEspecular = malla->getMaterial()->getEs();
        }else{
            //colorAmbiente = glm::vec3(0);
            colorDifuso = glm::vec3(0);
            colorEspecular = glm::vec3(0);
            exponenteEspecular = 0;
        }
    }
}

/**
 * Getter para consultar si estamos en modo de seleccion de malla o no
 * @return
 */
bool IGV::MenuMaterial::getSeleccionMalla() {
    return seleccionMalla;
}
