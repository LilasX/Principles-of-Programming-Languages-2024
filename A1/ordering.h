#ifndef ORDERING_H
#define ORDERING_H

#include "data.h"
#include "calc.h"

// Function to compare student ID to sort in ascending order 
int cmpID(const void* a, const void* b);

// Function to compare student last name to sort in ascending order 
int cmpLast(const void* a, const void* b);

// Function to compare student exam score to sort in descending order 
int cmpExam(const void* a, const void* b);

// Function to compare student total score to sort in descending order 
int cmpTotal(const void* a, const void* b);

// Function to sort the spreadsheet by student ID in ascending order 
void sortByID(Student students[], int count);

// Function to sort the spreadsheet by student last name in ascending order 
void sortByLast(Student students[], int count);

// Function to sort the spreadsheet by student exam score in descending order 
void sortByExam(Student students[], int count);

// Function to sort the spreadsheet by student total score in descending order 
void sortByTotal(Student students[], int count);

// Function to sort the spreadsheet by column
void sortSpreadsheet(Student students[], int count);

#endif
