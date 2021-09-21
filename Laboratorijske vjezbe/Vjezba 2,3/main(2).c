#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct people* position;
typedef struct people
{
    char name[20];
    char sname[20];
    unsigned int year;
    position next;

} person;
 
person* create_person(void);
int add_at_head(position);
int print_list(position);
int add_at_tail(position);
position find_by_surname(char*, position);
int delete_by_surname(position);
int add_after(position);
position find_prev(char*, position);
int add_ahead(position);
int clear_list(position);

int main()
{
    position head = NULL;
    head = create_person();

    for(int i = 0; i < 2; i++)
    {
        add_at_head(head);
    }

    for(int i = 0; i < 2; i++)
    {
        add_at_tail(head);
    }
    
    print_list(head->next);

    char str[256];
    printf("\nInsert wanted surname : ");
    scanf("%s",str);

    position x = NULL;
    x = find_by_surname(str, head->next);
    if(x != NULL)
    {
        printf("Wanted person: %s %s\n", x->name, x->sname);
    }

    delete_by_surname(head);
    print_list(head->next);

    add_after(head->next);
    print_list(head->next);

    add_ahead(head);
    print_list(head->next);

    clear_list(head);
    print_list(head->next);
    free(head);

    return 1;
}

person* create_person()
{
    person* p = NULL;
    p = (person*)malloc(sizeof(person));

    if (!p)
    {
        printf("Error in creating a person!\n");
        return NULL;
    }
    p->next = NULL;
    
    return p;
}

int add_at_head(position head)
{
    position p = create_person();
    printf("\nInsert persons name : ");
    scanf("%s", p->name);

    printf("Insert persons surname : ");
    scanf("%s", p->sname);

    printf("Insert %ss year of birth : ", p->name);
    scanf("%d", &p->year);

    p->next = head->next;
    head->next = p;

    return 1;
}

int print_list(position p)
{
    if(p == NULL)
    {
        printf("\nEmpty list\n");
        return 0;
    }

    printf("\nList of people:\n");
    while(p != NULL)
    {
        printf("%s %s %d\n",p->name, p->sname, p->year);
        p = p->next;
    }

    return 1;
}

int add_at_tail(position head)
{
    position temp = head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    add_at_head(temp);
}

position find_by_surname(char* str, position head)
{
    position s = head;

    while(s != NULL && strcmp(s->sname, str) != 0)
    {
        s = s->next;
    }

    if(s == NULL)
    {
        printf("Person not found\n");
    }

    return s;
}

int delete_by_surname(position head)
{
    char str[20];
    printf("\nInsert surname to delete: ");
    scanf("%s", str);
    
    position help = find_prev(str, head);
    if(help == NULL)
    {
        return 0;
    }

    position temp = help->next;
    help->next = temp->next;
    free(temp);

    return 1;
}

int add_after(position head)
{
    char str[20];
    printf("\nInsert surname(after) : ");
    scanf("%s", str);

    while(head != NULL && strcmp(str, head->sname) != 0)
    {
        head = head->next;
    }

    if(head == NULL)
    {
        printf("Person does not exist\n");
        return 0;
    }

    add_at_head(head);
}

position find_prev(char* str, position head)
{
    position prev = head;
    position current = head->next;

    while(current != NULL && strcmp(str, current->sname) != 0)
    {
        prev = current;
        current = current->next;
    }

    if(prev->next == NULL)
    {
        printf("\nPerson does not exist\n");
        return NULL;
    }

    return prev;
}

int add_ahead(position head)
{
    char str[20];
    printf("\nInsert surname(before) : ");
    scanf("%s", str);

    position help = find_prev(str, head);

    if(help == NULL)
    {
        return 0;
    }

    add_at_head(help);
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

    return 1;
}