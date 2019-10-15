//Maurizio Altamura
//4232977
//ma470229

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "ListyString.h"

void deleteChar(ListyString *listy, char key);
void deleteOneChar(ListyString *listy, char key);

int processInputFile(char *filename)
{
  // Read and process the input file
  ListyString *LS;
  int check, i = 0; 
  
  //create 2d array
  char *buffer[4];
  for (i = 0; i < 4; i++)
    buffer[i] = (char *)calloc(1024 , sizeof(char));

  FILE *fp;
  
  //if file fails to open return 1
  fp = fopen(filename, "r");
  if(fp == NULL)
    return 1;
  
  check = fscanf(fp, "%[^\n]\n", buffer[0]);
  
  LS = createListyString(buffer[0]);
  
  //To perform the string manipulations described in that section, call the corresponding required functions
  
  while (check != EOF)
  {
    check = fscanf(fp, "%s", buffer[1]);
    if(check == EOF)
      break;
    
    if(strcmp("@", buffer[1]) == 0)
    {
      check = fscanf(fp, "%s %s", buffer[2], buffer[3]);
      replaceChar(LS, buffer[2][0], buffer[3]);
    }
    
    if(strcmp("+", buffer[1]) == 0)
    {
      check = fscanf(fp, "%s", buffer[2]);
      LS = listyCat(LS, buffer[2]); // key = str
    }
    
    if(strcmp("-", buffer[1]) == 0)
    {
      check = fscanf(fp, "%s", buffer[2]);
      deleteChar(LS, buffer[2][0]);
    }
    
    if(strcmp("~", buffer[1]) == 0)
    {
      reverseListyString(LS);
    }
    
    if(strcmp("?", buffer[1]) == 0)
    {
      printf("%d\n", listyLength(LS));
    }
    
    if(strcmp("!", buffer[1]) == 0)
    {
      printListyString(LS);
    }
  }

  LS = destroyListyString(LS);
  
  //for (i = 0; i < 4; i++)
    //free(buffer[i]);
  
  fclose(fp);
}

ListyString *createListyString(char *str)
{ 
  //Convert str to a ListyString by first dynamically allocating a new ListyString struct
  int i;
  ListyString *LS = calloc(1, sizeof(ListyString));
  
  if(str == NULL || strcmp("", str) == 0)
    return LS;
  
  //converting str to a linked list string whose head node will be stored inside that ListyString struct.
  LS->length = strlen(str);
  ListyNode *LN = calloc(1, sizeof(ListyNode));
  LS->head = LN;
  
  for(i = 0 ; i != LS->length; i++)
  {
    LN->data = str[i];
    if(i != LS->length - 1)
    {
      LN->next = calloc( 1, sizeof(ListyNode));
      LN = LN->next;
    }
  }
  
  //if(LN != NULL)
    //free(LN);
  LN = NULL;
  
  return LS;
}

ListyString *destroyListyString(ListyString *listy)
{
  //Free any dynamically allocated memory associated with the ListyString 
  
  if(listy == NULL || listy->head == NULL)
    return NULL;

  ListyNode *current = listy->head;
  
  while(current != NULL)
  {
    if(listy->head->next != NULL)
      free(listy->head->next);
      
    if(current->next != NULL)
      listy->head = current->next;
      
    current = current->next;
  }
  
  if(listy != NULL)
    free(listy);
  listy = NULL;
  if(current != NULL)
    free(current);
  current = NULL;
  
  return NULL;
}

ListyString *cloneListyString(ListyString *listy)
{
  // Using dynamic memory allocation, create and return a new copy of listy
  
  if(listy == NULL)
    return NULL;
    
  //ListyString *temper;
  //IMPORTANT
  //if listy->head is equal to NULL create a new ListyStruct whose head member is initialized to NULL and whose length member is initialized to zero
  //if(listy->head == NULL)
  //  temper = createListyString("");
  //  return temper;
    
  ListyNode *temp = listy->head;
  char *str;
  int i = 0;
  
  while(temp != NULL)
  {
    str[i] = temp->data;
    temp = temp->next;
    i++;
  }
  
  ListyString *newListy = createListyString(str);
  
  free(temp);
  temp = NULL;
  free(str);
  str = NULL;
  
  return newListy; 
}

void deleteChar(ListyString *listy, char key)
{
  //delete all instances of key in the linked list 
  
  if(listy == NULL || listy->head == NULL)
    return;
    
  ListyNode *current = listy->head;
  ListyNode *next = NULL;
  ListyNode *prev = listy->head;

  while(current != NULL)
  {
    next = current->next;
    
    if(current->data == key)
    {
      //update length of linked list
      listy->length = listy->length - 1;
      free(current);
      if(listy->head == current)
        listy->head = next;
      else
        prev->next = next;
        
      current = NULL;
    }
    
    if(current != NULL)
      prev = current;
      
    current = next;
  }
  
  
  //if(prev != NULL)
  //  free(prev);
  prev = NULL;
  if(current != NULL)
    free(current);
  current = NULL;
  
  if(next != NULL)
    free(next);
  next = NULL;
  
  return;
}

void deleteOneChar(ListyString *listy, char key)
{
  //delete one key of a linked list
  if(listy == NULL || listy->head == NULL)
    return;
    
  int flag = 0;
    
  ListyNode *current = listy->head;
  ListyNode *next = NULL;
  ListyNode *prev = listy->head;

  while(flag == 0)
  {
    next = current->next;
    
    if(current->data == key)
    {
      //update length of linked list
      listy->length = listy->length - 1;
      free(current);
      flag = 1;
      if(listy->head == current)
        listy->head = next;
      else
        prev->next = next;
    }
    
    if(flag != 1)
      prev = current;
      
    current = next;
  }
    
  
  if(prev != NULL)
  //  free(prev);
  prev = NULL;
  
  if(current != NULL)
  //  free(current);
  current = NULL;
  
  if(next != NULL)
  //  free(next);
  next = NULL;
  
  return;
}

