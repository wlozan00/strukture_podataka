#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 11

typedef struct _node* position;
typedef struct _node
{
    char name[20];
    char sname[20];
    int number;
    position next;
}node;

position* create_table();
position create_node();
int sort_input(position, position);
int hash_key(char*);
int get_data(char*, position*);
int print_students(position);
int print_table(position*);
position select_student(position*);
int clear_student(position);
int clear_table(position*);

int main()
{
    position* hash = create_table();
    get_data("students.txt", hash);
    print_table(hash);
    position student = select_student(hash);
    clear_table(hash);

    return 1;
}

position create_node()
{
    position s = (position)malloc(sizeof(node));
    if (s == NULL)
    {
        printf("Error in student creation!\n");
        return NULL;
    }
    s->next =  NULL;
    
    return s;
}

position* create_table()
{
    position* h = (position*)malloc(SIZE * sizeof(position));
    if (h == NULL)
    {
        printf("Error in hash table creation!\n");
        return NULL;
    }

    for (int i = 0; i < SIZE; i++)
    {
        h[i] = create_node();
    }
   
    return h;
}

int hash_key(char* str)
{
    int sum = 0;

    for(int i = 0; i < 5; i++)
    {
        sum += str[i];
    }

    return (sum % SIZE);
}

int sort_input(position s, position h)
{
    if(s == NULL)
    {
        printf("Error, no student to input!\n");
        return 0;
    }

    while(h->next != NULL && (strcmp(s->sname, h->next->sname) > 0 || (strcmp(s->sname, h->next->sname) == 0 && strcmp(s->name, h->next->name) > 0)))
    {
        h = h->next;
    }

    s->next = h->next;
    h->next = s;

    return 1;
}

int get_data(char* fname, position* table)
{
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
    {
        printf("Error in file oppening!\n");
        return 0;
    }

    char str[256];
    while(fgets(str, 256, fp) != NULL)
    {
        position s = create_node();
        fscanf(fp, "%s %s %d", s->name, s->sname, &s->number);
        sort_input(s, table[hash_key(s->sname)]);
    }
    fclose(fp);

    return 1;
}

int print_students(position t_row)
{
    if(t_row == NULL)
    {
        printf("********* Empty row *********");
        return 0;
    }
    while(t_row != NULL)
    {
        printf("--------> %s %s ", t_row->name, t_row->sname);
        t_row = t_row->next;
    }

    return 1;
}

int print_table(position* table)
{
    printf("\n***STUDENT HASH TABLE***\n");
    printf("\n");
    for(int i = 0; i < SIZE; i++)
    {
        printf("%d ", i);
        print_students(table[i]->next);
        printf("\n");
    }
    printf("\n");

    return 1;
}

position select_student(position* table)
{
    char t_name[20];
    char t_sname[20];
    printf("Insert name : ");
    scanf("%s", t_name);
    printf("Insert surname : ");
    scanf("%s", t_sname);

    position s = table[hash_key(t_sname)];
    while(s != NULL && (strcmp(t_name, s->name) != 0 || strcmp(t_sname, s->sname) != 0))
    {
        s = s->next;
    }

    if(s == NULL)
    {
        printf("Student not found\n");
        return NULL;
    }

    printf("Selected student : %s %s  Student number : %d\n", s->name, s->sname, s->number);

    return s;
}

int clear_student(position t_row)
{
    while(t_row->next != NULL)
    {
        position help = t_row->next;
        t_row->next = help->next;
        free(help);
    }
    free(t_row);

    return 1;
}

int clear_table(position* table)
{
    for(int i = 0; i < SIZE; i++)
    {
        clear_student(table[i]);
    }
    free(table);

    return 1;
}