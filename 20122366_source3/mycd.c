#include "myheader.h"

void mycd()
{
    if(options[1]!=NULL)
    {
	printf("usage error! : usage -> cd [filename]\n");
	return;
    }
    if( options[0]==NULL || !strcmp(options[0],"~"))
	chdir("/home");
    else
    {
    if(strcmp(options[0],"--help")==0)
    {
	printf("usage -> mycd [FILENAME]\n");
	printf("change directory to [FILENAME]\n");
	printf("if there is no [FILENAME],change to home directory\n");
	return ;
    }

    if( chdir(options[0])!=0)
   	printf("this is not correct path!!!\n");
    }
}
