#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _node* position;
typedef struct _node{
    int value;
    position next;
}node;

position create_node();
int push_stack(position);
int pop_stack(position);
position find_last(position);
int push_queue(position);
int pop_queue(position);
int print_list(position);
int clear_list(position);

int main()
{
    position stack = create_node();
    position queue = create_node();
    srand(time(NULL));

    for (int i = 0; i < 4; i++)
    {
        push_stack(stack);
    }
    printf("Stack : ");
    print_list(stack->next);
    printf("%d\n", pop_stack(stack));
    printf("-----------------------------\n");
    for (int i = 0; i < 4; i++)
    {
        push_queue(queue);
    }
    printf("Queue : ");
    print_list(queue->next);
    printf("%d\n", pop_queue(queue));

    clear_list(stack);
    clear_list(queue);

    return 1;
}

position create_node()
{
    position n = (position)malloc(sizeof(node));
    if(!n)
    {
        printf("Error in memory allocation!\n");
        return NULL;
    }
    n->value = 0;
    n->next = NULL;

    return n;
}

int push_stack(position s)
{
    position n = create_node();
    int val = 10 + (rand() % 91);
    n->value = val;
    n->next = s->next;
    s->next = n;

    return 1;
}

int pop_stack(position s)
{
    position help = s->next;
    if(help == NULL)
    {
        printf("Empty stack\n");
        return 0;
    }

    int x = help->value;
    s->next = help->next;
    free(help);

    return x;
}

int print_list(position h)
{
    if(h == NULL)
    {
        printf("Empty list\n");
        return 0;
    }

    while(h != NULL)
    {
        printf("%d  ", h->value);
        h = h->next;
    }
    printf("\n");

    return 1;
}

position find_last(position h)
{
    position last = h;
    while(last->next != NULL)
    {
        last = last->next;
    }

    return last;
}

int push_queue(position q)
{
    position n = create_node();
    int val = 10 + (rand() % 91);
    n->value = val;

    position last = find_last(q);
    n->next = last->next;
    last->next = n;

    return 1;
}

int pop_queue(position q)
{
    pop_stack(q);
}

int clear_list(position h)
{
    while(h->next != NULL)
    {
        pop_stack(h);
    }
    free(h);

    return 1;
}