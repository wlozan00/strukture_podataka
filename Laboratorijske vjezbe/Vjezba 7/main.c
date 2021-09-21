#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef struct _node* position;
typedef struct _node
{
    double val;
    position next;
}node;

position create_node(void);
char* read_from_file(char*);
double calculate_postfix(char*, position);
int push(double, position);
double pop(position);
double temp_result(char, position);
int clear_stack(position);

int main()
{
    position s_head = create_node();
    char* expr = read_from_file("postfix.txt");
    printf("Postfix expression to calculate : %s\n", expr);
    printf("Result of postfix expression : %lg\n", calculate_postfix(expr, s_head));
    free(s_head);
    
    return 1;
}

position create_node()
{
    position s = (position)malloc(sizeof(node));
    if (!s)
    {
        printf("Error in memory allocation!\n");
        return NULL;
    }
    s->next = NULL;

    return s;
}

char* read_from_file(char* fname)
{
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        printf("Error in file oppening!\n");
        return NULL;
    }
    char* str = (char*)malloc(50* sizeof(char));
    memset(str,'\0', 50);

    while(fgets(str, 50, fp) != NULL)
    {
        fscanf(fp, "%s", str);
    }
    fclose(fp);

    return str;
}

int push(double d, position stack)
{
    position n = create_node();
    n->val = d;
    n->next = stack->next;
    stack->next = n;

    return 1;
}

double pop(position stack)
{
    if(stack->next == NULL)
    {
        return INT_MIN;
    }
    position help = stack->next;
    double x = help->val;

    stack->next = help->next;
    free(help);

    return x;
}

double temp_result(char c, position stack)
{
    double b = pop(stack);
    double a = pop(stack);
    if(a  == INT_MIN || b == INT_MIN)
    {
        return INT_MIN;
    }

    switch(c)
    {
        case '+': 
            return a + b;
            break;
        
        case '-':
            return a - b;
            break;

        case '*':
            return a * b;
            break;

        case '/':
            return a / b;
            break;
        default:
            printf("Error, unknown operation!\n");
            return 0;
    }
}

double calculate_postfix(char* str, position stack)
{
    int pos = 0;
    while(*str != '\0')
    {
        double val;
        if(sscanf(str, "%lg%n", &val, &pos))                  //%n znaci koliko je brojeva ucitala funkcija sscanf()
        {
            push(val, stack);
            str += pos;
        }

        else
        {
            char op;
            sscanf(str, " %c%n", &op, &pos);                //razmak je ispred %s u funkciji sscanf() zbog razmaka izmedu
            push(temp_result(op, stack), stack);           //operanda i operacije
            str += pos;
        }
    }
    
    if(stack->next->next != NULL)
    {
        printf("Too many operands in postfix expression!\n");
        clear_stack(stack);
        return INT_MIN;
    }
    else if(stack->next->val == INT_MIN)
    {
        printf("Too many operations in postfix expression!\n");
        return INT_MIN;
    }

    return pop(stack);
}

int clear_stack(position stack)
{
    while(stack->next != NULL)
    {
        position help = stack->next;
        stack->next = help->next;
        free(help);
    }

    return 1;
}