#include <queue.h>

/*enqueue vehicle*/
extern void enqueue(QUEUE **head, char key, int arrivalTime) {
    QUEUE *newNode;
    if (!(newNode = (QUEUE *) malloc(sizeof(QUEUE)))) {
        fprintf(stderr, "Out of memory\n No more space for addition of the queue.\n");
        exit(1);
    }
    if (!newNode) return;

    newNode->key = key;
    newNode->arrivalTime = arrivalTime;
    newNode->next = *head;

    *head = newNode;
}

/*dequeue vehicle*/
extern int dequeue(QUEUE **head) {
    QUEUE *current, *prev = NULL;
    int arrivalTime = -1;

    if (*head == NULL) return;

    current = *head;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    
    arrivalTime = current->arrivalTime;
    free(current);
    
    if (prev)
        prev->next = NULL;
    else
        *head = NULL;
 
    return arrivalTime;
}


/*get queue size*/
extern int getSize(QUEUE *head) {
    int size = 0;
    QUEUE *current = head;
    while (current != NULL) {
        size++; 
        current = current->next;
    }
    return size;
}

