//
// Created by secre on 24/12/2024.
//

#include "MenuTransformaciones.h"

void IGV::MenuTransformaciones::refrescarMenu() {
    try{
        if(ImGui::CollapsingHeader("Transformaciones"))
        {
            if(Renderer::getInstancia().getEscena().getModelo() == nullptr)
            {
                ImGui::Text("No hay ningun modelo cargado, selecciona y carga uno");
                return;
            }

            if(ImGui::Button("Resetear matriz de modelado"))
            {
                Renderer::getInstancia().getEscena().getModelo()->resetearMatrizModelado();
            }

            if(ImGui::TreeNode("Traslación"))
            {
                ImGui::DragFloat("X", &traslacionX, 0.005f, -1.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);
                ImGui::DragFloat("Y", &traslacionY, 0.005f, -1.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);
                ImGui::DragFloat("Z", &traslacionZ, 0.005f, -1.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);

                if(ImGui::Button("Resetear valores"))
                {
                    traslacionX = 0;
                    traslacionY = 0;
                    traslacionZ = 0;
                }

                if(ImGui::Button("Aplicar"))
                {
                    Renderer::getInstancia().getEscena().getModelo()->aplicarTraslacionEjeX(traslacionX);
                    Renderer::getInstancia().getEscena().getModelo()->aplicarTraslacionEjeY(traslacionY);
                    Renderer::getInstancia().getEscena().getModelo()->aplicarTraslacionEjeZ(traslacionZ);
                }

                ImGui::TreePop();
            }

            if(ImGui::TreeNode("Rotación"))
            {
                ImGui::DragFloat("X", &rotacionX, 0.5f, -90.0f, 90.0f, "%.3f", ImGuiSliderFlags_None);
                ImGui::DragFloat("Y", &rotacionY, 0.5f, -90.0f, 90.0f, "%.3f", ImGuiSliderFlags_None);
                ImGui::DragFloat("Z", &rotacionZ, 0.5f, -90.0f, 90.0f, "%.3f", ImGuiSliderFlags_None);

                if(ImGui::Button("Resetear valores"))
                {
                    rotacionX = 0;
                    rotacionY = 0;
                    rotacionZ = 0;
                }

                if(ImGui::Button("Aplicar"))
                {
                    Renderer::getInstancia().getEscena().getModelo()->aplicarRotacionEjeX(rotacionX);
                    Renderer::getInstancia().getEscena().getModelo()->aplicarRotacionEjeY(rotacionY);
                    Renderer::getInstancia().getEscena().getModelo()->aplicarRotacionEjeZ(rotacionZ);
                }

                ImGui::TreePop();
            }

            if(ImGui::TreeNode("Escalado"))
            {
                ImGui::Checkbox("Escalado uniforme", &escaladoUniformeActivo);

                if(escaladoUniformeActivo)
                {
                    ImGui::DragFloat("Uniforme", &escaladoUniforme, 0.005f, -2.0f, 2.0f, "%.3f", ImGuiSliderFlags_None);
                }else{
                    ImGui::DragFloat("X", &escaladoX, 0.005f, -2.0f, 2.0f, "%.3f", ImGuiSliderFlags_None);
                    ImGui::DragFloat("Y", &escaladoY, 0.005f, -2.0f, 2.0f, "%.3f", ImGuiSliderFlags_None);
                    ImGui::DragFloat("Z", &escaladoZ, 0.005f, -2.0f, 2.0f, "%.3f", ImGuiSliderFlags_None);
                }

                if(ImGui::Button("Resetear valores"))
                {
                    escaladoX = 1;
                    escaladoY = 1;
                    escaladoZ = 1;
                    escaladoUniforme = 1;
                }

                if(ImGui::Button("Aplicar"))
                {
                    if(escaladoUniformeActivo)
                    {
                        Renderer::getInstancia().getEscena().getModelo()->escalarUniforme(escaladoUniforme);
                    }else{
                        Renderer::getInstancia().getEscena().getModelo()->aplicarEscaladoEjeX(escaladoX);
                        Renderer::getInstancia().getEscena().getModelo()->aplicarEscaladoEjeY(escaladoY);
                        Renderer::getInstancia().getEscena().getModelo()->aplicarEscaladoEjeZ(escaladoZ);
                    }
                }

                ImGui::TreePop();
            }
        }
    }catch(std::exception &e)
    {
        std::cout << e.what() << "\n";
    }
}
