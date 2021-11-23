#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Inputs.h"
#include "parser.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int deteccion=-1;
	FILE* pArchivo;

	puts("Entre a la funcion controller al menos");
	if(pArrayListEmployee!=NULL && path!=NULL)
	{
		puts("Hola llegue hasta aca, ");
		if(ll_isEmpty(pArrayListEmployee)==1)
		{
			puts("paso");
			if((pArchivo=fopen(path,"r"))!=NULL)
			{
				puts("paso el null");
				if(parser_EmployeeFromText(pArchivo, pArrayListEmployee)==0)
				{
					deteccion=0;
				}
				else
				{
					puts("\nSalio mal el parse");
				}
			}
		}
		else
		{
			puts("ERROR. No se consiguio cargarlo");
		}
	}



    return deteccion;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path,LinkedList* pArrayListEmployee)
{
	int deteccion=-1;

	FILE* fpArchivo;
	fpArchivo=fopen(path, "w");

	if(pArrayListEmployee!=NULL && path!=NULL && fpArchivo!=NULL)
	{

		parser_EmployeeFromBinary(fpArchivo, pArrayListEmployee);
		deteccion=0;
	}
	else
	{
		puts("ERROR. No se cargo de forma binaria");
	}






    return deteccion;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int deteccion=-1;
	int idAux;
	char nombreAux[64];
	int horasTrabajadasAux;
	int sueldoAux;
	Employee* empleadoAux=employee_new();
	if(pArrayListEmployee!=NULL && empleadoAux!=NULL)
	{
			if(pedir_texto(nombreAux, "Ingrese el nombre del empleado ingresado\n", "\nError\n", 1)==0)
			{
				if(pedirTipoInt(&horasTrabajadasAux, "Ingrese las hora del trabajas por el empleado\n ", "\nError al pedir horas\n", 1,999, 99)==0)
				{
					if(pedirTipoInt(&sueldoAux, "Ingrese el sueldo del empleado\n", "\nError al ingresar sueldo\n", 1, 999999, 1)==0)
					{
						idAux=crearId();
						if(employee_setNombre(empleadoAux, nombreAux)==0 && employee_setHorasTrabajadas(empleadoAux, horasTrabajadasAux)==0 && employee_setId(empleadoAux, idAux)==0 && employee_setSueldo(empleadoAux, sueldoAux)==0)
						{
							deteccion=ll_add(pArrayListEmployee, empleadoAux);
						}
						else
						{
							puts("Error en la funcion controller_addEmployee");
						}
					}
				}
			}
	}



    return deteccion;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int deteccion;
	int index;
	int opcion;
	char nombreAux[64];
	int sueldoAux;
	int horasAux;
	if(pArrayListEmployee!=NULL && pedirTipoInt(&index, "Ingrese la posicion del empleado que desee modificar\n", "\nError en la funcion editEmployee\n", 0, pArrayListEmployee->size, 1)==0)
	{
		Employee* empleadoAux=ll_get(pArrayListEmployee, index);

		if(pedirTipoInt(&opcion, "\n\tCAMPOS\n1. Editar Nombre.\n2. Editar sueldo\n3. Editar horas trabajadas.\n4. SALIR", "Error en la funcion de editEmployee\n", 1, 5,999)==0)
		{

			while(opcion!=4)
			{
					switch(opcion)
				{
					case 1:
						if(pedir_texto(nombreAux, "Ingrese el nuevo nombre del empleado", "ERROR", 1)==0)
						{
							if(employee_setNombre(empleadoAux, nombreAux)==0)
							{
								puts("Nombre actualizado");
							}

						}
						break;
					case 2:
						if(pedirTipoInt(&sueldoAux, "Ingrese el nuevo sueldo\n", "ERROR/editemployee\n", 0, 99999,1)==0)
						{
							if(employee_setSueldo(empleadoAux, sueldoAux)==0)
							{
								puts("Sueldo actualizado");
							}
						}
						break;
					case 3:
						if(pedirTipoInt(&horasAux, "Ingrese la nueva cantidad de horas trabajadas\n", "Error.\n", 1, 9999, 1)==0)
						{
							if(employee_setHorasTrabajadas(empleadoAux, horasAux)==0)
							{
								puts("Horas de trabajo actualizada");
							}
						}
						break;
				}

			}
			deteccion=0;
		}
	}






    return deteccion;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int deteccion=-1;
	int indexABorrar;
	Employee* empleadoAux;
	if(pArrayListEmployee!=NULL)
	{
		if(pedirTipoInt(&indexABorrar, "Ingrese la posion del empleado que desee deletear\n", "ERROR. pedirtipo\n", 0, ll_len(pArrayListEmployee), 1)==0)
		{
			empleadoAux=ll_get(pArrayListEmployee, indexABorrar);
			employee_delete(empleadoAux);
			ll_remove(pArrayListEmployee, indexABorrar);
			deteccion=0;
		}
	}



    return deteccion;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int deteccion;
	deteccion=-1;
	Employee* empleadoAux=employee_new();
	char nombreAux[64];
	int sueldoAux;
	int idAux;
	int horasAux;
	int len;


	len=ll_len(pArrayListEmployee);
	printf("\nLen: %d\n", len);
	if(pArrayListEmployee!=NULL && empleadoAux!=NULL)
	{
		puts("\nNo son los condicionales");
		for(int i=0; i<=len; i++)
		{
			printf("\ni=%d", i);

			empleadoAux=ll_get(pArrayListEmployee,i);
			if(employee_getHorasTrabajadas(empleadoAux, &horasAux)==0 && employee_getId(empleadoAux, &idAux)==0 && employee_getNombre(empleadoAux, nombreAux)==0 && employee_getSueldo(empleadoAux, &sueldoAux)==0)
			{
				puts("\n\t\tLISTA DE EMPLEADOS:");
				printf("*NOMBRE: [%s]\t\tID: [%d]\t\tHORAS TRABAJADAS: [%d]\t\tSUELDO: [%d]\n\n", nombreAux, idAux, horasAux, sueldoAux);
			}

		}
		deteccion=0;
	}
	else
	{
		puts("Salio mal el controllear");
		employee_delete(empleadoAux);
	}




    return deteccion;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int deteccion=-1;
	int opcion;
	if(pArrayListEmployee!=NULL)
	{
		if(pedirTipoInt(&opcion, "\tMenu\n1) Ordenar por sueldo\n2) Ordenar por horas trabajadas\n3) Ordenar por Nombre\n4) SALIR\n", "ERROR\n", 1, 4, 99)==0)
		{
			switch(opcion)
			{
				case 1:
					deteccion=ll_sort(pArrayListEmployee, OrdenarPorSueldo, 1);
					puts("Ordenando...");
					break;
				case 2:
					deteccion=ll_sort(pArrayListEmployee, OrdenarPorHora, 1);
					puts("Ordenando...");
					break;
				case 3:
					deteccion=ll_sort(pArrayListEmployee, OrdenarPorNombre, 1);
					puts("Ordenando...");
					break;
				case 4:
					puts("Saliendo...\n");
					break;
			}
		}
	}

    return deteccion;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pArchivoTexto;
	int deteccion=-1;
	int idAux;
	char nombreAux[128];
	int horasAux;
	int sueldoAux;
	Employee* empleadoAux;

	pArchivoTexto=fopen(path, "w");

	if(pArrayListEmployee!=NULL && path!=NULL && pArchivoTexto!=NULL)
	{
		rewind(pArchivoTexto);
		fprintf(pArchivoTexto, "idAux,nombreAux,horasAux,sueldoAux\n");
		for(int i=0; i<ll_len(pArrayListEmployee);i++)
		{
			empleadoAux=(Employee*)ll_get(pArrayListEmployee, i);
			employee_getId(empleadoAux, &idAux);
			employee_getNombre(empleadoAux, nombreAux);
			employee_getHorasTrabajadas(empleadoAux, &horasAux);
			employee_getSueldo(empleadoAux, &sueldoAux);
			fprintf(pArchivoTexto,"%d,%s,%d,%d\n", idAux,nombreAux,horasAux,sueldoAux);
		}
		deteccion=0;
		printf("\nSalio bien el guardado\n");
	}

	fclose(pArchivoTexto);

    return deteccion;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int deteccion=-1;
	Employee* empleadoAux;
	FILE* pArchivoBinario=fopen(path, "wb");

		if(path!=NULL && pArrayListEmployee!=NULL && pArchivoBinario!=NULL)
		{
			for(int i=0; i<ll_len(pArrayListEmployee); i++)
			{
				empleadoAux=ll_get(pArrayListEmployee, i);
				fwrite(empleadoAux, sizeof(Employee), 1, pArchivoBinario);
			}
			puts("No saque el juego ni apaga la consola");
			puts("Guardando...");
			deteccion=0;
		}

			fclose(pArchivoBinario);
    return deteccion;
}






//SORT        : ORDENAR
//MAP         : Permite transformar los elementos de una lista
//REDUCE      : Ejecuta una funcion rductora sobre cada elemento, devolviendo como unico resultado un
//FILTER      :	Filtra todos los elementos que cumplan la condicion implementada por la funcion dada


