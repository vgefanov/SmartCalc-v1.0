#include "smartcalc1.h"

// создает новый элемент
struct list *create_list_item(double val, int priority, enum element element) {
    struct list *item = malloc(sizeof(struct list));
    if (item != NULL) {
        item->val = val;
        item->element = element;
        item->priority = priority;
        item->next = NULL;
    } else {
        fprintf(stderr, "Error. Incorrect data\n");
    }
    return item;
}

// вставляет элемент в начало списка
void insert_start_list(double val, int priority, enum element element, struct list **head) {
    struct list *new_item = create_list_item(val, priority, element);
    if (*head == NULL) {
        *head = new_item;
    } else {
        new_item->next = *head;
        *head = new_item;
    }
}

// вставляет элемент в конец списка
void insert_end_list(double val, int priority, enum element element, struct list **head) {
    struct list *new_item = create_list_item(val, priority, element);
    if (*head == NULL) {
        *head = new_item;
    } else {
        struct list *tmp = *head;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new_item;
    }
}

// удаляет элемент из начала списка
void delete_start_list(struct list **head) {
    if (*head != NULL) {
        struct list *tmp = *head;
        *head = tmp->next;
        free(tmp);
    }
}

// удаляет элемент из конца списка
void delete_end_list(struct list **head) {
    if (*head != NULL) {
        struct list *tmp_first = *head;
        struct list *tmp_last = *head;
        if (tmp_last->next != NULL) {
            while (tmp_last->next != NULL) {
                tmp_first = tmp_last;
                tmp_last = tmp_last->next;
            }
            tmp_first->next = NULL;
            free(tmp_last);
        } else {
            *head = NULL;
            free(tmp_last);
        }
    }
}

// возвращает элемент из начала списка
int return_start_list(double *val, int *priority, enum element *element, struct list **head) {
    int status = 0;
    if (*head != NULL) {
        struct list *item = *head;
        *val = item->val;
        *element = item->element;
        *priority = item->priority;
    } else {
        status = 1;
    }
    return status;
}

// возвращает элемент из конца списка
int return_end_list(double *val, int *priority, enum element *element, struct list **head) {
    int status = 0;
    if (*head != NULL) {
        struct list *item = *head;
        while (item->next != NULL) {
            item = item->next;
        }
        *val = item->val;
        *element = item->element;
        *priority = item->priority;
    } else {
        status = 1;
    }
    return status;
}

// вычисляет выражения
int calling_function(struct list **stack) {
    while ((*stack)->next != NULL) {
        struct list *buff = NULL;
        struct list operator= {0, 0, 0, NULL};
        struct list operand2 = {0, 0, 0, NULL};
        struct list operand3 = {0, 0, 0, NULL};
        struct list operand4 = {0, 0, 0, NULL};
        return_start_list(&operator.val, &operator.priority, &operator.element, stack);
        while (operator.element<4) {
            insert_end_list(operator.val, operator.priority, operator.element, &buff);
            delete_start_list(stack);
            int res = return_start_list(&operator.val, &operator.priority, &operator.element, stack);
            if (res == 1) {
                return 1;
            }
        }
        delete_start_list(stack);
        if (operator.element<10) {
            return_end_list(&operand2.val, &operand2.priority, &operand2.element, &buff);
            delete_end_list(&buff);
            return_end_list(&operand3.val, &operand3.priority, &operand3.element, &buff);
            delete_end_list(&buff);
        } else {
            return_end_list(&operand2.val, &operand2.priority, &operand2.element, &buff);
            delete_end_list(&buff);
        }
        switch (operator.element) {
            case 4: {
                operand4.val = operand3.val + operand2.val;
                break;
            }
            case 5: {
                operand4.val = operand3.val - operand2.val;
                break;
            }
            case 6: {
                operand4.val = operand3.val * operand2.val;
                break;
            }
            case 7: {
                operand4.val = operand3.val / operand2.val;
                break;
            }
            case 8: {
                operand4.val = pow(operand3.val, operand2.val);
                break;
            }
            case 9: {
                operand4.val = fmod(operand3.val, operand2.val);
                break;
            }
            case 10: {
                operand4.val = cos(operand2.val);
                break;
            }
            case 11: {
                operand4.val = sin(operand2.val);
                break;
            }
            case 12: {
                operand4.val = tan(operand2.val);
                break;
            }
            case 13: {
                operand4.val = acos(operand2.val);
                break;
            }
            case 14: {
                operand4.val = asin(operand2.val);
                break;
            }
            case 15: {
                operand4.val = atan(operand2.val);
                break;
            }
            case 16: {
                operand4.val = sqrt(operand2.val);
                break;
            }
            case 17: {
                operand4.val = log(operand2.val);
                break;
            }
            case 18: {
                operand4.val = log10(operand2.val);
                break;
            }
            default: {
                fprintf(stderr, "Error. Incorrect data\n");
                return 1;
            }
        }
        // operand4.element = operand3.element;
        insert_start_list(operand4.val, operand4.priority, operand4.element, stack);
        while (buff != NULL) {
            double val = 0;
            enum element element = 0;
            int priority = 0;
            int res = return_end_list(&val, &priority, &element, &buff);
            if (res == 0) {
                insert_start_list(val, priority, element, stack);
                delete_end_list(&buff);
            }
        }
    }
    return 0;
}

