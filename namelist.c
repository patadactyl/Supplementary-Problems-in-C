/***********************************************************************
 * Name:  Patrick Charlton                                             *
 * Box:   e189                                                         *
 * Assignment name: Supplemental Problem 2: Linked Lists in C          *
 *      (25% off if name/number does not match assignment)             *
 * Assignment for Tuesday March 19, 2019;                              *
 ***********************************************************************/

/* *********************************************************************
 * Academic honesty certification:                                     *
 *   Written/online sources used:                                      *
 *     Silbeschatz, Abraham. "Operating Systems Concepts               *
 *                                                                     *
 * Help obtained                                                       *
 *                                                                     *
 *         None                                                        *
 *                                                                     *
 *   My/our signature(s) below confirms that the above list of sources *
 *   is complete AND that I/we have not talked to anyone else          *
 *   (e.g., CSC 161 students) about the solution to this problem       *
 *                                                                     *
 *   Signature:                                                        *
 ***********************************************************************/

/* A program shell  to maintain a linked list of names */

/* library for standard I/O */
#include <stdio.h>

/* library for memory allocation */
#include <stdlib.h>

/* library for string length and other string functions */
#include <string.h>

/* Maximum length of names */
#define strMax 20

struct node
{ char data [strMax];
  struct node * next;
};

/* function prototypes, listed in alphabetical order */

void addName(struct node ** firstPtr);
/* pre-condition:  firstPtr points to the pointer
                   designating the head of a list
  post-condition:  a name is read and
                   inserted into the list at a designated place
*/

