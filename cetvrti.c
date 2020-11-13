#include <stdio.h>
#include <stdlib.h>
#define LEN 256

typedef struct _polinoms *position;
typedef struct _polinoms
{
    int exp;
    int koef;
    position next;
} polinoms;

int get(const char *, position); //uzima polinome iz datoteke
int add(position, position, position);
int multiply(position, position, position);
int counter(const char *); //brojac koliko cvorova treba alocirati
int print(position);
int sortInput(position, int, int); //stvaranje cvorova i sortirano upisivanje elemenata
int clear(position);

int main()
{
    position head1, head2, rez1, rez2;

    head1 = (position)malloc(sizeof(polinoms));
    head2 = (position)malloc(sizeof(polinoms));
    rez1 = (position)malloc(sizeof(polinoms));
    rez2 = (position)malloc(sizeof(polinoms));

    if (head1 == NULL || head2 == NULL || rez2 == NULL || rez1 == NULL)
    {
        perror("malloc");
        return -1;
    }

    head1->next = NULL;
    head2->next = NULL;
    rez1->next = NULL;
    rez2->next = NULL;

    printf("Prva vezana lista:\n");
    get("polinomi1.txt", head1);
    print(head1->next);
    printf("-------------------------------------------------\n");
    printf("Druga vezana lista:\n");
    get("polinomi2.txt", head2);
    print(head2->next);
    printf("-------------------------------------------------\n");
    printf("Zbroj polinoma:\n");
    add(head1, head2, rez1);
    print(rez1->next);
    printf("-------------------------------------------------\n");
    printf("Umnozak polinoma:\n");
    multiply(head1, head2, rez2);
    print(rez2->next);
    printf("-------------------------------------------------\n");

    clear(head1);
    clear(head1);
    clear(rez1);
    clear(rez2);

    free(head1);
    free(head2);
    free(rez1);
    free(rez2);

    return 0;
}

int counter(const char *name)
{ //polinome sam zapisao redak po redak
    FILE *fp = NULL;
    fp = fopen(name, "r");

    int n = 0;
    char buffer[256];

    if (fp == NULL)
    {
        printf("Greska u otvaranju datoteke\n");
        return -1;
    }

    while (fgets(buffer, 256, fp) != NULL)
    {
        ++n;
    }

    fclose(fp);
    return n;
}

int sortInput(position temp, int a, int b)
{
    position new = (position)malloc(sizeof(polinoms));

    if (new == NULL)
    {
        perror("malloc");
        return -1;
    }

    new->koef = a;
    new->exp = b;

    while (temp->next != NULL && temp->next->exp < new->exp)
    {
        temp = temp->next;
    }

    new->next = temp->next;
    temp->next = new;

    return 0;
}

int get(const char *name, position temp)
{
    FILE *fp = NULL;
    fp = fopen(name, "r");

    if (fp == NULL)
    {
        printf("Greska u otvaranju datoteke\n");
        return -1;
    }

    for (int i = 0; i < counter(name); i++)
    {
        fscanf(fp, "%d %d", &temp->koef, &temp->exp);
        sortInput(temp, temp->koef, temp->exp);
    }

    fclose(fp);
    return 0;
}

int print(position temp)
{

    while (temp != NULL)
    {
        printf("%d  %d\n", temp->koef, temp->exp);
        temp = temp->next;
    }

    return 0;
}

int add(position temp1, position temp2, position rez)
{
    position p = temp1->next;
    position q = temp2->next;

    if (p == NULL && q == NULL)
    {
        printf("Nema se sto zbrojiti\n");
        return -1;
    }

    while (p != NULL && q != NULL)
    {
        if (p->exp == q->exp)
        {
            sortInput(rez, p->koef + q->koef, p->exp);

            p = p->next;
            q = q->next;
        }

        else if (p->exp < q->exp)
        {
            sortInput(rez, p->koef, p->exp);
            p = p->next;
        }

        else
        {
            sortInput(rez, q->koef, q->exp);
            q = q->next;
        }
    }

    while (p != NULL)
    {
        sortInput(rez, p->koef, p->exp);
        p = p->next;
    }

    while (q != NULL)
    {
        sortInput(rez, q->koef, q->exp);
        q = q->next;
    }

    return 0;
}

int multiply(position temp1, position temp2, position rez)
{
    position p = NULL;
    position q = NULL;

    for (p = temp1->next; p != NULL; p = p->next)
    {
        for (q = temp2->next; q != NULL; q = q->next)
        {
            sortInput(rez, p->koef * q->koef, p->exp + q->exp);
        }
    }

    return 0;
}

int clear(position temp)
{
    position help = NULL;
    while (temp->next != NULL)
    {
        help = temp->next;
        temp->next = help->next;
        free(help);
    }

    return 0;
}