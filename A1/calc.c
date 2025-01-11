#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "spreadsheet.h"
#include "calc.h"
#include "data.h"

// Function to calculate the Total score of a student
float calculateTotal(int a1, int a2, int a3, int midterm, int exam)
{
    // Maximum scores for each work
    const int maxA = 40;
    const int maxM = 25;
    const int maxE = 40;

    // Calculate the average score of the assignments
    float avgA = (a1 + a2 + a3) / 3.0;
    
    // Calculate the weighted score of the assignments
    float weightA = (avgA / maxA) * 25.0;

    // Calculate the weighted score of the midterm
    float weightM = ((float)midterm / maxM) * 25.0;

    // Calculate the weighted score of the exam
    float weightE = ((float)exam / maxE) * 50.0;

    // Calculate the total score
    float total = weightA + weightM + weightE;

    return total;
}

// Function to set the default grade mapping
void defaultGradeMapping(GradeMapping* map)
{
    map->gradeA = 80;
    map->gradeB = 70;
    map->gradeC = 60;
    map->gradeD = 50;
}

// Function to assign the Grade letter for a student
char assignGrade(float total, GradeMapping map)
{
    if(total >= map.gradeA)
    {
        return 'A';
    }
    else if(total >= map.gradeB)
    {
        return 'B';
    }
    else if(total >= map.gradeC)
    {
        return 'C';
    }
    else if(total >= map.gradeD)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

// Function to display a histogram of the grade distribution
void histogramGrade(Student students[], int count, GradeMapping* map)
{
    // Clear the console
    system("clear");

    // Counters for each grade letter
    int aCount = 0;
    int bCount = 0;
    int cCount = 0;
    int dCount = 0;
    int fCount = 0;

    // Assign each student's grade letter and count each grade letter's occurrences
    for(int i = 0; i < count; i++)
    {
        char grade = assignGrade(students[i].total, *map);

        switch(grade)
        {
            case 'A':
                aCount++;
                break;
            case 'B':
                bCount++;
                break;
            case 'C':
                cCount++;
                break;
            case 'D':
                dCount++;
                break;
            case 'F':
                fCount++;
                break;
        }
    }

    // Print grade distribution
    printf("COMP 348 Grade Distribution\n");

    printf("\nA: ");
    for(int i = 0; i < aCount; i++)
    {
        printf("*");
    }
    printf("\nB: ");
    for(int i = 0; i < bCount; i++)
    {
        printf("*");
    }
    printf("\nC: ");
    for(int i = 0; i < cCount; i++)
    {
        printf("*");
    }
    printf("\nD: ");
    for(int i = 0; i < dCount; i++)
    {
        printf("*");
    }
    printf("\nF: ");
    for(int i = 0; i < fCount; i++)
    {
        printf("*");
    }
    
    printf("\n\nPress 'c' or 'C' to continue: ");
}

// Function to update the last name of a student
void updateLast(Student students[], int count, GradeMapping* map)
{
    int studentID;

    // Clear the console
    system("clear");

    // Print the spreadsheet
    displaySpreadsheet(students, count, map);

    printf("\n\nEnter Student ID: ");
    scanf("%d", &studentID);

    // Check if student ID exist in the spreadsheet
    for(int i = 0; i < count; i++)
    {
        if(students[i].id == studentID)
        {
            printf("\nEnter Updated Last Name: ");
            scanf("%19s", students[i].lastName);

            printf("\nLast name updated\n\n");
            return;
        }
    }

    printf("\nStudent ID %d not found. \nPlease try again.\n", studentID);
}

// Function to update the exam score of a student
void updateExam(Student students[], int count, GradeMapping* map)
{
    int studentID;
    int examScore;

    // Clear the console
    system("clear");

    // Print the spreadsheet
    displaySpreadsheet(students, count, map);

    printf("\n\nEnter Student ID: ");
    scanf("%d", &studentID);

    // Check if student ID exist in the spreadsheet
    for(int i = 0; i < count; i++)
    {
        if(students[i].id == studentID)
        {
            printf("\nEnter Updated Exam Grade: ");
            scanf("%d", &examScore);

            // Check if the exam score is within the valid range
            if(examScore >= 0 && examScore <= 40)
            {
                // Update the exam score of the student
                students[i].exam = examScore;

                printf("\nExam grade updated\n\n");
                return;
            }
            else
            {
                printf("\nInvalid Exam Grade. \nPlease try again.\n");
                return;
            }
        }
    }

    printf("\nStudent ID %d not found. \nPlease try again.\n", studentID);
}

// Function to update the grade mapping
void updateGradeMapping(GradeMapping* map)
{
    int gA;
    int gB;
    int gC;
    int gD;

    system("clear");

    printf("Current Mapping: \n");
    printf("A: >= %d\n", map->gradeA);
    printf("B: >= %d\n", map->gradeB);
    printf("C: >= %d\n", map->gradeC);
    printf("D: >= %d\n", map->gradeD);
    printf("F: < %d\n\n\n", map->gradeD);

    printf("Entering new A baseline: ");
    scanf("%d", &gA);
    printf("Entering new B baseline: ");
    scanf("%d", &gB);
    printf("Entering new C baseline: ");
    scanf("%d", &gC);
    printf("Entering new D baseline: ");
    scanf("%d", &gD);

    // Check if the baseline is within the valid range
    if((gA >= 0 && gA <= 100) && (gB >= 0 && gB <= 100) && 
    (gC >= 0 && gC <= 100) && (gD >= 0 && gD <= 100))
    {
        // Check if the baselines make sense
        if(gA > gB && gB > gC && gC > gD)
        {
            // Update the exam score of the student
            map->gradeA = gA;
            map->gradeB = gB;
            map->gradeC = gC;
            map->gradeD = gD;

            printf("\nNew Mapping\n\n");
            printf("Current Mapping: \n");
            printf("A: >= %d\n", map->gradeA);
            printf("B: >= %d\n", map->gradeB);
            printf("C: >= %d\n", map->gradeC);
            printf("D: >= %d\n", map->gradeD);
            printf("F: < %d\n\n", map->gradeD);
            return;
        }
        else
        {
            printf("\nConflict Mappings. \nPlease try again.\n");
            return;
        }
    }

    printf("\nInvalid baselines. \nPlease try again.\n");
}

// Function to delete a student from the spreadsheet
void deleteStudent(Student students[], int* count, GradeMapping* map)
{
    int studentID;

    // Clear the console
    system("clear");

    // Print the spreadsheet
    displaySpreadsheet(students, *count, map);

    printf("\n\nEnter Student ID: ");
    scanf("%d", &studentID);

    // Check if student ID exist in the spreadsheet
    for(int i = 0; i < *count; i++)
    {
        if(students[i].id == studentID)
        {
            // Shift all the students by one position to delete the student
            for(int j = i; j < *count - 1; j++)
            {
                students[j] = students[j+1];
            }

            //Decrease the number of students 
            (*count)--;

            printf("\nStudent successfully deleted\n\n");
            return;
        }
    }

    printf("\nStudent ID %d not found. \nPlease try again.\n", studentID);
}