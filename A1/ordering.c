#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "calc.h"
#include "data.h"
#include "spreadsheet.h"

// Function to compare student ID to sort in ascending order 
int cmpID(const void* a, const void* b)
{
    const Student* sA = (const Student*)a;
    const Student* sB = (const Student*)b;

    return (sA->id > sB->id) - (sA->id < sB->id); 
}

// Function to compare student last name to sort in ascending order 
int cmpLast(const void* a, const void* b)
{
    const Student* sA = (const Student*)a;
    const Student* sB = (const Student*)b;

    return strcmp(sA->lastName, sB->lastName);
}

// Function to compare student exam score to sort in descending order 
int cmpExam(const void* a, const void* b)
{
    const Student* sA = (const Student*)a;
    const Student* sB = (const Student*)b;

    return (sB->exam > sA->exam) - (sB->exam < sA->exam);
}

// Function to compare student total score to sort in descending order 
int cmpTotal(const void* a, const void* b)
{
    const Student* sA = (const Student*)a;
    const Student* sB = (const Student*)b;

    return (sB->total > sA->total) - (sB->total < sA->total);
}

// Function to sort the spreadsheet by student ID in ascending order 
void sortByID(Student students[], int count)
{
    qsort(students, count, sizeof(Student), cmpID);
}

// Function to sort the spreadsheet by student last name in ascending order 
void sortByLast(Student students[], int count)
{
    qsort(students, count, sizeof(Student), cmpLast);
}

// Function to sort the spreadsheet by student exam score in descending order 
void sortByExam(Student students[], int count)
{
    qsort(students, count, sizeof(Student), cmpExam);
}

// Function to sort the spreadsheet by student total score in descending order 
void sortByTotal(Student students[], int count)
{
    qsort(students, count, sizeof(Student), cmpTotal);
}

// Function to sort the spreadsheet by column
void sortSpreadsheet(Student students[], int count)
{
    system("clear");

    int sortColumn;

    printf("Column Options");
    printf("\n");
    printDashes("Column Options");

    printf("\n1. Student ID");
    printf("\n2. Last name");
    printf("\n3. Exam");
    printf("\n4. Total");

    printf("\n\nSort Column: ");

    // Hold the user input to check if it's an integer
    int validInput;

    do
    {
        // Store user input to check if it's an integer input
        validInput = scanf("%d", &sortColumn);

        // Check if input is an integer
        if(validInput != 1)
        {
            // Clear the input buffer
            while (getchar() != '\n');
            // Set sortColumn to an invalid integer user input
            sortColumn = 0;
        }
    } 
    while (validInput != 1 || sortColumn < 1 || sortColumn > 4);
    
    switch (sortColumn)
    {
        case 1:
            sortByID(students, count);
            printf("\nSort column updated");
            break;
        case 2:
            sortByLast(students, count);
            printf("\nSort column updated");
            break;
        case 3:
            sortByExam(students, count);
            printf("\nSort column updated");
            break;
        case 4:
            sortByTotal(students, count);
            printf("\nSort column updated");
            break;
    }

    printf("\n\nPress 'c' or 'C' to continue: ");
}