#include <stdio.h>
#include <stdlib.h>

struct tree {
    char info;
    struct tree *left;
    struct tree *right;
};

struct tree *root;

struct tree *stree(struct tree *root, struct tree *node, char info);
void print_tree(struct tree *root, int l);
struct tree *delTree(struct tree *root, char key);

int main(void){
    char s[80];
    root = NULL;

    do {
        printf("enter a letter: ");
        gets(s);
        root = stree(root, root, *s);
    }while(*s);

    print_tree(root, 0);

    return 0;
}

struct tree *stree(struct tree *root, struct tree *node, char info){
    if(!node){
        node = (struct tree *)malloc(sizeof(struct tree));

        if(!node){
            printf("\nout of memory\n");
            exit (0);
        }
        node->left = NULL;
        node->right = NULL;
        node->info = info;

        if(!root) return node;
        if(info < root->info) root->left = node;
        else root->right = node;

        return node;
    }
    if (info < node->info) stree(node, node->left, info);
    else stree(node, node->right, info);

    return root;
}

void print_tree(struct tree *node, int l){
    int i;

    if(!node) return;

    print_tree(node->right, l++);
    for(i = 0; i<l; ++i) printf(" ");
    printf("%c\n", node->info);
    print_tree(node->left, l++);
}

struct tree *delTree(struct tree *root, char key){
    struct tree *p, *p2;

    if(!root) return root;

    if(root->info == key) {
        if(root->left == root->right){
            free(root);
            return NULL;
        }
        else if(root->left == NULL){
            p = root->right;
            free(root);
            return p;
        }
        else if(root->right == NULL){
            p = root->left;
            free(root);
            return p;
        }
        else{
            p2 = root->right;
            p = root->right;
            while(p->left) p = p->left;
            p->left = root->left;
            free(root);
            return p2;
        }
        root = delTree(root, key);
    }
    if(root->info < key) root->right = delTree(root->right, key);
    else root->left = delTree(root->left, key);
    return root;
}

