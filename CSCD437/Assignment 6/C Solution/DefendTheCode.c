#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_STRING 50

void getName(char* firstOrLast, char* name);
void getFilename(char* inOrOut, char* name);
void strip(char* array);

int main()
{
    char firstName[MAX_STRING], lastName[MAX_STRING], inputFile[MAX_STRING], outputFile[MAX_STRING];

    getName("first", firstName);
    getName("last", lastName);
	getFilename("in", inputFile);
	getFilename("out", outputFile);

    printf("\r\n%s %s\r\n", firstName, lastName);
	printf("%s\r\n", inputFile);
	printf("%s\r\n", outputFile);

    combiner();

    return 0;
}

void getName(char* firstOrLast, char* name)
{
    int isValid = 0;
    char buff[MAX_STRING + 1];
    regex_t nameRegex;

	memset(buff, '\0', MAX_STRING);
	memset(name, '\0', MAX_STRING);
    regcomp(&nameRegex, "^[A-Za-z'-]{1,50}$", REG_EXTENDED);
    while (!isValid)
    {
        printf("Enter your %s name (50 or fewer characters)\r\n", firstOrLast);
        
        if (fgets(buff, MAX_STRING, stdin))
		{
			strip(buff);

			if (!regexec(&nameRegex, buff, 0, 0, 0))
			{
			isValid = 1;
			}

			else
			{
			printf("%s", "Invalid name\r\n");
			}
		}
	
		else
		{
			printf("%s", "Invalid name\r\n");
		}
    }

    strncpy(name, buff, strlen(buff));
    regfree(&nameRegex);
}

void getFilename(char* inOrOut, char* name)
{
	int isValid = 0;
	char buff[MAX_STRING + 1];
	regex_t fileRegex;

	memset(buff, '\0', MAX_STRING);
	memset(name, '\0', MAX_STRING);
	regcomp(&fileRegex, "^[A-Za-z0-9]{1,50}(.txt)$", REG_EXTENDED);

	while(!isValid)
	{
		printf("Enter an %sput file (must be a .txt file in the same directory as the application)\r\n", inOrOut);
		
		if (fgets(buff, MAX_STRING, stdin))
		{
			strip(buff);

			if (!regexec(&fileRegex, buff, 0, 0, 0))
			{
				isValid = 1;
			}

			else
			{
				printf("%s", "Invalid filename\r\n");
			}
		}

		else
		{
			printf("%s", "Invalid filename\r\n");
		}
	}

	strncpy(name, buff, strlen(buff));
    regfree(&fileRegex);
}

void strip(char *array)
{
	if(array == NULL)
	{
		perror("array is null");
		exit(-99);
	}

	int len = strlen(array), x = 0;

	while(array[x] != '\0' && x < len)
	{
	  if(array[x] == '\r')
		 array[x] = '\0';

	  else if(array[x] == '\n')
		 array[x] = '\0';

	  x++;
    }
}

int combiner(){
    char * cwd = current_directory();
    printf(cwd);

    return 0;
}


char * current_directory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char *cwd_tosend = (char *)malloc(sizeof(char) * sizeof(cwd)+1);
        return cwd_tosend;
    }
    else {
        return null;
    }
}