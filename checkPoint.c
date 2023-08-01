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
void insertEnd(struct Student** head, const char* firstName, const char* lastName, const char* phone, char* le>
      struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
      strcpy(newNode->firstName, firstName);
      strcpy(newNode->lastName, lastName);
      strcpy(newNode->phone, phone);
      strcpy(newNode->level, level);
      strcpy(newNode->className, className);
	        memcpy(newNode->scores, scores, sizeof(int) * 12);

    if (*head == NULL) {
        // If the list is empty, make the new node the head
        *head = newNode;
    } else {
        // Find the last node in the list
        struct Student* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Attach the new node to the last node in the list
        current->next = newNode;
    }

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

    struct Student* head = NULL;
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
        insertEnd(&head, firstName, lastName, phone, level, className, scores);
printf("%d",counter);
printf("\n");
counter = counter + 1;
    }

    fclose(file);



// Loop to print each student's information stored in the linked list
    struct Student* current = head;
   while (current != NULL) {
        printStudent(current);
        current = current->next;
    }
	
    // Free memory
    current = head;
    while (current != NULL) {
        struct Student* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
	