include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _list *position;
typedef struct _list
{
    char name[20];
    char sname[20];
    int year;
    position next;
} list;

int unosP(position);
int ispis(position);
int unosK(position);
position find(char *, position);
int brisi(char *, position);

int main()
{
    position head = NULL;
    head = (position)malloc(sizeof(list));

    char s1[20];
    char s2[20];
    position element = NULL;

    printf("Unesi nove strukture na pocetak liste:\n");
    for (int i = 0; i < 2; i++)
    {
        unosP(head);
    }

    printf("Unesi nove strukture na kraj liste:\n");
    for (int i = 0; i < 2; i++)
    {
        unosK(head);
    }
    puts("\n");

    ispis(head->next);

    puts("\n");
    printf("Unesi prezime studenta kojeg trazis:\n");
    scanf("%s", s1);
    element = find(s1, head->next);
    printf("Trazeni student:\n");
    printf("%s %s %d\n", element->name, element->sname, element->year);

    printf("Unesi ime studenta kojeg zelis izbrisati:\n");
    scanf("%s", s2);
    brisi(s2, head->next);

    ispis(head->next);

    free(head);
    return 0;
}

int unosP(position temp)
{
    position new = NULL;
    new = (position)malloc(sizeof(list));
    if (new == NULL)
    {
        perror("Greska pri alokaciji memorije\n");
        return -1;
    }
    scanf("%s %s %d", new->name, new->sname, &new->year);
    new->next = temp->next;
    temp->next = new;
    return 0;
}

int ispis(position temp)
{
    while (temp != NULL)
    {
        printf("%s\t%s\t%d\n", temp->name, temp->sname, temp->year);
        temp = temp->next;
    }
    return 0;
}

int unosK(position temp)
{
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    unosP(temp);
    return 0;
}

position find(char *tmp, position help)
{
    while (help != NULL && strcmp(help->sname, tmp) != 0) //koristi ovu funkciju za provjeru stringova, vraca 0 ako su identicni
    {
        help = help->next;
    }
    if (help == NULL)
    {
        printf("Element nije u listi!\n");
        return NULL;
    }
    return help;
}

int brisi(char *tmp, position help)
{
    position prev = help;
    while (help != NULL && strcmp(help->sname, tmp) != 0)
    {
        prev = help;
        help = help->next;
    }
    if (help != NULL)
    {
        prev->next = help->next;
        free(help);
    }
    return 0;
}
