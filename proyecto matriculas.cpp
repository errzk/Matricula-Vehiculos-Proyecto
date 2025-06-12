#include<stdio.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
	char placa[8];
	int cedula;
	int anio;
	char tipo;
	float avaluo;
	float costoMatricula;
	int intentos;
	float multas;
	bool revisado;
} Vehiculo;

void mostrar_menu() {
	printf("	REGISTRO DE MATRICULACIÓN VEHICULAR	\n");
	printf("1. Registrar vehiculo.\n");
	printf("2. Registrar revision tecnica.\n");
	printf("3. Buscar por placa.\n");
	printf("4. Listar vehiculos.\n");
	printf("5. Recuperar informacion.\n");
	printf("6. Salir.\n");
}

void registrar_vehiculo(char placa[8], int cedula, int anio, char tipo, float avaluo, Vehiculo (*listaVehiculos)[20], int *cantidadVehiculos) {
	Vehiculo vehiculo;
	
	strncpy(vehiculo.placa, placa, 7);
	vehiculo.placa[7] = '\0';
	
	vehiculo.cedula = cedula;
	vehiculo.anio = anio;
	vehiculo.tipo = tipo;
	vehiculo.avaluo = avaluo;
	
	vehiculo.costoMatricula = 0;
	vehiculo.intentos = 0;
	vehiculo.multas = 0.0f;
	
	vehiculo.revisado = false;
	
	(*listaVehiculos)[*cantidadVehiculos] = vehiculo;
	(*cantidadVehiculos)++;
}

bool revision_vehiculo(Vehiculo *vehiculo) {
	char respuesta;
	
	printf("	INTENTO %d/3\n", vehiculo->intentos + ); // Se suma + 1 para que imprima "INTENTO 1/3" y no "INTENTO 0/3"
	printf("¿Frenos en optimo estado? (S/N)\n");
	scanf(" %c", &respuesta);
	
	if(respuesta == 'N') {
		vehiculo->intentos++;
		system("cls");
		printf("Revision DESAPROBADA\n");
		return false;
	}
	
	printf("¿Suspensión en buen estado? (S/N)\n");
	scanf(" %c", &respuesta);
	if(respuesta == 'N') {
		vehiculo->intentos++;
		system("cls");
		printf("Revision DESAPROBADA\n");
		return false;
	}
	
	printf("¿Sistema de escape en optimo estado? (S/N)\n");
	scanf(" %c", &respuesta);
	if(respuesta == 'N') {
		vehiculo->intentos++;
		system("cls");
		printf("Revision DESAPROBADA\n");
		return false;
	}
	
	printf("¿Alineacion en buen estado? (S/N)\n");
	scanf(" %c", &respuesta);
	if(respuesta == 'N') {
		vehiculo->intentos++;
		system("cls");
		printf("Revision DESAPROBADA\n");
		return false;
	}
	
	printf("¿Neumaticos en estado optimo? (S/N)\n");
	scanf(" %c", &respuesta);
	if(respuesta == 'N') {
		vehiculo->intentos++;
		system("cls");
		printf("Revision DESAPROBADA\n");
		return false;
	}
	
	vehiculo->revisado = true;
	printf("REVISION APROBADA\n");
	return true;
}

float calcular_matricula_carro(Vehiculo vehiculo) {
	float costoMatricula = vehiculo.avaluo * 0.02;
	
	if (vehiculo.anio < 2015) 
		costoMatricula *= 0.9;
	costoMatricula += vehiculo.multas;
	return costoMatricula;
}

int main() {
	int opcion;
	Vehiculo listaVehiculos[20];
	int cantidadVehiculos = 0;
	while(true) {
		mostrar_menu();
		printf("Seleccione la opcion deseada\n");
		scanf("%d", &opcion);
		system("cls");
		
		switch(opcion) {
		case 1:
			char placa[8];
			int cedula;
			int anio;
			char tipo;
			float avaluo;
			
			printf("Ingrese la placa: ");
			scanf("%s", &placa);  
			
			printf("Ingrese la cédula: ");
			scanf("%d", &cedula);
			
			printf("Ingrese el año: ");
			scanf("%d", &anio);
			
			// Limpiar buffer antes de leer un carácter
			while ((getchar()) != '\n'); 
			
			printf("Ingrese el tipo de Vehiculo (Carro/Moto)(C/M): ");
			scanf("%c", &tipo);
			
			printf("Ingrese el avalúo: ");
			scanf("%f", &avaluo);
			
			registrar_vehiculo(placa, cedula, anio, tipo, avaluo, &listaVehiculos, &cantidadVehiculos);

			system("cls");
			break;
		case 2:
			if(cantidadVehiculos > 0) {
				int numVehiculo;
				printf("¿Que vehiculo desea verficar?\n");
				scanf("%d", &numVehiculo);
				
				if(listaVehiculos[numVehiculo - 1].revisado) {
					printf("El vehiculo ya aprobo las revisiones\n");
					break;
				}
				if(revision_vehiculo(&listaVehiculos[numVehiculo - 1])) {
					listaVehiculos[numVehiculo - 1].costoMatricula = calcular_matricula_carro(listaVehiculos[numVehiculo - 1]);
					
					printf("Placa: %s\n", listaVehiculos[numVehiculo - 1].placa);
					printf("cedula: %d\n", listaVehiculos[numVehiculo - 1].cedula);
					printf("Anio: %d\n", listaVehiculos[numVehiculo - 1].anio);
					printf("Avaluo: %.2f\n", listaVehiculos[numVehiculo - 1].avaluo);
					printf("El costo de matricula es: %.2f\n", listaVehiculos[numVehiculo - 1].costoMatricula);
				}
				else if(listaVehiculos[numVehiculo - 1].intentos == 3) {
					listaVehiculos[numVehiculo - 1].intentos = 0;
					listaVehiculos[numVehiculo - 1].multas += 50;
					
					printf("Alcanzó el maximo de intentos fallidos\n");
					printf("Acaba de recibir una MULTA\n");
					printf("	Intentos reiniciados	\n");
				}
			} else {
				printf("No hay vehiculos para realizar las verficaciones\n");
				printf("(Registre un vehiculo)\n");
			}
			break;
		case 6:
			return 0;
			break;
		default:
			printf("Ingrese una opción valida\n");
			break;
		}
	}
}
