#ifndef CALC_H
#define CALC_H

#include "data.h"

typedef struct 
{
    int gradeA;
    int gradeB;
    int gradeC;
    int gradeD;
} GradeMapping;

// Function to calculate the Total score of a student
float calculateTotal(int a1, int a2, int a3, int midterm, int exam);

// Function to set the default grade mapping
void defaultGradeMapping(GradeMapping* map);

// Function to assign the Grade letter for a student
char assignGrade(float total, GradeMapping map);

// Function to display a histogram of the grade distribution
void histogramGrade(Student students[], int count, GradeMapping* map);

// Function to update the last name of a student
void updateLast(Student students[], int count, GradeMapping* map);

// Function to update the exam score of a student
void updateExam(Student students[], int count, GradeMapping* map);

// Function to update the grade mapping
void updateGradeMapping(GradeMapping* map);

// Function to delete a student from the spreadsheet
void deleteStudent(Student students[], int* count, GradeMapping* map);

#endif
