#include "myheader.h"

DIR *dp;
struct dirent *dirp;
struct stat info;
char prevel[11];
struct passwd *uid;
struct group *gid;
char * ttime;
char path[1000];
int check=0;

void saving();

void myls()
{

    getcwd(path,1024);
    if(options[0] !=NULL  && options[1]==NULL) 
    {
	if(strcmp(options[0],"--help")==0)
	{
	    printf("usage -> myls (FILENAME)\n");
	    printf("print FILENAME's infomation\n");
	    printf("if there is no FILENAME, print all file's infomation in current directory\n");
	    return ;
	}

	if(strcmp(options[0],"-a")==0)
	{
	    dp = opendir(path);

	    while(dirp = readdir(dp))//implementation
		saving();
	}
	else
	{
	    int count = 0;

	    //if file
	    if(strncmp(options[0],"/",1)==0)		//absolute path
	    {
		dp = opendir(options[0]);
		check =1;
	    }
	    else					//relative path
	    {
		strcat(path,"/");
		strcat(path,options[0]);
		dp=opendir(path);
	    }


	    if(dp==NULL)
	    {
		getcwd(path,1024);
		dp = opendir(path);
		while(dirp = readdir(dp))//implementation
		{
		    if(dirp->d_name[0]=='.')
			;
		    else if(strcmp(dirp->d_name,options[0])==0)
		    {
			saving();
			count++;
		    }
		}
		if(count ==0)
		    printf("the file or directoy do not exist\n");
	    }
	    else //if dir
	    {
		while(dirp = readdir(dp))//implementation
		{
		    if(dirp->d_name[0]=='.')
			;
		    else
			saving();
		}

	    }

	}

    }
    else  if(options[0]!=NULL && options[1]!=NULL )  
    {
	if(strcmp(options[1],"-a")==0)
	{
	    int count = 0;
	    //if file

	    if(strncmp(options[0],"/",1)==0)		//absolute path
	    {
		dp = opendir(options[0]);
		check =1;
	    }
	    else					//relative path
	    {
		strcat(path,"/");
		strcat(path,options[0]);
		dp=opendir(path);
	    }

	    if(dp==NULL)
	    {
		getcwd(path,1024);
		dp = opendir(path);
		while(dirp = readdir(dp))//implementation
		{
		    if(strcmp(dirp->d_name,options[0])==0)
		    {
			saving();
			count++;
		    }
		}
		if(count ==0)
		    printf("the file or directoy do not exist\n");
	    }
	    else //if dir
	    {
		while(dirp = readdir(dp))//implementation
		    saving();

	    }

	}
	else
	{
	    printf("usage error! : usage -> myls [filename] (-a)\n");
	    return;
	}

    }
    else if(options[0]==NULL)
    {
	dp = opendir(path);
	while(dirp = readdir(dp))//implementation
	{
	    if(dirp->d_name[0]=='.')
		;
	    else
		saving();
	}

    }

}

void saving()
{
    memset(prevel,'-',10);
    char str[1000];
    if(check==1)
    {
	lstat(options[0],&info);
	check=0;
    }
    else if(check==0)
    {
	sprintf(str,"%s/%s",path,dirp->d_name);
	lstat(str,&info);
    }


    if(S_ISREG(info.st_mode))
	prevel[0] = '-';
    else if(S_ISDIR(info.st_mode))
	prevel[0] = 'd';
    else if(S_ISCHR(info.st_mode))
	prevel[0] = 'c';
    else if(S_ISBLK(info.st_mode))
	prevel[0] = 'b';
    else if(S_ISFIFO(info.st_mode))
	prevel[0] = 'f';
    else if(S_ISLNK(info.st_mode))
	prevel[0] = 'l';
    else if(S_ISSOCK(info.st_mode))
	prevel[0] = 's';

    if(info.st_mode & S_IRUSR)
	prevel[1]='r';
    if(info.st_mode & S_IWUSR)
	prevel[2]='w';
    if(info.st_mode & S_IXUSR)
	prevel[3]='x';
    if(info.st_mode & S_IRGRP)
	prevel[4]='r';
    if(info.st_mode & S_IWGRP)
	prevel[5]='w';
    if(info.st_mode & S_IXGRP)
	prevel[6]='x';
    if(info.st_mode & S_IROTH)
	prevel[7]='r';
    if(info.st_mode & S_IWOTH)
	prevel[8]='w';
    if(info.st_mode & S_IXOTH)
	prevel[9]='x';


    uid = getpwuid(info.st_uid);
    gid = getgrgid(info.st_gid);
    ttime = ctime(&info.st_mtime);
    ttime[(strlen(ttime)-1)]='\0';
    printf("%s %3d %s %s %d %s %s\n",prevel,(int)info.st_nlink,uid->pw_name,gid->gr_name,info.st_size,ttime,dirp->d_name);


}
