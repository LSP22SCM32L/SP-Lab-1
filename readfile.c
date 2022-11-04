//C program for reading file and values from the text file
#include <stdio.h>
#include <stdlib.h>
#include "readfile.h"

FILE *file;

//function to open file
int open_file(char* txt_file){
    
    file = fopen("small.txt", "r");
    if (file == 0){ //if file not found return -1
        return -1;
    }
    else {
        return 0;
    }
};

//function to close the file
void close_file(){
    fclose(file);
};

//function to read an int from the file
int read_int(char arr[], int num, int* var){
    char fname[64]; 
    char lname[64];

    int id;
    int salary;

    if (num == 0){
        sscanf(arr, "%i %s %s %i", var, fname, lname, &salary); 
    }
    else{
        sscanf(arr, "%i %s %s %i", &id, fname, lname, var);
    }
    
    return 0;
};

//function to read a float from the file
int read_float(char arr[], int num, int* var){
    char fname[64];
    char lname[64];

    int id;
    int salary;

    if (num == 0){
        sscanf(arr, "%f %s %s %f", var, fname, lname, &salary);
    }
    else{
        sscanf(arr, "%f %s %s %f", &id, fname, lname, var);
    }
    
    return 0;
};

//function to read a string from the file
int read_string(char arr[], int num, char savestring[]){
    char fname[64];
    char lname[64];

    int id;
    int salary;

    if (num == 0){
        sscanf(arr, "%i %s %s %i", &id, savestring, lname, &salary);
    }
    else{
        sscanf(arr, "%f %s %s %f", &id, fname, savestring, &salary);
    }
    
    return 0;
};

