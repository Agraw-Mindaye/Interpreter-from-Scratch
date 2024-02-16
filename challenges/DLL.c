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

// return number of items in list
int DLL_length(struct List *list) {
    struct Node *p;
    int n = 0;

    for (p = list->head; p != NULL; p = p->next) {
        ++n;
    }
    return n;
}

// find a node in list
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

// insert node into list
void DLL_insert(List* list, char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(value);
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = newNode; // update old tail
    } else {
        list->head = newNode;
    }
    list->tail = newNode;
}

// delete a node from list
void DLL_delete(List* list, char* value) {
    Node* temp = list->head;
    Node* prev = NULL;

    if (temp != NULL && strcmp(temp->data, value) == 0) {
        list->head = temp->next;
        if (list->head == NULL) {
            list->tail = NULL;
        }
        free(temp->data);
        free(temp);
        return;
    }

    // find node to be deleted
    while (temp != NULL && strcmp(temp->data, value) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // if node not found
    if (temp == NULL) return;

    // unlink node from list
    prev->next = temp->next;

    if (temp->next == NULL) {
        list->tail = prev; // update tail if last element was deleted
    }
    free(temp->data);
    free(temp);
}

// print entire list
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

// clear entire list
void DLL_clear(struct List *list) {
    Node* current = list->head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    // Reset head and tail pointers
    list->head = NULL;
    list->tail = NULL;
}

// function to clear user input buffer
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
        DLL_print(&myList);
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                fgets(value, 100, stdin);
                value[strcspn(value, "\n")] = 0;
                DLL_insert(&myList, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                fgets(value, 100, stdin);
                value[strcspn(value, "\n")] = 0; 
                DLL_delete(&myList, value);
                break;
            case 3:
                printf("Enter value to find: ");
                fgets(value, 100, stdin);
                value[strcspn(value, "\n")] = 0;
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
                DLL_clear(&myList);
                printf("Exiting\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }

    return 0;
}