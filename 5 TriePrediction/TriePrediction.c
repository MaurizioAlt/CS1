// Maurizio Altamura
// 4232977
// ma470229

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TriePrediction.h"

TrieNode *createTrieNode(void);
int *insertString(TrieNode *root, char *str, int index);
void stripPunctuators(char *str);
void getMostFrequentWordHelper(TrieNode *root, char *buffer, int *max, char *mostFrequentWordBuffer, int letter);
void prefixCountHelper(TrieNode *root, int *total);

// Helper function called by printTrie(). (Credit: Dr. S.)
void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0. (Credit: Dr. S.)
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

//tries.c (Credit: Dr. S.)
TrieNode *buildTrie(char *filename)
{
  //filename is the name of a corpus text file to process. Open the file and create a trie 
  int len;
  TrieNode *root;
	TrieNode *temp = NULL;
	char str[1024];
	char buffer[1024];
	char previousWord[1024];

	FILE *ifp;
	ifp = fopen(filename, "r");

	root = createTrieNode();
	strcpy(previousWord, "");
	
	while(fscanf(ifp, "%s", buffer) != EOF)
  {
    //printf("%s\n", buffer);
    
    len = strlen(buffer);
		strcpy(str, buffer);
		stripPunctuators(str);

		if(buffer[len-1] == '!' || buffer[len-1] == '?' || buffer[len-1] == '.')
    {
		  if(temp == NULL)
				insertString(root, str, 0);
			else
      {
				insertString(root, str, 0);
				if(temp->subtrie == NULL) 
					temp->subtrie = createTrieNode();
				insertString(temp->subtrie, str, 0);
				temp = NULL;
      }
        
		  if(previousWord[len-1] == '!' || previousWord[len-1] == '?' || previousWord[len-1] == '.')
      {
				strcpy(previousWord, buffer);
				continue;
			}
		}
		else 
    {
			insertString(root, str, 0);
			if(temp == NULL)
				temp = getNode(root, str);
			else
      {
				if(temp->subtrie == NULL)
					temp->subtrie = createTrieNode();
				insertString(temp->subtrie, str, 0);
				temp = getNode(root, str);
			}
		}
		strcpy(previousWord, buffer);
	}
 
	fclose(ifp);
	return root;
}

int processInputFile(TrieNode *root, char *filename)
{
  //This function takes in the root of a trie and the name of an input file
  int len = 0, j = 0, i =0;
	TrieNode *temp = NULL;
	char buffer[1024];
	TrieNode *node = NULL;
 
	FILE *ifp;
	ifp = fopen(filename, "r");

	while(fscanf(ifp, "%s", buffer) != EOF)
  {
		//printf(buffer, "%s");

		if(strcmp(buffer, "!") == 0)
			printTrie(root, 0);
			//printf("%s\n", buffer);

		else if(strcmp(buffer, "@") == 0)
    {
			//printf("%s", buffer);
			fscanf(ifp, "%s", buffer);
			fscanf(ifp, "%d", &i);
			printf("%s", buffer);
      
			for(j = 0; j < i; j++)
      {
				temp = getNode(root, buffer);
				if(temp == NULL || temp->subtrie == NULL)
					break;
				getMostFrequentWord(temp->subtrie, buffer);
				printf(" %s", buffer);
			}

			printf("\n");
    }
  
    else
    {
      printf("%s\n", buffer);
      len = strlen(buffer);
      
      for(i = 0; i < len; i++)
 	      buffer[i] = tolower(buffer[i]);
      
      if(getNode(root, buffer) == NULL)
      {
		 	 printf("(INVALID STRING)\n");
		 	 continue;
		 }
		  node = getNode(root, buffer);
		  if(node->subtrie == NULL)
      {
		 	  printf("(EMPTY)\n");
		 	  continue;
		  }
		  printTrie(node->subtrie, 1);
   }
  }
  
  destroyTrie(root);
  fclose(ifp);
 	return 0;
}

TrieNode *destroyTrie(TrieNode *root)
{
  // Free all dynamically allocated memory associated with this trie
  int i;
  
  if(root == NULL)
    return NULL;
  
	for(i = 0; i < 26; i++) 
	//if (root->children[i] != NULL) 
			destroyTrie(root->children[i]);

	//if (root->subtrie != NULL)
		destroyTrie(root->subtrie);
	
	free(root);
	return NULL;
}

TrieNode *getNode(TrieNode *root, char *str)
{
  //Searches the trie for the specified string, str
  int i, letter, len = strlen(str);
  TrieNode *wizard = root;
  
  if (root == NULL || str == NULL)
    return NULL;
  
  for(i = 0; i < len; i++)
  {
    letter = tolower(str[i]) - 'a';
    wizard = wizard->children[letter];
    if (wizard == NULL)
      return NULL;
      
    if( (wizard->count >= 1) && (i == len-1) )
      return wizard;
    if( (wizard->count == 0) && (i == len-1) )
      return NULL;
  }
  
  return wizard;
}

