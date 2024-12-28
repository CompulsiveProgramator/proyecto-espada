//
// Created by secre on 24/12/2024.
//

#ifndef PROYECTO_ESPADA_MENUTRANSFORMACIONES_H
#define PROYECTO_ESPADA_MENUTRANSFORMACIONES_H

#include "../../Renderer.h"
#include "Menu.h"

namespace IGV{
    /**
     * Menu para aplicar transformaciones al modelo ;)
     */
    class MenuTransformaciones: public Menu{
    private:
        // Para las traslaciones:
        float traslacionX = 0;
        float traslacionY = 0;
        float traslacionZ = 0;
        // Para las rotaciones:
        float rotacionX = 0;
        float rotacionY = 0;
        float rotacionZ = 0;
        // Para los escalados:
        float escaladoX = 1;
        float escaladoY = 1;
        float escaladoZ = 1;
        float escaladoUniforme = 1;
        bool escaladoUniformeActivo = false;
    public:
        MenuTransformaciones() = default;
        void refrescarMenu() override;
    };
}



#endif //PROYECTO_ESPADA_MENUTRANSFORMACIONES_H
