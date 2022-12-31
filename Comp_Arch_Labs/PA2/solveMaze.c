#include "../graphutils.h" // header for functions to load and free adjacencyList


void printAns(graphNode_t* arr, graphNode_t sou, graphNode_t par);

// A program to solve a maze that may contain cycles using BFS

// BFS requires using a queue data structure
typedef struct QueueNode {
    graphNode_t graphNode;
    struct QueueNode* next;
} QueueNode;

struct Queue {
    struct QueueNode* front; // front (head) of the queue
    struct QueueNode* back; // back (tail) of the queue
};
typedef struct Queue Queue;

// Append a new QueueNode to the back of the Queue
struct Queue enqueue ( struct Queue queue, graphNode_t graphNode ) {
    QueueNode* newNode = malloc(sizeof(QueueNode));
    newNode->graphNode  = graphNode;
    newNode -> next = NULL;

    if(queue.back == NULL){
        queue.front = newNode;
        queue.back = newNode;
    }
    else{
        queue.back->next = newNode;
        queue.back = newNode;
    }
    return queue;
}

// Remove a QueueNode from the front of the Queue
graphNode_t dequeue ( Queue* queue ) {
    if(queue->front == NULL){
        return -100000;
    }
    else{
        QueueNode* temp = queue->front;
        if(queue->back == temp){
            queue->back = NULL;
        }
        queue->front = temp->next;
        graphNode_t data = temp->graphNode;
        free(temp);
        return data;
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

    // First, read the query file to get the source and target nodes in the maze
    FILE* fp2 = fopen(argv[2], "r");
    if (!fp2) {
        perror("fopen failed");
        return 0;
    }

    int source;
    fscanf(fp2, "%d", &source);

    graphNode_t target;
    fscanf(fp2, "%ld", &target);

    fclose(fp2);

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    adjMatrixToList(argv[1], &adjacencyList);

    // USE A QUEUE TO PERFORM BFS
    Queue queue = { .front=NULL, .back=NULL };

    // An array that keeps track of who is the parent node of each graph node we visit
    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i<graphNodeCount; i++) {
        parents[i] = -1; // -1 indicates that a nodes is not yet visited
    }

    queue = enqueue(queue, adjacencyList[source].graphNode);


    graphNode_t current = dequeue(&queue);

    
    while ( current != target ) {
        AdjacencyListNode* temp = adjacencyList[current].next;
        // so long as we haven't found the target node yet, iterate through the adjacency list
        // add each neighbor that has not been visited yet (has no parents) to the queue of nodes to visit
        while(temp){
            if(parents[temp->graphNode]==-1){ //Only enqueue if we have not visited the node yet
                queue = enqueue(queue, temp->graphNode); //Enqueues each connected node
                parents[temp->graphNode]=adjacencyList[current].graphNode; //Sets the parent of node
            }
            temp = temp->next;
        }

        // Visit the next node at the front of the queue of nodes to visit
        current = dequeue(&queue);
    }

    // Now that we've found the target graph node, use the parent array to print maze solution
    // Print the sequence of edges that takes us from the source to the target node
    printAns(parents, (graphNode_t)source, target);
    

    // free any queued graph nodes that we never visited because we already solved the maze
    while ( queue.front ) {
        dequeue(&queue);
    }
    free (parents);
    freeAdjList ( graphNodeCount, adjacencyList );

    return EXIT_SUCCESS;
}


//Easier to recursivly print the solution
void printAns(graphNode_t* arr, graphNode_t sou, graphNode_t par){

    if(arr[par] == sou){ 
        printf("%ld %ld\n",sou, par);
    }
    else{
        printAns(arr, sou, arr[par]);
        printf("%ld %ld\n", arr[par], par);
    }
}