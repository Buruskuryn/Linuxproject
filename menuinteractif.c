#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int confirmation;

void handler(int signal)
{
	char choix;
	if (signal==SIGINT)
	{
		printf(" Confirmer l'arret : ");
		scanf("%c",&choix);	
		if (choix == 'o' )
			confirmation = 1;
	}
}	


int main( int argc, char * argv[])
{
	char c = '\0';
	printf ("\n[Mini_Shell]>>");
	do
	{
		c = getchar();
		if (c == '\n' )
			printf("[Mini_shell]>>");
		if (signal(SIGINT,handler)== SIG_ERR)
		{
		perror("SIGINT");
		exit(1);
		}
	}while (confirmation != 1);
	fflush(stdout);
	return 0;
}
