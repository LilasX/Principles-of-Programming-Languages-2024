#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "spreadsheet.h"
#include "data.h"
#include "calc.h"
#include "ordering.h"

// Function to print the menu and and to handle user input
void displayMenu()
{
    const char* menuTitle = "Spreadsheet Menu";
    const char* options[] = {"Display Spreadsheet", "Display Histogram", "Set Sort Column", 
    "Update Last Name", "Update Exam Grade", "Update Grade Mapping", "Delete Student", "Exit"};

    // Get user input
    int selection;

    // Hold the user input to check if it's an integer
    int validInput;

    int studentCount = 0;
    int studentsCapacity = 10;
    Student* students = malloc(studentsCapacity * sizeof(Student));

    if(students == NULL)
    {
        printf("ERROR : Unable to allocate memory for students.\n\n");
        return;
    }    

    // Read students data from the text file input
    readFile("students.txt", &students, &studentCount, &studentsCapacity);

    // Set the default grade mapping
    GradeMapping map;
    defaultGradeMapping(&map);

    // Sort the spreadsheet by student ID in ascending order by default
    sortByID(students, studentCount);

    do
    {
        // Clear the console 
        system("clear");

        // Print the menu title
        printf("%s\n", menuTitle);

        // Print the dashes to underline the menu title
        int titleLength = strlen(menuTitle);

        // Print the dashes depending on the length of the menu title
        for(int i = 0; i < titleLength; i++)
        {
            printf("-");
        }
        printf("\n");

        // Print the menu options
        for(int i = 0; i < 8; i++)
        {
            printf("%d. %s\n", i + 1, options[i]);
        }

    
        printf("\nSelection: ");

        // Store user input to check if it's an integer input
        validInput = scanf("%d", &selection);

        // Check if input is an integer
        if(validInput != 1)
        {
            // Clear the input buffer
            while (getchar() != '\n');
            // Set selection to an invalid integer user input
            selection = 0;
        }

        switch (selection)
        {
            char proceed;

            // Display Spreadsheet
            case 1:
                displaySpreadsheet(students, studentCount, &map);
                printf("\nPress 'c' or 'C' to continue: ");
                do
                {
                    scanf("%c", &proceed);
                } 
                while ((proceed != 'c') && (proceed != 'C'));
                selection = 0;
                break;
            // Display histogram of grade distribution
            case 2:
                histogramGrade(students, studentCount, &map);
                do
                {
                    scanf("%c", &proceed);
                } 
                while ((proceed != 'c') && (proceed != 'C'));
                selection = 0;
                break;
            // Sort the spreadsheet by column
            case 3:
                sortSpreadsheet(students, studentCount);
                do
                {
                    scanf("%c", &proceed);
                } 
                while ((proceed != 'c') && (proceed != 'C'));
                selection = 0;
                break;
            // Update the last name of a student
            case 4:
                updateLast(students, studentCount, &map);
                printf("\nPress 'c' or 'C' to continue: ");
                do
                {
                    scanf("%c", &proceed);
                } 
                while ((proceed != 'c') && (proceed != 'C'));
                selection = 0;
                break;
            // Update the exam score of a student
            case 5:
                updateExam(students, studentCount, &map);
                printf("\nPress 'c' or 'C' to continue: ");
                do
                {
                    scanf("%c", &proceed);
                } 
                while ((proceed != 'c') && (proceed != 'C'));
                selection = 0;
                break;
            // Update the grade mapping
            case 6:
                updateGradeMapping(&map);
                printf("\nPress 'c' or 'C' to continue: ");
                do
                {
                    scanf("%c", &proceed);
                } 
                while ((proceed != 'c') && (proceed != 'C'));
                selection = 0;
                break;
            // Delete a student data from the spreadsheet
            case 7:
                deleteStudent(students, &studentCount, &map);
                printf("\nPress 'c' or 'C' to continue: ");
                do
                {
                    scanf("%c", &proceed);
                } 
                while ((proceed != 'c') && (proceed != 'C'));
                selection = 0;
                break;
            // Exit
            case 8:
                printf("\nGoodbye and thank you for using our spreadsheet app.\n\n");
                break;
            default:
                printf("Invalid Input.\n");
                break;
        }

    } 
    while (validInput != 1 || selection < 1 || selection > 8);

    free(students);
}

// Function to print dashes matching the header length
void printDashes(const char* header)
{
    for(int i = 0; i < strlen(header); i++)
    {
        printf("-");
    }
}

// Function to print the spreadsheet with headers and data from the text file input
void displaySpreadsheet(Student students[], int count, GradeMapping* map)
{
    // Clear the console
    system("clear");

    // Headers
    char idHeader[] = "ID";
    char lastNameHeader[] = "Last";
    char firstNameHeader[] = "First";
    char a1Header[] = "A1";
    char a2Header[] = "A2";
    char a3Header[] = "A3"; 
    char midtermHeader[] = "Midterm";
    char examHeader[] = "Exam";
    char totalHeader[] = "Total";
    char gradeHeader[] = "Grade";

    // Print the title
    printf("COMP 348 GRADE SHEET\n\n");

    // Print headers
    printf("%-5s %-20s %-20s %-5s %-5s %-5s %-9s %-6s %-7s %-6s\n", idHeader, lastNameHeader, firstNameHeader,
    a1Header, a2Header, a3Header, midtermHeader, examHeader, totalHeader, gradeHeader);

    // Print dashes to underline headers
    printDashes(idHeader);
    printf("%-4s","");
    printDashes(lastNameHeader);
    printf("%-17s","");
    printDashes(firstNameHeader);
    printf("%-16s","");
    printDashes(a1Header);
    printf("%-4s", "");
    printDashes(a2Header);
    printf("%-4s", "");
    printDashes(a3Header);
    printf("%-4s", "");
    printDashes(midtermHeader);
    printf("%-3s", "");
    printDashes(examHeader);
    printf("%-3s", "");
    printDashes(totalHeader);
    printf("%-3s", "");
    printDashes(gradeHeader);
    printf("\n");

    // Print student data for each row
    for(int i = 0; i < count; i++)
    {
        // Calculate the total score of each student
        students[i].total = calculateTotal(students[i].a1, students[i].a2, students[i].a3, students[i].midterm, students[i].exam);
        
        // Assign the Grade letter for each student
        students[i].grade = assignGrade(students[i].total, *map);

        printf("%-4d  %-19s  %-19s  %-4d  %-4d  %-4d  %-8d  %-6d %-7.2f %-4c\n", students[i].id, 
        students[i].lastName, students[i].firstName, students[i].a1, students[i].a2, students[i].a3, 
        students[i].midterm, students[i].exam, students[i].total, students[i].grade);
    }
}

int main()
{
    displayMenu();

    return 0;
}

