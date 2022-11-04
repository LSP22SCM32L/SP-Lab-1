/* C program that adds employees to a database with user actions that can modify or look up 
    records in the database. It uses external text file to populate the database */

#include <stdio.h>
#include "readfile.h"
#include <string.h>
#define MAXNAME 64

extern FILE *file;
int emps;


//employee structure
struct employee{
    int id;
    int salary;
    char fname[MAXNAME];
    char lname[MAXNAME];
};

//declare a library of employees, limit of employees is 1024 as specified in the requirements
struct employee library[1024];

//function that makes the database
void new_database(char* text_file){
    if (open_file(text_file) == 0){
        int ret;
        char buffer[135];

        while (fgets(buffer, sizeof(buffer), file)){
            ret = read_int(buffer, 0, &library[emps].id);
            ret = read_int(buffer, 1, &library[emps].salary);
            ret = read_string(buffer, 0, &library[emps].fname);
            ret = read_string(buffer, 1, &library[emps].lname);
            emps++;
        }
        if (feof(file)){
            close_file(file);
        }
    }
}

//1. Print the Database
void printDatabase(struct employee employees[], int length){
    int i;

    printf("\nFirstName\tLastName\t\tSalary\tID\n");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < length; i++){
        printf("%s\t%s\t\t%i\t%i\n", employees[i].fname, employees[i].lname, employees[i].salary, employees[i].id);
    }
    printf("---------------------------------------------------------------\n");
    printf("Number of Employees (%i)\n", length);
};

//2. Lookup employee by ID using linear search
int findID(struct employee employees[], int length, int target){
    int i;

    for (i = 0; i < length; i++){
        if (employees[i].id == target){
            return i;
        }
    }
    return -1;
};

//3. Lookup employee by last name using linear search
int findLastName(struct employee employees[], int length, char* target_lname){
    int i;

    for (i = 0; i < length; i++){
        if (strcmp(employees[i].lname, target_lname) == 0){
            return i;
        }
    }
    return -1;
};

//4. Add an Employee
int addEmployee(struct employee employees[]){
    int addsalary;
    char addfname[MAXNAME];
    char addlname[MAXNAME];
    int yes;

    printf("Enter the first name of the employee: ");
    scanf("%s", addfname);
    int fname_length = strlen(addfname);

    if (fname_length > 64){
        printf("First name is too long. First name must be <= 64 characters!\n");
    }

    printf("Enter the last name of the employee: ");
    scanf("%s", addlname);
    int lname_length = strlen(addlname);

    if (lname_length > 64){
        printf("Last name is too long. Last name must be <= 64 characters!\n");
    }

    printf("Enter employee's salary (30000 to 150000): ");
    scanf("%d", &addsalary);
    if (addsalary < 30000 || addsalary > 150000)
    {
        printf("Salary is outside of given range!\n");
    }

    printf("do you want to add the following employee to the DB?  ");
    printf("%s %s, Salary: %d\n", addfname, addlname, addsalary);
    printf("Enter 1 for yes, 0 for no: ");
    scanf("%d", &yes);

    //if yes copy the employee values into the library
    if (yes == 1){
        strcpy(library[emps].fname, addfname);
        strcpy(library[emps].lname, addlname);
        library[emps].id = library[emps - 1].id + 3;
        library[emps].salary = addsalary;
        emps++;
    }
    return 1;
};

//swap function for quicksort
void swap(struct employee* a, struct employee* b){
    struct employee temp = *a;
    *a = *b;
    *b = temp;
};

//partition function for quicksort
int partition(struct employee employees[], int l, int h){
    struct employee x = employees[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++){
        if (employees[j].id <= x.id){
            i++;
            swap(&employees[i], &employees[j]);
        }
    }
    swap (&employees[i + 1], &employees[h]);
    return (i + 1);
};

//recursive quicksort function to sort the employee library
void quickSort(struct employee employees[], int l, int h){
    if (l < h){
        int p = partition(employees, l, h);
        quickSort(employees, l, p - 1);
        quickSort(employees, p + 1, h);
    }
};

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("wrong argument");
    }
    else{
        new_database(argv[1]);
        quickSort(library, 0, emps);

        int return_val;
        int choice;

        while(1){
            //print the menu for the user to select an action
            printf("\nEmployee DB Menu:\n");
            printf("----------------------------------\n");
            printf("(1) Print the Database\n");
            printf("(2) Lookup by ID\n");
            printf("(3) Lookup by Last Name\n");
            printf("(4) Add an Employee\n");
            printf("(5) Quit\n");
            printf("----------------------------------\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch(choice){
                case 1: //print the database if 1 is selected
                    printDatabase(library, emps);
                    break;
                case 2: ; //find employee by id if 2 is selected
                    int id1;
                    printf("\nEnter a 6 digit employee id: ");
                    scanf("%d", &id1);
                    return_val = findID(library, emps, id1);
                    if (return_val == -1){
                        printf("\nEmployee with id '%d' not found in DB\n", id1);
                    }
                    else{
                        printf("\nFirstName\tLastName\t\t\tSalary\t\tID\n");
                        printf("---------------------------------------------------------------\n");
                        printf("%s\t%s\t%i\t%i\n", library[return_val].fname, library[return_val].lname, library[return_val].salary, library[return_val].id);
                        printf("---------------------------------------------------------------\n");
                    }
                    break;
                case 3: ; //find employee by last name if 3 is selected
                    char name[MAXNAME];
                    printf("\nEnter Employee's last name (no extra spaces): ");
                    scanf("%s", name);
                    return_val = findLastName(library, emps, name);
                    if (return_val == -1){
                        printf("\nEmployee with name '%s' not found in DB\n", name);
                    }
                    else{
                        printf("\nFirstName\tLastName\t\t\tSalary\t\tID\n");
                        printf("---------------------------------------------------------------\n");
                        printf("%s\t%s\t%i\t%i\n", library[return_val].fname, library[return_val].lname, library[return_val].salary, library[return_val].id);
                        printf("---------------------------------------------------------------\n");
                    }
                    break;
                case 4: //add an employee to the library if 4 is selected 
                    addEmployee(library);
                    break;
                case 5: //quit the program if 5 is selected
                    printf("\ngoodbye!");
                    return 0;
                    break;
                default: //throw 400 for wrong input
                    printf("!400!\n");
                    break;
            }
        }
    }
    return 0;
}
