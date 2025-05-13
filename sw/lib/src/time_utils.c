#include "time_utils.h"
#include <time.h>

//EPOCH: tiempo en milisegundos desde el 1 de enero de 1970

// Convierte una estructura struct tm (año, mes, día, hora, etc.) 
// en una cantidad de milisegundos desde el Epoch.
uint64_t tm_to_epoch_ms(struct tm* t) {

    //struct tm copy = *t;        // Copia local

    // mktime tambien normaliza tm para ajustar horas minutos y segundos y convierte tm a s
    //time_t s = mktime(&copy);   // Convierte a s desde Epoch ( tm -> s )

    //return (uint64_t)s * 1000;  // Convierte a ms y retorna  ( s -> return(ms) ) 
    //return -1;
}

// Convierte un valor en milisegundos desde Epoch a un 
// struct tm desglosado (con año, mes, día, hora, etc.).
void epoch_ms_to_tm(uint64_t ms, struct tm* t) {
 
    // time_t seconds = ms / 1000;             // Conversion de ms a s ( ms -> s )

    // gmtime trabaja con segundos y convierte ms a tm
    //struct tm* result = gmtime(&seconds);   // Convierte ms a tm ( ms -> tm )
    
    //*t = *result;                           // Copia tm a puntero
}