int parser(char expression[256], struct list **head, double val_of_x) {
    int expression_length = (int)strlen(expression);
    for (int i = 0; i < expression_length; i++) {
        switch (expression[i]) {
            case '(': {
                insert_end_list(0, -1, 0, head);
                break;
            }
            case ')': {
                insert_end_list(0, -1, 1, head);
                break;
            }
            case 'x': {
                insert_end_list(val_of_x, 0, 2, head);
                break;
            }
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
            case '.': {
                char *start_ptr = &expression[i];
                for (; digit(expression[i]); i++) {
                }
                char *end_ptr = &expression[--i];
                double number = strtod(start_ptr, &end_ptr);
                insert_end_list(number, 0, 3, head);
                break;
            }
            case '+': {
                insert_end_list(0, 1, 4, head);
                break;
            }
            case '-': {
                insert_end_list(0, 1, 5, head);
                break;
            }
            case '*': {
                insert_end_list(0, 2, 6, head);
                break;
            }
            case '/': {
                insert_end_list(0, 2, 7, head);
                break;
            }
            case '^': {
                insert_end_list(0, 3, 8, head);
                break;
            }
            case 'm': {
                int res = strncmp(&expression[i], "mod", 3);
                if (res == 0) {
                    insert_end_list(0, 2, 9, head);
                    i += 2;
                }
                break;
            }
            case 's': {
                int res = strncmp(&expression[i], "sin(", 4);
                if (res == 0) {
                    insert_end_list(0, 4, 11, head);
                    i += 2;
                } else {
                    res = strncmp(&expression[i], "sqrt(", 5);
                    if (res == 0) {
                        insert_end_list(0, 4, 16, head);
                        i += 3;
                    }
                }
                break;
            }
            case 'c': {
                int res = strncmp(&expression[i], "cos(", 4);
                if (res == 0) {
                    insert_end_list(0, 4, 10, head);
                    i += 2;
                }
                break;
            }
            case 't': {
                int res = strncmp(&expression[i], "tan(", 4);
                if (res == 0) {
                    insert_end_list(0, 4, 12, head);
                    i += 2;
                }
                break;
            }
            case 'a': {
                int res = strncmp(&expression[i], "asin(", 5);
                if (res == 0) {
                    insert_end_list(0, 4, 14, head);
                    i += 3;
                } else if (!strncmp(&expression[i], "acos(", 5)) {
                    insert_end_list(0, 4, 13, head);
                    i += 3;
                } else if (!strncmp(&expression[i], "atan(", 5)) {
                    insert_end_list(0, 4, 15, head);
                    i += 3;
                }
                break;
            }
            case 'l': {
                int res = strncmp(&expression[i], "ln(", 3);
                if (res == 0) {
                    insert_end_list(0, 4, 17, head);
                    i += 1;
                } else {
                    res = strncmp(&expression[i], "log(", 4);
                    if (res == 0) {
                        insert_end_list(0, 4, 18, head);
                        i += 2;
                    }
                }
                break;
            }
            case ' ': {
                break;
            }
            default: {
                fprintf(stderr, "Error. Incorrect data\n");
                printf("Error. Incorrect char - %c ", expression[i]);
                return 1;
            }
        }
    }
    return 0;
}

