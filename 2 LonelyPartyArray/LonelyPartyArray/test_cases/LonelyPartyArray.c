//Maurizio Altamura
//ma470229
//4232977

#include <stdio.h> 
#include <stdlib.h> 
#include "LonelyPartyArray.h"

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
  //initialize
  int i = num_fragments;
  
  //create (malloc) party array
  LPA *party = malloc(sizeof (LPA));
  if(party == NULL)
    return NULL;
  
  //initialize variables
  party->num_fragments = num_fragments;
  party->fragment_length = fragment_length;
  party->num_active_fragments = 0;
  party->size = 0;
  
  //malloc fragments
  party->fragments = malloc(sizeof(int *) * (party->num_fragments));
  if(party->fragments == NULL)
    return NULL;
  
  //malloc fragment_sizes
  party->fragment_sizes = malloc(sizeof(int) * (party->num_fragments));
  if(party->fragment_sizes == NULL)
    return NULL;

  //set fragments[i] and fragment_sizes[i] to a base value(Null and 0, respectively)
  while(i != 0)
  {
    --i;
    party->fragments[i] = NULL;
    party->fragment_sizes[i] = 0;
  }
  
  //print proof
  printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", (num_fragments * fragment_length),  num_fragments);

  //return party address
  return party; 
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party) 
{
  //initialize
  int i = 0;
  
  //check is party is null
  if(party == NULL)
    return NULL;
    
  //free all fragments[i]
  for(i = 0; i < party->num_fragments; i++)     
    free(party->fragments[i]);
  
  //free fragments
  free(party->fragments);
  
  //free fragment_sizes
  free(party->fragment_sizes);
  
  //free party
  free(party);
  
  //set party to null
  party = NULL;
  
  //print proof
  printf("-> The LonelyPartyArray has returned to the void.\n");
  
  return NULL; 
}

int set(LonelyPartyArray *party, int index, int key)
{
  //check if party is null
  if(party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in set().\n");
    return LPA_FAILURE;
  }
  
  //initialize variables after checking for party == null so as to not seg fault 
  int i = 0, j = party->fragment_length - 1 , k = 0, l = 0;
    
  //while i is less than or equal to the absolute value of index
  while(i <= abs(index))
  {
    //when index is between the two boundaries of the fragment_length differences
    if(abs(index) <= j && abs(index) >= i)
    {
      //if index is invalid(too high or to low)
      if(index > (party->num_fragments * party->fragment_length - 1) || index < 0)
      {
        printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, k, index - (party->fragment_length*k));
        return LPA_FAILURE;
      }
      
      //when fragment[k] is null
      if(party->fragments[k] == NULL)
      {
        
        //increase num_active_fragments if the array was previously empty
        if(party->fragments[k] == NULL)
          party->num_active_fragments++;
      
        //malloc for ints for fragments[k][]
        party->fragments[k] = (int *)malloc(sizeof(int) * party->fragment_length);
        if(party->fragments[k] == NULL)
          return LPA_FAILURE;
          
        //print proof
        printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", k, party->fragment_length, i, j);
        
        //set all unused fragments to unused in fragments[k][i]
        for(l = 0; l < party->fragment_length; l++)
          party->fragments[k][l] = UNUSED;
      }
      
      //if the index being changed was unused, increment size and fragment_sizes by one
      if(party->fragments[k][index - (party->fragment_length*k)] == UNUSED)
      {
        party->size++;
        party->fragment_sizes[k]++;
      }
      
      //set key to the proper index
      party->fragments[k][index - (party->fragment_length*k)] = key;
      
      break;
    }
    
    //increments of variables in the while loop
    i = i + party->fragment_length;
    j = j + party->fragment_length;
    if(index >= 0)
      k++;
    if(index < 0)
      k--;
  }
  
  return LPA_SUCCESS; 
}

