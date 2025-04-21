// C program for linked list implementation of stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "concurrent_stack.h"

struct ConcurrentStack* concurrent_stack_init(struct StackNode* stack) {
    struct ConcurrentStack* cStack = malloc(sizeof(struct ConcurrentStack));
    cStack->stack = stack;
    pthread_mutex_init(&cStack->mutex, NULL);
    return cStack;
}

int concurrent_isEmpty(struct ConcurrentStack* root) {
    return !root->stack;
}

void concurrent_push(struct ConcurrentStack* root, int data) {
    pthread_mutex_lock(&root->mutex);
    push(&root->stack, data);
    pthread_mutex_unlock(&root->mutex);
}

int concurrent_pop(struct ConcurrentStack* root) {
    pthread_mutex_lock(&root->mutex);
    int ret = pop(root->stack);
    pthread_mutex_unlock(&root->mutex);
    return ret;
}

int concurrent_top(struct ConcurrentStack* root) {
    pthread_mutex_lock(&root->mutex);
    int data = top(root->stack);
    pthread_mutex_unlock(&root->mutex);
    return data;
}

void concurrent_stackFree(struct ConcurrentStack* root) {
    while(!concurrent_isEmpty(root))
        concurrent_pop(root);
}
