#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define STACK_MAX (100001)

typedef struct pair_t {
    int first;
    int second;
} pair_t;

typedef struct stack_t {
    int size;
    pair_t data[STACK_MAX + 1];
    
    // data[i].first - value of element
    // data[i].second - max in stack on this element and bottom
} stack_t;

int max(int a, int b){
    if (a > b) return a;
    return b;
}

void InitStack (stack_t * stack) {
    stack -> size = 0;
}

bool StackEmpty (stack_t * stack) {
   return (stack -> size == 0);
}

pair_t StackPush (stack_t * stack, int value) {
   stack -> data[stack -> size].first = value;
   stack -> data[stack -> size].second = value;
   
   if (!StackEmpty(stack) && stack -> data[stack -> size - 1].second > stack -> data[stack -> size].second)
        stack -> data[stack -> size].second = stack -> data[stack -> size - 1].second;

   stack -> size++;
}

pair_t StackPop (stack_t * stack) {
   return stack -> data[--stack -> size];
}

pair_t StackTop (stack_t * stack) {
   return stack -> data[stack -> size - 1];
} 

typedef struct queue_t{
    stack_t stack1;
    stack_t stack2;
    //add only in stack1, take only from stack2
} queue_t;

void InitQueue(queue_t * queue){
    InitStack(&queue -> stack1);
    InitStack(&queue -> stack2);
}

int QueueMaximum(queue_t * queue){
    if (StackEmpty(&queue -> stack1))
        return StackTop(&queue -> stack2).second;
    if (StackEmpty(&queue -> stack2))
        return StackTop(&queue -> stack1).second;

    return max(StackTop(&queue -> stack1).second, StackTop(&queue -> stack2).second);
}

void Enqueue(queue_t * queue, int value){
    StackPush(&queue -> stack1, value);
}

int Dequeue(queue_t * queue){
    if (StackEmpty(&queue -> stack2))
        while (!StackEmpty(&queue -> stack1)) {
            StackPush(&queue -> stack2, StackPop(&queue -> stack1).first);
        }
    //if stack2 is empty move stack1 in it
    return StackPop(&queue -> stack2).second;
}

bool QueueEmpty(queue_t * queue){
    return (StackEmpty(&queue -> stack1) & StackEmpty(&queue -> stack2));
}

int main() {
    int n;
    scanf("%d\n", &n);
    queue_t queue;
    InitQueue(&queue);
    char operation[10];
    int x;
    
    for (n; n > 0; n--){
        scanf("%s", operation);
        if (!strcmp ("ENQ", operation)){
            scanf("%d", &x);
            Enqueue(&queue, x);
        }
        else if (!strcmp ("DEQ", operation)){
            printf("%d\n", Dequeue(&queue));
        }       
        else if  (!strcmp ("MAX", operation)){
            printf("%d\n", QueueMaximum(&queue));
        }       
        else if (!strcmp ("EMPTY", operation)){
            printf("%s\n", QueueEmpty(&queue) ? "true": "false");
        }
    }
    return (EXIT_SUCCESS);
}
