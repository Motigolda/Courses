#include <stdio.h>
#include "StudentList.h"
#include <stdlib.h>
#define STUDENT_TEMPLATE "Student ID: %d\nGrade1: %d\nGrade2: %d"

StudentList* createList(){
    StudentList* student_list = malloc(sizeof(StudentList));
    student_list->head = NULL;
    return student_list;
}

void deleteList(StudentList* student_list){
    if (student_list == NULL) return;
    
    StudentNode* current_student = student_list->head;
    StudentNode* student_to_delete = NULL;
    while(current_student != NULL){
        student_to_delete = current_student;
        current_student = current_student->next;
        free(student_to_delete);
    }

    free(student_list);
}

void printStudentNode(StudentNode* const student_node){
    if (student_node == NULL) return;

    if (student_node->st == NULL) return;
    
    printf(STUDENT_TEMPLATE, 
        student_node->st->id, 
        student_node->st->grade1, 
        student_node->st->grade2);
}

void printStudentList(StudentList* const student_list){

}

void addToList(StudentList* student_list, Student* student){

}
