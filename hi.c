//Including libraries
#include <stdio.h>
#include <string.h>

//Defining colors to highlight searched words
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

//Declaring functions
void title();
int prompt();
void newFile();
void edit();
void saveAs();
void search();
void compare();
void deleteFile();
void again();

int main()
{
    //Printing the title of the program
    title();

    //Prompting the user to initiate a process
    int selection;
    selection = prompt();

    //Validating Input
    while ((selection < 1 || selection > 6))
    {
        printf("Please enter a number between 0 and 6\n");
        printf("Select an option: ");
        scanf("%d", &selection);
    }

    //Initiating the user selected process
    switch (selection)
    {
        case 1:
            newFile();
            break;

        case 2:
            edit();
            break;

        case 3:
            saveAs();
            break;

        case 4:
            search();
            break;

        case 5:
            compare();
            break;

        case 6:
            deleteFile();
            break;
    }

    //Asking the user to use the program again
    again();

    return 0;
}

void title()
{
    printf("                    _____  ____  \\   /  _____       ____   __    _____  _____   ___    ___\n");
    printf("                      |   |       \\_/     |        |      |  \\     |      |    |   |  |___|\n");
    printf("                      |   |----   / \\     |        |----  |   |    |      |    |   |  |\\\n");
    printf("                      |   |____  /   \\    |        |____  |__/   __|__    |    |___|  | \\\n\n");
}

int prompt()
{
    printf("FOR CREATING A NEW FILE:                                   PRESS 1\n");
    printf("FOR EDITING A FILE:                                        PRESS 2\n");
    printf("FOR SAVING A FILE AS ANOTHER FILE WITH A DIFFERENT NAME:   PRESS 3\n");
    printf("FOR SEARCHING A WORD OR A PATTERN IN A FILE:               PRESS 4\n");
    printf("FOR CHECKING IF TWO FILES ARE EXACTLY SAME:                PRESS 5\n");
    printf("FOR DELETING A FILE:                                       PRESS 6\n");
    printf("Select an option: ");
    int selection;
    scanf("%d", &selection);
    return selection;
}

void newFile()
{
    //Prompt the user for filename
    printf("Enter the name of file to be created: ");
    char fileName[20];
    scanf("%s", fileName);

    //Creating a file
    FILE *fp = fopen(fileName, "w");

    //Writing to the file
    char c;
    printf("\n\n\nEnter the text\nPress Escape Key and then Enter key to exit.\nThe editor will stop taking input once the escape key is pressed.\n");
    scanf(" %c", &c);
    fputc(c, fp);
    while (1)
    {
        scanf("%c", &c);

        //Saving and exiting the file
        if (c == 27)
        {
            fclose(fp);
            printf("File created Successfully.\n");
            break;
        }

        fputc(c, fp);
    }
}

void edit()
{
    int temp;
    int lineNumber = 1;
    int numberOfLines = 1;
    char line[1000];
    char c;
    //Prompt the user for filename
    printf("Enter the name of file to be edited: ");
    char fileName[20];
    scanf("%s", fileName);

    //checking a file
    FILE *fp = fopen(fileName,  "r");
    if (fp == NULL)
    {
        printf("File does not exist.\n");
        return;
    }

    //Displaying the file contents with line numbers
    printf("1) ");
    while (!feof(fp))
    {
        c = fgetc(fp);
        printf("%c", c);
        if (c == '\n')
        {
            numberOfLines++;
            printf("%d) ", numberOfLines);
        }
    }
    fclose(fp);

    //prompting the user to edit according to line number
    while (1)
    {
        printf("\nEnter the line number to be edited: ");
        scanf("%d", &lineNumber);
        if (lineNumber <= numberOfLines && lineNumber > 0)
        {
            break;
        }
    }

    //Displaying till the desired line
    FILE *fp1 = fopen(fileName, "r");
    FILE *fp2 = fopen("temp", "w");
    temp = 1;
    while (temp != lineNumber)
    {
        c = fgetc(fp1);
        fputc(c, fp2);
        printf("%c", c);
        if (c == '\n')
        {
            temp++;
        }
    }

    //moving fp1 to the next line
    do
    {
        c = fgetc(fp1);
    }
    while (c != '\n');

    printf("\n\n To exit the editing mode press the Escape key and then Enter key.\n");
    //Entering the text
    scanf(" %c", &c);
    fputc(c, fp2);
    while (1)
    {
        scanf("%c", &c);
        if (c == 27)
        {
            break;
        }
        fputc(c, fp2);
    }


    //Printing the rest
    fputc('\n', fp2);
    while (!feof(fp1))
    {
        c = fgetc(fp1);
        if (c != EOF)
        {
            fputc(c, fp2);
            printf("%c", c);
        }
    }
    fclose(fp1);
    fclose(fp2);

    //Copying temp to mainfile
    fp1 = fopen("temp", "r");
    fp2 = fopen(fileName, "w");

    //Copying the file
    while (!feof(fp1))
    {
        c = getc(fp1);
        if (c != EOF)
        {
            fputc(c, fp2);
        }
    }

    //Closing both files and removing temp
    printf("\nFile Edited Successfully.\n");
    fclose(fp1);
    fclose(fp2);
    remove("temp");
}

