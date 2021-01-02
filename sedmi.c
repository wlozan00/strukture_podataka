#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define len 256

typedef struct node *stack;
typedef struct node
{
    float element;
    stack next;
} Node;

stack allocate(void);
float push(float, stack);
float pop(stack);
float read(const char *, stack);

int main()
{
    stack head = allocate();

    read("postfix.txt", head);

    float x = pop(head);
    printf("Rezultat operacije iznosi : %.2f\n", x);

    free(head);

    return 0;
}

stack allocate()
{
    stack newNode = NULL;
    newNode = (stack)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Greska u alokaciji memorije\n");
        return NULL;
    }

    newNode->next = NULL;

    return newNode;
}

float push(float x, stack head)
{
    stack q = allocate();
    q->element = x;

    q->next = head->next;
    head->next = q;

    return 0;
}

float pop(stack head)
{
    stack help = head->next;

    float x = help->element;

    if (head->next == NULL)
    {
        printf("Prazan stack\n");
    }

    if (help->next == NULL)
    {
        free(help);
        return x;
    }

    head->next = help->next;
    free(help);

    return x;
}

float read(const char *name, stack head)
{
    int position = 0;
    float a, b;

    FILE *fp = NULL;
    fp = fopen(name, "r");

    if (!fp)
    {
        printf("File not open\n");
        return -1;
    }

    char *buffer = NULL;
    buffer = (char *)malloc(len);

    fgets(buffer, len, fp);
    fclose(fp);

    printf("Postfiks izraz glasi : %s", buffer);

    while (*buffer != '\0')
    {
        float n = 0;
        sscanf(buffer, "%f%n", &n, &position);

        if (n)
        {
            push(n, head);
            buffer += position;
        }
        else
        {
            char op;
            sscanf(buffer, "%c%n", &op, &position);

            buffer += position;

            switch (op)
            {
            case '+':
            {
                a = pop(head);
                b = pop(head);
                push(a + b, head);
                break;
            }

            case '-':
            {
                a = pop(head);
                b = pop(head);
                push(b - a, head);
                break;
            }

            case '*':
            {
                a = pop(head);
                b = pop(head);
                push(a * b, head);
                break;
            }

            case '/':
            {
                a = pop(head);
                b = pop(head);
                push(b / a, head);

                break;
            }
            }
        }
    }
    printf("\n");

    return 0;
}
