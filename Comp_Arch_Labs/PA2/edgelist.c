#include "../graphutils.h" // header for functions to load and free adjacencyList


// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    int graphNodeCount;
    fscanf(fp, "%d", &graphNodeCount);

    fclose(fp);



    // FIRST, READ THE ADJACENCY MATRIX FILE
    AdjacencyListNode* adjacencyList = NULL;
    adjMatrixToList(argv[1], &adjacencyList);

    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h

    AdjacencyListNode* temp = adjacencyList;

    for(unsigned int i = 0; i < graphNodeCount; i++){
        AdjacencyListNode* dest = temp[i].next;
        while(dest){
            if(dest->graphNode < i){
                break;
            }
            printf("%d %d\n", i, (int)(dest->graphNode));
            dest = dest->next;
        }
    }

    // NOW, BE SURE TO FREE THE ADJACENCY LIST
    freeAdjList(graphNodeCount,adjacencyList);

    return EXIT_SUCCESS;
}
