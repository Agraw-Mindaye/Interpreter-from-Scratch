// This program demonstrates a doubly linked list in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node of a doubly linked list
typedef struct Node {
    char* data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
} List;

List DLL_new() {
    List list;
    list.head = NULL;
    list.tail = NULL;
    return list;
}

// return the number of items in the list
int DLL_length(struct List *list) {
    struct Node *p;
    int n = 0;

    for (p = list->head; p != NULL; p = p->next) {
        ++n;
    }
    return n;
}

Node* DLL_find(List* list, char* value) {
    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, value) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void DLL_insert(List* list, char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(value);
    newNode->next = NULL; // As it will be the last node
    newNode->prev = list->tail; // Previous last node becomes the penultimate node

    if (list->tail != NULL) {
        list->tail->next = newNode; // Update the old tail
    } else {
        list->head = newNode; // If the list was empty, new node is also the head
    }
    list->tail = newNode; // Update the tail to the new node
}

void DLL_delete(List* list, char* value) {
    Node* temp = list->head;
    Node* prev = NULL;

    // If the node to be deleted is the head
    if (temp != NULL && strcmp(temp->data, value) == 0) {
        list->head = temp->next;
        if (list->head == NULL) {
            list->tail = NULL; // List is now empty
        }
        free(temp->data);
        free(temp);
        return;
    }

    // Find the node to be deleted
    while (temp != NULL && strcmp(temp->data, value) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // Node not found
    if (temp == NULL) return;

    // Unlink node from list
    prev->next = temp->next;
    if (temp->next == NULL) {
        list->tail = prev; // Update tail if last element was deleted
    }
    free(temp->data);
    free(temp);
}

void DLL_print(List* list) {
    Node* current = list->head;
    if (current == NULL) {
        printf("\n(list is empty)\n");
        return;
    }

    printf("\nList contents:\n");
    printf("[");
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("]");
    printf("\n");
}

void DLL_clear(struct List *list) {
    Node* current = list->head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->data); // Free the node's data
        free(current); // Free the node
        current = next;
    }

    // Reset the head and tail pointers
    list->head = NULL;
    list->tail = NULL;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {

    List myList = DLL_new();
    char value[100];
    int choice;

    while (1) {
        printf("\nDoubly Linked List Operations:\n");
        printf("1. Insert into DLL\n");
        printf("2. Delete a value from DLL\n");
        printf("3. Find a value in DLL\n");
        printf("4. Clear DLL\n");
        printf("5. Quit\n");
        DLL_print(&myList); // Display the list
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                fgets(value, 100, stdin);
                value[strcspn(value, "\n")] = 0; // Remove newline character
                DLL_insert(&myList, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                fgets(value, 100, stdin);
                value[strcspn(value, "\n")] = 0; // Remove newline character
                DLL_delete(&myList, value);
                break;
            case 3:
                printf("Enter value to find: ");
                fgets(value, 100, stdin);
                value[strcspn(value, "\n")] = 0; // Remove newline character
                Node* found = DLL_find(&myList, value);
                if (found != NULL) {
                    printf("Value '%s' found in the list.\n", value);
                } else {
                    printf("Value '%s' not found in the list.\n", value);
                }
                break;
            case 4:
                DLL_clear(&myList);
                printf("The list has been cleared.\n");
                break;
            case 5:
                DLL_clear(&myList); // Cleanup before exit
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}