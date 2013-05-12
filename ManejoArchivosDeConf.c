/*
* Archivo de configuracion
* recibir un string y buscar
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int puerto;
	int thread;
	int timeout;//default
	char *logpath;
	char *logfile;
}propiedades;

char *copiar(char *, int *);

int main(void){
	char * leido ="Puerto =1234#012Thread =10#012#011timeout =10#011logpath =/home/user/Escritorio/daemon#011logfile =demonio.log";
	char * resultado;
	char * temp;
	int tam=0, i,cont=0;
	propiedades config;
	
/*encontramos la posicion de los numeros y longitudes*/	
	resultado=copiar(leido,&tam);
/*copiamos los numeros y paths donde corresponden*/
	while(cont<5){
		temp = (char *)malloc( tam*sizeof(char) );
		if (temp==NULL) {
            		printf( "error en malloc\n");
            		exit;
        	}
			if(cont==0){
				strncpy(temp,resultado,tam);
				config.puerto=atoi(temp);
			}else if(cont== 1){
				strncpy(temp,resultado,tam);
				config.thread=atoi(temp);
			}else if(cont ==2){
				strncpy(temp,resultado,tam);
				config.timeout=atoi(temp);
			}else if(cont ==3){
				strncpy(temp,resultado,tam);
				config.logpath= (char *) malloc (tam*sizeof(char)); //cambio1 pero a mi me sale con basura jaja
				strcpy(config.logpath, temp);
			}else if(cont==4){
				strncpy(temp,resultado,tam); 
				config.logfile= (char *) malloc (tam*sizeof(char)); //cambio2
				strcpy(config.logfile, temp); 
			}
		cont++;
		if(cont<5){
			resultado=copiar(resultado,&tam);
		}
		free(temp);//al liberar memoria se pierde tu char por eso el strcpy
	}	
	printf("la estructura es\n ->puerto=%d\n ->thread=%d\n ->timeout=%d\n ->logpath=%s\n ->logfile=%s\n", config.puerto, config.thread, config.timeout, config.logpath, config.logfile);
return 0;
system ("pause");
}

char *copiar(char *leido, int *prueba){
char *responder;
char *separador;

	responder = strstr(leido,"=")+1;
	while(responder[0]==32)// cambio3: por si hay varios espacios jaja! Optimizado como dice nuestro amigo MMartinez
	{
		responder=responder+1;//cambio4: ya sabés que en la primera posición está tu espacio ¬¬
	}
	separador = strstr(responder,"#");
	*prueba=separador-responder;
	if(separador==NULL){
		separador = strstr(responder,"\0");
		*prueba=strlen(responder);
	}	
	
return responder;
}
