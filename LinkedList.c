#include<stdlib.h>
#include<stdio.h>
#include <string.h>
struct Node {
	int data;
	struct Node *next;
	struct Node *prev;
};
struct Node *head = NULL;

void show(struct Node* node)
{
	if (node == NULL)
	{
		printf("There is no list to show\n");
		return;
	}
	struct Node* last;
	printf("Traveral in forward direction\n");
	while (node != NULL) 
	{
		printf(" %d ", node->data);
		last = node;
		node = node->next;
	}
	printf("\nTraveral in reverse direction\n");
	while(last != NULL)
	{
		printf(" %d ", last->data);
		last = last->prev;
	}
	printf("\n");
}

void append(struct Node** head, int new_data)
{
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	struct Node* last = *head;
	new_node->data = new_data;
	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->prev = NULL;
		*head = new_node;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return;
}

void prepend(struct Node** head, int new_data)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->prev = NULL;
	new_node->next = (*head);
	if ((*head) !=NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void insert(struct Node** head, int new_data, int index)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	struct Node* current = *head;
	char str[2];
	// In case there is no list
	if (*head == NULL)
	{
		printf("You have no list stored\n");
		printf("Would you like to make a new list starting with value '%d' (y/n)? \n", new_data);
		scanf("%s", str);
		if (strcmp(str, "y") == 0)
		{
			new_node->data = new_data;
			new_node->next = NULL;
			new_node->prev = NULL;
			*head = new_node;
			return;
		}
		else 
		{
			printf("No action performed\n");
			return;
		}

	}
	// In case the index is too big for the list or it makes new node the last one
	for (int i=0; i<index; i++)
	{
		if ((current->next == NULL) && (i == index-1))
		{
			new_node->data = new_data;
			new_node->next = NULL;
			current->next = new_node;
			new_node->prev = current;
			return;
		}
		if ((current->next == NULL) && (i<index-1))
		{
			printf("Index that you chose can't be reached\n");
			printf("Would you like to store value '%d' at index '%d' (y/n)?\n", new_data, i+1);
			scanf("%s", str);
			if (strcmp(str, "y") == 0)
			{
				new_node->data = new_data;
				new_node->next = NULL;
				current->next = new_node;
				new_node->prev = current;
				return;
			}				
			else 
			{
				printf("No action performed\n");
				return;
			}
		}
		if (current->next == NULL) break;
		else current = current->next;
	}
	current = current->prev;
	new_node->data = new_data;
	new_node->next = current->next;
	current->next->prev = new_node;
	current->next = new_node;
	new_node->prev = current;
	
}

void reverse(struct Node** head_ref)
{
    struct Node* temp = NULL;
    struct Node* current = *head_ref;
 
    /* swap next and prev for all nodes of
      doubly linked list */
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
 
    /* Before changing head, check for the cases like empty
       list and list with only one node */
    if (temp != NULL)
        *head_ref = temp->prev;
    printf("List reversed\n");
}

void remove(struct Node** head_ref, int index)
{
	// if head is the only node
	if (((*head_ref)->prev == NULL) && ((*head_ref)->next == NULL))
	{
		(*head_ref)->next = NULL;
		(*head_ref)->prev = NULL;
		(*head_ref) = NULL;
		printf("This was the unique node\nThere is no list anymore\n");
		return;
	}
	struct Node* del = (*head_ref);
	for (int i=0; i<index; i++) 
	{
		if (del->next == NULL) // if there is a node at choosen index
		{
			printf("There is no node at index '%d'\n", index);
			return;
		}
		// in the end del will be node that we have to remove
		del = del->next;
	}
	// if del is a last node
	if (del->next == NULL)
	{
		del->prev->next = NULL;
		free(del);
		printf("Node deleted\n");
		return;
	}
	//if del is the head
	if (del->prev == NULL) 
	{
		(*head_ref) = del->next;
		(*head_ref)->prev = NULL;
		free(del);
		printf("Node deleted\n");
		return;
	}
	// if del is between two nodes
	del->prev->next = del->next;
	del->next->prev = del->prev;
	free(del);
	printf("Node deleted\n");
	return;
}

void sortedInsert(struct Node** head_ref, struct Node* newNode)
{
    struct Node* current;
 
    // if list is empty
    if (*head_ref == NULL)
        *head_ref = newNode;
 
    // if the node is to be inserted at the beginning
    // of the doubly linked list
    else if ((*head_ref)->data >= newNode->data) {
        newNode->next = *head_ref;
        newNode->next->prev = newNode;
        *head_ref = newNode;
    }
 
    else {
        current = *head_ref;
 
        // locate the node after which the new node
        // is to be inserted
        while (current->next != NULL &&
               current->next->data < newNode->data)
            current = current->next;
 
        /*Make the appropriate links */
 
        newNode->next = current->next;
 
        // if the new node is not inserted
        // at the end of the list
        if (current->next != NULL)
            newNode->next->prev = newNode;
 
        current->next = newNode;
        newNode->prev = current;
    }
}
 
// function to sort a doubly linked list using insertion sort
void insertionSort(struct Node** head_ref)
{
    // Initialize 'sorted' - a sorted doubly linked list
    struct Node* sorted = NULL;
 
    // Traverse the given doubly linked list and
    // insert every node to 'sorted'
    struct Node* current = *head_ref;
    while (current != NULL) {
 
        // Store next for next iteration
        struct Node* next = current->next;
 
        // removing all the links so as to create 'current'
        // as a new node for insertion
        current->prev = current->next = NULL;
 
        // insert current in 'sorted' doubly linked list
        sortedInsert(&sorted, current);
 
        // Update current
        current = next;
    }
 
    // Update head_ref to point to sorted doubly linked list
    *head_ref = sorted;
}

