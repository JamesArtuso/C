#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct BSTNode BSTNode;
typedef struct stack stack;
typedef struct stackNode stackNode;

struct BSTNode {
    int val;
    struct BSTNode* l_child;
    struct BSTNode* r_child;
};


struct stack{
    BSTNode* data;
    stack* next;
};

stack* push(stack* root, BSTNode* d){
    stack* stackNode = malloc(sizeof(stack));
    stackNode -> data = d;
    stackNode -> next = root;
    return(stackNode);
}

stack* pop(stack** root){
    if(root == NULL){
        return NULL;
    }
    stack* returnStack = *root;
    *root = (*root) -> next;
    return returnStack;
}


BSTNode* insert(BSTNode* root, int v){
    if(root == NULL){
        root = malloc(sizeof(BSTNode));
        root -> val = v;
        root -> l_child = NULL;
        root -> r_child = NULL;
    }
    else if(v > (root -> val)){
        root -> r_child = insert(root -> r_child, v);
    }
    else if(v < (root -> val)){
        root -> l_child = insert(root -> l_child, v);
    }
    return root;
}

void delete(BSTNode* root){
    if(root->l_child)delete(root->l_child);
    if(root->r_child)delete(root->r_child);
    free(root);
}


void explore(BSTNode* root){
    if(root->r_child)explore(root->r_child);
    printf("%d ", root-> val);
    if(root->l_child)explore(root->l_child);
}


int main(int argc, char* argv[])
{
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct BSTNode* root = NULL;

    char buff[256];
    while ( fscanf(fp, "%s", buff)!=EOF ) {
        int i = atoi(buff);
        root = insert(root, i);
    }


    explore(root);

    delete(root);
    fclose(fp);
    return 0;
}
