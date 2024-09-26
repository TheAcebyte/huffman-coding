#include <stdio.h>
#include "utils.h"

void printMe() {
    printf("Yo");
}

void swap(TreeNode** array, int i, int j) {
    TreeNode* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}