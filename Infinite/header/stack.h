#include <stdio.h>
#include <stdlib.h>
typedef struct stack_el
{
    int value;
    struct stack_el* next;
} stack_el;

stack_el new_stack_el(int value)
{
    stack_el el = {value, NULL};
    return el;
}

void push(stack_el **ptr, int value)
{
    stack_el* new_element = (stack_el*)malloc(sizeof(stack_el));
    if (new_element == NULL) {
        fprintf(stderr, "Memory allocation failed in push\n");
        exit(1);
    }

    new_element->value = value;
    new_element->next = *ptr;
    *ptr = new_element;
}

int pop(stack_el **ptr)
{
    if (*ptr == NULL) {
        fprintf(stderr, "Attempted to pop from empty stack\n");
        return -1;
    }
    
    int value = (*ptr)->value;
    stack_el* temp = *ptr;
    *ptr = (*ptr)->next;

    
    free(temp);
    return value;
}

//Here my code begins
int peek(stack_el *ptr)
{
    if (ptr == NULL) {
        printf("Stack is empty\n");
        return '\0';  // Return null character to indicate empty stack
    }
    return ptr->value;
}