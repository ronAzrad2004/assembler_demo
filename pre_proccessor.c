#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 81

struct Node {
    char data[MAX_LEN]; 
    struct Node* next;
};

struct Node* mac_names = NULL;

struct Node* createNode(const char* str) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        strncpy(newNode->data, str, sizeof(newNode->data) - 1); 
        newNode->data[sizeof(newNode->data) - 1] = '\0'; 
        newNode->next = NULL;
    }
    return newNode;
}


void insertNode(struct Node** head, char* str) {
    struct Node* newNode = createNode(str);
    if (newNode == NULL) {
        return;
    }
    
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next; 
        }
        current->next = newNode; 
    }
}


void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        current = current->next;
    }
}


void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp); 
    }
}
int findNode(struct Node* head, char *str) {
    struct Node* current = head;
    int count=0;
    while (current != NULL) {
        if (strcmp(current->data,str)==0) {
            return count;
        }
        current = current->next;count++;
    }
    return -1;
}
void writeFile(FILE *f,struct Node* head,int pos){ 
    struct Node* current = head;
    int count=0;
    while (current != NULL) {
        if (count>=pos) {
            fprintf(f,"%s",current->data);
            return;
        }
        current = current->next;count++;
    }
    
}
void removeSpaces(char *str) {
    char *start = str;

    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    if (start != str) {
        char *dest = str;
        while (*start) {
            *dest++ = *start++;
        }
        *dest = '\0'; 
    }
}
/*checking if the string exists in the list of macro names*/
int is_exists_macro(char *str){
  if(findNode(mac_names,str)==-1)
      return 0;
  return 1;
}
int isDuplicated(char *target,struct Node* head,int place){
struct Node* temp=head;
int count=0;
while(temp!=NULL){
if(count!=place)
  if(!strcmp(target,temp->data))
     return 1;
temp=temp->next;
count++;
}
freeList(temp);
return 0;
}

int areEquals(char *str,struct Node* mac_names,int pos){
   return(!strcmp(str,".entry")||!strcmp(str,".extern")||!strcmp(str,".data")||!strcmp(str,".string")||isDuplicated(str,mac_names,pos));
}
int check_legal_name(struct Node* mac_names){
    struct Node* temp = mac_names;
    while(temp!=NULL){
      if(areEquals(temp->data,mac_names,findNode(mac_names,temp->data)))
        return 1;
      temp=temp->next;
    }
    freeList(temp);
    return 0;
}
/*freeing the local list*/
void freeLocal(){
freeList(mac_names);
}
/*the main function you are calling from the main_file, it takes the input from stdin and write the output on a file named pre_proccessing_file*/

int pre_proccess() {
    FILE *fptr, *file, *logs;
    char c[MAX_LEN];
    int error = 0;
    char *str = (char *)malloc(MAX_LEN * 3);
    struct Node *head = NULL;

    /* Open the file "pre_proccessing_file" for writing and clear its content */
    file = fopen("pre_proccessing_file", "w");
    fprintf(file, " ");
    fclose(file);

    /* Open the log file "logs.out" for writing and clear its content */
    file = fopen("logs.out", "w");
    fprintf(file, " ");

    /* Reopen "pre_proccessing_file" for appending data */
    fptr = fopen("pre_proccessing_file", "a");

    /* Reopen "logs.out" for appending log entries */
    logs = fopen("logs.out", "a");

    /* Check if "pre_proccessing_file" failed to open */
    if (fptr == NULL) {
        error = 1;
        return error;
    }

    /* Read input from stdin line by line */
    while ((fgets(c, MAX_LEN, stdin)) != NULL) {
        str[0] = '\0'; /* Initialize str to an empty string */
        c[strcspn(c, "\n")] = '\0'; /* Remove the newline character from input */
        removeSpaces(c); /* Remove spaces from the input line */

        /* Check if the line starts with "macr" */
        if (!strncmp(c, "macr", 4)) {
            char *temp = c + 4;
            removeSpaces(temp); /* Remove spaces from the rest of the line */
            insertNode(&mac_names, temp); /* Insert the macro name into the list */

            /* Read lines until "endmacr" is encountered */
            while ((fgets(c, MAX_LEN, stdin)) != NULL) {
                c[strcspn(c, "\n")] = '\0'; /* Remove the newline character */
                removeSpaces(c); /* Remove spaces from the input line */
                if (!strcmp(c, "endmacr")) {
                    break; /* Exit the loop when "endmacr" is found */
                }
                strcat(str, c); /* Append the line to the string */
                strcat(str, "\n"); /* Add a newline character to the string */
            }
            insertNode(&head, str); /* Insert the macro content into the list */
        } else {
            /* If the line is a known macro name, write its content to the file */
            if (findNode(mac_names, c) != -1) {
                writeFile(fptr, head, findNode(mac_names, c));
            } else {
                /* Otherwise, write the line directly to the file */
                fprintf(fptr, "%s\n", c);
            }
        }
    }

    /* Check for illegal macro names */
    error = check_legal_name(mac_names);
    if (error) {
        /* Log an error message and remove the preprocessing file if an error occurs */
        fprintf(logs, "invalid name to the macro it might be already taken or a name of existed code operation");
        remove("pre_proccessing_file");
        fclose(logs);
    } else {
        /* If no errors, remove the log file and close the file pointer */
        remove("logs.out");
        fclose(fptr);
    }

    /* Free the linked list memory */
    freeList(head);

    /* Free the dynamically allocated string */
    free(str);

    /* Inform the user of the generated preprocessing file */


    return error; /* Return the error status */
}
