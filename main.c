#include <stdio.h>
#include "mvehiculos.h"

int main() {
	int opcion;
	
	while(true) {
		mostrar_menu();
		printf("Seleccione la opcion deseada\n");
		scanf("%d", &opcion);
		system("cls");
		
		switch(opcion) {
		case 1:
			registrar_vehiculo();
			break;
		case 2: {
			Vehiculo* vehiculoSolicitado = vehiculo_revisable();
			if(vehiculoSolicitado != NULL) {
				if(realizar_revision_tecnica(vehiculoSolicitado))
					mostrar_costo_matricula(vehiculoSolicitado);
			}
			break;
		}
		case 3:
			mostrar_info_vehiculo(buscar_por_placa());
			break;
		case 6:
			printf("Saliendo del programa...");
			return 0;
			break;
		default:
			printf("Ingrese una opcion valida\n");
			simular_pausa();
			break;
		}
	}
}
