#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define couleur(param) printf("\033[%sm",param)

struct dirent* fichier;

void clearScreen() 
{
	printf("\033[2J\033[1;1H");
	
}

void changePrompt()
{
	couleur("31");
	char buffer[PATH_MAX +1];
	char *dos=getcwd(buffer,PATH_MAX +1);
	char *nom = getenv("USER");

	printf("%s/%s : ",nom,dos);
	couleur("34");
}

void Lister_RepC()
{
	couleur("0");
	DIR* rep = opendir("."); 
	if (rep)   
	{
		while ((fichier = readdir(rep)) != NULL)
		if (strcmp(fichier->d_name,".") && strcmp(fichier->d_name,".."))
    		printf("%s  ", fichier->d_name);
	}
	printf("\n");

	
}

void Lister(char *direc)
{
	couleur("0");
	DIR* rep = opendir(direc); 
	if (rep)   
	{
		while ((fichier = readdir(rep)) != NULL)
		{
			if (strcmp(fichier->d_name,".") && strcmp(fichier->d_name,".."))
    			printf("%s  ", fichier->d_name);
		}
	}
	printf("\n");

}

void cd(char *direc)
{
	DIR * rep = opendir(direc);
	if (rep)
	{
		chdir(direc);
		closedir(rep);
	}
	else
	printf("Le répertoire n'existe pas");
}



int main( int argc, char * argv[], char * envp[])
{
	clearScreen();
	char c[100];
	char direc[100];
	while(strcmp(c,"exit"))
	{
		changePrompt();	
		//gets(c);
		scanf("%s ",c);
		
		if (strcmp(c,"Lister_RepC")==0)
		{
			Lister_RepC();
		}
		if (strcmp(c,"Lister")==0)
		{
			scanf("%s",direc);
			Lister(direc);
		}
		if (strcmp(c,"cd")==0)
		{
			scanf("%s",direc);
			cd(direc);
		}
		
		
				

		
	}
	return 0;
}
