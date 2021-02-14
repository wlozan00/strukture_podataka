#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 11

typedef struct _person *student;
typedef struct _person
{
    int numb;
    char name[20];
    char sname[20];
    student next;

} Person;

int init(student[]);
int print(student[]);
int key(char *);
student make_student(void);
int add_student(student[]);
student find(student[]);
int clear_table(student[]);

int main()
{
    student Hash[size];

    init(Hash);

    int n;
    printf("Insert number of students : ");
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        add_student(Hash);
    }

    printf("\n****STUDENT HASH TABLE****\n");
    printf("\n");
    print(Hash);

    find(Hash);

    clear_table(Hash);

    for (int i = 0; i < size; ++i)
    {
        free(Hash[i]);
    }

    return 0;
}

int init(student h[])
{
    for (int i = 0; i < size; ++i)
    {
        h[i] = (student)malloc(sizeof(Person));
    }

    for (int i = 0; i < size; ++i)
    {
        if (h[i] == NULL)
        {
            printf("Erorr in memory allocation!\n");
            return 0;
        }

        else
        {
            h[i]->next = NULL;
            return 1;
        }
    }
}

int print(student h[])
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d", i);

        if (h[i]->next == NULL)
        {
            printf("\t--null--\n");
        }

        else
        {
            student help = h[i]->next;

            while (help != NULL)
            {
                printf("\t%s  %s-->\t", help->name, help->sname);
                help = help->next;
            }
            printf("\n");
        }
    }

    return 1;
}

int key(char *c)
{
    unsigned int val = 0;
    unsigned int index;

    for (int i = 0; i < 5; ++i)
    {
        val += c[i];
    }

    index = val % size;

    return index;
}

student make_student()
{
    student new = NULL;
    new = (student)malloc(sizeof(Person));
    new->numb = -1;

    if (new == NULL)
    {
        printf("Erorr in student allocation!\n");
        return NULL;
    }

    printf("Insert student name :\n");
    scanf("%s", new->name);

    printf("Insert student surname :\n");
    scanf("%s", new->sname);

    printf("Insert student number :  ");
    scanf("%d", &new->numb);

    if (new->numb == -1)
    {
        printf("Error in student number!\n");
        return NULL;
    }

    new->next = NULL;

    return new;
}

int add_student(student h[])
{
    student s = NULL;
    s = make_student();

    if (h[key(s->sname)]->next == NULL)
    {
        s->next = h[key(s->sname)]->next;
        h[key(s->sname)]->next = s;
    }

    else
    {
        student temp = h[key(s->sname)];
        while (temp->next != NULL && strcmp(s->sname, temp->next->sname) > 0)
        {
            temp = temp->next;
        }

        s->next = temp->next;
        temp->next = s;
    }

    return 1;
}

student find(student h[])
{
    char t_name[20], t_sname[20];

    printf("\nEnter the name of the student : ");
    scanf("%s", t_name);

    printf("\nEnter the surname of the student :");
    scanf("%s", t_sname);

    student p = h[key(t_sname)];

    while (p != NULL)
    {
        if (strcmp(p->name, t_name) == 0 && strcmp(p->sname, t_sname) == 0)
        {
            printf("\nStudent %s %s has the number %d\n", p->name, p->sname, p->numb);
            return p;
        }

        p = p->next;
    }

    if (p == NULL)
    {
        printf("\nStudent not found\n");
        return NULL;
    }
}

int clear_table(student h[])
{
    student help = NULL;

    for (int i = 0; i < size; ++i)
    {
        if (h[i]->next != NULL)
        {
            while (h[i]->next != NULL)
            {
                help = h[i]->next;
                h[i]->next = help->next;
                free(help);
            }
        }
    }

    return 0;
}