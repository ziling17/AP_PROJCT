#include <stdio.h>
#include <string.h>

void hexEditor(char* filename);

int main()
{
    char filename[50];
    FILE *file;

    do{
        printf("\n_____________________________________________________________________________________________\n");
        printf("\nThis program is a HEX EDITOR that is able to show the content of a selected file,chosen by\n");
        printf("the user. The program will be TERMNATED, once'*'(asterisk)is entered.\n");
        printf("_____________________________________________________________________________________________\n");
        printf("Please Enter TEXT filename: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename , "\n")]= '\0';
        
        if(strcmp(filename, "*") == 0)
        {
            printf("\nProgram Terminated.");
            break;
        }
        
        file = fopen(filename, "rb");
        if(file == NULL)
        {
            printf("\nERROR!! PLEASE TRY AGAIN.");
            continue;
        }

        hexEditor(filename);
        fclose(file);
        printf("Press any key to CONTINUE...");
        getchar();
    while (getchar() != '\n');

    }while(1);
}

void hexEditor (char* filename)
{
    FILE *file;
    size_t no_bytes;
    int offset=0 , i;
    char buffer[10];
    long filesize; 
    
    file = fopen (filename, "rb");
    
    printf("\n\n___________________________________________________________________________________\n");
    printf("|%-10s|%-43s|%-26s|\n","  OFFSET","                 HEX VALUES"," CONTENT OF FILE IN ASCII");
    printf("|__________|___________________________________________|__________________________|\n");
    printf("|%-10s|%-43s|%-26s|\n"," ","  00  01  02  03  04  05  06  07  08  09  "," ");
    printf("|__________|___________________________________________|__________________________|\n");

    while((no_bytes = fread( buffer, 1 , sizeof(buffer) , file )) > 0)
    {
        //OFF SET
        printf("| %08d |",offset);
        offset += no_bytes ; 

        //HEX VALUES
        for(i=0 ; i<sizeof(buffer) ; i++)
        {
            if(i< no_bytes)
            {
                printf("  %02X",buffer[i]);
            }
            else
            {
                printf("    ");
            }
        }
        printf("   |        ");
        
        //ASCII VALUE
        for(i=0 ; i< sizeof(buffer) ; i++)
        {
            if(i< no_bytes)
            {
                if(buffer[i]>31 && buffer[i]<127)
                {
                    printf("%c",buffer[i]);
                }
                else
                {
                    printf(".");
                }
            }
            else
            {
                printf(" ");
            }
        }
    printf("        |\n");
    }

    filesize = ftell(file);
    printf("|__________|___________________________________________|__________________________|\n");
    printf("\tFILE NAME\t: %s",filename);
    printf("\n\tFILE SIZE\t: %d bytes\n\n",filesize);
    fclose(file);
}