int stack_work(struct list **initial_list, struct list **stack) {
    struct list *additional_stack = NULL;
    while (*initial_list != NULL) {
        double initial_list_val = 0;
        enum element initial_list_element = 0;
        int initial_list_priority = 0;
        int res =
            return_start_list(&initial_list_val, &initial_list_priority, &initial_list_element, initial_list);
        if (res == 0) {
            if (initial_list_element == 3 || initial_list_element == 2) {
                insert_end_list(initial_list_val, initial_list_priority, initial_list_element, stack);
            }
            if (initial_list_element > 9 || initial_list_element == 0) {
                insert_end_list(initial_list_val, initial_list_priority, initial_list_element,
                                &additional_stack);
            }
            if (initial_list_element > 3 && initial_list_element < 10) {
                double additional_stack_val = 0;
                enum element additional_stack_element = 0;
                int additional_stack_priority = 0;
                int additional_res = return_end_list(&additional_stack_val, &additional_stack_priority,
                                                     &additional_stack_element, &additional_stack);
                while (additional_stack_priority >= initial_list_priority && additional_res == 0) {
                    insert_end_list(additional_stack_val, additional_stack_priority, additional_stack_element,
                                    stack);
                    delete_end_list(&additional_stack);
                    additional_res = return_end_list(&additional_stack_val, &additional_stack_priority,
                                                     &additional_stack_element, &additional_stack);
                }
                insert_end_list(initial_list_val, initial_list_priority, initial_list_element,
                                &additional_stack);
            }
            if (initial_list_element == 1) {
                double additional_stack_val = 0;
                enum element additional_stack_element = 0;
                int additional_stack_priority = 0;
                int additional_res = return_end_list(&additional_stack_val, &additional_stack_priority,
                                                     &additional_stack_element, &additional_stack);
                while (additional_stack_element != 0 && additional_res == 0) {
                    insert_end_list(additional_stack_val, additional_stack_priority, additional_stack_element,
                                    stack);
                    delete_end_list(&additional_stack);
                    additional_res = return_end_list(&additional_stack_val, &additional_stack_priority,
                                                     &additional_stack_element, &additional_stack);
                }
                if (additional_res == 0) {
                    delete_end_list(&additional_stack);
                } else {
                    return 1;
                }
                additional_res = return_end_list(&additional_stack_val, &additional_stack_priority,
                                                 &additional_stack_element, &additional_stack);
                if (additional_res == 0) {
                    insert_end_list(additional_stack_val, additional_stack_priority, additional_stack_element,
                                    stack);
                    delete_end_list(&additional_stack);
                }
            }
        } else {
            fprintf(stderr, "Error. Incorrect data\n");
            while (additional_stack != NULL) {
                delete_end_list(&additional_stack);
            }
            return 1;
        }
        delete_start_list(initial_list);
    }
    double additional_stack_val = 0;
    enum element additional_stack_element = 0;
    int additional_stack_priority = 0;
    int additional_res = return_end_list(&additional_stack_val, &additional_stack_priority,
                                         &additional_stack_element, &additional_stack);
    if (additional_res == 0 && (additional_stack_element == 0 || additional_stack_element == 1)) {
        while (additional_stack != NULL) {
            delete_end_list(&additional_stack);
        }
        return 1;
    }
    while (additional_res == 0) {
        insert_end_list(additional_stack_val, additional_stack_priority, additional_stack_element, stack);
        delete_end_list(&additional_stack);
        additional_res = return_end_list(&additional_stack_val, &additional_stack_priority,
                                         &additional_stack_element, &additional_stack);
        if (additional_res == 0 && (additional_stack_element == 0 || additional_stack_element == 1)) {
            while (additional_stack != NULL) {
                delete_end_list(&additional_stack);
            }
            return 1;
        }
    }
    return 0;
}

int calculation(char *str, double value_of_x, double *result) {
    int execution_status = 0;
    char expression[256] = "";
    struct list *initial_list = NULL;
    struct list *resulting_stack = NULL;
    snprintf(expression, sizeof(expression), "%s", str);
    if (strlen(expression) > 0) {
        execution_status = parser(expression, &initial_list, value_of_x);
        if (execution_status == 0) {
            execution_status = stack_work(&initial_list, &resulting_stack);
            if (execution_status == 0) {
                execution_status = calling_function(&resulting_stack);
                if (execution_status == 0) {
                    *result = (*resulting_stack).val;
                }
            }
        }
    }
    while (initial_list != NULL) {
        delete_end_list(&initial_list);
    }
    while (resulting_stack != NULL) {
        delete_end_list(&resulting_stack);
    }
    return execution_status;
}

// int main() {
//    double res = 0.0;
//    char *str = "20+3-4*3";
//    calculation(str, 0.0, &res);
//    printf("%f", res);
//    return 0;
// }
