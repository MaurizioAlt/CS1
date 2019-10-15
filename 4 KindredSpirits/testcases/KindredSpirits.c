//Maurizio Altamura
//4232977
//ma470229

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "KindredSpirits.h"

int isReflection(node *a, node *b)
{
//determine whether the trees rooted at a and b are reflections of one another
  if (a == NULL && b == NULL)
      return 1;
  if (a == NULL || b == NULL)
      return 0;
      
  if(a->data == b->data)
    if(isReflection(a->right, b->left) == 1)
      if(isReflection(a->left, b->right) == 1)
        return 1;
      
  return 0;
}

node *createNode(int data)
{
  node *newNode = calloc(1, sizeof(node));
  newNode->data = data;
  
  return newNode;
}

node *makeReflection(node *root)
{
//creates a new tree, which is a reflection of the tree rooted at root
  if(root == NULL)
    return NULL;

  node *newRoot = createNode(root->data);
  newRoot->left = makeReflection(root->right);
  newRoot->right = makeReflection(root->left);
  
  return newRoot;
}

// stacks > webcourses
typedef struct Stack
{
  struct Stack *next;
  int data;
} Stack;
Stack *createStack(void)
{
  Stack *s = calloc(1, sizeof(Stack));
  return s;
}

// Push a new element onto the top of the stack.
Stack *push(Stack *s, int data)
{
  Stack *node = calloc(1, sizeof(Stack));
  node->data = data;
  node->next = s;
  //s->next = node;
  return node;
}
// Remove the top element from the stack
Stack *pop(Stack *s)
{
  if(s == NULL)
    return NULL;
  Stack *temp = s;
  //*data = s->data;
  s = s->next;
  free(temp);
  return s;
}

//    bst.c > Review for Exam #2 > Webcourses
Stack *preorder(node *root, Stack *sa)
{
  if (root == NULL)
    return sa;
    
  //printf("%d ", root->data);
  sa = push(sa, root->data);
  
  preorder(root->left, sa);
  preorder(root->right, sa);
}
  
Stack *postorder(node *root, Stack *sb)
{
  if (root == NULL)
    return sb;
    
  postorder(root->left, sb);
  postorder(root->right, sb);
  
  //printf("%d ", root->data);
  push(sb, root->data);
}

Stack *destroyStack(Stack *s)
{
  if (s == NULL)
    return NULL;
  while(s != NULL)
    s = pop(s);
  return NULL;
}

int KS(node *a, node *b)
{
  if(a == NULL && b == NULL)
    return 1; 
    
  if(a == NULL || b == NULL)
    return 0;
    
  Stack *sa = createStack();
  Stack *sb = createStack();
  
  sa = preorder(a, sa);
  sb = postorder(b, sb);
  
  while( (sa->next != NULL) && (sb->next != NULL) )
  {
    if(sa->data != sb->data)
    {
      sa = destroyStack(sa);
      sb = destroyStack(sb);
      return 0;
    }
    pop(sa);
    pop(sb);
  }
  return 1;
}

int kindredSpirits(node *a, node *b)
{
//determines whether the trees rooted at a and b are kindred spirits
  return ( KS(a, b) || KS(b, a) );
}
double difficultyRating(void)
{
  return 3.0;
}
double hoursSpent(void)
{
  return 5.0;
}