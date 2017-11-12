#include "myheader.h"

DIR *dp;
struct dirent *dirp;
struct stat info;

void deleting(char *);

void myrm()
{
    int count = 0;

    if(options[0] == NULL)
    {
	printf("usage error! : usage -> myrm (-rf) [filename]\n");
	return ;
    }

    if(strcmp(options[0],"--help")==0)
    {
	printf("usage -> myrm (-rf) [filename]\n");
	printf("remove [filename]\n");
	printf("-rf option : delete all filename's path\n");
	return ;
    }


    if(options[0] !=NULL  && options[1]==NULL)  
    {
	//if file
	dp=opendir(options[0]);
	if(dp==NULL)
	{
	    dp = opendir(".");
	    while(dirp = readdir(dp))//implementation
	    {
		if(strcmp(dirp->d_name,options[0])==0)
		{
		    if(remove(options[0])!=0)
		    {
			printf("remove error!\n");
			return ;
		    }
		    count++;
		}
	    }
	    if(count ==0)
		printf("the file do not exist\n");
	}
	else //if dir
	{
	    printf("it is directory! it can't be deleted!\n");
	    return ;

	}


    }
    else  if(options[0]!=NULL && options[1]!=NULL )  
    {
	if(strcmp(options[0],"-rf")==0)
	{
	    int count = 0;
	    //if file
	    dp=opendir(options[1]);
	    if(dp==NULL)
	    {
		dp = opendir(".");
		while(dirp = readdir(dp))//implementation
		{
		    if(strcmp(dirp->d_name,options[1])==0)
		    {
			if(remove(options[1])!=0)
			{
			    printf("remove error!\n");
			    return ;
			}
			count++;
		    }
		}
		if(count ==0)
		    printf("the file or directoy do not exist\n");
	    }
	    else //if dir
	    {
		closedir(dp);
		deleting(options[1]);		//recursice call

	    }

	}
	else
	{
	    printf("usage error! : usage -> myrm (-rf) [filename]\n");
	    return;
	}

    }
    else if(options[0]==NULL)
    {
	printf("usage error! : usage -> myrm (-rf) [filename]\n");
	return;
    }

}

void deleting(char * path)		//recursive delete
{
    DIR * dp2;
    struct dirent *dirp2;
    struct stat info2;
    char pathbuf[1024];

    chdir(path);
    getcwd(pathbuf,1024);
    dp2 = opendir(pathbuf);

    while(dirp2 = readdir(dp2))//implementation
    {
	if((strcmp(dirp2->d_name,".")==0) ||(strcmp(dirp2->d_name,"..")==0))
	    continue;
	lstat(dirp2->d_name,&info2);

	if(S_ISDIR(info2.st_mode))
	    deleting(dirp2->d_name);
	else
	{
	    if(remove(dirp2->d_name)!=0)
	    {
		printf("remove error!\n");
		return ;
	    }
	}


    }

    closedir(dp2);
    chdir("..");
    rmdir(path);

    return ;
}
