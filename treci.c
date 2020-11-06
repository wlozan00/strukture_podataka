#include <stdio.h>
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

int unosP(position); //unos novog studenta na pocetak vezane liste
int ispis(position);
int oslobodi(position); //brisanje svih elemenata vezane liste
int unosIza(char *, position);
int unosIspred(char *, position);
int sortUnos(position);
int upisi(char *, position); //upis vezane liste u datoteku
int procitaj(char *, position);

int main()
{
    int n;
    position head = NULL;
    head = (position)malloc(sizeof(list));
    /* printf("Unesi nove studente:\n");
    for (int i = 0; i < 4; i++)
    {
        unosP(head);                        
    }
    ispis(head->next);

    printf("Unesi prezime iza kojeg zelis dodati novog studenta:\n");
    char s1[20];
    scanf("%s", s1);
    unosIza(s1, head);
    puts("\n");
    ispis(head->next);

    printf("Unesi prezime ispred kojeg zelis dodati novog studenta:\n");
    char s2[20];
    scanf("%s", s2);
    unosIspred(s2, head);
    puts("\n");
    ispis(head->next); */

    //sortiranje elemenata vezaniih listi jos nisam savladao pa sam odlucio pozvati funkciju sotrirani unos
    //zbog toga sam zakomentirao pozive ostalih funkcija u mainu

    printf("Odredi broj novih studenata:\n");
    scanf("%d", &n);

    printf("Unesi nove studente sortirane po prezimenu:\n");
    for (int i = 0; i < n; i++)
    {
        sortUnos(head);
    }
    puts("\n");

    ispis(head->next);

    upisi("Studenti.txt", head);

    procitaj("Studenti.txt", head);

    oslobodi(head->next);

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

int unosIza(char *tmp, position temp)
{
    while (temp != NULL && strcmp(tmp, temp->sname) != 0)
    {
        temp = temp->next;
        if (temp == NULL)
        {
            printf("Element nije u listi\n");
            return -1;
        }
    }
    printf("Unesi novog studenta:\n");
    unosP(temp);
}

int unosIspred(char *tmp, position temp)
{
    while (temp->next != NULL && strcmp(tmp, temp->next->sname) != 0)
    {
        temp = temp->next;
        if (temp->next == NULL)
        {
            printf("Element nije u listi\n");
            return -1;
        }
    }
    printf("Unesi novog studenta:\n");
    unosP(temp);
    return 0;
}

int oslobodi(position temp)
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

int sortUnos(position temp)
{
    position new = NULL;
    new = (position)malloc(sizeof(list));
    scanf("%s %s %d", new->name, new->sname, &new->year);

    while (temp->next != NULL && strcmp(temp->next->sname, new->sname) < 0)
    {
        temp = temp->next;
    }

    new->next = temp->next;
    temp->next = new;

    return 0;
}

int upisi(char *name, position temp)
{
    FILE *fp = NULL;
    fp = fopen(name, "w");
    if (fp == NULL)
    {
        perror("Greska\n");
        return -1;
    }

    fprintf(fp, "Studenti glase:\n");

    while (temp != NULL)
    {

        fprintf(fp, "%s\t%s\t%d\n", temp->name, temp->sname, temp->year);
        temp = temp->next;
    }
    fclose(fp);
    return 0;
}

int procitaj(char *name, position temp)
{
    FILE *fp = NULL;
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        perror("Greska\n");
        return -1;
    }

    while (temp != NULL)
    {
        fscanf(fp, "%s %s %d", temp->name, temp->sname, &temp->year);
        temp = temp->next;
    }

    fclose(fp);
    return 0;
}