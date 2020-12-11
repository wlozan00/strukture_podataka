#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node *position;
typedef struct node
{
    int element;
    position next;
} stack;

position allocate(void);
int push_stack(int, position);
int pop_stack(position);
int push_line(int, position);
int pop_line(position);
int print(position);

int main()
{
    position head1 = NULL;
    head1 = allocate();

    srand(time(NULL));

    printf("Simulacija stoga:\n");

    for (int i = 0; i < 5; i++)
    {
        push_line(10 + rand() % 91, head1);
    }

    print(head1->next);

    pop_line(head1);
    pop_line(head1);

    print(head1->next);

    position head2 = NULL;
    head2 = allocate();

    printf("Simulacija reda:\n");

    for (int i = 0; i < 5; i++)
    {
        push_stack(10 + rand() % 91, head2);
    }

    print(head2->next);

    pop_stack(head2);
    pop_stack(head2);

    print(head2->next);

    return 0;
}

position allocate(void)
{
    position q = NULL;
    q = (position)malloc(sizeof(stack));

    if (q == NULL)
    {
        printf("Greska u mallocu\n");
        return NULL;
    }

    q->next = NULL;

    return q;
}

int push_line(int x, position temp)
{
    position q = NULL;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    q = allocate();

    q->element = x;
    q->next = temp->next;
    temp->next = q;

    return 0;
}

int print(position temp)
{
    while (temp != NULL)
    {
        printf("%d  ", temp->element);

        temp = temp->next;
    }

    printf("\n");

    return 0;
}

int pop_line(position temp)
{
    position help;
    help = temp->next;

    int x;
    x = help->element;

    temp->next = help->next;
    free(help);

    return x;
}

int push_stack(int x, position temp)
{
    position q = allocate();
    q->element = x;

    q->next = temp->next;
    temp->next = q;
}

int pop_stack(position temp)
{
    pop_line(temp);
}