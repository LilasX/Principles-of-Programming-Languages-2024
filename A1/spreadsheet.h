#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include "data.h"
#include "calc.h"

// Funtion to print the menu and to handle user input
void displayMenu();

// Function to print dashes matching the header length
void printDashes(const char *header);

// Function to print the spreadsheet with headers and data from the text file input
void displaySpreadsheet(Student students[], int count, GradeMapping* map);

#endif
