#include <stdlib.h>
#include <stdio.h>
#include <string.h>

 
struct Student* studentsByLevelAndClass[12][10] = { NULL };

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

int loadData(/*struct Student** studentsByLevelAndClass*/){
 const char* filename = "students_with_class.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

// 2D array of pointers to struct Student
    //struct Student* studentsByLevelAndClass[12][10] = { NULL };

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

    return 0;
}

void insertNewStudent(){
    char firstName[50];
    char lastName[50];
    char phone[11];
    char level[5];
    char className[5];
    int scores[10];

    printf("Enter the student's first name: ");
    scanf("%49s", firstName);

    printf("Enter the student's last name: ");
    scanf("%49s", lastName);

    printf("Enter the student's phone number: ");
    scanf("%10s", phone);

    printf("Enter the student's level: ");
    scanf("%4s", level);

    printf("Enter the student's class: ");
    scanf("%4s", className);

    printf("Enter the student's 10 scores: ");
    for (int i = 0; i < 10; i++) {
        scanf("%d", &scores[i]);
    }

    // Insert the student into the linked list (end)
    insertEnd(&studentsByLevelAndClass[atoi(level) - 1][atoi(className) - 1], firstName, lastName, phone, level, className, scores);

}

enum menu_inputs {
    Insert = '0',
    Delete = '1',
    Edit = '2',
    Search = '3',
    Showall = '4',
    Top10 = '5',
    UnderperformedStudents = '6',
    Average = '7',
    Export = '8',
    Exit = '9'
};

void menu() {
    char input;
    // school.name = "schoolName";
    do {
        printf("\n|School Manager<::>Home|\n");
        printf("--------------------------------------------------------------------------------\n");
        //printf("Welcome to ( %s ) School!\nYou have inserted ( %zu ) students.\n\n", school.name, school.numOfStudents);
        printf("\t[0] |--> Insert\n");
        printf("\t[1] |--> Delete\n");
        printf("\t[2] |--> Edit\n");
        printf("\t[3] |--> Search\n");
        printf("\t[4] |--> Show All\n");
        printf("\t[5] |--> Top 10 students per course\n");
        printf("\t[6] |--> Underperformed students\n");
        printf("\t[7] |--> Average per course\n");
        printf("\t[8] |--> Export\n");
        printf("\t[9] |--> Exit\n");
        printf("\n\tPlease Enter Your Choice (0-9): ");
        input = getc(stdin);
        fflush(stdin);
        getc(stdin);
        switch (input) {
            case Insert:
                insertNewStudent();
                break;
            case Delete:
                //deleteStudent();
                break;
            case Edit:
                //editStudentGrade();
                break;
            case Search:
                //searchStudent();
                break;
            case Showall:
                //printAllStudents();
                break;
            case Top10:
                //printTopNStudentsPerCourse();
                break;
            case UnderperformedStudents:
                //printUnderperformedStudents();
                break;
            case Average:
                //printAverage();
                break;
            case Export:
                //exportDatabase();
                break;
            case Exit:
                //handleClosing();
                break;
            default:
                printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-10!\nPress any key to continue...",
                       input);
                getc(stdin);
                getc(stdin);
                break;
        }
    } while (input != Exit);
}


int main() {
     //struct Student* studentsByLevelAndClass[12][10] = { NULL };
     loadData(/*&studentsByLevelAndClass*/);
    
     menu();

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
