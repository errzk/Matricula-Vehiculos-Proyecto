#include "mvehiculos.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <ctype.h>

Vehiculo listaVehiculos[20];
int cantidadVehiculos = 0;

void simular_pausa() {
	
	while(getchar() != '\n'); 
	printf("\nPresione ENTER para continuar\n");
	getchar();
	system("cls");
}

void mostrar_menu() {
	printf("1. Registrar vehiculo\n");
	printf("2. Realizar revision tecnica\n");
	printf("3. Buscar por placa\n");
	printf("4. Listar vehiculos\n");
	printf("5. Recuperar informacion\n");
	printf("6. Salir\n");
}

//VERIFICACIONES DE DATOS LEIDOS

//Lee y verifica la placa ingresada
void placa_valida(char placa[8]) {
	char entrada[99];
	while(true) {
		scanf("%[^\n]", entrada); //Lee (incluso espacios) hasta encontrar el salto de linea 
		
		if(strlen(entrada) != 7) {
			printf("La placa debe tener 7 caracteres\n");
			simular_pausa();
		} else {
			system("cls");
			strcpy(placa, entrada);
			for(int i = 0; i < 7; i++) {
				if((i >= 0 && i < 3 && !isalpha(placa[i])) || (i >= 3 && i < 7 && !isdigit(placa[i]))) {
					printf("ERROR: Formato de placa invalido (ABC1234)");
					simular_pausa();
					goto error_placa_invalida;
				} 
			}
			for(int i = 0; i < cantidadVehiculos; i++) {
				if(strcmp(listaVehiculos[i].placa, placa) == 0) {
					printf("La placa ya fue registrada\n");
					simular_pausa();
					goto error_placa_invalida;
				}
			}
			while(getchar() != '\n');
			break;
		}
		error_placa_invalida:
		   printf("Ingrese una placa valida: ");
	}
}


//Lee y verifica que la placa ingresada tenga 10 caracteres
void cedula_valida(char cedula [11]) {
	char entrada[99];
	while(true)  {
		scanf("%[^\n]", entrada);
		if(strlen(entrada) != 10) {
			printf("ERROR: La cedula debe contener 10 caracteres\n");
			simular_pausa();
			printf("Ingrese una cedula valida: ");
		} else {
			strcpy(cedula, entrada);
			while(getchar() != '\n');
			break;
		}
	}
	system("cls");
}

bool anio_valido(int anio) {
	system("cls");
	if(anio > 2025 || anio < 1900) {
		printf("Anio invalido\n");
		simular_pausa();
		return false;
	}
	return true;
}

bool tipo_valido(int tipo) {
	system("cls");
	if(tipo == 1 || tipo == 2) {
		return true;
	} 
	
	printf("ERROR: Tipo de vehiculo invalido\n");
	simular_pausa();
	return false;
}

bool avaluo_valido(float avaluo) {
	system("cls");
	if(avaluo <= 0) {
		printf("Avaluo invalido\n");
		simular_pausa();
		return false;
	}
	return true;
}

//REGISTRA UN VEHICULO EN EL ARRAY

void registrar_vehiculo() {
	Vehiculo vehiculo;
	char placa[8];
	char cedula [11];
	int anio;
	int tipo;
	float avaluo;
	
	while(getchar() != '\n');
	//Pedir datos del vehiculo
	
	printf("Ingrese la placa: ");
	placa_valida(placa);
	
	printf("Ingrese la cedula: ");
	cedula_valida(cedula);
	
	printf("Ingrese el anio: ");
	scanf("%d", &anio);
	while(!anio_valido(anio)) {
		printf("Ingrese un anio valido: ");
		scanf("%d", &anio);
	}
	
	//while ((getchar()) != '\n');
	
	printf("Ingrese el tipo de Vehiculo\n");
	printf("1 para carro | 2 para moto\n");
	scanf("%d", &tipo);
	while(!tipo_valido(tipo)) {
		printf("Ingrese un tipo de Vehiculo valido\n");
		printf("1 para carro | 2 para moto\n");
		scanf("%d", &tipo);
	}
	
	printf("Ingrese el avaluo: ");
	scanf("%f", &avaluo);
	while(!avaluo_valido(avaluo)) {
		printf("Ingrese un avaluo valido: ");
		scanf("%f", &avaluo);
	}
	
	//Asignacion de los campos del vehiculo
	strncpy(vehiculo.placa, placa, 7);
	vehiculo.placa[7] = '\0';
	strncpy(vehiculo.cedula, cedula, 10);
	vehiculo.cedula[10] = '\0';
	vehiculo.anio = anio;
	vehiculo.tipo = tipo;
	vehiculo.avaluo = avaluo;
	
	//Se asignan valores por defecto a los campos que luego serán calculados
	vehiculo.costoMatricula = 0;
	vehiculo.intentos = 0;
	vehiculo.multas = 0.0f;
	vehiculo.apruebaRevision = false;
	
	listaVehiculos[cantidadVehiculos] = vehiculo;
	cantidadVehiculos++;
	printf("Vehiculo registrado con exito\n");
	simular_pausa();
}

