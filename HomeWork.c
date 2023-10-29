#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int student_number;
    char name[50];
    int age;
    int record_number;
    struct Student* next;
};

struct Student* head = NULL;

// Function to add a student record to the end of the list
void addStudent(int student_number, char name[], int age) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->student_number = student_number;
    strcpy(newStudent->name, name);
    newStudent->age = age;
    newStudent->next = NULL;
    
    if (head == NULL) {
        newStudent->record_number = 1;
        head = newStudent;
    } else {
        struct Student* temp = head;
        int record_number = 2;
        while (temp->next != NULL) {
            temp = temp->next;
            record_number++;
        }
        newStudent->record_number = record_number;
        temp->next = newStudent;
    }
}

// Function to display all student records
void displayStudents() {
    struct Student* temp = head;
    while (temp != NULL) {
        printf("%d- %s %d %d\n", temp->record_number, temp->name, temp->age, temp->student_number);
        temp = temp->next;
    }
}

// Function to search for a student by name
struct Student* searchStudent(char name[]) {
    struct Student* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // Student not found
}

// Function to delete the next node after a student with a given name
void deleteNextStudent(char name[]) {
    struct Student* target = searchStudent(name);
    if (target != NULL && target->next != NULL) {
        struct Student* temp = target->next;
        target->next = temp->next;
        free(temp);
    }
}

// Function to find and print the student with the longest name
void findLongestName() {
    struct Student* temp = head;
    struct Student* longest = head;
    
    while (temp != NULL) {
        if (strlen(temp->name) > strlen(longest->name)) {
            longest = temp;
        }
        temp = temp->next;
    }
    
    printf("The longest name in the list: %s\nLength: %lu\n", longest->name, strlen(longest->name));
}

int main() {
    char name[50];
    int student_number, age;
    
    // Add student records until -1 is entered
    while (1) {
        printf("Enter student number (or -1 to stop): ");
        scanf("%d", &student_number);
        if (student_number == -1)
            break;
        
        printf("Enter student name: ");
        scanf("%s", name);
        
        printf("Enter student age: ");
        scanf("%d", &age);
        
        addStudent(student_number, name, age);
    }

    // Display all student records
    displayStudents();
    
    // Search for a student by name
    printf("Enter a name to search: ");
    scanf("%s", name);
    struct Student* foundStudent = searchStudent(name);
    if (foundStudent != NULL) {
        printf("Student found: %d- %s %d %d\n", foundStudent->record_number, foundStudent->name, foundStudent->age, foundStudent->student_number);
    } else {
        printf("Student not found.\n");
    }
    
    // Delete the next student after a given name
    printf("Enter a name to delete the next student: ");
    scanf("%s", name);
    deleteNextStudent(name);
    displayStudents();
    
    // Find and print the student with the longest name
    findLongestName();
    
    // Clean up and free memory
    struct Student* current = head;
    while (current != NULL) {
        struct Student* next = current->next;
        free(current);
        current = next;
    }
    
    return 0;
}
