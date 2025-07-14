#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/* ****************************************************************************************** */
#include "my_str_funcs.h"
/* ****************************************************************************************** */
#define FALSE 0
#define TRUE 1
/* ****************************************************************************************** */
#define ERROR -1
#define OK 0
/* ****************************************************************************************** */
#define MAX_SIZE_NAME 32
#define NONE_LINE  0
/* ****************************************************************************************** */
#define FLAG_EXTERN 2
#define FLAG_ENTRY 1
#define FLAG_UNKOWN 0
/* ****************************************************************************************** */
typedef struct checkpoint {
	char name[MAX_SIZE_NAME];
	int number_line;
	int status_flag;
	struct checkpoint * next; 
}checkpoint;
/* ****************************************************************************************** */
int flag_has_any_extern = FALSE;
int flag_has_any_entry = FALSE;
/* ****************************************************************************************** */
checkpoint * head_checkpoints = NULL;
/* ****************************************************************************************** */
void del_output_files_if_exists(void)
{
	remove("ps.ent");
	remove("ps.ext");
}
/* ****************************************************************************************** */
checkpoint * find_by_name(char * name)
{
	checkpoint * node = head_checkpoints;
	for(; node != NULL; node = node->next)
		if(is_equals_strs(node->name, name))
			return node;
	return NULL;
}
/* ****************************************************************************************** */
void create_checkpoint(char * name)
{
	checkpoint * node = head_checkpoints;
	if(find_by_name(name) != NULL)return;
	if(head_checkpoints == NULL)
	{
		head_checkpoints = (checkpoint *)malloc(sizeof(checkpoint));
		head_checkpoints->status_flag = FLAG_UNKOWN;
		strs_copy(name, head_checkpoints->name);
	}
	else {
		for(; node->next != NULL; node = node->next);
		node->next = (checkpoint *)malloc(sizeof(checkpoint));
		node->next->status_flag = FLAG_UNKOWN;
		strs_copy(name, node->next->name);
	}
}
/* ****************************************************************************************** */
void status_extern(char * name)
{
    checkpoint * node_extern = find_by_name(name);
	FILE * temp = fopen("ps.ext", "w");
	fclose(temp);
	flag_has_any_extern = TRUE;
	if(node_extern == NULL)
	{
			create_checkpoint(name);
			status_extern(name);
	}
	else node_extern->status_flag = FLAG_EXTERN;
}
/* ****************************************************************************************** */
void status_entry(char * name)
{
	checkpoint * node_entry = find_by_name(name);
	flag_has_any_entry = TRUE;
	if(node_entry == NULL)
	{
			create_checkpoint(name);
			status_entry(name);
	}
	else node_entry->status_flag = FLAG_ENTRY;
}
/* ****************************************************************************************** */
int get_status_flag_of_type_checkpoint(char * name)
{
	checkpoint * current_node = find_by_name(name);
	if(current_node == NULL)return ERROR;
	return current_node->status_flag;
}
/* ****************************************************************************************** */
void set_number_line(char * name, int number_line)
{
	checkpoint * current_node = find_by_name(name);
	if(current_node == NULL)
	{
		create_checkpoint(name);
		set_number_line(name, number_line);
	}
	else current_node->number_line = number_line;
}
/* ****************************************************************************************** */
int get_number_line(char * name)
{
	checkpoint * current_node = find_by_name(name);
	if(current_node == NULL)return ERROR;
	return current_node->number_line;
}
/* ****************************************************************************************** */
int is_extern(char * name)
{
	return get_status_flag_of_type_checkpoint(name) == FLAG_EXTERN;
}
/* ****************************************************************************************** */
int is_entry(char * name)
{
	return get_status_flag_of_type_checkpoint(name) == FLAG_ENTRY;
}
/* ****************************************************************************************** */
void free_checkpoints(void)
{
	checkpoint * node = head_checkpoints, * prev_node = NULL;
	for(; node != NULL; prev_node = node, node = node->next, free(prev_node));
	prev_node = head_checkpoints = NULL;
}
/* ****************************************************************************************** */
void print_checkpoints_we_have(void)
{ /* temp function, AFTER DELETE THIS LINE */
	checkpoint * node = head_checkpoints;
	int count = 0, count_unknown = 0, count_entry = 0, count_extern = 0;
	for(; node != NULL; node = node->next, count++)
		if(node->status_flag == 1)count_entry++;
		else if(node->status_flag == 2)count_extern++;
		else count_unknown++;
	printf("Your have %d checkpoints\nentry checkpoints = %d\nextern checkpoints = %d\nunsigned checkpoints = %d\n", count, count_entry, count_extern, count_unknown);
	for(node = head_checkpoints; node != NULL; node = node->next){
		printf("\nname: %s\nstatus = ", node->name);
		switch(node->status_flag){
			case 1:printf("entry\n");break;
			case 2:printf("extern\n");break;
			default:printf("unsigned\n");break;
		}
		if(node->status_flag != 2)
			printf("number line: %d\n", node->number_line);
	}
}
/* ****************************************************************************************** */
void write_entry_checkpoints_if_exists(void)
{
	FILE * file;
	checkpoint * node;
	if(flag_has_any_entry == FALSE)return;
	file = fopen("ps.ent", "w");
	for(node = head_checkpoints; node != NULL; node = node->next)
		if(node->status_flag == 1)
			fprintf(file, "%s %d\n", node->name, node->number_line);
	fclose(file);
}
/* ****************************************************************************************** */
int is_has_any_extern(void)
{
	return flag_has_any_extern;
}
/* ****************************************************************************************** */