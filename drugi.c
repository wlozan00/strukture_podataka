#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _osoba *Pozicija;
typedef struct _osoba
{
    char ime[20];
    char prezime[20];
    int godina;
    Pozicija next;

} Osoba;

int ispisi(Osoba *);
int unosP(Osoba *);
int unosK(Osoba *);
Pozicija find(char *, Osoba *);

int main()
{
    Osoba *head;
    head = (Osoba *)malloc(sizeof(Osoba));
    head->next = NULL;
    printf("Unesi nove studente:\n");
    unosP(head);
    unosK(head);
    ispisi(head->next);
    char a[20];
    scanf("%s", a);
    Pozicija trazeni = find(a, head);
    printf("%s %s %d\n", trazeni->ime, trazeni->prezime, trazeni->godina);
    return 0;
}

int ispisi(Osoba *temp)
{
    while (temp != NULL)
    {
        printf("%-10s %-10s %-d\n", temp->ime, temp->prezime, temp->godina);
        temp = temp->next;
    }
    return 0;
}
int unosP(Osoba *head)
{
    Osoba *new;
    new = (Osoba *)malloc(sizeof(Osoba));
    scanf("%s %s %d", new->ime, new->prezime, &new->godina);

    new->next = head->next;
    head->next = new;

    return 0;
}
int unosK(Osoba *head)
{
    while (head->next != NULL)
    {
        head = head->next;
    }

    unosP(head);

    return 0;
}
Pozicija find(char *x, Pozicija head)
{
    while (strcmp(head->next->prezime, x) != 0 && head->next != NULL)
    {
        head = head->next;
    }
    return head->next;
}