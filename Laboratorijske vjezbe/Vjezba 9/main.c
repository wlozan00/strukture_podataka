#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _node* tree;
typedef struct _node
{
    int value;
    tree left;
    tree right;
}node;

tree create_node();
tree add_vlue(int, tree);
tree print_tree(tree);
tree find(int, tree);
tree find_min(tree);
tree delete_value(int, tree);
tree clear_tree(tree);

int main()
{
    tree root = NULL;
    srand(time(NULL));

    for (int i = 0; i < 8; i++)
    {
        root = add_vlue(rand() % 15, root);
    }
    root = print_tree(root);
    printf("\n");

    root = delete_value(rand() % 10, root);
    print_tree(root);
    printf("\n");

    root = clear_tree(root);

    return 1;
}

tree create_node()
{
    tree s = (tree)malloc(sizeof(node));
    if (!s)
    {
        printf("Erorr in memory allocation!\n");
        return NULL;
    }
    s->left = NULL;
    s->right = NULL;

    return s;
}

tree add_vlue(int x, tree s)
{
    if(s == NULL)
    {
        s = create_node();
        s->value = x;
    }

    if(x < s->value)
    {
        s->left = add_vlue(x, s->left);
    }

    else if(x > s->value)
    {
        s->right = add_vlue(x, s->right);
    }

    return s;
}

tree print_tree(tree s)
{
    if(s != NULL)
    {
        s->left = print_tree(s->left);
        printf("%d ", s->value);
        s->right = print_tree(s->right);
    }

    return s;
}

tree find(int x, tree s)
{
    if(s == NULL)
    {
        printf("Value not found\n");
        return NULL;
    }

    if(x < s->value)
    {
        return find(x, s->left);
    }

    else if(x > s->value)
    {
        return find(x, s->right);
    }

    return s;
}

tree find_min(tree s)
{
    while(s->left != NULL)
    {
        s = s->left;
    }

    return s;
}

tree delete_value(int x, tree s)
{
    if(s == NULL)
    {
        printf("Value not found, can't bee deleted\n");
        return NULL;
    }

    if(x < s->value)
    {
        s->left = delete_value(x, s->left);
    }

    else if (x > s->value)
    {
        s->right = delete_value(x, s->right);
    }

    else
    {   
        if(s->left == NULL || s->right == NULL)
        {
            tree temp = s;

            if(s->left == NULL)
            {
                s = s->right;
            }

            else
            {
                s = s->left;
            }

            free(temp);
        }

        else
        {
            tree temp = find_min(s->right);
            s->value = temp->value;
            s->right = delete_value(temp->value, s->right);
        }
    }

    return s;
}

tree clear_tree(tree s)
{
    if(s != NULL)
    {
        s->left = clear_tree(s->left);
        s->right = clear_tree(s->right);
        free(s);
    }

    return NULL;
}