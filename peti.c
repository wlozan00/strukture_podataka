#include <stdio.h>
#include <stdlib.h>
#define len 256

typedef struct _node *position;
typedef struct _node
{
    int element;
    position next;
} Node;

int read(const char *);                //brojac redova datoteke koju otvaramo
int sortInput(const char *, position); //unosi elemente (sortirane) datoteke u vezanu listu
int newSort(int, position);            //sortirani unos novog elementa tipa int u vezanu listu
int print(position);
int Union(position, position, position);
position cut(position, position);
int check(position); //provjerava ima li dvostrukih elemenata u vezanoj listi

int main()
{
    position head1 = NULL;
    position head2 = NULL;
    head1 = (position)malloc(sizeof(Node));
    head2 = (position)malloc(sizeof(Node));

    if (head1 == NULL)
    {
        perror("malloc1\n");
        return -1;
    }

    if (head2 == NULL)
    {
        perror("malloc2\n");
        return -1;
    }

    head1->next = NULL;
    head2->next = NULL;

    printf("Prva vezana lista glasi:\n");
    sortInput("list1.txt", head1);
    check(head1->next);
    print(head1->next);
    printf("--------------------------------------------------------\n");
    printf("Druga vezana lista glasi:\n");
    sortInput("list2.txt", head2);
    check(head2->next);
    print(head2->next);
    printf("--------------------------------------------------------\n");
    printf("Unija vezanih listi glasi:\n");
    position rez1 = NULL;
    rez1 = (position)malloc(sizeof(Node));

    if (rez1 == NULL)
    {
        perror("malloc3\n");
        return -1;
    }

    rez1->next = NULL;

    Union(head1->next, head2->next, rez1);
    print(rez1->next);
    printf("--------------------------------------------------------\n");
    printf("Presjek vezanih lista glasi:\n");
    position rez2 = NULL;

    rez2 = cut(head1->next, head2->next);
    print(rez2->next);
    printf("--------------------------------------------------------\n");

    return 0;
}

int read(const char *name)
{
    FILE *fp = NULL;
    fp = fopen(name, "r");

    if (fp == NULL)
    {
        perror("Greska u citanju datoteke\n");
        return -1;
    }

    char buffer[len];
    int n = 0;

    while (fgets(buffer, len, fp) != NULL)
    {
        ++n;
    }

    fclose(fp);
    return n;
}

int newSort(int num, position temp)
{
    position new = NULL;
    new = (position)malloc(sizeof(Node));

    if (new == NULL)
    {
        perror("malloc\n");
        return -1;
    }

    new->element = num;

    while (temp->next != NULL && temp->next->element < new->element)
    {
        temp = temp->next;
    }

    new->next = temp->next;
    temp->next = new;

    return 0;
}

int sortInput(const char *name, position temp)
{
    FILE *fp = NULL;
    fp = fopen(name, "r");

    if (fp == NULL)
    {
        perror("Greska u otvaranju datoteke\n");
        return -1;
    }

    for (int i = 0; i < read(name); i++)
    {
        fscanf(fp, "%d", &temp->element);
        newSort(temp->element, temp);
    }

    fclose(fp);
    return 0;
}

int print(position x)
{
    while (x != NULL)
    {
        printf("%d\n", x->element);
        x = x->next;
    }

    return 0;
}

int Union(position p, position q, position r)
{
    while (p != NULL && q != NULL)
    {
        if (p->element < q->element)
        {
            newSort(p->element, r);
            p = p->next;
        }

        else if (q->element < p->element)
        {
            newSort(q->element, r);
            q = q->next;
        }

        else
        {
            newSort(p->element, r);
            p = p->next;
            q = q->next;
        }
    }

    while (p != NULL)
    {
        newSort(p->element, r);
        p = p->next;
    }

    while (q != NULL)
    {
        newSort(q->element, r);
        q = q->next;
    }

    return 0;
}

position cut(position p, position q)
{
    position rez = NULL;
    rez = (position)malloc(sizeof(Node));

    if (rez == NULL)
    {
        perror("rez\n");
        return NULL;
    }

    rez->next = NULL;

    while (p != NULL && q != NULL)
    {
        if (p->element == q->element)
        {
            newSort(q->element, rez);
            p = p->next;
            q = q->next;
        }

        else if (q->element < p->element)
        {
            q = q->next;
        }

        else
        {
            p = p->next;
        }
    }

    return rez;
}

int check(position temp)
{
    position q;

    while (temp != NULL && temp->next != NULL)
    {
        if (temp->element == temp->next->element)
        {
            q = temp->next->next;

            if (q == NULL) //kada usporedujemo zadnji  predzadnji element
            {
                temp->next = NULL;
            }

            free(temp->next); //dealociraj element prvo pa onda postavi pokazivace
            temp->next = q;
        }

        if (temp->element != temp->next->element)
        {
            temp = temp->next;
        }
    }

    return 0;
}