void replaceChar(ListyString *listy, char key, char *str)
{
  //replaces all instances of key with str
  if(listy == NULL || listy->head == NULL)
     return;
     
  ListyString *temp = NULL;
  
  ListyNode *current = listy->head;
  ListyNode *next = NULL;
  ListyNode *prev = current;
   
  while (current != NULL)
  {
    next = current->next;
    if(current->data == key)
    {
      temp = createListyString(str);
      deleteOneChar(listy, key);
      //update length of linked list
      listy->length = listy->length + strlen(str);
      current = temp->head;
      
      if(current == NULL)
        break;
      
      while(current->next != NULL)
        current = current->next;
        
      if(prev->data == key)
      {
        current->next = listy->head;
        current = current->next;
      }
      else
      {
        current->next = next;
        if(prev != listy->head)//
          current = current->next;
      }
      
      if(listy->head == next)
        listy->head = temp->head;
      else if(listy->head == current)
      {
        listy->head = temp->head;
        current = prev;
      }
      else
        prev->next = temp->head;
    }
    
    if(current != prev)
        prev = current; 
    
    current = next;
  }
  
  
  if(temp != NULL)
    free(temp);
  temp = NULL;
  if(prev != NULL)
  //  free(prev);
  prev = NULL;
  if(current != NULL)
    free(current);
  current = NULL;
  if(next != NULL)
    free(next);
  next = NULL;
  
  return;
}

void reverseListyString(ListyString *listy)
{
  // Reverse the linked list contained within listy
  if(listy == NULL || listy->head == NULL)
    return;
    
  ListyNode *prev = NULL;
  ListyNode *current = listy->head;
  ListyNode *next = NULL;
    
  //make the next pointers point to previous
  while (current != NULL)
  {
    next  = current->next;  
    current->next = prev;
    prev = current;
    current = next;
  }
  listy->head = prev;
  
  if(prev != NULL)
  //  free(prev);
  prev = NULL;
  
  if(current != NULL)
    free(current);
  current = NULL;
  
  if(next != NULL)
    free(next);
  next = NULL;
  
  return; 
}

ListyString *listyCat(ListyString *listy, char *str)
{
  //Concatenate str to the end of the linked list string inside listy
  
  if(str == NULL || strcmp("", str) == 0)
    return listy;
  
  if(listy == NULL && strcmp("", str) == 1)
  {
    ListyString *temp = createListyString(str);
    return temp;
  }
   
  if(listy == NULL && str == NULL)
    return NULL;
    
  if(listy == NULL && str != NULL && strcmp("", str) == 0)
  {
    ListyString *temp = createListyString(str);
    return temp;
  }
    
  //function will cause the creation of a new ListyString, thus return a pointer to that new ListyString
    
  ListyString *temp = createListyString(str);
  
  if(listy->head == NULL)
  {
    listy->head = temp->head;
    listy->length = strlen(str);
    return listy;
  }
  
  ListyNode *current = listy->head;
  
  while(current->next != NULL)
    current = current->next;
  
  current->next = temp->head;
  listy->length = listy->length + strlen(str);
  
  if(temp != NULL)
    free(temp);
  temp = NULL;
  
  if(current != NULL)
  //  free(current);
  current = NULL;
  
  return listy;
}

int listyCmp(ListyString *listy1, ListyString *listy2)
{
  // Compare the two ListyStrings. Return 0 (zero) if they represent equivalent strings. 
  if (listy1 == listy2 )
		return 0;
   
  if((listy1 == NULL && listy2->head == NULL) || (listy2 == NULL && listy1->head == NULL))
    return 1;

  int flag = 0;
  
  ListyNode *current1 = listy1->head;
  ListyNode *current2 = listy2->head;
  
  while(current1 != NULL && current2 != NULL)
  {
    if(current1->data != current2->data)
      flag = 1;
      
    current1 = current1->next;
    current2 = current2->next;
    
    if(flag == 1)
      return flag;
  }
  
  if(current1 != NULL)
    current1 = destroyListyString(current1);
  
  if(current2 != NULL)
    current1 = destroyListyString(current1);
  
  return 0;
}

int listyLength(ListyString *listy)
{
  //Return the length of the ListyString 
  
  //If listy is NULL, return -1. If listy is non-NULL, but listy->head is NULL, return zero.
  if(listy == NULL)
    return -1;
  if(listy != NULL && listy->head == NULL)
    return 0;
    
  return listy->length;
}

void printListyString(ListyString *listy)
{ 
  //Print the string stored in listy, followed by a newline character 
  //If listy is NULL, or if listy represents an empty string, print (empty string)
  if(listy == NULL || listy->head == NULL)// || temp->head->data == "")
  {
    printf("(empty string)\n");
    return;
  }

  ListyNode *temp = listy->head;

  while(temp != NULL)
  {
    printf("%c", temp->data);
    temp = temp->next;
  }
  printf("\n");
  
  if(temp != NULL)
    free(temp);
  temp = NULL;
  
  return;
}

double difficultyRating(void)
{
  //pretty difficult and diagrams are needed for everything
  return 4.0;
}

double hoursSpent(void)
{
  //lots of thinking and diagram creations
  return 20.0;
}

int main(int argc, char **argv)
{
  // capture the name of an input file and call the processInputFile
  processInputFile(argv[1]);
  return 0;
}