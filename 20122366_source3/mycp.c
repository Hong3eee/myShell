#include "myheader.h"

void mycp()
{
    FILE * fp,* fp2;
    if(options[0] == NULL)
    {
	printf("usage error! : usage -> mycp [source] [dest]\n");
	return ;
    }

    if(strcmp(options[0],"--help")==0)
    {
	printf("usage -> mycp [source] [dest]\n");
	printf("copy source to dest\n");
	return ;
    }
    if(options[1]==NULL)
    {
	printf("usage error! : usage -> mycp [source] [dest]\n");
    	return;
    }

    if(access(options[1],F_OK)==0)
    {
	printf("dest file already exists\n");
	return;
    }

   if((fp = fopen(options[0],"r")) == NULL)
   {
       printf("source can't be read\n");
	return ;
   }  
  fp2 = fopen(options[1],"w");
  char buf[1024]= {};

      while(fgets(buf,1024,fp))		//copy all source's data to dest
	  fputs(buf,fp2);

      fclose(fp);
      fclose(fp2);
}
