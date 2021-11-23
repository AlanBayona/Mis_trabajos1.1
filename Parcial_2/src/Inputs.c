#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inputs.h"

static int validarFloat(char cadenaFloat[]);
static int getInt(int* pResultado);
static int getFloat(float* pResultado);
static int validarEntero(char charDeEnteros[]);
static int validarTexto(char cadenaDeCaracteres[]);
static int validar_Correo(char cadenaDeCaracteres[]);
static int validarDireccion(char cadenaDeCaracteres[]);
static int validarChar(char* pLetra);
static int validarNumeroTexto(char cadenaDeCaracteres[]);


//Entradas de tipo string





int pedirChar(char* pCaracter, char* mensaje, char* mensajeError, char minimo, char maximo)
{
	int deteccion;
	char bufferChar;
	deteccion=-1;


	if(pCaracter!=NULL && mensaje!=NULL && mensajeError!=NULL && maximo>minimo)
	{
		printf("%s", mensaje);
						if(myGets(&bufferChar, sizeof(bufferChar))==0 && validarChar(&bufferChar)==0)
						{
							if(bufferChar>=minimo && bufferChar<=maximo)
							{
								*pCaracter=bufferChar;
								deteccion=0;
							} else
							{
								printf("%s", mensajeError);
							}
						}



	}


	return deteccion;
}


static int validarChar(char* pLetra)
{
	int deteccion;
	deteccion=-1;

	if( (pLetra>='A' && pLetra<='Z') || (pLetra>='a' && pLetra<='z'))
	{
		deteccion=0;
	}

	return deteccion;
}








int pedir_texto(char cadenaDeCaracteres[], char* mensaje, char* mensajeError, int reintentos)
{

	int deteccion;
	int i;
	char bufferChar[64];
	deteccion=-1;

	if(cadenaDeCaracteres!=NULL && mensaje!=NULL && mensajeError!=NULL && reintentos!=0)
	{
		for(i=0; i<reintentos; i++)
		{
			printf("%s", mensaje);

			if(myGets(bufferChar,sizeof(bufferChar))==0 && validarTexto(bufferChar)==0)
			{
				deteccion=0;
				strcpy(cadenaDeCaracteres, bufferChar);
						break;
			}
			else
			{
				printf("%s", mensajeError);//mensaje de error por si la cosa se pone complicada xd
			}
			}
		}

		return deteccion;
	}





int pedirCorreo(char cadenaDeCaracteres[], char* mensaje, char* mensajeError, int reintentos)
{
	int deteccion;
	int i;
	char bufferChar[69];
	deteccion=-1;

	if(cadenaDeCaracteres!=NULL && mensaje!=NULL && mensajeError!=NULL && reintentos>0)
	{
		for(i=0; i<reintentos; i++)
		{
			printf("%s", mensaje);
			//aca directamente usamos la funcion getFloat para cargar un numero float
			if(myGets(bufferChar,sizeof(bufferChar))==0 && validar_Correo(bufferChar)==0)//ahi obtendremos la validacion mediante la funcion
			{
				deteccion=0;
				strcpy(cadenaDeCaracteres, bufferChar);
						break;
			}
			else
			{
				printf("%s", mensajeError);//mensaje de error por si la cosa se pone complicada xd
			}
			}
		}

		return deteccion;
}


int pedirDireccion(char cadenaDeCaracteres[], char* mensaje, char* mensajeError, int reintentos)
{

	int deteccion;
	int i;
	char bufferChar[64];
	deteccion=-1;

	if(cadenaDeCaracteres!=NULL && mensaje!=NULL && mensajeError!=NULL && reintentos>0)
	{
		for(i=0; i<reintentos; i++)
		{
			printf("%s", mensaje);
			if(myGets(bufferChar,sizeof(bufferChar))==0 && validarDireccion(bufferChar)==0)
			{
				deteccion=0;
				strcpy(cadenaDeCaracteres, bufferChar);
						break;
			}
			else
			{
				printf("%s", mensajeError);
			}
			}
		}

		return deteccion;
}














//Entradas de tipo number

int pedirTipoInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int deteccion= -1;
	int bufferInt;
	int i;

	 for(i=0; i<reintentos; i++)
	 {
		if(pResultado!=NULL && mensaje!= NULL && mensajeError!=NULL && minimo<=maximo && reintentos>0)
		{
			printf("%s", mensaje);
				if(getInt(&bufferInt)==0)
				{
					if(bufferInt>=minimo && bufferInt<=maximo)
					{
						*pResultado=bufferInt;
						deteccion=0;
						puts("Entro");
						break;
					} else
					{
						printf("%s", mensajeError);
					}
				}

		}

	 }


		return deteccion;
}



