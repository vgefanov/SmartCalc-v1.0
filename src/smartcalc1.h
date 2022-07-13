#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SRC_SMARTCALC1_H_
#define SRC_SMARTCALC1_H_

#define digit(ch) (((ch) >= '0' && (ch) <= '9') || (ch) == '.')

enum element {
    open_bracket,     // 0
    closing_bracket,  // 1
    x,                // 2
    number,           // 3
    addition,         // 4
    subtraction,      // 5
    multiplication,   // 6
    division,         // 7
    exponentiation,   // 8
    modulus,          // 9
    f_cos,            // 10
    f_sin,            // 11
    f_tan,            // 12
    f_acos,           // 13
    f_asin,           // 14
    f_atan,           // 15
    f_sqrt,           // 16
    f_ln,             // 17
    f_log,            // 18
};

struct list {
    double val;
    int priority;
    enum element element;
    struct list *next;
};
/**
 * @brief Создает новый элемент
 * 
 * @param val 
 * @param priority 
 * @param element 
 * @return struct list* 
 */
struct list *create_list_item(double val, int priority, enum element element);
/**
 * @brief 
 * 
 * @param val 
 * @param priority 
 * @param element 
 * @param head 
 */
void insert_start_list(double val, int priority, enum element element, struct list **head);
void insert_end_list(double val, int priority, enum element element, struct list **head);
void delete_start_list(struct list **head);
void delete_end_list(struct list **head);
int return_start_list(double *val, int *priority, enum element *element, struct list **head);
int return_end_list(double *val, int *priority, enum element *element, struct list **head);
int calling_function(struct list **stack);
int parser(char expression[256], struct list **head, double val_of_x);
int stack_work(struct list **initial_list, struct list **stack);
int calculation(char *str, double value_of_x, double *result);

#endif  // SRC_SMARTCALC1_H_
