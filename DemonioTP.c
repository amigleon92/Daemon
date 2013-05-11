/* Demonio parcial para choffis */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
//#include <time.h>
#include <syslog.h>

/* Archivo de configuración */
#define CONFIGFILE "/etc/demonio8.properties"
/* Longitud de lectura de propiedades del demonio*/
#define BUFLEN 256

typedef struct{
	int puerto= 8080;
	int thread= 10;
	int timeout= 10;//default
	char *logpath= "/home/lp3/log";
	char *logfile= "demonio8.log";
}propiedades;

int main(void){

    pid_t pid, sid;
    int openfile;

    /* 1ro. Creamos un hijo y el padre sale */	
    pid=fork();
    if (pid<0) {
        perror("error en fork");
        exit(EXIT_FAILURE);
    }
    if (pid>0) {
        /* En el padre, liberamos */
        exit(EXIT_SUCCESS);
    }

    /* En el hijo ... */
    /* Se abre el archivo de sistema */
    openlog("demoniotp", LOG_PID, LOG_DAEMON);

    /* Se lee el archivo de configuración */
    if((openfile = open(CONFIGFILE, O_RDONLY)) < 0) {
        syslog(LOG_ERR, "%s\n", "error al abrir CONFIGFILE");
        exit(EXIT_FAILURE);
    } else {
        /* Se lee el archivo de configuración */
        char readfile[BUFLEN]; /* Mantiene el valor leido */
        int len; /* La longitud del buffer  */

        if((len = read(openfile, readfile, BUFLEN)) < 0) {
            syslog(LOG_ERR, "%s\n", "error al leer CONFIGFILE");
            exit(EXIT_FAILURE);
        }
        readfile[len] = '\0';

        /* Cierra el archivo de configuración */
        if(close(openfile) < 0) {
            syslog(LOG_ERR, "%s\n", "error al cerrar CONFIGFILE");
            exit(EXIT_FAILURE);
        }


    /* 2do. Iniciamos una nueva sesión */
    if ((sid=setsid())<0) {
        perror("error en setsid");
        exit(EXIT_FAILURE);
    }

    /* 3ro. Hacemos de / el directorio actual */
    if ((chdir("/"))<0) {
        perror("error en chdir");
        exit(EXIT_FAILURE);
    }

    /* 4to. Restablecemos el modo de archivo */
    umask(0);

    /* 5to. Cerramos los descriptores de archivos innecesarios */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);


	 /* Hacemos el verdadero trabajo */
    len=strlen(ctime(&timebuf));
	/* Crea una estructura y se concatena el string para el path de log*/
    propiedades prop; 
    char *path;
	
    while (1) {

	
        char *buf=malloc(sizeof(char)*(len)+1);
        if (buf==NULL) {
            syslog(LOG_ERR, "%s\n", "error en malloc");
            exit(EXIT_FAILURE);
        }
	
        if ((fd=open(, O_CREAT | O_WRONLY | O_APPEND, 0600))<0) {
            syslog(LOG_ERR, "%s\n", "open");
            exit(EXIT_FAILURE);
        }
        time(&timebuf);
        strncpy(buf, ctime(&timebuf), len+1);
        write(fd, buf, len+1);
        close(fd);
        sleep(60);
    }

    /* Cierra el archivo de sistema y chau :P */
    closelog();
    exit(EXIT_SUCCESS);
    
    
    
	
    }
}
