#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>

#define couleur(param) printf("\033[%sm",param) //Cette ligne permet de modifier facilement la couleur dans le programme.

struct dirent* fichier;

void clearScreen()  //Cette fonction a pour but d'"effacer" le contenu de l'écran en effectuant un scroll.
{
	printf("\033[2J\033[1;1H");
	
}

void renommer(char* arg1,char* arg2) 
{
	couleur("31"); //Tous les commentaire qui sont toujours pour cette fonction des erreurs s'afficheront en rouge
	if(strlen(arg1)&&strlen(arg2))
	{
		if(!strcmp(arg1,arg2))
		{	
			printf("Opération impossible : le fichier source et le fichier destination sont les mêmes.\n");
		}
		else{if(rename(arg1,arg2))printf("Impossible de renommer ce fichier : %s n'existe pas.\n",arg1);}
	}
	else{printf("Veuillez saisir le nom de la source puis un nom de destination.\n");}
	couleur("0");
}

void supprimer(char* arg)
{
	couleur("31");
	if(remove(arg))printf("Suppression de %s impossible : ce fichier n'existe pas.\n",arg);
	couleur("0");
}

void diviserSaisie(char* saisie,char arg1[],char arg2[])
{
	char cmd[50]; //Pour séparer la saisie de la premiere partie de saisie.
	arg1[0]='\0'; //on initialise à zéro les arguments.
	arg2[0]='\0';
	unsigned int i=0;
	while((i<strlen(saisie)-1)&&(saisie[i]!=' ')&&(saisie[i]!='\n')) //On remplit cmd par le premier terme de la saisie.
	{
		cmd[i]=saisie[i];
		i++;
	}
	cmd[i]='\0'; // On indique que le terme est terminé.
	i++;
	unsigned int j=0;
	while((i+j<strlen(saisie)-1)&&(saisie[i+j]!=' ')&&(saisie[i+j]!='\n')) //on fait la même chose pour le premier argument...
	{
		arg1[j]=saisie[i+j];
		j++;
	}
	arg1[j]='\0';
	j++;
	unsigned int k=0;
	while((i+j+k<strlen(saisie)-1)&&(saisie[i+j+k]!=' ')&&(saisie[i+j+k]!='\n')) //... et pour le second.
	{
		arg2[k]=saisie[i+j+k];
		k++;
	}
	strcpy(saisie,cmd);

}

void help()
{
	couleur("32"); //Le texte s'affichera en vert.
	printf("---Liste des commandes disponibles---\n");
	printf("changePrompt : permet d'activer ou de désactiver l'affichage du chemin du répertoire courant dans le prompt.\n");
	printf("cd <arg> : permet de se déplacer vers le répertoire arg.\n");
	printf("exit : quitter le shell.\n");
	printf("help : afficher la liste des commandes disponibles.\n");
	printf("Lister <arg> : afficher le contenu du répertoire <arg>.\n");
	printf("Lister_RepC : affiche le contenu du répertoire courant.\n");
	printf("renommer <arg1> <arg2> : permet de renommer <arg2> un fichier nommé <arg1>.\n");
	printf("supprimer <arg> : Permet de supprimer le fichier nommé <arg>.\n");
	couleur("0");
}

void Lister_RepC()
{
	char repC[50];
	getcwd(repC,50); //On récupère le chemin du répertoire courant dans une chaîne de caractère.
	printf("Contenu du répertoire courant (%s) :\n",repC);
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
	char repC[50];
	getcwd(repC,50);
	printf("Contenu du répertoire %s/%s :\n",repC,direc);
	couleur("0");
	DIR* rep = opendir(direc); 
	if (rep)   
	{
		while ((fichier = readdir(rep)) != NULL)
		{
			if (strcmp(fichier->d_name,".") && strcmp(fichier->d_name,".."))
    			printf("%s  ", fichier->d_name);
		}
		printf("\n");
	}
	else //Si rep est nul, cela veut dire que le répertoire n'a pas été trouvé.
	{
		couleur("31");
		printf("Opération impossible : répertoire %s n'existe pas.\n",direc);
		couleur("0");
	}

}

void cd(char *direc)
{
	DIR * rep = opendir(direc);
	if (rep)
	{
		chdir(direc);
		closedir(rep);
	}
	else //De la même façon que pour la fonction Lister, si rep est nul, cela veut dire que le répertoire n'existe pas.
	{
		couleur("31");
		printf("Impossible d'aller vers %s : ce répertoire n'existe pas.\n",direc);
		couleur("0");
	}
}


int main()
{
	int q=0; //N'importe quelle valeur non nulle pour quitter
	int prompt=0; //Affiche le chemin du répertoire courant pour n'importe quelle valeur non nulle
	char* buf=(char*)malloc(50*sizeof(char)); //Correspond au chemin du repertoire courant
	if(!buf)
	{
		printf("Erreur malloc.");
		exit(-1);
	}
	char saisie[50]; //Correspond à la saisie de l'utilisateur
	char arg1[50]; //Premier argument
	char arg2[50]; //Deuxième argument
	
	clearScreen();
	while(!q)
	{
		if(prompt)getcwd(buf,50);
		else{buf[0]='\0';}
		saisie[0]='\0'; //mise à zéro de la saisie
		couleur("33");
		printf("%s:",buf); //On affiche le contenu de buf qui correspond à un prompt.
		couleur("0");
		//scanf("%s",saisie);
		fgets(saisie,sizeof(saisie),stdin); //Mieux qu'un scanf car le scanf s'arrête aux espaces.
		diviserSaisie(saisie,arg1,arg2); //permet d'interpréter la saisie en un fonction et des potentiels arguments
				
		if(!strcmp(saisie,"exit")) //strcmp renvoie 0 quand les deux chaînes sont identiques.
		{
			q=1; //Quand q=1 on sort de la boucle et le programme s'arrête.
		}
		else if(!strcmp(saisie,"changePrompt"))
		{
			if(!prompt)prompt=1;
			else{prompt=0;};
		}
		else if(!strcmp(saisie,"Lister_RepC"))
		{
			Lister_RepC();
		}
		else if(!strcmp(saisie,"Lister"))
		{
			Lister(arg1);
		}
		else if(!strcmp(saisie,"renommer"))
		{
			renommer(arg1,arg2);
		}
		else if(!strcmp(saisie,"supprimer"))
		{
			supprimer(arg1);
		}
		else if(!strcmp(saisie,"cd"))
		{
			cd(arg1);
		}
		else if(!strcmp(saisie,"help"))
		{
			help();
		}
		else //Si aucune des commandes ne correspond à la saisie, ça veut dire que la saisie est fausse.
		{
			couleur("31");
			printf("Commande introuvable, saisissez help pour afficher la liste des commandes disponibles.\n");
			couleur("0");
			
		}
	}
	free(buf); //On doit libérer la mémoire car il s'agissait d'une allocation dynamique.
	return 0;
}
