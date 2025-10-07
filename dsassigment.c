#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Customer {
    float arrivalTime;
    float serviceTime;
    struct Customer* next;
} Customer;

typedef struct TellerQueue {
    Customer* head;
    Customer* tail;
    int length;
} TellerQueue;

void enqueue(TellerQueue* queue, Customer* c) {
    if (queue->tail) {
        queue->tail->next = c;
    } else {
        queue->head = c;
    }
    queue->tail = c;
    queue->length++;
}

Customer* dequeue(TellerQueue* queue) {
    if (!queue->head){
        return NULL;
    }
    Customer* temp = queue->head;
    queue->head = temp->next;
    if (!queue->head) {
        queue->tail = NULL;
    }
    queue->length--;
    return temp;
}

float random_float(float max) {
    return ((float)rand() / RAND_MAX) * max;
}

int main() {
    srand(time(NULL));
    int customers = 100;
    int tellers = 4;
    float simTime = 60.0;
    float avgService = 2.3;

    TellerQueue queues[tellers];
    
    for (int i = 0; i < tellers; i++) {
        queues[i].head = queues[i].tail = NULL;
        queues[i].length = 0;
    }

    for (int i = 0; i < customers; i++) {
        Customer* c = (Customer*)malloc(sizeof(Customer));
        c->arrivalTime = random_float(simTime);
        c->serviceTime = avgService + random_float(3.0);
        c->next = NULL;
        int t = rand() % tellers;
        enqueue(&queues[t], c);
        printf("Customer %d arrives at %f, joins teller %d\n", i, c->arrivalTime, t);
    }

    for (int t = 0; t < tellers; t++) {
        printf("Teller %d serves:\n", t);
        while (queues[t].head) {
            Customer* c = dequeue(&queues[t]);
            printf("Served customer at %f (service %f)\n", c->arrivalTime, c->serviceTime);
            free(c);
        }
    }
    return 0;
}