void print(struct node * first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  The items on the list are printed from first to last
                   the list itself is unchanged
*/

void removeDuplicates (struct node * first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  each name on the list appears only once (no duplicate names)
                   when duplicates occur on the original list,
                      only the first occurence remains after processing
*/

void duplicate (struct node * firstPtr);
/* pre-condition:  first designates the first node of a list 
  post-condition:  each node is duplicated, with the new node inserted
                   after the original node
*/

int main (void) {
  /* program to coordinate the menu options and calls the requested function */

  struct node * first = NULL;   /* pointer to the first list item */
  char option[strMax];          /* user response to menu selection */

  printf ("Program to Maintain a List of Names\n");

  while (1) {
    /* print menu options */
    printf ("Options available\n");
    printf ("I - Insert a name (from the keyboard) into the list\n");
    printf ("P - Print the names on the list\n");
    printf ("R - Remove duplicate names (leaving only the first occurence)\n");
    printf ("D - Duplicate each node\n");
    printf ("Q - Quit\n");

    /* determine user selection */
    printf ("Enter desired option: ");
    scanf ("%s", option);
    
    switch (option[0])
      { case 'I':
        case 'i': 
          addName(&first);
          break;
        case 'P':
        case 'p': 
          print(first);
          break;
        case 'R':
        case 'r': 
          removeDuplicates(first);
          break;
        case 'D': 
        case 'd': 
          duplicate(first);
          break;
        case 'Q':
        case 'q':
          printf ("Program terminated\n");
          return 0;
          break;
        default: printf ("Invalid Option - Try Again!\n");
          continue;
      }
  }
}
        
void addName(struct node ** firstPtr) {
/* pre-condition:  firstPtr points to the pointer designating the head of a list
  post-condition:  a name is read and
                   inserted into the list at a designated place
*/

  char oldName [strMax];
  struct node * newNode = (struct node *)malloc(sizeof(struct node));
  struct node * listPtr;
  struct node * prevPtr;

   printf ("Enter name to be inserted into list: ");
   scanf ("%s", newNode->data);

   if (*firstPtr == NULL) {
     /* insert name's node at start of list */
     newNode->next = *firstPtr;
     *firstPtr = newNode;
   }
  
   else {
     printf ("Enter old name which new name should preceed, \n");
     printf ("or enter ? if new name should be placed last\n");
     scanf ("%s", oldName);

     if (strcmp (oldName, (*firstPtr)->data) == 0) {
       /* insert name's node at start of list */
       newNode->next = *firstPtr;
       *firstPtr = newNode;
     }
     else {
       /* insert name's node after start of the list */
       
       /* start at beginning of list */
       listPtr = (*firstPtr)->next;  /* the current node to search */
       prevPtr = *firstPtr;          /* the node behind listPtr */
       
       while (listPtr && (strcmp (oldName, listPtr->data) != 0)) {
         prevPtr = listPtr;
         listPtr = prevPtr->next;
       }

       newNode->next = prevPtr->next;
       prevPtr->next = newNode;
     }
   }
   printf ("%s inserted into the list\n\n", newNode->data);
}

void print(struct node * first){
/* pre-condition:  first designates the first node of a list 
  post-condition:  The items on the list are printed from first to last
                   the list itself is unchanged
*/    
  struct node * listElt = first;
  printf ("The names on the list are:\n\n");

  while (listElt) {
    printf ("%s\n", listElt->data);
    listElt = listElt->next;
  }

  printf ("\nEnd of List\n\n");
}

void removeDuplicates (struct node * first) {
/* pre-condition:  first designates the first node of a list 
  post-condition:  each name on the list appears only once (no duplicate names)
                   when duplicates occur on the original list,
                      only the first occurence remains after processing */
    
    /* Sets the current node pointer to the first pointer */
    struct node * current = first;
    
    /* initializes temporary and duplicate node pointers */
    struct node * temp;
    struct node * duplicate;
    
    /* Base case for if the list is empty. If list contains any elements move on */
    if(current == NULL) {
        printf("The list is empty. Please add list elements before proceeding \n");
    }
     
    /* Iterate through for each element */
    while (current != NULL && current->next != NULL)
    {
        /* Set the pointer temp to point to the same node as the pointer current.
           This will be the first pointer at the outset */
        temp = current;
    
    /* Iter ate trhough to compare the element set by the pointer temp with rest
     of the elements */
        while (temp->next != NULL)
        {
        /* If the element pointed to contains the same string as the element pointed
           to by current then delete it */
            if (strcmp(current->data, current->next->data) == 0)
            {
            /* If the strings match, set the duplicate pointer to the node after the temporary pointer.
               Then move the pointer going to the next node to the one after, skipping over the node
               to be deleted and thus breaking the link. After this use the free function to deallocate space
               for the node to be deleted, which is pointed to by duplicate. */
                duplicate = temp->next;
                temp->next = temp->next->next;
                free(duplicate);
            }
            else {
            /* If the strings don't match move on to check the next node */
                temp = temp->next;
            }
        }
        /* Move the pointer for the current node on to the next one and start the process over,
           doing the same checks as before but for a new node. */
        current = current->next;
    }
    print(first);
}


void duplicate (struct node * firstPtr)
/* pre-condition:  first designates the first node of a list 
  post-condition:  each node is duplicated, with the new node inserted
                   after the original node
*/
{
    
    /* Sets the current node pointer to the first pointer */
    struct node * temp = firstPtr;
    
    /* intialize new node to become the duplicate */
    struct node * duplicate;
    
    /* Create a boolean counter to find the node to be duplicated */
    int find = 1;
    
    /* Iterate through all nodes in the list until you reach the end of the linked list */
    while (temp != NULL) {
        /* find counter will start out as 1 (true) and will continue with logic */
        if (find) {
            /* Set pointer to the node duplicate to be the new duplicate created.
               Allocate additional space for the duplicate node(s) to fill */
            duplicate = (struct node *)malloc(sizeof(struct node));
            /* Copy over string data from the node being duplicated to the new duplicated node */
            strcpy(duplicate->data, temp->data);
            /* Replace temp and duplicate */
            duplicate->next = temp->next;
            temp->next = duplicate;
            find = 0;
        }
        else
        {
            find = 1;
        }
        /* Moves temp to the next element. Move on and repeat same processes with new element */
        temp = temp->next;
    }
    print(firstPtr);
}