int pedirTipoFloat(float* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	//primero ante nada declare algunas variables utiles
	int deteccion; //sera de retorno y el que verifique si esta bien
	int i; // index de la array.
	float bufferFloat;// esta variable es un auxiliar para poder pasar el dato por puntero
	deteccion=-1;//Tomo que salio mal desde un principio

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo<=maximo && reintentos!=0)
	{
		for(i=0; i<reintentos; i++)
		{
			printf("%s", mensaje);
			//aca directamente usamos la funcion getFloat para cargar un numero float
			if(getFloat(&bufferFloat)==0)//ahi obtendremos la validacion mediante la funcion
			{
					if(bufferFloat>=minimo && bufferFloat<=maximo)
					{
					//la condicion de minimo y max debe cambiar , cuando aprende bien cadena de caracteres
						deteccion=0;
						//ahora el numero que se uso para cargar el numero float
						*pResultado=bufferFloat;
						//lo vuelvo a cargar en el puntero que ingrese dentro del parametro de la funcion
						break;
					}
					else
					{
						printf("%s", mensajeError);//mensaje de error por si la cosa se pone complicada xd
					}
			}
		}

	}

	return deteccion;//0 para si salio bien
}



int myGets(char cadena[], int len)
{
	if(cadena != NULL && len > 0 && fgets(cadena, len,stdin)==cadena)
	{
		fflush(stdin);
			if(cadena[strlen(cadena)-1]=='\n')
			{
				cadena[strlen(cadena)-1]='\0';
			}
			return 0;
	}

	return -1;
}



//Las funciones static

static int validarFloat(char cadenaFloat[])
{

	int deteccion;
	int flagPunto;
	flagPunto=0;
	deteccion=-1;
	if(cadenaFloat!=NULL && strlen(cadenaFloat)>0)
	{
		for(int i=0; cadenaFloat[i]!='\0'; i++)
		{
			if(i==0 && (cadenaFloat[i]=='-' || cadenaFloat[i]=='+'))
			{
				continue;
			}
				if(cadenaFloat[i]>=48 && cadenaFloat[i]<=57)
				{
						deteccion=0;
				}
				else if(flagPunto==0 && cadenaFloat[i]== 46)
				{
					flagPunto=-1;
				} else {
					deteccion=-1;
					break;
				}

		}
	}


	return deteccion;
}
static int getInt(int* pResultado)//esta funcion en complemento de getFloat(debe cambiar el nombre) por eso es static
{
	int deteccion=-1;
	char buffer[64];

	if(pResultado!=NULL)
	{
		if(myGets(buffer,sizeof(buffer))==0 && validarEntero(buffer)==0)//luego con validarFloat, valido si la funcion ingresado por myGet sea numero, en este caso un numero float.
		{
			puts("dentro de getint");
			*pResultado=atoi(buffer);
			deteccion=0;
		}
	}

	return deteccion;
}

static int getFloat(float* pResultado)//esta funcion en complemento de getFloat(debe cambiar el nombre) por eso es static
{
	int deteccion=-1;
	char buffer[64];//creo una array de tipo array para almacenar lo que el usuario ingrese

	if(pResultado!=NULL)
	{//se usa la funcion myGet para pedir una cadena para
		if(myGets(buffer,sizeof(buffer))==0 && validarFloat(buffer)==0)//luego con validarFloat, valido si la funcion ingresado por myGet sea numero, en este caso un numero float.
		{
			*pResultado=atof(buffer);//esta funcion es para convertir las cadena de char en float, osea debe tener un punto (.)
			deteccion=0;//valido que salio bien con el 0
		}
	}

	return deteccion;
}
static int validarEntero(char charDeEnteros[])
{
	int deteccion;
	deteccion=-1;
	if(charDeEnteros!=NULL && strlen(charDeEnteros)>0)
	{
		for(int i=0; charDeEnteros[i]!='\0'; i++)
		{
			if(i==0 && (charDeEnteros[i]=='-' || charDeEnteros[i]=='+'))
			{
				continue;
			}

			if(charDeEnteros[i]>=48 && charDeEnteros[i]<=57)//donde 48=0 y 57=9 en ascii
			{
				deteccion=0;//osea que esta saliendo bien.

			}
			else
			{
				puts("ERROR EN LA LINEA 312//funcion: validaENtero");//borrar
				deteccion=-1;
				break;
			}
			printf("\ndeteccion devuelve un: %d\n", deteccion);

		}
	}
	return deteccion;
}





