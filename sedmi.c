#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define len 50

typedef struct node *stack;
typedef struct node
{
    float element;
    stack next;
} Node;

stack allocate(void);
int print(stack);
int push(float, stack);
float pop(stack);
int read(const char *, stack);

int main()
{
    stack head = allocate();

    read("postfix.txt", head);

    print(head->next);

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

int print(stack head)
{
    while (head != NULL)
    {
        printf("%.3g  ", head->element);

        head = head->next;
    }

    printf("\n");

    return 0;
}

int push(float x, stack head)
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

    if (head->next == NULL)
    {
        free(help);
        return x;
    }

    head->next = help->next;
    free(help);

    return x;
}

int read(const char *name, stack head)
{
    FILE *fp = NULL;
    fp = fopen(name, "r");

    if (!fp)
    {
        printf("File not open\n");
        return -1;
    }

    char buffer[len];

    fgets(buffer, len, fp);
    fclose(fp);

    char c;
    int a, b;

    sscanf(buffer, "%d  %d  %c", &a, &b, &c);

    return 0;
}