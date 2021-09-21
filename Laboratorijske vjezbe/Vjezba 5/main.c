#include<stdio.h>
#include<stdlib.h>

typedef struct _list* position;
typedef struct _list{
    int value;
    position next;
}list;

position create_node(void);
int sort_input(position, position);
int read_file(char*, position);
int print_list(position);
position list_union(position, position);
position list_intersection(position, position);
int clear_list(position);

int main()
{
    position head1 = create_node();
    position head2 = create_node();

    read_file("list1", head1);
    read_file("list2", head2);

    printf("List 1 : ");
    print_list(head1->next);
    printf("----------------------------------------------\n");
    printf("List 2 : ");
    print_list(head2->next);
    printf("----------------------------------------------\n");
    printf("List intersection : ");
    position result1 = list_intersection(head1->next, head2->next);
    print_list(result1->next);
    printf("----------------------------------------------\n");
    printf("List union : ");
    position result2 = list_union(head1->next, head2->next);
    print_list(result2->next);

    clear_list(head1);
    clear_list(head2);
    clear_list(result1);
    clear_list(result2);

    return 1;
}

position create_node()
{
    position s = (position)malloc(sizeof(list));
    if (!s)
    {
        printf("Error in memory allocation!\n");
        return NULL;
    }
    s->next = NULL;

    return s;
}

int sort_input(position s, position h)
{
    if(s == NULL || h == NULL)
    {
        return 0;
    }

    position temp = h;
    while (temp->next != NULL && (s->value <= temp->next->value))
    {
        temp = temp->next;
    }

    if(s->value == temp->value)
    {
        free(s);
        return 0;
    }

    else
    {
        s->next = temp->next;
        temp->next = s;

        return 1;
    }
}

int read_file(char* fname, position h)
{
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        printf("Error in file oppening!\n");
        return 0;
    }
    char str[50];

    while(fgets(str, 50, fp) != NULL)
    {
        position s = create_node();
        fscanf(fp, "%d", &s->value);
        sort_input(s, h);
    }
    fclose(fp);

    return 1;
}

int print_list(position h)
{
    if (h == NULL)
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

position list_intersection(position l1, position l2)
{
    position r = create_node();

    while(l1 != NULL && l2 != NULL)
    {
        if (l1->value == l2->value)
        {
            position s = create_node();
            s->value = l1->value;
            sort_input(s, r);

            l1 = l1->next;
            l2 = l2->next;
        }

        else if(l1->value > l2->value)
        {
            l1 = l1->next;
        }

        else
        {
            l2 = l2->next;
        }
        
    }

    return r;
}

position list_union(position l1, position l2)
{
    position r = create_node();
    while(l1 != NULL && l2 != NULL)
    {
        position s = create_node();
        if(l1->value > l2->value)
        {
            s->value = l1->value;
            sort_input(s, r);
            l1 = l1->next;
        }

        else if(l1->value < l2->value)
        {
            s->value = l2->value;
            sort_input(s, r);
            l2 = l2->next;
        }

        else
        {
            s->value = l1->value;
            sort_input(s, r);
            l1 = l1->next;
            l2 = l2->next;
        }
        
    }

    while(l1 != NULL)
    {
        position s = create_node();
        s->value = l1->value;
        sort_input(s, r);
        l1 = l1->next;
    }

    while(l2 != NULL)
    {
        position s = create_node();
        s->value = l2->value;
        sort_input(s, r);
        l2 = l2->next;
    }

    return r;
}

int clear_list(position h)
{
    while(h->next != NULL)
    {
        position help = h->next;
        h->next = help->next;
        free(help);
    }
    free(h);

    return 1;
}