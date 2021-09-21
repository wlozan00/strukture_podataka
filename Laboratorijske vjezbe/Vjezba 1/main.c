#include<stdio.h>
#include<stdlib.h>
#define M 40.00

typedef struct{
    char name[20];
    char sname[20];
    int pts;
}student;

student* create_students(int);
int student_counter(char*);
int get_data(char*, student*, int);
int print_students(student*, int);

int main()
{
   int x;
   student* s = NULL;

    x = student_counter("students.txt");
    printf("Number of students : %d\n", x);

    s = create_students(x);
    get_data("students.txt", s, x);
    print_students(s, x);
    free(s);

    return 1;
}

student* create_students(int n)
{
    student* s = (student*)malloc(n*sizeof(student));

    if(s == NULL)
    {
        printf("Error in student creation!\n");
        return NULL;
    }

    return s;
}


int student_counter(char* name)
{
    FILE *fp = NULL;
    int n = 0;

    fp = fopen(name, "r");
    if (!fp)
    {
        printf("Error in file oppening!\n");
        return 0;
    }

    char buffer[256];
    while(fgets(buffer, 256, fp) != NULL)
    {
        n++;
    }
    fclose(fp);

    return n;
}

int get_data(char* name, student* s, int n)
{
    FILE *fp = NULL;
    fp = fopen(name, "r");
    
    if (!fp)
    {
        printf("Error in file oppening!\n");
        return 0;
    }
    
    for(int i = 0; i < n; i++)
    {
        fscanf(fp, "%s %s %d\n", (s+i)->name, (s+i)->sname, &(s+i)->pts);
    }
    fclose(fp);

    return 1;
}

int print_students(student* s, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s %s %d %.2f\n",(s+i)->name, (s+i)->sname, (s+i)->pts, (float)((s+i)->pts) / M * 100);
    }

    return 1;
}