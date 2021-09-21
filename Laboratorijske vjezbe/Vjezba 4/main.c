#include<stdio.h>
#include<stdlib.h>

typedef struct poly* position;
typedef struct poly{
    int koef;
    int exp;
    position next;
}node;

position create_node();
int sort_input(position, position);
int read_from_file(char*, position);
int print_list(position);
position add_lists(position, position);
position multiply_lists(position, position);
int clear_list(position);

int main()
{
    position head1 = create_node();
    position head2 = create_node();

    read_from_file("file1", head1);
    read_from_file("file2", head2);

    printf("List 1\n");
    print_list(head1->next);
    printf("-------------------------------------\n");
    printf("List2\n");
    print_list(head2->next);

    printf("-------------------------------------\n");
    printf("Result of adding lists 1 and 2 :\n");
    position result1 = add_lists(head1->next, head2->next);
    print_list(result1->next);

    printf("-------------------------------------\n");
    printf("Result of multiplying lists 1 and 2 :\n");
    position result2 = multiply_lists(head1->next, head2->next);
    print_list(result2->next);

    clear_list(head1);
    clear_list(head2);
    clear_list(result1);
    clear_list(result2);

    return 1;
}

position create_node()
{
    position s = (position)malloc(sizeof(node));
    
    if(!s)
    {
        printf("\nError in memory allocation!\n");
        return NULL;
    }
    
    s->next = NULL;
    
    return s;
}

int sort_input(position s, position h)
{
    if(!s)
    {
        printf("\nElement does not exist\n");
        return 0;
    }

    position help = h;
    while(help->next != NULL && (s->exp <= help->next->exp))
    {
        help = help->next;
    }

    if(s->exp == help->exp)
    {
        help->koef += s->koef;
        free(s);
        return 0;
    }

    else
    {
        s->next = help->next;
        help->next = s;
        return 1;
    }
}

int read_from_file(char* fname, position h)
{
    FILE *fp = fopen(fname, "r");
    if (!fp)
    {
        printf("\nError in file oppening!\n");
        return 0;
    }
    char str[256];
    
    while(fgets(str, 256, fp) != NULL)
    {
        position s = create_node();
        fscanf(fp, "%d %d",&s->koef, &s->exp);
        sort_input(s, h);
    }
    fclose(fp);

    return 1;
}

int print_list(position h)
{
    if(!h)
    {
        printf("\nEmpty list\n");
        return 0;
    }

    while (h != NULL)
    {
        printf ("Koeficent : %d Eksponent : %d\n", h->koef, h->exp);
        h = h->next;
    }
    
    return 1;
}

position add_lists(position l1, position l2)
{
    position r = create_node();

    while(l1 != NULL && l2 != NULL)
    {
        position s = create_node();

        if(l1->exp == l2->exp)
        {
            s->exp = l1->exp;
            s->koef = l1->koef + l2->koef;
            sort_input(s, r);
            l1 = l1->next;
            l2 = l2->next;
        }

        else if(l1->exp > l2->exp)
        {
            s->exp = l1->exp;
            s->koef = l1->koef;
            sort_input(s, r);
            l1 = l1->next;
        }

        else 
        {
            s->exp = l2->exp;
            s->koef = l2->koef;
            sort_input(s, r);
            l2 = l2->next;
        }
    }

    while(l1 != NULL)
    {
        position s = create_node();
        s->exp = l1->exp;
        s->koef = l1->koef;
        sort_input(s, r);
        l1 = l1->next;
    }

    while(l2 != NULL)
    {
        position s = create_node();
        s->exp = l2->exp;
        s->koef = l2->koef;
        sort_input(s, r);
        l2 = l2->next;
    }

    return r;
}

position multiply_lists(position l1, position l2)
{
    position r = create_node();
    position help = l2;

    while(l1 != NULL)
    {
        while(l2 != NULL)
        {
            position s = create_node();
            s->koef = l1->koef * l2->koef;
            s->exp = l1->exp + l2->exp;
            sort_input(s, r);
            l2 = l2->next;
        }

        l2 = help;
        l1 = l1->next;
    }

    return r;
}

int clear_list(position head)
{
    position help = NULL;
    while(head->next != NULL)
    {
        help = head->next;
        head->next = help->next;
        free(help);
    }
    free(head);

    return 1;
}