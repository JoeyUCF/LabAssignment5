#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int count = 0;
	node* current = head;

	// Iterates through the list sand increments for every node
	while(current != NULL){
		count++;
		current = current->next;
	}
	return count;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	int len = length(head);
	char* str = (char*)malloc((len + 1) * sizeof(char)); // Additional one is to account for null terminator

	// Checks if the Str was allocated
	if (str == NULL){
		printf("Memory did not allocate");
		return NULL;
	}

	int i = 0;
	node* current = head;

	// Iterates through the nodes and sets the str[index] to the current letter
	while(current != NULL){
		str[i] = current->letter;
		current = current->next;
		i++;
	}

	// Null operator at the end of the string
	str[i] = '\0';
	return str;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{

	// Creates new node in memory and checks if it was allocated
	node* newNode = (node*)malloc(sizeof(node));
	if (newNode == NULL){
		return;
	}

	// Initializes newNode members
	newNode->letter = c;
	newNode->next = NULL;

	// Checks if the provided pNode is NULL
	if(*pHead == NULL){
		*pHead = newNode;
	} else { // Iterates through the list while it is not null
		node* current = *pHead;
		while(current->next != NULL){
			current = current->next;
		}
		// After finding a null head (end of list) it points the last node to the new node.
		current->next = newNode;
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	node* current = *pHead;
	node* next;

	while (current != NULL){ // While NOT NULL
		next = current->next; // Stores the pointer to the next node in NEXT
		free(current); // Frees the current NODE
		current = next; // Sets current NODE to the next pointer to continue iterating
	}
	*pHead = NULL; // Sets the head of the list to NULL after deleting everything

}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}