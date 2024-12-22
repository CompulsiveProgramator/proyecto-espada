#include <iostream>
#include "utilities/Interfaz.h"

int main( int argc, char **argv ) {
    IGV::Interfaz::getInstancia().configurar_ventana(argc, argv, 600,300,100,100, "Proyecto espada");
    IGV::Interfaz::getInstancia().inicia_bucle_visualizacion();
    return 0;
}