//funciones static para el pedir_texto

static int validarTexto(char cadenaDeCaracteres[])
{
	int deteccion;
	deteccion=-1;
	if(cadenaDeCaracteres!=NULL && strlen(cadenaDeCaracteres)>0)
	{
		for(int i=0; cadenaDeCaracteres[i]!='\0'; i++)
		{

				if((cadenaDeCaracteres[i]>='a' && cadenaDeCaracteres[i]<='z')||(cadenaDeCaracteres[i]>='A' && cadenaDeCaracteres[i]<='Z') || cadenaDeCaracteres[i]==164)//donde 48=0 y 57=9 en ascii
				{
						deteccion=0;//osea que esta saliendo b
						puts("Salio bien");
				}
				else
				{
					deteccion=-1;
					puts("\nSalio mal, en funcion validarTexto\n");
					break;
				}

		}
	}
	return deteccion;
}



static int validar_Correo(char cadenaDeCaracteres[])
{
	int deteccion;
	int flagArroba;
	flagArroba=0;
	deteccion=-1;
	if(cadenaDeCaracteres!=NULL && strlen(cadenaDeCaracteres)>0)
	{
		for(int i=0; cadenaDeCaracteres[i]!='\0'; i++)
		{
				if((flagArroba==0 && cadenaDeCaracteres[i]==64)||(cadenaDeCaracteres[i]>='a' && cadenaDeCaracteres[i]<='z')||(cadenaDeCaracteres[i]>='A' && cadenaDeCaracteres[i]<='Z') || cadenaDeCaracteres[i]==96 )//donde 48=0 y 57=9 en ascii
				{
					flagArroba=-1;
					deteccion=0;
				}
				else
				{
					deteccion=-1;
					break;
				}

		}
	}
	return deteccion;
}






static int validarDireccion(char cadenaDeCaracteres[])
{
	int deteccion;
	deteccion=-1;


	if(cadenaDeCaracteres!=NULL && strlen(cadenaDeCaracteres)>0)
	{
		for(int i=0; cadenaDeCaracteres[i]!='\0'; i++)
		{
				if((cadenaDeCaracteres[i]>='0' && cadenaDeCaracteres[i]<='9')
						||(cadenaDeCaracteres[i]>='a' && cadenaDeCaracteres[i]<='z')
						||(cadenaDeCaracteres[i]>='A' && cadenaDeCaracteres[i]<='Z')
						|| cadenaDeCaracteres[i]==96 )//donde 48=0 y 57=9 en ascii
				{
					deteccion=0;
				}
				else
				{
					deteccion=-1;
					break;
				}

		}
	}
	return deteccion;
}


int pedir_NumeroTexto(char cadenaDeCaracteres[], char* mensaje, char* mensajeError, int reintentos)
{

	int deteccion;
	int i;
	char bufferChar[64];
	deteccion=-1;

	if(cadenaDeCaracteres!=NULL && mensaje!=NULL && mensajeError!=NULL && reintentos!=0)
	{
		for(i=0; i<reintentos; i++)
		{
			printf("%s", mensaje);

			if(myGets(bufferChar,sizeof(bufferChar))==0 && validarNumeroTexto(bufferChar)==0)
			{
				deteccion=0;
				strcpy(cadenaDeCaracteres, bufferChar);
						break;
			}
			else
			{
				printf("%s", mensajeError);//mensaje de error por si la cosa se pone complicada xd
			}
			}
		}

		return deteccion;
	}



static int validarNumeroTexto(char cadenaDeCaracteres[])
{
	int deteccion;
	deteccion=-1;
	if(cadenaDeCaracteres!=NULL && strlen(cadenaDeCaracteres)>0)
	{
		for(int i=0; cadenaDeCaracteres[i]!='\0'; i++)
		{

				if((cadenaDeCaracteres[i]>='0' && cadenaDeCaracteres[i]<='9'))//donde 48=0 y 57=9 en ascii
				{
						deteccion=0;//osea que esta saliendo b
						puts("Salio bien de la funcion [validarNumeroTexto]");
				}
				else
				{
					deteccion=-1;
					puts("\nSalio mal, en funcion validarNumeroTexto\n");
					break;
				}

		}
	}
	return deteccion;
}


/**
 * \brief Crea un id de manera creciente
 * \param void
 * \return Retorna numeroMagico que sera un numero que ira creciendo cada vez que se llame
 */
int crearId(void)
{
  static int numeroMagico=0;

		numeroMagico++;

	return numeroMagico;
}
