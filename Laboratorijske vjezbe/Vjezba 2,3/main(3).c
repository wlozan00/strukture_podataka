#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct people* position;
typedef struct people
{
    char name[20];
    char sname[20];
    int year;
    position next;

}person;

person* create_person(void);
int sorted_input(position, position);
int read_from_file(char*, position);
int write_to_file(char*, position);
int clear_list(position);

int main()
{
    position head = create_person();
    read_from_file("people.txt", head);
    write_to_file("sorted.txt", head->next);
    clear_list(head);
    free(head);

    return 1;
}

person* create_person()
{
    person* p = NULL;
    p = (position)malloc(sizeof(person));

    if (!p)
    {
        printf("\nError in creating person!\n");
        return NULL;
    }
    p->next = NULL;

    return p;
}

int sorted_input(position s, position head)
{
    if (!s)
    {
        printf("\nElement to input does not exist!\n");
        return 0;
    }

    position help = head;

    while(help->next != NULL && strcmp(s->sname,help->next->sname) > 0)
    {
        help = help->next;
    }

    s->next = help->next;
    help->next = s;

    return 1;
}

int read_from_file(char* fname, position head)
{
    FILE* fp = NULL;
    fp = fopen(fname, "r");

    if (!fp)
    {
        printf("Error in file oppening!\n");
        return 0;
    }
    char str[256];

    while(fgets(str, 256, fp) != NULL)
    {
        position s = create_person();
        fscanf(fp," %s %s %d", s->name, s->sname, &s->year);
        sorted_input(s, head);
    }
    fclose(fp);

    return 1;
}

int write_to_file(char* fname, position head)
{
    FILE* fp = NULL;
    fp = fopen(fname, "w");
    if (!fp)
    {
        printf("Erorr in file oppening!\n");
        return 0;
    }

    while(head != NULL)
    {
        fprintf(fp, "%s %s %d\n", head->name, head->sname, head->year);
        head = head->next;
    }
    fclose(fp);

    return 1;
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