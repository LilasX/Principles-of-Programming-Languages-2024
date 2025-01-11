#ifndef DATA_H
#define DATA_H

#define ROW_LENGTH 256

// Information related to each student (what to print in each row of the spreadsheet)
typedef struct
{
    int id;
    char lastName[50];
    char firstName[50];
    int a1;
    int a2;
    int a3;
    int midterm;
    int exam;
    float total;
    char grade;
}  Student;


// Function to read the text file input and store the data in an array
void readFile(const char* filename, Student** students, int* count, int* capcity);

// Function to parse each row in the text file input and store the data in each Student struct
void parseStudent(char* row, Student* student);

#endif