void search(struct Node** head_ref, int value)
{
	if ((*head_ref) == NULL)
	{
		printf("There is no list!\n");
		return;
	}
	struct Node* current = (*head_ref);
	int i=0;
	int k=0;
	while (current != NULL)
	{
		if (value == current->data)
		{
			printf("value '%d' is stored at index '%d'\n", value, i);
			k++;
		}
		current = current->next;
		i++;
	}
	if (k == 0)
	{
		printf("Value '%d' was not found\n", value);
	}
}

void save(struct Node** head_ref)
{
	FILE *file;
	char str[50];
	printf("If you have an existing file and you choose it's name ");
	printf("it will be overwritten\n");
	printf("Choose a name for the file: ");
	scanf("%s", str);
	file = fopen(str, "w");
	struct Node* current = (*head_ref);
	while (current != NULL)
	{
		fprintf(file, "%d <-> ", current->data);
		current = current->next;
	}
	fclose(file);
	printf("List succesfully saved\n");
}

void load(struct Node** head_ref)
{
	FILE *file;
	char str[50];
	printf("Choose a name for the file: ");
	scanf("%s", str);
	file = fopen(str, "r");
	if (file == NULL)
	{
		printf("There is no such file\n");
		printf("Loading failed\n");
		return;
	}
	int value;
	while(fscanf(file, "%d <-> ", &value) > 0)
	{
		append(&head, value);
	}
	printf("Loading was succesful\n");
	fclose(file);
}

void join(struct Node** head_ref)
{
	printf("Note: resulting list will not be saved automaticaly\n");
	printf("There are three possible ways to join two lists\n");
	printf("0 - cancel operation\n");
	printf("1 - choose a list to append to the current one\n");
	printf("2 - append current list to another one\n");
	printf("Choose option: ");
	char str[50];
	scanf("%s", &str);
	if (strcmp(str, "1") == 0)
	{
		FILE* file;
		printf("Choose a file to append: ");
		scanf("%s", str);
		file = fopen(str, "r");
		if (file == NULL)
		{
			printf("There is no such file\n");
			printf("Joining falied\n");
			return;
		}
		int value;
		while(fscanf(file, "%d <-> ", &value) > 0)
		{
			append(&head, value);
		}
		printf("Joining succeded\n");
		fclose(file);
	}
	else if (strcmp(str, "2") == 0)
	{
		FILE* file;
		file = fopen("temp", "w");
		struct Node* current = (*head_ref);
		while (current != NULL)
		{
			fprintf(file, "%d <-> ", current->data);
			current = current->next;
		}
		fclose(file);
		printf("Choose a file to prepend: ");
		scanf("%s", str);
		file = fopen(str, "r");
		if (file == NULL)
		{
			printf("There is no such file\n");
			printf("Joining falied\n");
			return;
		}
		struct Node* temp_head = NULL;
		int value;
		while(fscanf(file, "%d <-> ", &value) > 0)
		{
			append(&temp_head, value);
		}
		fclose(file);
		(*head_ref) = temp_head;
		file = fopen("temp", "r");
		while(fscanf(file, "%d <-> ", &value) > 0)
		{
			append(&head, value);
		}
		fclose(file);
		printf("Files succesfully joined\n");
		return;
	}
	else {printf("No changes performed\n");return;}
}

int main()
{
	int value;
	int index;
	printf("Type 'help' to view all commands\n");
	while (1)
	{
		char str[10];
		//fgets(str, sizeof(str), stdin);
		//puts(str);
		printf("->");
		scanf("%s", &str);
		if (strcmp(str, "help") == 0) 
		{
			printf("'show' - print list\n");
			printf("'append' - add node at the end;\n");
			printf("'prepend' - add node at the beginning\n");
			printf("'insert' - add node to a specific index\n");
			printf("'reverse' - reverse list\n");
			printf("'remove' - remove node from a specific index\n");
			printf("'sort' - sort list\n");
			printf("'search' - search for a value\n");
			printf("'join' - combine two lists\n");
			printf("'save' - save list to a file\n");
			printf("'load' - load list from an existing file\n");
			printf("'exit' - exit program\n");
		}
		if (strcmp(str, "exit") == 0) {free(head); return 0;}
		if (strcmp(str, "show") == 0) 
		{
			if (head == NULL)
				printf("There is no list\n");
			else show(head);
		}
		if (strcmp(str, "append") == 0) 
		{
			printf("Choose a number to store: ");
			scanf("%d", &value);
			append(&head, value);

		}
		if (strcmp(str, "prepend") == 0) 
		{
			printf("Choose a number to store: ");
			scanf("%d", &value);
			prepend(&head, value);
		}
		if (strcmp(str, "insert") == 0) 
		{
			printf("note - indexing starts with 0\n");
			printf("Choose a number to store: ");
			scanf("%d", &value);
			printf("Choose index to store to: ");
			scanf("%d", &index);
			insert(&head, value, index);
		}
		if (strcmp(str, "reverse") == 0) 
		{
			reverse(&head);
		}
		if (strcmp(str, "remove") == 0) 
		{
			if (head == NULL) printf("There is no list to remove from\n");
			else
			{
				printf("Choose index of the node to remove: ");
				scanf("%d", &value);
				remove(&head, value);
			}
		}
		if (strcmp(str, "sort") == 0) 
		{
			insertionSort(&head);
			printf("List is sorted\n");
		}
		if (strcmp(str, "search") == 0) 
		{
			printf("Which value are you looking for? ");
			scanf("%d", &value);
			search(&head, value);
		}
		if (strcmp(str, "join") == 0) 
		{
			join(&head);
		}
		if (strcmp(str, "save") == 0) 
		{
			save(&head);
		}
		if (strcmp(str, "load") == 0) 
		{
			load(&head);
		}
	}
}