int get(LonelyPartyArray *party, int index)
{
  //if party is null return null 
  if(party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in get().\n");
    return LPA_FAILURE;
  }
  
  //initialize variables after being sure party wont seg fault
  int i = 0, j = party->fragment_length - 1 , k = 0, l = 0;
  
  //while i is less than the absolute value of index
  while(i <= abs(index))
  {
    //when index is between the two boundaries set by fragment_length
    if(abs(index) <= j && abs(index) >= i)
    {
      //when index is invalid
      if(index > (party->num_fragments * party->fragment_length - 1) || index < 0)
      {
        printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, k, index - (party->fragment_length*k));
        return LPA_FAILURE;
      }
      
      //check to see if the frag is null and thus unused
      if(party->fragments[k] == NULL)
        return UNUSED;
          
      return party->fragments[k][index - (party->fragment_length*k)];
    }
    
    //increment variable in while loop
    i = i + party->fragment_length;
    j = j + party->fragment_length;
    
    if(index >= 0)
      k++;
    if(index < 0)
      k--;
  }
}

int delete(LonelyPartyArray *party, int index)
{
  //if party is null
  if(party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in delete().\n");
    return LPA_FAILURE;
  }
  
  //initialize variables after being sure party wont seg fault
  int i = 0, j = party->fragment_length - 1 , k = 0, l = 0;
  
  //while i is less than or equal to the absolute value of index
  while(i <= abs(index))
  {
    //when index is between the boundaries set by fragment_length
    if(abs(index) <= j && abs(index) >= i)
    {
      //when index is invalid
      if(index > (party->num_fragments * party->fragment_length - 1) || index < 0)
      {
        printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, k, index - (party->fragment_length*k));
        return LPA_FAILURE;
      }
      //when fragment is null
      if(party->fragments[k] == NULL)
        return LPA_FAILURE;
      //if the array fragment is unused
      if(party->fragments[k][index - (party->fragment_length*k)] == UNUSED)   
        return LPA_FAILURE;
      //if the array fragment is in use, set it to unused and reduce size and fragment_size[k]
      if(party->fragments[k][index - (party->fragment_length*k)] != UNUSED)
      {
        party->fragments[k][index - (party->fragment_length*k)] = UNUSED;
        party->size--;
        party->fragment_sizes[k]--;
        //if the array becomes empty entirely, free it and set fragments[k] to null and reduce the active fragments by one
        if(party->fragment_sizes[k] == 0)
        {
          free(party->fragments[k]);
          party->fragments[k] = NULL;
          party->num_active_fragments--;
          printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", k, party->fragment_length, i, j);
        }
        
        return LPA_SUCCESS;
      }
    }
    //increment variables in while loop
    i = i + party->fragment_length;
    j = j + party->fragment_length;
    
    if(index >= 0)
      k++;
    if(index < 0)
      k--;
  }
  return 0;
}

int printIfValid(LonelyPartyArray *party, int index)
{
  //party is null?
  if(party == NULL)
  {
    return LPA_FAILURE;
  }
  
  //initialize variables and making sure party wont seg fault
  int i = 0, j = party->fragment_length - 1 , k = 0, l = 0;
  
  //while i is less than or equal to abs(index)
  while(i <= abs(index))
  {
    //when index is in boundaries set by frag length
    if(abs(index) <= j && abs(index) >= i)
    {
      //if index is invalid
      if(index > (party->num_fragments * party->fragment_length - 1) || index < 0)
        return LPA_FAILURE;

      //if the fragment is null return fail
      if(party->fragments[k] == NULL)
        return LPA_FAILURE;
        
      //if the fragment is unused return fail
      if(party->fragments[k][index - (party->fragment_length*k)] == UNUSED)   
        return LPA_FAILURE;

      //print proof and return success
      printf("%d\n", party->fragments[k][index - (party->fragment_length*k)]);
      return LPA_SUCCESS;
    }
    
    //increment variables in while loop
    i = i + party->fragment_length;
    j = j + party->fragment_length;
    
    if(index >= 0)
      k++;
    if(index < 0)
      k--;
  }
  
  
  return 0;
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
  int i = 0;
  //if party is null
  if(party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
    return party;
  }
  
  //while i is less than nuum fragments, free fragments and set them equal to null
  for(i = 0; i < party->num_fragments; i++) 
    {   
      free(party->fragments[i]);
      party->fragments[i] = NULL;
    }
  //while i is less than fragment length, set frag sizes to 0 
  for(i = 0; i < party->fragment_length; i++)
    party->fragment_sizes[i] = 0;
  
  //reset all variable in struct
  party->num_active_fragments = 0;
  party->size = 0;
  
  //print proof
  printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", party->num_fragments * party->fragment_length, party->num_fragments);
  
  //return party
  return party;
}

