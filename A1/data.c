#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "data.h"

/* // Function to parse each row in the text file input and store the data in each Student struct
void parseStudent(char* row, Student* student)
{
    sscanf(row, "%d|%[^|]|%[^|]|%d|%d|%d|%d|%d",&student->id, student->lastName, student->firstName,
    &student->a1, &student->a2, &student->a3, &student->midterm, &student->exam);
} */

// Function to parse each row in the text file input and store the data in each Student struct
void parseStudent(char* row, Student* student)
{
    // Split the row on "|" delimiter
    char* token = strtok(row, "|");

    // Parse each token and assign it to the student structure
    // Convert atoi -> convert to int
    student->id = atoi(token); 
    token = strtok(NULL, "|");

    // Copy last name
    strncpy(student->lastName, token, sizeof(student->lastName)); 
    token = strtok(NULL, "|");

    // Copy first name
    strncpy(student->firstName, token, sizeof(student->firstName)); 
    token = strtok(NULL, "|");

    // Convert the rest of the fields to integers
    student->a1 = atoi(token); 
    token = strtok(NULL, "|");
    student->a2 = atoi(token);
    token = strtok(NULL, "|");
    student->a3 = atoi(token);
    token = strtok(NULL, "|");
    student->midterm = atoi(token);
    token = strtok(NULL, "|");
    student->exam = atoi(token);
}

// Function to read the text file input and store the data in an array
void readFile(const char* filename, Student** students, int* count, int* capacity)
{
    FILE* fileP;
    char rowBuffer[ROW_LENGTH];
    *count = 0;

    // Open the text file input to read
    fileP = fopen(filename, "r");

    // Check if we can find the text file input and read it
    if(fileP == NULL)
    {
        printf("ERROR : Unable to open file %s.\n", filename);
        return;
    }

    // Read each line of the text file input and parse each row
    while (fgets(rowBuffer, ROW_LENGTH, fileP) != NULL)
    {
        if(*count >= *capacity)
        {
            *capacity *= 2;
            *students = realloc(*students, (*capacity) * sizeof(Student));

            if(*students == NULL)
            {
                printf("ERROR : Unable to allocate memory, students array not found.\n\n");
                fclose(fileP);
                return;
            }
        }
        
        parseStudent(rowBuffer, &(*students)[*count]);
        (*count)++;
    }
    
    // Close the text file input
    fclose(fileP);
}