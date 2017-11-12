#include "myheader.h"

void mymkdir()
{
    int check=-1;
    int i=0;
    int a=0;
    char currentdirectory[1024];
    char * token[20];
    getcwd(currentdirectory,1024);

    if(options[0] == NULL)
    {
	printf("usage error! : usage -> mymkdir (-p) [directory]\n");
	return ;
    }

    if(strcmp(options[0],"--help")==0)
    {
	printf("usage -> mymkdir (-p) [directory]\n");
	printf("make [directory]\n");
	printf("-p option : make all directory's path\n");
	return ;
    }

    if(options[2]!=NULL)
    {
	printf("usage error! : usage -> mymkdir (-p) [directory]\n");
	return ;
    }
    if(options[1]!=NULL) //two index
    {
	if(strcmp(options[0],"-p")==0)
	{
	    token[i] = strtok(options[1],"/");
	    while(token[i]!=NULL)
	    {
		i++;
		token[i] = strtok(NULL,"/");
	    }

	    for(a=0;a<i;a++)
	    {
		if(chdir(token[a])==0)			//change dir to present dir
		{
		    if(a == i-1)
		    {
			printf("this directory exists alreadey\n");
			chdir(currentdirectory);
		    }
		}
		else
		{
		    mkdir(token[a],0777);		//make dir and change to the dir
		    chdir(token[a]);
		    if(a == i-1)
		    {
			getcwd(buff,1024);
			printf("%s\n",buff);
			chdir(currentdirectory);
		    }
		}
	    }
	}
	else
	{
	    printf("this option is not correct! usage -> mkdir (-p) [directory]\n");
	    return;
	}

    }
    else// if((check = mkdir(options[0],0777)))
    {
	check = mkdir(options[0],0777);

	if(check != 0)
	    printf("this is not correct path!!!\n");
	else
	{
	    chdir(options[0]);

	    getcwd(buff,1024);
	    printf("%s\n",buff);
	    chdir(currentdirectory);
	}

    }
}
