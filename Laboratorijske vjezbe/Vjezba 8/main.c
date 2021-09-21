#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _node* dir;
typedef struct _node
{
    char name[20];
    dir sibling;
    dir child;
}node;

typedef struct _s_node* stack;
typedef struct _s_node
{
    dir element;
    stack next;
}s_node;

dir create_dir();
int add_dir(dir);
dir change_dir(dir);
int print_dir(dir);
int clear_all(dir);
stack create_snode();
int push(dir, stack);
dir pop(stack);
int clear_stack(stack);

int main()
{
    dir root = create_dir();
    strcpy(root->name, "Home");
    stack head = create_snode();
    dir d = root;
    char operation[20];
    printf("Select operation : ");
    scanf("%s", operation);

    while(strcmp(operation, "end") != 0)
    {
        if(strcmp(operation, "md") == 0)
        {
            add_dir(d);
        }
        else if(strcmp(operation, "l") == 0)
        {
            print_dir(d);
        }
        else if(strcmp(operation, "cd") == 0)
        {
            push(d, head);
            d = change_dir(d);
        }
        else if(strcmp(operation, "cd..") == 0)
        {
            d = pop(head);
            if(d == NULL)
            {
                d = root;
            }

            printf("You are now in %s\n", d->name);
        }
        else
        {
            printf("Wrong command, select valid one (cd, cd..,end, l, md)!\n");
        }

        printf("\nSelect operation : ");
        scanf("%s", operation);
    }
    clear_all(root);
    clear_stack(head);

    return 1;
}

dir create_dir()
{
    dir n = (dir)malloc(sizeof(node));
    if(!n)
    {
        printf("Erorr in creating directory!\n");
        return NULL;
    }
    n->child = NULL;
    n->sibling = NULL;

    return n;
}

int add_dir(dir root)
{
    dir d = create_dir();
    printf("Insert new directory name : ");
    scanf("%s", d->name);

    if(strcmp(d->name, root->name) == 0)
    {
        printf("Subdirectories can't bee named after their superdirectories!\n");
        free(d);
        return 0;
    }

    if(root->child == NULL)
    {
        root->child = d;
    }

    else
    {
        dir help = root->child;
        
        if(strcmp(help->name, d->name) >= 0)
        {
            if(strcmp(help->name, d->name) == 0)
            {
                printf("Directory name already exists!\n");
                free(d);
                return 0;
            }

            root->child = d;
            d->sibling = help;
        }

        else
        {
            while(help->sibling != NULL && strcmp(help->sibling->name, d->name) < 0)
            {
                help = help->sibling;
            }
            if(help->sibling != NULL && strcmp(help->sibling->name, d->name) == 0)
            {
                printf("Directory name alteady exists!\n");
                free(d);
                return 0;
            }

            d->sibling = help->sibling;
            help->sibling = d;
        }
    }

    return 1;
}

int print_dir(dir root)
{
    dir help = root->child;
    printf("List of directories in %s :\n", root->name);
    if(help == NULL)
    {
        printf("Empty directory\n");
        return 0;
    }

    while(help != NULL)
    {
        printf("%s  ", help->name);
        help = help->sibling;
    }
    printf("\n");

    return 1;
}

dir change_dir(dir root)
{
    char t_name[20];
    printf("Enter directory name to change to : ");
    scanf("%s", t_name);
    dir d = root->child;

    while(d != NULL && strcmp(t_name, d->name) != 0)
    {
        d = d->sibling;
    }

    if(d == NULL)
    {
        printf("There is no directory %s in %s\n",t_name, root->name);
        return root;
    }

    return d;
}

stack create_snode()
{
    stack s = (stack)malloc(sizeof(s_node));
    if(s == NULL)
    {
        printf("Erorr in creating stack nodes!\n");
        return NULL;
    }
    s->element = NULL;
    s->next = NULL;

    return s;
}

int push(dir d, stack head)
{
    if(d == NULL)
    {
        printf("No directory to push to stack!\n");
        return 0;
    }
    if(head->next != NULL && strcmp(d->name, head->next->element->name) == 0)         //sigurnosna mreza kod funkcije cd..
    {
        return 0;
    }

    stack s = create_snode();
    s->element = d;
    s->next = head->next;
    head->next = s;

    return 1;
}

dir pop(stack head)
{
    stack help = head->next;
    if(help == NULL)
    {
        return NULL;
    }

    dir d = help->element;
    head->next = help->next;
    free(help);

    return d;
}

int clear_stack(stack head)
{
    while(head->next != NULL)
    {
        stack help = head->next;
        head->next = help->next;
        free(help);
    }
    free(head);

    return 1;
}

int clear_all(dir d)
{
    if(d != NULL)
    {
        clear_all(d->sibling);
        clear_all(d->child);
        free(d);
    }

    return 1;
}