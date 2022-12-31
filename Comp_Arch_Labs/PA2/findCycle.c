#include "../graphutils.h"



// A program to find a cycle in a directed graph

//Mirrors printCycle bc its essentially a test run of "can you print the list"
bool getSource(graphNode_t curr, graphNode_t source, graphNode_t* visited){
    if(curr == source){
        return true;
    }
    if(curr == -1){
        return false;
    }
    return getSource(visited[curr], source, visited);
}


void printCycle(graphNode_t curr, graphNode_t source, graphNode_t* visited){
    if(curr == source){
        printf("%ld ",curr);
        return;
    }
    printCycle(visited[curr], source, visited);
    printf("%ld ",curr);
}


typedef struct StackNode {
    graphNode_t graphNode;
    graphNode_t parent;
    struct StackNode* next;
} StackNode;

struct Stack {
    struct StackNode* top; // top of the stack
};
typedef struct Stack Stack;


struct Stack push ( struct Stack stack, graphNode_t graphNode, graphNode_t parent ) {
    StackNode* newNode = malloc(sizeof(StackNode));
    newNode->graphNode  = graphNode;
    newNode->next = NULL;
    newNode->parent = parent;

    if(stack.top == NULL){
        stack.top = newNode;
    }
    else{
        newNode->next = stack.top;
        stack.top = newNode;
    }
    return stack;
}


StackNode* peek(Stack* stack){
    if(stack->top == NULL) return NULL;
    else{
        return stack->top;
    }
}   


StackNode* pop ( Stack* stack ) {
    if(stack->top == NULL){
        return NULL;
    }
    else{
        StackNode* temp = stack->top;
        stack->top = temp->next;
        return temp;
    }
}



int main ( int argc, char* argv[] ) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    int graphNodeCount;
    fscanf(fp, "%d", &graphNodeCount);

    fclose(fp);

    AdjacencyListNode* adjacencyList;
    adjMatrixToList(argv[1], &adjacencyList);

    graphNode_t ans;

    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
        for (size_t i=0; i<graphNodeCount; i++) {
            parents[i] = -1;
        }

    bool isCyclic = false;


    //Start at source = 0 node, then for every DFS, if you dont find a cycle,
    //start again but at source + 1
    for (unsigned source=0; source<graphNodeCount; source++) {

        graphNode_t* visited = calloc( graphNodeCount, sizeof(graphNode_t) );
        for (size_t i=0; i<graphNodeCount; i++) {
            visited[i] = -1; 
        }

        Stack stack = { .top = NULL};

        graphNode_t parent = -1;
        graphNode_t current = source;

        stack = push(stack, adjacencyList[source].graphNode, -1);


        while ( peek(&stack) ) {
            StackNode* currstacknode = pop(&stack);
            current = currstacknode->graphNode;
            parent = currstacknode->parent;
            free(currstacknode);

            //Do a DFS, but mark if you have visited the node before
            //If you have been there before and you can print a cycle,
            //send it!
            if(visited[current] != -1 && getSource(visited[parent], parent, visited)){
                ans = parent;
                isCyclic = true;
                break;
            }            
            else{
                visited[current] = parent;
            }

            AdjacencyListNode* neighbor = adjacencyList[current].next;
            while(neighbor){
                if(adjacencyList[neighbor->graphNode].next){
                    stack = push(stack, neighbor->graphNode, current);
                }
                neighbor = neighbor->next;
            }


        }


        for (size_t i=0; i<graphNodeCount; i++) {
            parents[i] = visited[i];
        }


        free(visited);
        while(peek(&stack)){
            free(pop(&stack));
        }

        if(isCyclic) break;
    }



    if (!isCyclic) { printf("DAG\n"); }
    else{
        printCycle(parents[ans], ans, parents);
    }


    freeAdjList ( graphNodeCount, adjacencyList );
    free(parents);
    return EXIT_SUCCESS;
}