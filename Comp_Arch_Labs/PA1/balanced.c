#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct Node Node;

// Struct to hold the expected close brace character and a pointer to the next element.
struct Node{
    char close;
    Node* next;
};

Node* push(Node* curr, char c){
    Node* nodeNode = malloc(sizeof(Node));
    nodeNode -> close = c;
    nodeNode -> next = curr;
    return(nodeNode);
}

void deleteNodes(Node* curr){
    if((*curr).next){
        deleteNodes(curr->next);
    }
    free(curr);
    
}

Node* pop(Node** curr){
    if(curr == NULL){
        return NULL;
    }
    Node* returnNode = *curr;
    *curr = ((*curr)->next);
    return returnNode;
}


int main(int argc, char* argv[])
{

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    bool balanced = true;

    char buff;


    Node* stack = malloc(sizeof(Node));
    stack -> close = 'N';
    stack -> next = NULL;

    while ( fscanf(fp, "%c", &buff)==1 ) {
        if(buff == '(' || buff == '[' || buff == '{' || buff == '<'){
            stack = push(stack, buff);
        }  
        else{
            Node* current = pop(&stack);
            switch(buff){
                case ')':
                    if(current->close != '('){
                        balanced = false;

                    }
                    break;
                case ']':
                    if(current->close != '['){
                        balanced = false;
                    }
                    break;
                case '}':
                    if(current->close != '{'){
                        balanced = false;
                    }
                    break;
                    
                case '>':
                    if(current->close != '<'){
                        balanced = false;
                    }
                    break;
            }
            free(current);
        }

    }

    Node* current = pop(&stack);
    if(current->close != 'N'){
        balanced = false;
        deleteNodes(stack);
    }
    free(current);

    printf ( balanced ? "yes" : "no" );
    fclose(fp);
    return 0;
}