void getMostFrequentWordHelper(TrieNode *root, char *buffer, int *max, char *mostFrequentWordBuffer, int letter)
{
	int i;

	if(root == NULL)
		return;

	if(root->count > *max || *max == 0)
  {
		*max = root->count;
    strcpy(buffer, mostFrequentWordBuffer);
	}
 
	mostFrequentWordBuffer[letter + 1] = '\0';

	for (i = 0; i < 26; i++)
  {
		mostFrequentWordBuffer[letter] = 'a' + i;
		getMostFrequentWordHelper(root->children[i], buffer, max, mostFrequentWordBuffer, letter + 1);
	}
	mostFrequentWordBuffer[letter] = '\0';
}

void getMostFrequentWord(TrieNode *root, char *str)
{
  //Searches the trie for the most frequently occurring word and copies it into the string variable passed to the function, str
	int max = 0;

	char buffer[1024] = {'\0'};
	char mostFrequentWordBuffer[1024];

  strcpy(str, "");

	TrieNode *lastGetNode = getNode(root, str);

	if(lastGetNode == NULL || lastGetNode->subtrie == NULL)
  {  
    getMostFrequentWordHelper(root, buffer, &max, mostFrequentWordBuffer, 0);
    if(max == 0)
      strcpy(str, "");
    else
      strcpy(str, buffer);
		return;
	}
	else
	  getMostFrequentWordHelper(lastGetNode->subtrie, buffer, &max, mostFrequentWordBuffer, 0);
     
	strcpy(str, buffer);	
	return;
}

int containsWord(TrieNode *root, char *str)
{
  //Searches the trie for the specified string, str
  int i, letter;
  int len = strlen(str);
  TrieNode *wizard = root;
  
  if (root == NULL || str == NULL)
    return 0;
  for(i = 0; i < len; i++)
  {
    letter = tolower(str[i]) - 'a';
    wizard = wizard->children[letter];
    if(wizard == NULL)
      return 0;
    if( (wizard->count >= 1) && (i == len-1) )
      return 1;
    if( (wizard->count == 0) && (i == len-1) )
      return 0; 
  }
  
  return 0;
}

void prefixCountHelper(TrieNode *root, int *total)
{
  int j;
  
  if(root == NULL)
    return;
  if(root->count > 0)
    *total += root->count;
    
  for(j = 0; j < 26; j++)
    prefixCountHelper(root->children[j], total);
  
  return; 
}

int prefixCount(TrieNode *root, char *str)
{
  // Counts the number of strings in the trie (with count = 1) that begin with the specified string, str
  int total = 0;
  TrieNode *wizard;
  
  if(root == NULL || str == NULL)
    return 0;
  if(strcmp(str, "") == 0)
    wizard = root;
  else
    wizard = getNode(root, str);

  prefixCountHelper(wizard, &total);
  return total;
}

TrieNode *createTrieNode(void)
{
  //tries.c (Credit: Dr. S.)
  TrieNode *newRoot = calloc(1, sizeof(TrieNode));
  return newRoot;
}

int *insertString(TrieNode *root, char *str, int index)
{
  // Inserts the string str into the trie
  //tries.c (Credit: Dr. S.)
  int i = 0, j = 0, letter = 0;
	int length = strlen(str);
  char buffer[1024];
  TrieNode *wizard = root;

	if (index >= length)
		return 0;
	
	letter = tolower(str[index]) - 'a';

	if (wizard->children[letter] == NULL)
		wizard->children[letter] = createTrieNode();

	if (index == length - 1) 
		wizard->children[letter]->count++;
   
  index++;

	insertString(wizard->children[letter], str, index);
 
  return 0;
}

void stripPunctuators(char *str)
{
  //Takes a string, str, and removes all punctuation from the strin
  int i = 0, j = 0;
  int len = strlen(str);
	char buffer[1024];

	for(i = 0; i < len; i++)
  {
		if(isalpha(str[i]))
    {
			buffer[j] = str[i];
			buffer[j] = tolower(buffer[j]);
      j++;
		}
	}
	buffer[j] = '\0';
 
	strcpy(str, buffer);
}

double difficultyRating(void)
{
	return 5.0;
}

double hoursSpent(void)
{
	return 24.0;
}

int main(int argc, char **argv)
{
  TrieNode *root = buildTrie(argv[1]);
  
  if (argc != 3)
    return 0;
  
  processInputFile(root, argv[2]);
  
  //root = destroyTrie(root);
  //free(root);
  
  return 0;
}
