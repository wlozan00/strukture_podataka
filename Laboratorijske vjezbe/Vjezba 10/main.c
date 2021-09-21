#include<stdio.h>
#include<stdlib.h>

typedef struct _t_node* tree;
typedef struct _t_node
{
    char symbol;
    tree left;
    tree right;
}t_node;

typedef struct _s_node* stack;
typedef struct _s_node
{
    tree element;
    stack next;
}s_node;

char* get_expression(char*);
tree create_tree(char);
stack create_stack();
int push(tree, stack);
tree pop(stack);
int is_number(char*);
tree get_infix(char*, stack);
FILE* open_file(char*);
int write_to_file(FILE*, tree);
tree clear_tree(tree);
int clear_stack(stack);

int main()
{
    char* expr = get_expression("postfix.txt");
    stack head = create_stack();
    tree result = get_infix(expr, head);
    
    if (result == NULL)
    {
        printf("Error in postfix expression!\n");
        return 0;
    }
    
    FILE* fp = open_file("infix.txt");
    write_to_file(fp, result);
    fclose(fp);
    result = clear_tree(result);
    printf("Success!\n");

    return 1;
}

char* get_expression(char* fname)
{
    FILE* fp = fopen(fname, "r");
    if(!fp)
    {
        printf("Error in file oppening!\n");
        return NULL;
    }

    char* str = (char*)malloc(50 * sizeof(char));
    while(fgets(str, 50, fp) != NULL)
    {
        fscanf(fp, "%s", str);
    }
    fclose(fp);

    return str;
}

tree create_tree(char c)
{
    tree s = (tree)malloc(sizeof(t_node));
    if(!s)
    {
        printf("Error in tree creation!\n");
        return NULL;
    }
    s->symbol = c;
    s->left = NULL;
    s->right = NULL;

    return s;
}

stack create_stack()
{
    stack s = (stack)malloc(sizeof(s_node));
    if(!s)
    {
        printf("Error in stack creation!\n");
        return NULL;
    }
    s->next = NULL;

    return s;
}

int push(tree s, stack t_head)
{
    stack n = create_stack();
    n->element = s;
    n->next = t_head->next;
    t_head->next = n;

    return 1;
}

tree pop(stack t_head)
{
    stack help = t_head->next;
    if (help == NULL)
    {
        return NULL;
    }
    
    tree x = help->element;
    t_head->next = help->next;
    free(help);

    return x;
}

int is_number(char* str)
{
    int numb;
    if(sscanf(str, "%d", &numb))
    {
        return 1;
    }

    return 0;
}

tree get_infix(char* str, stack s)
{
    while(*str != '\0')
    {
        tree t = create_tree(*str);

        if(is_number(str))
        {
            push(t, s);
        }

        else
        {
            tree b = pop(s);
            tree a = pop(s);
            t->left = a;
            t->right = b;
            push(t, s);
        }
        
        str += 2;
    }

    if(s->next->next != NULL || (s->next->element->left == NULL || s->next->element->right == NULL))
    {
        clear_stack(s);
        return NULL;
    }

    tree r = pop(s);

    return r;
}

FILE* open_file(char* fname)
{
    FILE* fp = fopen(fname, "w");
    if(fp == NULL)
    {
        printf("Error in file oppening(w)!\n");
        return NULL;
    }

    return fp;
}

int write_to_file(FILE* fp, tree s)
{
    if(s == NULL)
    {
        return 0;
    }

   if(s->symbol == '+' || s->symbol == '-' || s->symbol == '*' || s->symbol == '/')
   {
       fprintf(fp, "(");
       write_to_file(fp, s->left);
       fprintf(fp, " %c ", s->symbol);
       write_to_file(fp, s->right);
       fprintf(fp, ")");
   }

   else
   {
       write_to_file(fp, s->left);
       fprintf(fp, "%c", s->symbol);
       write_to_file(fp, s->right);
   }
   
    return 1;
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

int clear_stack(stack s)
{
    while(s->next != NULL)
    {
        stack help = s->next;
        help->element = clear_tree(help->element);
        s->next = help->next;
        free(help);
    }
    free(s);

    return 1;
}