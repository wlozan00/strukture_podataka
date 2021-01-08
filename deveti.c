#include <stdio.h>
#include <stdlib.h>

typedef struct node *tree;
typedef struct node
{
    int el;
    tree L;
    tree R;
} Node;
typedef struct node *position;

tree add(int, tree);
int print_tree(tree);
tree delete (int, tree);
position find(int, tree);
position findMin(tree);
position findMax(tree);
tree clear(tree);

int main()
{
    tree root = NULL;

    root = add(16, root);
    root = add(7, root);
    root = add(11, root);
    root = add(3, root);
    root = add(21, root);
    root = add(24, root);
    root = add(18, root);
    root = add(19, root);

    print_tree(root);
    printf("\n");

    root = delete (21, root);
    print_tree(root);
    printf("\n");

    root = clear(root);

    return 0;
}

tree add(int x, tree s)
{
    if (s == NULL)
    {
        s = (tree)malloc(sizeof(Node));

        if (s == NULL)
        {
            printf("Error!\n");
            return NULL;
        }

        s->el = x;
        s->L = NULL;
        s->R = NULL;
    }

    else
    {
        if (x < s->el)
        {
            s->L = add(x, s->L);
        }

        else if (x > s->el)
        {
            s->R = add(x, s->R);
        }
    }

    return s;
}

int print_tree(tree s)
{
    if (s == NULL)
    {
        return 0;
    }

    printf("%d ", s->el);
    print_tree(s->L);
    print_tree(s->R);
}

position find(int x, tree s)
{
    if (s == NULL)
    {
        printf("Element not in tree\n");
        return s;
    }

    if (s->el == x)
    {
        return s;
    }

    else if (x < s->el)
    {
        return find(x, s->L);
    }

    else
    {
        return find(x, s->R);
    }
}

position findMin(tree s)
{
    if (s == NULL)
    {
        printf("Empty tree\n");
        return NULL;
    }

    while (s->L != NULL)
    {
        s = s->L;
    }

    return s;
}

position findMax(tree s)
{
    if (s == NULL)
    {
        printf("Empty tree\n");
        return s;
    }

    while (s->R != NULL)
    {
        s = s->R;
    }

    return s;
}

tree delete (int x, tree s)
{
    if (s == NULL)
    {
        printf("Element not in list\n");
        return NULL;
    }

    if (x == s->el)
    {
        if (s->L != NULL)
        {
            position temp = findMax(s->L);
            s->el = temp->el;
            s->L = delete (temp->el, s->L);
        }

        else if (s->R != NULL)
        {
            position temp = findMin(s->R);
            s->el = temp->el;
            s->R = delete (temp->el, s->R);
        }

        else
        {
            s = NULL;
            free(s);
        }
    }

    else if (x < s->el)
    {
        s->L = delete (x, s->L);
    }

    else
    {
        s->R = delete (x, s->R);
    }

    return s;
}

tree clear(tree s)
{
    if (s != NULL)
    {
        s->L = clear(s->L);
        s->R = clear(s->R);
        free(s);
    }

    return NULL;
}