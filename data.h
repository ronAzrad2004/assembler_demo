#ifndef TAGS_LIST_H
#define TAGS_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 90

/* Structure definition */
typedef struct tags {
    int rowNum;                   /* Row number of the tag */
    char flag;                    /* Flag associated with the tag */
    char Add_flag;                /* Additional flag for the tag */
    char name[MAX_LEN];           /* Name of the tag */
    char nums[MAX_LEN];           /* Associated numbers or data */
    struct tags* next;            /* Pointer to the next tag in the list */
} tags;

/**********************************************************************
* Function: createNode
* Description: Creates a new node (tag) and initializes its values.
* Parameters:
*   - int rowNum: Row number of the tag.
*   - char flag: Flag associated with the tag.
*   - char Add_flag: Additional flag for the tag.
*   - const char* name: Name of the tag.
*   - const char* nums: Associated numbers or data.
* Returns: A pointer to the newly created tag node.
**********************************************************************/
tags* createNode(int rowNum, char flag, char Add_flag, const char* name, const char* nums);

/**********************************************************************
* Function: insertNode
* Description: Inserts a tag node into the linked list.
* Parameters:
*   - tags** head: Pointer to the pointer of the head of the list.
*   - tags* t: Pointer to the tag node to insert.
* Returns: void
**********************************************************************/
void insertNode(tags** head, tags* t);

/**********************************************************************
* Function: findNode
* Description: Finds a tag node in the list by its name.
* Parameters:
*   - tags* head: Pointer to the head of the list.
*   - const char* str: Name of the tag to search for.
* Returns: 1 if the tag is found, 0 otherwise.
**********************************************************************/
int findNode(tags* head, const char* str);

/* Global Variables */
extern tags* tags_names;
extern char d_str[MAX_LEN];

#endif /* TAGS_LIST_H */
