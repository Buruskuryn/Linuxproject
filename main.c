#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void help()
{
	printf("---Liste des commandes disponibles---\n");
	printf("exit : quitter le shell.\n");
	printf("help : afficher la liste des commandes disponibles.\n");
	printf("Lister_RepC : affiche le contenu du répertoire courant.\n");
	printf("changePrompt : permet d'activer ou de désactiver l'affichage du chemin du répertoire courant dans le prompt.\n");
}

void list()
{
	pid_t pid=fork();
	if(!pid)
	{
		execlp("ls","ls","-l",NULL);
	}
	else{while(wait(0)!=-1);}
}

int main()
{
	int q=0; //N'importe quelle valeur non nulle pour quitter
	int prompt=0; //Affiche le chemin du répertoire courant pour n'importe quelle valeur non nulle
	char* buf=(char*)malloc(50*sizeof(char)); //Correspond au chemin du repertoire courant
	if(!buf)
	{
		printf("Erreur malloc");
		exit(-1);
	}
	char saisie[50]; //Correspond à la saisie de l'utilisateur
	while(!q)
	{
		if(prompt)getcwd(buf,50);
		else{buf[0]='\0';}
		saisie[0]='\0'; //mise à zéro de la saisie
		printf("%s:",buf);
		scanf("%s",saisie);
		
		if(!strcmp(saisie,"exit"))
		{
			q=1;
		}
		else if(!strcmp(saisie,"changePrompt"))
		{
			if(!prompt)prompt=1;
			else{prompt=0;};
		}
		else if(!strcmp(saisie,"Lister_RepC"))
		{
			list();
		}	
		else if(!strcmp(saisie,"help"))
		{
			help();
		}
		else
		{
			printf("Commande invalide, saisissez help pour afficher la liste des commandes disponibles.\n");
		}
	}
	free(buf);
	return 0;
}
