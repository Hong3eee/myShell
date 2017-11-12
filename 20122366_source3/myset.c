#include "myheader.h"

void myset()
{
    if(strcmp(options[0],"--help")==0)
    {
	printf("usage -> myset PATH [-n/-a] [target]\n");
	printf("you have to fill in the \"[\" between \"]\"\n");
	printf("-n option : overwrite [target] on PATH \n");
	printf("-a option : add [target] on PATH \n");
	return ;
    }

    if(options[2]==NULL)
    {
	printf("usage error! : usage -> myset PATH (-n/-a) [path]\n");
	return ;
    }
    if(strcmp(options[1],"-n")==0)
	setenv("PATH",options[2],1);
    else if(strcmp(options[1],"-a")==0)
    {
	char * tmp = getenv("PATH");
	strcat(tmp,":");
	strcat(tmp,options[2]);
	setenv("PATH",tmp,1);
    }
}
