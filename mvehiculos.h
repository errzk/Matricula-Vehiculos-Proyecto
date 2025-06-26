#ifndef MVEHICULOS_H
#define MVEHICULOS_H
#include <stdbool.h>

typedef struct {
	char placa[8];
	char cedula[11];
	int anio;
	int tipo;
	float avaluo;
	float costoMatricula;
	int intentos;
	float multas;
	bool apruebaRevision;
} Vehiculo;

extern Vehiculo listaVehiculos[20];
extern int cantidadVehiculos;

void simular_pausa(void);
void mostrar_menu(void);

void placa_valida(char placa[8]);
void cedula_valida(char cedula[11]);
bool anio_valido(int anio);
bool tipo_valido(int tipo);
bool avaluo_valido(float avaluo);

void registrar_vehiculo(void);
Vehiculo* buscar_por_placa(void);
Vehiculo* vehiculo_revisable(void);
void verificar_multa_por_desaprobacion(Vehiculo *vehiculo);
bool realizar_revision_tecnica(Vehiculo *vehiculo);
void mostrar_costo_matricula(Vehiculo *vehiculo);
void mostrar_info_vehiculo(Vehiculo *vehiculo);

#endif
