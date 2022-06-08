#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <vector>

using namespace std;

///-------------------------------------PROIECT DROPBOX---------------------------------------------

vector<string> par;//vector unde: pe prima pozitie va fi retinut numele comenzii, iar pe urmatoarele pozitii - parametrii comenzii


///----------------------------------------LAUNCH COMMAND-------------------------------------------------
void FORK()
{
    const char *programname = "/mnt/c/users/teo/desktop/so/dbxcli-linux-amd64"; //SE INTRODUCE CALEA ABSOLUTA A PROGRAMULUI DE EXECUTAT
    const char **argv = new const char* [par.size() + 2];   // spatiu in plus pentru nume si NULL 
    argv [0] = programname;         // argv[0] = numele programului
    for (int j = 0;  j < par.size() + 1;  ++j)     // copierea argumentelor
             argv [j + 1] = par[j] .c_str();
    argv [par.size() + 1] = NULL; 
    
    pid_t myproc = fork();
    if (myproc == 0)
        execv(programname, (char**)argv);//executia programului :  dbxcli-linux-amd64
 
	waitpid(myproc, NULL, 0);
}

///-------------------------------------------LAST COMMAND------------------------------------------------
void end()
{
    string x;
    cin >> x;
    if (x == "Y" or x == "y")
        printf("\nStop:    ^C\n");
    else if (x == "N" or x == "n")
        printf("\n\nYou can introduce another command\n\n");
    else
    {
        printf("\n!!!!!!!!!        Y/N          !!!!!!!!!!!!!!!!!\n");
        end();
    }
}


///-------------------------------------------READ COMMANDS-----------------------------------------------
void read()
{
    string buf;
    printf("\033[1;35m\n----------DROPBOX------------\nPentru comenzi valabile:    --help\n\n\033[0m\n");
    while(1)
    {
        par.clear();

        cin >> buf;
        if(buf == "--help")
        {
            par.push_back(buf);
            FORK();      
            printf("\nExtra commands:\n  about       details");
        }
        else if (buf == "cp")
        {
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            printf("\033[1;35m \nCopy a file or folder to a different location in the user's Dropbox. If the source path is a folder all its contents will be copied.\n\033[0m\n");
            FORK();
        }
        else if (buf == "du")
        {
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            printf("\033[1;35m \n Display usage information:\n\033[0m\n");
            FORK();
        }
        else if (buf == "get")
        {
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            printf("\033[1;35m \n Download file...\n\033[0m\n");
            FORK();
        }
        else if (buf == "logout")
        {
            par.push_back(buf);
            printf("\033[1;35m \n Log out of the current session:\n\033[0m\n");
            FORK();
        }
        else if(buf == "ls")
        {
             par.push_back(buf);
             printf("\033[1;35m \n  List files and folders:\n\033[0m\n");
             FORK();
        }
        else if(buf == "mkdir")
        {
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            printf("\033[1;35m \n Created a new directory\n\033[0m\n");
            FORK();
        }
        else if (buf == "mv")
        {
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            printf("\033[1;35m \n Move files:\n\033[0m\n");
            FORK();
        }
        else if(buf == "put")
        {
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            printf("\033[1;35m \n  Upload files:\n\033[0m\n");
            FORK();
        }
        else if(buf == "restore")
        {
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            printf("\033[1;35m \n  Restore files:\n\033[0m\n");
            FORK();
        }
        else if (buf == "revs")
        {
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            printf("\033[1;35m \n  List file revisions:\n\033[0m\n");
            FORK();
        }
        else if (buf == "rm")
        {
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            printf("\033[1;35m \n  Remove file...\n\033[0m\n");
            FORK();
        }
        else if (buf == "search")
        {
            par.push_back(buf);
            cin >> buf;
            par.push_back(buf);
            printf("\033[1;35m \n Search:\n\033[0m\n");
            FORK();
        }
        else if(buf == "team")
        {
            par.push_back(buf);
            cin >> buf;
            if (buf == "info")
                par.push_back(buf);
            else if(buf =="add-member")
                par.push_back(buf);
            else if("list-groups")
                par.push_back(buf);
            else if("list-members")
                par.push_back(buf);
            else if("remove-member")
                par.push_back(buf);
            printf("\033[1;35m \n Team management commands:\n\033[0m\n");
            FORK();
        }
       else if (buf == "account")
         {
             par.push_back(buf);
             printf("\nACCOUNT INFORMATION:\n");
             printf("\033[1;35m \n Display account information:\n\033[0m\n");
             FORK();
         }
         else if (buf == "version")
         {
             par.push_back(buf);
             printf("\033[1;35m \n  Print version information:\n\033[0m\n");
             FORK();
         }
         else if(buf == "about")
        {
            printf("\033[1;34m  \n|| DROPBOX || \n  by Schipor Ioana Teodora & Chelaru Gabriela \n\033[0m\n");
        }
         else
         
         printf("\n\033[1;41m !!!WRONG COMMAND. Try again!!!\033[0m\n");

         printf("\n\nWas this the last command?  Y/N\n");
        end();
       
    }

}
int main()
{
    read();
	return 0;
}