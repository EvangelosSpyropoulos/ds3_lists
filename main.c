#include "doublylinkedlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int insert_student(DoublyLinkedList* list, const char* AM, const char* full_name, const int semester);
int remove_student(DoublyLinkedList* list, const char* AM);
int search_student(DoublyLinkedList* list, const char* AM, Node** student_node);
int search_student_by_name(DoublyLinkedList* list, const char* full_name, Node** student_node);
void edit_student(DoublyLinkedList* list, const char* AM, const char* new_AM, const char* full_name, const int semester);

// Returns copy of nodes. Modifying the returned list does not mutate the initial list.
// Should be freed with call to free_resources.
DoublyLinkedList get_semester_student_list(DoublyLinkedList* list, const int semester);

void print_students_in_semester(DoublyLinkedList* list, const int semester);

void input_AM(char* AM, const int n);
void input_full_name(char* full_name, const int n);
void input_semester(int* semester);


int main() {
    int ch;
    char AM[21];
    char full_name[21];
    int semester;
    Node* student_node;
    
    DoublyLinkedList student_list = init_list();

    do {
        printf("Options:\n"
        "1 Insert student.\n"
        "2 Remove student.\n"
        "3 Search student by AM.\n"
        "4 Search student by full name.\n"
        "5 Edit student data.\n"
        "6 Print student list by semester.\n"
        "0 Exit\n\n");
        scanf("%d", &ch);
        getc(stdin);
        switch(ch) {
            case 1:
                input_AM(AM, 21);
                input_full_name(full_name, 21);
                input_semester(&semester);
                if ( insert_student(&student_list, AM, full_name, semester) == 0) {
                    printf("Student inserted.\n");
                } else {
                    printf("Student with given AM already exists.");
                }
                break;
            case 2:
                input_AM(AM, 21);
                if (remove_student(&student_list, AM) == 0) {
                    printf("Student removed.\n");
                } else {
                    printf("Student not found.\n");
                }
                break;
            case 3:
                input_AM(AM, 21);
                if (search_student(&student_list, AM, &student_node) == 0) {
                    printf("\nAM: %s\n", student_node->AM);
                    printf("Full Name: %s\n", student_node->full_name);
                    printf("Semester: %d\n", student_node->semester);
                } else {
                    printf("Student not found.\n");
                }
                break;
            case 4:
                input_full_name(full_name, 21);
                if (search_student_by_name(&student_list, full_name, &student_node) == 0) {
                    printf("\nAM: %s\n", student_node->AM);
                    printf("Full Name: %s\n", student_node->full_name);
                    printf("Semester: %d\n", student_node->semester);
                } else {
                    printf("Student not found.\n");
                }
                break;
            case 5:
                printf("Editing student.\n");
                input_AM(AM, 21);
                printf("Input new data.");
                char new_AM[21];
                input_AM(new_AM, 21);
                input_full_name(full_name, 21);
                input_semester(&semester);
                edit_student(&student_list, AM, new_AM, full_name, semester);
                break;
            case 6:
                input_semester(&semester);
                print_students_in_semester(&student_list, semester);
                break;
            case 0:
                break;
            default:
                break;
        }
        printf("\n");
    } while (ch != 0);
    
    free_resources(&student_list);

    return 0;
}

int insert_student(DoublyLinkedList* list, const char* AM, const char* full_name, const int semester) {
    Node* next_node;
    
    // Student with given AM already exists.
    if (search_student(list, AM, &next_node) == 0) { return 1; };
    
    insert_node_before(new_node(AM, full_name, semester), next_node);
    return 0;
}

int remove_student(DoublyLinkedList* list, const char* AM) {
    Node* student_node;
    if (search_student(list, AM, &student_node) == 0) {
        remove_node(student_node);
        return 0;
    }

    return 1;
}

int search_student(DoublyLinkedList* list, const char* AM, Node** student_node) {
    return search_list(list, AM, student_node);
}

int search_student_by_name(DoublyLinkedList* list, const char* full_name, Node** student_node) {
    
    if (list->head->next == list->tail) { 
        (*student_node) = list->tail;
        return 1;
    }

    (*student_node) = list->head->next;
    while ((*student_node) != list->tail) {
        if (strcmp((*student_node)->full_name, full_name) == 0) {
            return 0;
        }
        (*student_node) = advance(*student_node, 1);
    }

    return 1;
}

void edit_student(DoublyLinkedList* list, const char* AM, const char* new_AM, const char* full_name, const int semester) {
    Node* student_node;
    if (search_student(list, AM, &student_node) == 0) {
        if (strcmp(AM, new_AM) != 0) {
            free(student_node->AM);
            student_node->AM = (char*) malloc(strlen(new_AM) + 1);
            strcpy(student_node->AM, new_AM);
        }
        if (strcmp(student_node->full_name, full_name) != 0) {
            free(student_node->full_name);
            student_node->full_name = (char*) malloc(strlen(full_name) + 1);
            strcpy(student_node->full_name, full_name);
        }
        student_node->semester = semester;
    } else {
        printf("Student not found.\n");
    }
}

DoublyLinkedList get_semester_student_list(DoublyLinkedList* list, const int semester) {
    Node* student_node = list->head->next;
    DoublyLinkedList semester_list = init_list();
    while (student_node != list->tail) {
        if (student_node->semester == semester) {
            insert_student(&semester_list, student_node->AM, student_node->full_name, student_node->semester);
        }
        student_node = advance(student_node, 1);
    }
    return semester_list;
}

void print_students_in_semester(DoublyLinkedList* list, const int semester) {
    DoublyLinkedList semester_list = get_semester_student_list(list, semester);

    Node* student_node = semester_list.head->next;
    
    if (student_node == semester_list.tail) {
        printf("No students in semester %d.\n", semester);
    } else {
        while (student_node != semester_list.tail) {
            printf("AM: %s\n", student_node->AM);
            printf("Full Name: %s\n", student_node->full_name);
            printf("Semester: %d\n\n", student_node->semester);
            student_node = advance(student_node, 1);
        }
    }

    free_resources(&semester_list);
}

void input_AM(char* AM, int n) {
    printf("\nInput student's AM [max %d characters]: ", n - 1);
    fgets(AM, n, stdin);
}

void input_full_name(char* full_name, int n) {
    printf("\nInput student's full name [max %d characters]: ", n - 1);
    fgets(full_name, n, stdin);
}

void input_semester(int* semester) {
    printf("\nInput student's semester: ");
    scanf("%d", semester);
}