int getSize(LonelyPartyArray *party)
{
  //check if party is null, and returns -1 or size
  if(party == NULL)
    return -1;
    
  return party->size;
}

int getCapacity(LonelyPartyArray *party)
{
  //check party is null, return -1 or return the maximum number of elements that party can hold
  if(party == NULL)
    return -1;
    
  return party->num_fragments * party->fragment_length ;
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
  //check party is null, returns - or maximum number of elements that party can hold without allocating any new array fragments
  if(party == NULL)
    return -1;
    
  return party->fragment_length * party->num_active_fragments;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
  //check if party is null, return 0 or  return the number of bytes that would be used if we were using a standard array rather than a LonelyPartyArray struct
  if(party == NULL)
    return 0;
    
  return (long long unsigned int)(getCapacity(party) * sizeof(int));
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
  //initialize variables
  int k = 0;
  int total = 0;
  
  //if party is null return 0
  if(party == NULL)
    return 0;
  //loops for which fragments are valid and hold values in them 
  for(k = 0; k < party->num_fragments; k++)
  {
    if(party->fragments[k] != NULL)
      total = total + (sizeof(int) * party->fragment_length);
  }
  total = total + (sizeof(int*) * party->num_fragments);
  total = total + (sizeof(int) * party->num_fragments);
  
  //adds all them up
  return (long long unsigned int)(sizeof(LPA *) + sizeof(LPA) + total);
}

double difficultyRating(void)
{
  //pretty difficult
  return 4.5; 
}

double hoursSpent(void)
{
  //lots of troubleshooting and logic
  return 25.0;
}

LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
{
  int i, j;
  
  LPA *partytwo = malloc(sizeof (LPA));
  if(partytwo == NULL)
    return NULL;
    
  partytwo->num_fragments = party->num_fragments;
  partytwo->fragment_length = party->fragment_length;
  partytwo->num_active_fragments = party->num_active_fragments;
  partytwo->size = party->size;
  
  partytwo->fragments = (int **)malloc(sizeof(int *) * (partytwo->num_fragments));
  if(partytwo->fragments == NULL)
    return NULL;
  
  partytwo->fragment_sizes = (int *)malloc(sizeof(int) * (partytwo->num_fragments));
  if(partytwo->fragment_sizes == NULL)
    return NULL;
    
  for(i = 0; i < partytwo->num_fragments; i++)
  {
    partytwo->fragment_sizes[i] = party->fragment_sizes[i];
    partytwo->fragments[i] = (int *)malloc(sizeof(int) * (partytwo->fragment_length));
    if(partytwo->fragments[i] == NULL)
      return NULL;
    
    for(j = 0; j < partytwo->fragment_length; j++)
    {
      if(party->fragments[i] != NULL)
        partytwo->fragments[i][j] = party->fragments[i][j];
    }
  }
      
  printf("test5\n");

  printf("-> Successfully cloned the LonelyPartyArray. (capacity: %d, fragments: %d)\n", (partytwo->num_fragments * partytwo->fragment_length),  partytwo->num_fragments);

  return partytwo;
}
