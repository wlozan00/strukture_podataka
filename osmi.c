#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *directory;
typedef struct node
{
    char name[20];
    directory child;
    directory sibling;

} Node;

typedef struct snode *stack;
typedef struct snode
{
    directory el;
    stack next;

} Snode;

directory allocate(void);
int md(directory);
directory cd(directory);
int dir(directory);
directory dir_exit(directory);
int push(directory, stack);
directory pop(stack);
stack stack_exit(stack);

int main()
{
    directory p = NULL;
    p = allocate();
    printf("Insert root directory name :\n");
    fgets(p->name, 20, stdin);
    puts("");

    stack head = (stack)malloc(sizeof(Snode));
    head->next = NULL;

    char func[50] = {'\0'};
    printf("\nChoose function:\n md \n cd \n cd.. \n dir \n exit\n");
    puts("");

    while (strcmp(func, "exit\n") != 0)
    {
        fgets(func, 50, stdin);

        if (strcmp(func, "md\n") == 0)
        {
            md(p);
        }
        else if (strcmp(func, "cd\n") == 0)
        {
            push(p, head);
            p = cd(p);
        }
        else if (strcmp(func, "cd..\n") == 0)
        {
            p = pop(head);
            printf("\nLocation : Directory %s\n", p->name);
        }
        else if (strcmp(func, "dir\n") == 0)
        {
            dir(p);
        }
        else if (strcmp(func, "exit\n") == 0)
        {
            printf("\nEND\n");
            p = dir_exit(p);
            head = stack_exit(head);
        }
        else
        {
            printf("\nError, enter name again!\n");
        }
    }

    return 0;
}

directory allocate()
{
    directory q = NULL;
    q = (directory)malloc(sizeof(Node));

    if (q == NULL)
    {
        printf("Erorr\n");
        return NULL;
    }

    q->sibling = NULL;
    q->child = NULL;

    return q;
}

int push(directory d, stack s)
{
    stack new_s = NULL;
    new_s = (stack)malloc(sizeof(Snode));

    if (new_s == NULL)
    {
        printf("Error\n");
        return -1;
    }

    new_s->el = d;
    new_s->next = s->next;
    s->next = new_s;

    return 0;
}

directory pop(stack s)
{
    if (s->next == NULL)
    {
        printf("Empty stack\n");
        return NULL;
    }

    stack temp = s->next;
    directory val = temp->el;

    s->next = temp->next;
    free(temp);

    return val;
}

int dir(directory p)
{
    puts("");

    if (p == NULL)
    {
        printf("Folder does not exist !\n");
        return -1;
    }

    else
    {
        printf("Directories in (%s) :\n", p->name);
        directory temp = p->child;

        if (temp != NULL)
        {
            while (temp != NULL)
            {
                printf("%s\n", temp->name);
                temp = temp->sibling;
            }
        }

        else
        {
            printf("%s : ", p->name);
            printf("Empty folder!\n");
        }
    }
    return 0;
}

int md(directory p)
{
    directory new_d = NULL;
    directory temp = NULL;

    if (p == NULL)
    {
        printf("Error !\n");
        return 0;
    }

    else
    {
        new_d = allocate();
        printf("Insert new directory name : ");
        fgets(new_d->name, 20, stdin);

        if (p->child == NULL)
        {
            new_d->child = p->child;
            p->child = new_d;
        }

        else
        {
            temp = p->child;

            if (p->child->sibling == NULL && strcmp(new_d->name, p->child->name) < 0)
            {
                p->child = new_d;
                temp->sibling = new_d->sibling;
                new_d->sibling = temp;
            }

            else if (p->child->sibling == NULL && strcmp(new_d->name, p->child->name) >= 0)
            {
                p->child->sibling = new_d;
            }

            else if (p->child->sibling != NULL && strcmp(new_d->name, p->child->name) < 0)
            {
                p->child = new_d;
                new_d->sibling = temp;
            }

            else if (p->child->sibling != NULL && strcmp(new_d->name, p->child->name) >= 0)
            {
                while (temp->sibling != NULL && strcmp(temp->sibling->name, new_d->name) < 0)
                {
                    temp = temp->sibling;
                }

                new_d->sibling = temp->sibling;
                temp->sibling = new_d;
            }
        }

        printf("Directory made!\n");
    }

    return 1;
}

directory cd(directory p)
{
    directory temp = NULL;
    char name[20];

    if (p == NULL)
    {
        printf("Folder does not exist !\n");
        return NULL;
    }

    else
    {
        printf("Insert subdirectory name : ");
        fgets(name, 20, stdin);

        temp = p->child;
        while (temp != NULL && strcmp(temp->name, name) != 0)
        {
            temp = temp->sibling;
        }

        printf("Location : Directory %s\n", name);

        if (temp == NULL)
        {
            printf("Error, file (%s) not in directory\n", name);
            return NULL;
        }

        return temp;
    }
}

directory dir_exit(directory p)
{
    if (p != NULL)
    {
        p->sibling = dir_exit(p->sibling);
        p->child = dir_exit(p->child);
        free(p);
    }

    return NULL;
}

stack stack_exit(stack s)
{
    if (s != NULL)
    {
        s->next = stack_exit(s->next);
        free(s);
    }

    return NULL;
}
