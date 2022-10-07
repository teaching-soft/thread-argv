/***************************************************************************
	file				 : main.c 	
    begin                : 2019
    copyright            : (C) 2019 by Giancarlo Martini and friends
    email                : gm@giancarlomartini.it
                                                                          
    This program is free software; you can redistribute it and/or modify  
    it under the terms of the GNU General Public License as published by  
    the Free Software Foundation; either version 2 of the License, or     
    (at your option) any later version.                                   
                                                                         
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

// Dichiarazione della struttura per il passaggio delle info
struct th_info {
	int th_index;
};

// Funzione che viene chiamata quando si avvia il thread
void *th_function(void *struct_info)
{
	// Info passate al thread
	struct th_info *struct_ptr = (struct th_info *)struct_info;
	// Prende l'id del thread
	pthread_t tid = pthread_self();
	// Stampa un pò di info
	printf("TID: %ld  |  INDEX: %d  | PTR: %p\n", tid, struct_ptr->th_index,
	       struct_ptr);
	// Libera la memoria allocata per la struttura
	free(struct_ptr);
}

int main(int argc, char *argv[])
{
	// Controlla che sia stata specificato il numero di thread sulla linea di comando 
	if (argc < 2) {
		printf("ERRORE, non è stato specificato il numero di tread\n");
		exit(1);
	}
	// Recupera il numero di thread da copiare e lo converte in int
	int n_thread = atoi(argv[1]);

	pthread_t tid;
	for (int i = 0; i < n_thread; i++) {
		// Crea la struttura che conterrà le info allocandone la memoria
		struct th_info *ti = malloc(sizeof(struct th_info));
		// Imposta il valore di indice del thread
		ti->th_index = i;
		// Stampa un pò di info
		printf("Avvio il thread %d - %p\n", i, ti);
		// Crea/Avvia ilthread
		pthread_create(&tid, NULL, th_function, ti);
	}
	// Esce quando sono initi tutti i thread
	pthread_exit(0);
}
