#include <stdio.h>
#include <stdlib.h>
#include "libs/utils.h"
#include "libs/priority-queue.h"

typedef struct Node {
    int value;
} Node;


int main(int argc, char** argv) {
    Node node1 = {69};
    Node node2 = {420};
    Node* array[] = {&node1, &node2};

    printf("%d %d\n", node1.value, node2.value);
    printf("%d %d\n", node1.value, node2.value);

    return 0;
}