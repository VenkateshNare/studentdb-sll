#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Node structure for the Singly-Linked List
struct StudentNode {
    char name[50];
    int roll;
    float marks;
    struct StudentNode* next; // Pointer to the next student node
};

// Function prototypes
void add_student(struct StudentNode** head);
void display_students(struct StudentNode* head);
void sort_student_names(struct StudentNode* head);
void free_list(struct StudentNode* head);

int main() {
    struct StudentNode* head = NULL; // Initially, the database is empty
    int choice;

    while (1) {
        printf("\n=== STUDENT DATABASE MENU (LINKED LIST) ===\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Sort Student Names (A-Z)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                add_student(&head);
                break;
            case 2:
                display_students(head);
                break;
            case 3:
                sort_student_names(head);
                break;
            case 4:
                printf("Exiting database application. Cleaning up memory...\n");
                free_list(head);
                exit(0);
            default:
                printf("Invalid choice! Select an option between 1 and 4.\n");
        }
    }
    return 0;
}

// 1. Feature to add a new student record at the end of the list
void add_student(struct StudentNode** head) {
    // Dynamically allocate memory for a new student node
    struct StudentNode* newNode = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    if (newNode == NULL) {
        printf("\nMemory allocation failed! Cannot add student.\n");
        return;
    }

    printf("\nEnter student details:\n");
    printf("Name: ");
    while (getchar() != '\n'); // Clear input buffer trailing characters
    fgets(newNode->name, sizeof(newNode->name), stdin);
    newNode->name[strcspn(newNode->name, "\n")] = '\0'; // Remove trailing newline

    printf("Roll Number: ");
    scanf("%d", &newNode->roll);

    printf("Marks: ");
    scanf("%f", &newNode->marks);
    
    newNode->next = NULL;

    // If the list is empty, make the new node the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Otherwise, traverse to the end of the list and append it
        struct StudentNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Student added successfully!\n");
}

// 2. Feature to print out all records by traversing the list
void display_students(struct StudentNode* head) {
    if (head == NULL) {
        printf("\nThe student database is currently empty.\n");
        return;
    }

    struct StudentNode* temp = head;
    printf("\n%-20s %-10s %-5s\n", "Name", "Roll No", "Marks");
    printf("-----------------------------------------\n");
    while (temp != NULL) {
        printf("%-20s %-10d %-5.2f\n", temp->name, temp->roll, temp->marks);
        temp = temp->next;
    }
}

// 3. Feature to alphabetically sort student names (Bubble Sort on Node Data)
void sort_student_names(struct StudentNode* head) {
    if (head == NULL || head->next == NULL) {
        printf("\nNot enough records to perform sorting (need at least 2 records).\n");
        return;
    }

    int swapped;
    struct StudentNode* ptr1;
    struct StudentNode* lptr = NULL; // Tracks the end of the sorted boundary

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) {
                // Swap names
                char tempName[50];
                strcpy(tempName, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tempName);

                // Swap roll numbers
                int tempRoll = ptr1->roll;
                ptr1->roll = ptr1->next->roll;
                ptr1->next->roll = tempRoll;

                // Swap marks
                float tempMarks = ptr1->marks;
                ptr1->marks = ptr1->next->marks;
                ptr1->next->marks = tempMarks;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("\nRecords sorted alphabetically by name! Select 'Display Students' to view.\n");
}

// Helper function to release all dynamically allocated nodes from memory
void free_list(struct StudentNode* head) {
    struct StudentNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

