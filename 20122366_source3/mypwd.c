#include "myheader.h"

void mypwd()
{
    if(options[0]==NULL)
    {
    getcwd(buff,1024);
    printf("%s\n",buff);
    }
    else 
    {
	if(strcmp(options[0],"--help")==0)
	{
	    printf("usage -> mypwd\n");
	    printf("show current directory\n");
	    return ;
	}
	else
	    printf("usage error! : usage -> mypwd\n");

    }
}
