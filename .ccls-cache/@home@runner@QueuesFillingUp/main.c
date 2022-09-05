#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define Trace()
// printf("%s: %d\n", __FUNCTION__, __LINE__)

/**********************************************
Declared node blueprint
**********************************************/
struct Node {
  int value;
  struct Node *next;
};
typedef struct Node Node;

struct Queue {
  Node *head;
};
typedef struct Queue Queue;

/**********************************************
Create a new node from item and returns pointer
to the newly created node
**********************************************/
Node *createNode(int num) {
  Node *newNode = (Node *)malloc(sizeof(Node));

  if (newNode) // sanity check
  {
    newNode->value = num;
    newNode->next = NULL;
  } else {
    printf("createNode:: could not malloc node !\n");
  }

  return newNode;
}

/**********************************************
Free a node
**********************************************/
void destroyNode(Node *node) {
  if (node) // sanity check
  {
    free(node);
    return;
  }
  printf("destroyNode:: Not the end of the world but you just tried to free a "
         "null pointer !\n");
}

/**********************************************
appends item to list tail
**********************************************/
void push(Queue *que, int value) {
  assert(que != NULL && "Invalid Queue\n"); // idiot proofing
  // this is also not needed - Node* prevNode = NULL; sorry for this again!! :(
  Node *newNode = createNode(value); // litu:: not needed -> ,prevNode);
  assert(newNode != NULL && "Could not allocate Memory\n"); // sanity check

  if (!que->head) // Appending first node to empty list
  {
    que->head = newNode;
    return;
  }

  Node *lastNode = que->head;
  while (lastNode->next)
    lastNode = lastNode->next;

  lastNode->next = newNode;
}

int pop(Queue *que) {
  assert(que->head != NULL && "Popping from empty stack\n");

  Node *firstNode = que->head;

  int result = firstNode->value; // copy the value

  if (firstNode->next) {
    que->head = firstNode->next; //  setting new head
  } 
  else                         // popping last element
  {
    que->head = NULL; // setting head to NULL
  }
  destroyNode(firstNode);

  return result;
}

/**********************************************
Destroys the entire list
**********************************************/
void destroyQueue(Queue *que) {
  if (!que)
    return;

  Node *freePos = que->head;
  for (; freePos !=
         NULL;) // iterate through que until we reach null (which is end of que)
  {
    Node *next = freePos->next;
    destroyNode(freePos);
    freePos = next;
  }
  que->head = NULL;

  free(que);
}

/**********************************************
Display List contents
**********************************************/
void showQueue(Queue *que) {
  if (!que) {
    printf("showList:: Integer que is empty ! First create a new integer\n");
    return;
  }

  for (Node *pickPos = que->head; pickPos != NULL;) {
    printf("%d\n", pickPos->value);
    pickPos = pickPos->next;
  }
  printf("\n");
}

/**********************************************
Main Entry
**********************************************/
int main(void) {
  printf("\nProgram to Show Queue operation\n");
  printf("-------------------------------------------\n");

  Queue *myQueue = (Queue *)malloc(sizeof(Queue));
  myQueue->head = NULL;
  assert(myQueue != NULL && "Failed to allocate Queue\n");

  push(myQueue, 1);
  push(myQueue, 2);
  push(myQueue, 3);
  push(myQueue, 4);
  push(myQueue, 5);

  for (int i = 0; i < 5; ++i)
    printf("%d\n", pop(myQueue));

  // cleanup
  destroyQueue(myQueue);

  return 0;
}
