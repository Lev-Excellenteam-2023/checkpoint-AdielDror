#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char firstName[50];
    char lastName[50];
    char phone[11];
    char level[5];
    char className[5];
    int scores[12];
    struct Student* next;
};

// Function to insert a new node at the end of the list
void insertEnd(struct Student** head, const char* firstName, const char* lastName, const char* phone, char* level, char* className, int scores[]) {

  struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    if (newNode == NULL) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    strcpy(newNode->firstName, firstName);
    strcpy(newNode->lastName, lastName);
    strcpy(newNode->phone, phone);
    strcpy(newNode->level, level);
    strcpy(newNode->className, className);
    memcpy(newNode->scores, scores, sizeof(int) * 12);

    newNode->next = *head;
    *head = newNode;

}

// Function to print the person's information
void printStudent(struct Student* person) {
    printf("First Name: %s\n", person->firstName);
    printf("Last Name: %s\n", person->lastName);
    printf("Phone: %s\n", person->phone);
    printf("Level: %s\n", person->level);
	    printf("Class: %s\n", person->className);
    printf("Scores: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", person->scores[i]);
    }
    printf("\n\n");
}

int main() {
    const char* filename = "students_with_class.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

// 2D array of pointers to struct Student
    struct Student* studentsByLevelAndClass[12][10] = { NULL };
	
    char firstName[50];
    char lastName[50];
    char phone[11];
    char level[5];
    char className[5];
    int scores[10];
    int counter = 1;

    // Loop to read each person's information from the file and add them to the linked list
    while (fscanf(file, "%49s %49s %10s %4s %4s", firstName, lastName, phone, level, className) != EOF) {
        for (int i = 0; i < 10; i++) {
            fscanf(file, "%d", &scores[i]);
        }
        insertEnd(&studentsByLevelAndClass[atoi(level) - 1][atoi(className) - 1], firstName, lastName, phone, level, className, scores);
		printf("%d\n", counter);
        counter++;
    }

    fclose(file);



    // Loop to print each student's information stored in the linked list
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            struct Student* current = studentsByLevelAndClass[i][j];
            while (current != NULL) {
                printStudent(current);
                current = current->next;
            }
        }
    }

    // Free memory
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            struct Student* current = studentsByLevelAndClass[i][j];
            while (current != NULL) {
                struct Student* temp = current;
                current = current->next;
                free(temp);
            }
        }
    }


    return 0;
}
	