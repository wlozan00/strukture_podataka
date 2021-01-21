#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *tree;
typedef struct node
{
    char ele[50];
    tree L;
    tree R;

} Node;

typedef struct snode *stack;
typedef struct snode
{
    tree p;
    stack next;

} Snode;

tree get_postfix(const char *, stack);
int push(tree, stack);
tree pop(stack);
int write_infix(FILE *, tree);
int isNumber(char *);
tree create(char *);

int main()
{
    tree t = NULL;

    stack s = NULL;
    s = (stack)malloc(sizeof(Snode));

    if (!s)
    {
        printf("Error\n");
        return -1;
    }

    s->p = NULL;
    s->next = NULL;

    t = get_postfix("postfix.txt", s);

    FILE *fp = NULL;
    fp = fopen("infix.txt", "w");
    if (!fp)
    {
        printf("ERROR!\n");
        return -1;
    }

    write_infix(fp, t);

    fclose(fp);

    return 0;
}

int push(tree t, stack s)
{
    stack new_s = NULL;
    new_s = (stack)malloc(sizeof(Snode));

    if (!new_s)
    {
        printf("Error\n");
        return -1;
    }

    new_s->p = t;

    new_s->next = s->next;
    s->next = new_s;

    return 0;
}

tree create(char *c)
{
    tree new_tree = NULL;
    new_tree = (tree)malloc(sizeof(Node));

    if (!new_tree)
    {
        printf("Erorr in tree alocation\n");
        return NULL;
    }

    new_tree->L = NULL;
    new_tree->R = NULL;
    strcpy(new_tree->ele, c);

    return new_tree;
}

tree pop(stack s)
{
    tree x = NULL;
    stack temp = s->next;

    if (temp == NULL)
    {
        return NULL;
    }

    x = temp->p;

    s->next = temp->next;
    free(temp);

    return x;
}

int isNumber(char *s)
{
    int n;

    if (sscanf(s, "%d", &n) == 1)
    {
        return 1;
    }

    return 0;
}

tree get_postfix(const char *name, stack s)
{
    tree x = NULL;
    FILE *fp = NULL;
    fp = fopen(name, "r");

    if (!fp)
    {
        printf("Erorr in file opening\n");
        return NULL;
    }

    char buffer[50];

    while (!feof(fp))
    {
        fscanf(fp, "%s", buffer);
        x = create(buffer);

        if (isNumber(buffer))
        {
            push(x, s);
        }

        else
        {
            x->R = pop(s);
            x->L = pop(s);

            push(x, s);
        }
    }
    fclose(fp);

    tree r = pop(s);

    if (!r)
    {
        printf("Error\n");
        return NULL;
    }

    if (pop(s))
    {
        printf("Error\n");
        return 0;
    }

    return r;
}

int write_infix(FILE *name, tree s)
{
    if (s == NULL)
    {
        return 0;
    }

    fprintf(name, "%s", "(");
    write_infix(name, s->L);
    fprintf(name, "%s", s->ele);
    write_infix(name, s->R);
    fprintf(name, "%s", ")");
}
