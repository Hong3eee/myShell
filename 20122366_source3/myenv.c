#include "myheader.h"

void myenv()
{
    char ** env = environ;

    FILE * fp;
    char * search;

    if(options[0] != NULL)
    {
	if(strcmp(options[0],"--help")==0)
	{
	    printf("usage -> myenv (STRING)\n");
	    printf("myenv : print all my environment variable\n");
	    printf("myenv STRING: print my STRING's environment variable\n");
	    return ;
	}
	if((search = getenv(options[0]))==NULL)
	    printf("the eniroment do not exist\n");
	else
	    printf("%s=%s\n",options[0],search);

    }
    else
    {
	while(*env)
	    printf("%s\n",*env++);
    }
}