void saveAs()
{
    char file1[20];
    char file2[20];
    FILE *fp1;
    FILE *fp2;

    //Prompting the user for entering the name of the file to be copied
    printf("Enter the name of existing file which is to be copied: ");
    scanf("%s", file1);
    fp1 = fopen(file1, "r");

    //Checking if the file exists
    if (fp1 == NULL)
    {
        printf("File does not exist.\n");
        return;
    }

    //Prompting the user for the name of new file
    printf("Enter the name of new file: ");
    scanf("%s", file2);
    fp2 = fopen(file2, "w");

    //Copying the file
    char c;
    while (!feof(fp1))
    {
        c = getc(fp1);
        if (c != EOF)
        {
            fputc(c, fp2);
        }
    }

    //Closing both files
    printf("File copied Successfully.\n");
    fclose(fp1);
    fclose(fp2);
}

void search()
{
    FILE *fp1;
    char c, word[100], fileName[20];

    //Prompting for filename and the word to be searched
    printf("Enter the name of the file: ");
    scanf("%s", fileName);
    fp1 = fopen(fileName, "r");
    if (fp1 == NULL)
    {
        printf("File does not exist.\n");
    }
    printf("Enter the word or pattern you want to search: ");
    scanf(" %[^\n]", word);
    char temp[strlen(word)];
    strcpy (temp, word);

    //Printing all text and highlighting the required pattern/word
    while (!feof(fp1))
    {
        c = fgetc(fp1);
        if(c == word[0])
        {
            temp[0] =  c;
            for (int i = 1; i < strlen(word); i++)
            {
                c = fgetc(fp1);
                temp[i] = c;
            }
            if (!strcmp(word, temp))
            {
                printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, temp);
            }
            else
            {
                printf("%s", temp);
            }
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
}

void compare()
{
    char file1[20];
    char file2[20];
    FILE *fp1;
    FILE *fp2;

    // prompting  the  user for filenames and checking the file's existence
    printf("Enter the name of the first file: ");
    scanf("%s", file1);
    fp1 = fopen(file1, "r");
    if (fp1 == NULL)
    {
        printf("File does not exist.\n");
    }
    printf("Enter the name of the second file: ");
    scanf("%s", file2);
    fp2 = fopen(file2, "r");
    if (fp2 == NULL)
    {
        printf("File does not exist.\n");
    }

    //Comparing both files
    char c1;
    char c2;
    while (!feof(fp1) || !feof(fp2))
    {
        c1 = getc(fp1);
        c2 = getc(fp2);
        if (c1 != c2)
        {
            printf("Both files are different.\n");
            return;
        }
    }
    printf("Both files are same.\n");
}

void deleteFile()
{
    char fileName[20];
    FILE *fp;
    //Prompting the user for filename
    printf("Enter the name of file to be deleted: ");
    scanf("%s", fileName);

    //Checking if the file exists
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("File does not exit.\n");
        return;
    }
    fclose(fp);

    //Deleting the file
    remove(fileName);
    printf("File deleted Successfully.\n");
}

void again()
{
    //Asking if user wants to use the program again
    char again;
    printf("Do you want to use the text editor again? (y/n)\n");
    scanf(" %c", &again);
    if (again == 'y')
    {
        main();
    }
    else
    {
        return;
    }
}
