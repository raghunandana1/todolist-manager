#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TASKS 100
#define MAX_TITLE_LEN 100

typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char priority[10]; 
    char due_date[15]; 
    bool is_completed;
} Task;

// Global variables to store our list in memory
Task burrow[MAX_TASKS];
int task_count = 0;
int next_id = 1;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addTask() {
    if (task_count >= MAX_TASKS) {
        printf("\nYour Burrow is full! Delete some tasks first.\n");
        return;
    }

    Task newTask;
    newTask.id = next_id++;
    newTask.is_completed = false;

    printf("\n--- Add a New Task ---\n");
    
    printf("Task title: ");
    fgets(newTask.title, MAX_TITLE_LEN, stdin);
    newTask.title[strcspn(newTask.title, "\n")] = 0; 

    int prioChoice;
    printf("Pace/Priority (1 = Turtle, 2 = Fox, 3 = Hare): ");
    scanf("%d", &prioChoice);
    clearBuffer();
    
    if (prioChoice == 1) strcpy(newTask.priority, "Turtle");
    else if (prioChoice == 3) strcpy(newTask.priority, "Hare");
    else strcpy(newTask.priority, "Fox"); // Default

    
    printf("Due Date (YYYY-MM-DD, or press Enter to skip): ");
    fgets(newTask.due_date, 15, stdin);
    newTask.due_date[strcspn(newTask.due_date, "\n")] = 0;

    burrow[task_count] = newTask;
    task_count++;

    printf("Task added successfully!\n");
}

void listTasks() {
    if (task_count == 0) {
        printf("\nYour Burrow is empty. No tasks to show!\n");
        return;
    }

    printf("\n--- Your Burrow Tasks ---\n");
    printf("%-5s | %-3s | %-20s | %-8s | %-12s\n", "ID", "St", "Title", "Pace", "Due Date");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < task_count; i++) {
        char status = burrow[i].is_completed ? 'X' : ' ';
        printf("%-5d | [%c] | %-20s | %-8s | %-12s\n", 
            burrow[i].id, 
            status, 
            burrow[i].title, 
            burrow[i].priority, 
            strlen(burrow[i].due_date) > 0 ? burrow[i].due_date : "None"
        );
    }
}

void markCompleted() {
    int id;
    printf("\nEnter the ID of the task to mark complete: ");
    scanf("%d", &id);
    clearBuffer();

    for (int i = 0; i < task_count; i++) {
        if (burrow[i].id == id) {
            burrow[i].is_completed = true;
            printf("Great job! Task '%s' marked as done.\n", burrow[i].title);
            return;
        }
    }
    printf("Task ID not found.\n");
}

void deleteTask() {
    int id;
    printf("\nEnter the ID of the task to delete: ");
    scanf("%d", &id);
    clearBuffer();

    int found_index = -1;
    for (int i = 0; i < task_count; i++) {
        if (burrow[i].id == id) {
            found_index = i;
            break;
        }
    }

    if (found_index != -1) {
        // Shift remaining tasks left to fill the gap
        for (int i = found_index; i < task_count - 1; i++) {
            burrow[i] = burrow[i + 1];
        }
        task_count--;
        printf("Task deleted successfully.\n");
    } else {
        printf("Task ID not found.\n");
    }
}

int main() {
    int choice;

    printf("Welcome to Burrow CLI (C Edition)\n");

    while (1) {
        printf("\nMain Menu:\n");
        printf("1. View Tasks\n");
        printf("2. Add Task\n");
        printf("3. Mark Task Completed\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            printf("Invalid input please enter a number\n");
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                listTasks();
                break;
            case 2:
                addTask();
                break;
            case 3:
                markCompleted();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                printf("Goodbye gng!\n");
                return 0;
            default:
                printf("dumbarse\n");
        }
    }

    return 0;
}