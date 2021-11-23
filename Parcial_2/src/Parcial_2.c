/*
 ============================================================================
 Name        : Parcial_2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "Inputs.h"
#include "parser.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/


int main()
{
	setbuf(stdout, NULL);
    int option = 0;
    int flagDeCarga=0;

    LinkedList* listaEmpleados = ll_newLinkedList();
    do{
    	pedirTipoInt(&option, "\tMENU\n1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n3. Alta de empleado\n4. Modificar datos de empleado\n5. Baja de empleado\n6. Listar empleados\n7. Ordenar empleados\n8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n9. Guardar los datos de los empleados en el archivo data.csv (modo binario).\n\n\t10. SALIR.\n", "ERROR en el pedir.", 1, 10, 1);
        switch(option)
        {
            case 1:
            	if(flagDeCarga==0)
            	{
                controller_loadFromText("data.csv",listaEmpleados);
            	flagDeCarga=1;
            	}
            	else
            	{
            		puts("Los datos ya fueron cargdos, maquina");
            	}
                break;
            case 2:
            	if(flagDeCarga==0)
            	{
            		controller_loadFromBinary("binario.bin", listaEmpleados);
            		flagDeCarga=1;
            	}
            	else
            	{
            		puts("Ya fue cargado de manera binaria, fuera...");
            	}
            	break;
            case 3:
            	controller_addEmployee(listaEmpleados);
            	break;
            case 4:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
            		if(controller_ListEmployee(listaEmpleados)==0)
            		{
            			puts("\n");
            			controller_editEmployee(listaEmpleados);
            		}
            	}
            	else
            	{
            		puts("Cargue primero la lista");
            		puts("Volviendo al menu....");
            	}
            	break;
            case 5:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
            	controller_removeEmployee(listaEmpleados);
            	}
            	else
            	{
            		puts("Cargue la lista primero\nVolviendo al menu");

            	}
            	break;
            case 6:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
            		controller_ListEmployee(listaEmpleados);
            	}
            	else
            	{
            		puts("Cargue la lista primero\nVolviendo al menu");
            	}
            	break;
            case 7:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
            		if(controller_sortEmployee(listaEmpleados)==0)
            		{
            			puts("\t\tLISTA ORDENADA");
            			controller_ListEmployee(listaEmpleados);
            		}
            	}
            	else
            	{
            		puts("Ingrese una carga primero");
            	}
            	break;
            case 8:
            	if(flagDeCarga==1 && ll_isEmpty(listaEmpleados)==0)
            	{
            	controller_saveAsText("data.csv" , listaEmpleados);
            	}
            	else
            	{
            		puts("No hay nada que guardar");
            	}
            	break;
            case 9:
            	if(flagDeCarga==1 && ll_isEmpty(listaEmpleados))
            	{
            	controller_saveAsBinary("binario.bin" , listaEmpleados);
            	}
            	else
            	{
            		puts("NO hay nada q guardar");
            	}
            	break;
            case 10:
            	puts("Adios.\n");
            	break;
        }
    }while(option != 10);
    return 0;
}
