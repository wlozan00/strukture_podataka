#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 256
#define max 40

typedef struct student
{
    char ime[20];
    char prezime[20];
    int bodovi;
    float postotak;
} osoba;

int brojac(char *);
int unos(char *, int, osoba *);
int ispis(int, osoba *);

int main()
{
    int n;
    n = brojac("student.txt");
    printf("Datoteka ima %d redaka\n", n);
    osoba *st = NULL;
    st = (osoba *)malloc(n * sizeof(osoba));
    if (st == NULL)
    {
        perror("Greska!\n");
    }
    printf("Maksimalni broj bodova iznosi %d\n", max);
    unos("student.txt", n, st);
    ispis(n, st);
    free(st);
    return 0;
}

int brojac(char *ime)
{
    int br = 0;
    FILE *fp = NULL;
    fp = fopen(ime, "r");
    if (fp == NULL)
    {
        perror("Greska!\n");
        return -1;
    }
    char buffer[LEN];
    while (fgets(buffer, LEN, fp) != 0)
    {
        br++;
    }
    fclose(fp);
    return br - 1;
}
int unos(char *ime, int n, osoba *o)
{
    FILE *fp = NULL;
    fp = fopen(ime, "r");
    if (fp == NULL)
    {
        perror("Greska!\n");
        return -1;
    }
    int i;
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%s %s %d", (o + i)->ime, (o + i)->prezime, &(o + i)->bodovi);
        (o + i)->postotak = 100 * (double)(o + i)->bodovi / max;
    }
    fclose(fp);
    return 0;
}
int ispis(int n, osoba *o)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Ime:%s\tPrezime:%s\tBodovi:%d\tPostotak:%.2f\n", (o + i)->ime, (o + i)->prezime, (o + i)->bodovi, (o + i)->postotak);
    }
    return 0;
}