Vehiculo* buscar_por_placa() {
	//Verifica que existan vehiculos registrados
	if(cantidadVehiculos > 0) {
		while(getchar() != '\n');
		char placa[99];
		printf("Escriba la placa del vehiculo\n");
		scanf("%[^\n]", placa);
		system("cls");
		
		for(int i = 0; i < cantidadVehiculos; i++) {
			if(strcmp(listaVehiculos[i].placa, placa) == 0) {
				return &listaVehiculos[i];
			}
		}
		
		printf("No se encontro un vehiculo con esa placa\n");
		simular_pausa();
		return NULL;
	}
	printf("No hay vehiculos registrados\n");
	printf("(Registre un vehiculo)\n");
	simular_pausa();
	return NULL;
}

//Devuelve un vehiculo si se le puede hacer las revisiones tecnicas, si no, devuelve null
Vehiculo* vehiculo_revisable() {
	Vehiculo *vehiculoDeseado = buscar_por_placa();
	
	if(vehiculoDeseado == NULL) {
		return NULL;
	}
	else if (vehiculoDeseado->apruebaRevision) {
		system("cls");
		printf("El vehiculo ya aprobo las revisiones tecnicas\n");
		simular_pausa();
		return NULL;
	}
	return vehiculoDeseado;
}

//Verifica si alcanzaste los 3 intentos permitidos antes de recibir una multa
void verificar_multa_por_desaprobacion(Vehiculo *vehiculo) {
	if(vehiculo->intentos == 3) {
		vehiculo->intentos = 0;
		vehiculo->multas += 50;
		
		printf("Alcanzo el maximo de intentos fallidos\n");
		printf("Acaba de recibir una MULTA\n");
		printf("---Intetos reiniciados---\n");
	}
}

//Devuelve true si pasa la revision tecnica y false si no
bool realizar_revision_tecnica(Vehiculo *vehiculo) {
	char respuesta;
	char preguntas[4][50] = {
		"Frenos en optimo estado? (S/N)\n",
			"Suspension en buen estado? (S/N)\n",
			"Sistema de escape en optimo estado? (S/N)\n",
			"Neumaticos en estado optimo? (S/N)\n"
	};
	
	for(int i = 0; i < 4; i++) {
		printf("INTENTO %d/3\n", vehiculo->intentos + 1);
		printf("%s", preguntas[i]);
		scanf(" %c", &respuesta);
		
		if(respuesta == 'N') {
			vehiculo->intentos++;
			printf("Revision DESAPROVADA\n");
			verificar_multa_por_desaprobacion(vehiculo);
			simular_pausa();
			return false;
		}
		system("cls");
	}
	
	vehiculo->apruebaRevision = true;
	printf("REVISION APROBADA\n");
	return true;
}

void mostrar_costo_matricula(Vehiculo *vehiculo) {
	printf("-----------------\n");
	printf("Placa: %s\n", vehiculo->placa);
	printf("Cedula: %s\n", vehiculo->cedula);
	printf("Anio: %d\n", vehiculo->anio);
	if(vehiculo->tipo == 1)
		printf("Tipo: Carro\n");
	else 
		printf("Tipo: Moto\n");
	printf("Avaluo: %.2f$\n", vehiculo->avaluo);
	printf("-----------------\n");
	
	vehiculo->costoMatricula = vehiculo->avaluo * 0.02;
	printf("Costo original de matriucula: %.2f$\n", vehiculo->costoMatricula);
	if (vehiculo->anio < 2015) {
		float descuento = vehiculo->costoMatricula * 0.1;
		vehiculo->costoMatricula *= 0.9;
		printf("Descuento por antiguedad: %.2f$\n", descuento);
	}
	vehiculo->costoMatricula += vehiculo->multas;
	
	printf("Multas: %.2f$\n", vehiculo->multas);
	printf("TOTAL de matricula: %.2f$\n", vehiculo->costoMatricula);
	simular_pausa();
}

void mostrar_info_vehiculo(Vehiculo *vehiculo) {
	if(vehiculo == NULL)
		return;
	
	system("cls");
	printf("-----------------\n");
	printf("Placa: %s\n", vehiculo->placa);
	printf("cedula: %s\n", vehiculo->cedula);
	printf("Anio: %d\n", vehiculo->anio);
	if(vehiculo->tipo == 1)
		printf("Tipo: Carro\n");
	else 
		printf("Tipo: Moto\n");
	printf("Avaluo: %.2f$\n", vehiculo->avaluo);
	printf("-----------------\n");
	
	if(vehiculo->apruebaRevision) 
		printf("Revision tecnica APROBADA\n");
	else printf("Revision tecnica PENDIENTE\n");
	printf("-----------------\n");
	simular_pausa();
}
