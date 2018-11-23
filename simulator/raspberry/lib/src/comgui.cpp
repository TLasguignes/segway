/*
 * Copyright (C) 2018 dimercur
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \author INSA Toulouse
 * \version 1.0
 * \date 20 Juillet 2017
 */

#include "comgui.h"

/**
	Fonction utilisée par le thread affichagepour initialisation de socket
*/

int init_socket(int port){

	//Initialisation de socket de Linux
	int sockfd;
	struct sockaddr_in serv_addr;
	char *serv_host;
	struct hostent *host_ptr; 

	//port = SERV_TCP_PORT;
	// changer localhost en adresse IP serveur (faire DEFINE à modifier par l'étudiant)
	serv_host = (char*)"localhost";
	//serv_host = (char*)ADRESSE_IP;

	if((host_ptr = gethostbyname(serv_host)) == NULL) {
		printf("gethostbyname error");
		exit(1);
	}

	if(host_ptr->h_addrtype !=  AF_INET) {
		printf("unknown address type");
		exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = 
	((struct in_addr *)host_ptr->h_addr_list[0])->s_addr;
	serv_addr.sin_port = htons(port);

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("can't open stream socket");
		exit(1);
	}
 
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("can't connect to server\n");
		exit(1);
	}
        
        printf("Connexion établie avec le server\n");
	return sockfd;
}


/**
	Fonction utilisée par le thread affichage afin d'ajouter à la trame d'envoi
	une information de type float.
	@params char * str : string qui doit être envoyé à l'affichage
	@params char label : label de la donnée (voir format d'envoi)
	@params float data : donnée
	@params int indice : indice de tableau
*/

void add_info_float(unsigned char * str, char label, float data,int * indice ){
	int ind= *indice;
	float tampon=100000.05f + data;
	unsigned char* f =(unsigned char*)&tampon;

	str[ind ++] = '<';
	str[ind ++] = label;
	str[ind ++] = f[0];
	str[ind ++] = f[1];
	str[ind ++] = f[2];
	str[ind ++] = f[3];
	str[ind++] = '\n';
	
	*indice=ind;
}

/**
	Fonction utilisée par le thread affichage afin d'ajouter à la trame d'envoi
	une information de type int.
	@params char * str : string qui doit être envoyé à l'affichage
	@params char label : label de la donnée (voir format d'envoi)
	@params int data : donnée
	@params int indice : indice de tableau
*/

void add_info_int(unsigned char * str, char label, int data,int * indice ){
	int ind= *indice;
	float tampon=100000.05f + data;
	unsigned char* f =(unsigned char*)&tampon;

	str[ind ++] = '<';
    	str[ind ++] = label;
    	str[ind ++] = f[0];
    	str[ind ++] = f[1];
    	str[ind ++] = f[2];
    	str[ind ++] = f[3];
	str[ind++] = '\n';
	
	*indice=ind;
}


/**
	Envoie une trame vers l'affichage
	@params int sock : numéro de socket
	@params char * msg : tableau de caractères à envoyer, maximum 256 caractères
*/
void send_trame(int sock, unsigned char * msg,int* indice){
	int j =* indice ;
	/* write a message to the server */
	write(sock, msg, j);
	*indice=0;
}
