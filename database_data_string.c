#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/* ****************************************************************************************** */
#include "my_str_funcs.h"
/* ****************************************************************************************** */
#define TRUE 1
#define FALSE 0
/* ****************************************************************************************** */
#define ERROR -1
#define OK 0
/* ****************************************************************************************** */
#define MAX_SIZE_NAME 32
#define MAX_SIZE_VALUES 90
/* ****************************************************************************************** */
typedef struct node_data {
	char name[MAX_SIZE_NAME];
	char values[MAX_SIZE_VALUES];
	int status_flag; /* 1 - data integers, 2 - strings */
	struct node_data * next;
}nodes;
/* ****************************************************************************************** */
nodes * head_node_data = NULL;
/* ****************************************************************************************** */
nodes * create_new_node(char * name)
{
	nodes * node = (nodes *)malloc(sizeof(nodes));
	strs_copy(name, node->name);
	return node;
}
/* ****************************************************************************************** */
nodes * find_node_by_name(char * name)
{
	nodes * node = head_node_data;
	for(; node != NULL; node = node->next)
		if(is_equals_strs(node->name, name))
			return node;
	return NULL;
}
/* ****************************************************************************************** */
void set_values(char * name, char * values, int status_data)
{
	nodes * node = head_node_data;
	if(head_node_data == NULL){
		node = head_node_data = create_new_node(name);
		strs_copy(values, head_node_data->values);
		head_node_data->status_flag = status_data;
	}
	else {for(; node->next != NULL; node = node->next);
		node->next = create_new_node(name);
		strs_copy(values, node->next->values);
		node->next->status_flag = status_data;
	}
}
/* ****************************************************************************************** */
char * get_values(char * name)
{
	nodes * node = find_node_by_name(name);
	return node != NULL ? node->values : NULL;
}
/* ****************************************************************************************** */
int get_status_flag_of_type_var(char * name)
{
	nodes * node = find_node_by_name(name);
	return node != NULL ? node->status_flag : ERROR;
}
/* ****************************************************************************************** */
void free_all_nodes(void)
{
	nodes * current_node = head_node_data, * prev_node = NULL;
	for(; current_node != NULL; prev_node = current_node, current_node = current_node->next, free(prev_node));
	prev_node = head_node_data = NULL;
}
/* ****************************************************************************************** */
void temp_function_print_results(void)
{ /* temp function, AFTER DELETE THIS LINE */
	nodes * node = head_node_data;
	int count = 0, count_data = 0, count_str = 0;
	for(; node != NULL; node = node->next, count++)
		if(node->status_flag == 1)count_data++;
		else count_str++;
	printf("You have %d variables, %d is integers, %d is strings\n", count, count_data, count_str);
	for(node = head_node_data; node != NULL; node = node->next)
		printf("\nname: %s\nvalues: %s\n", node->name, node->values);
}
/* ****************************************************************************************** */
int is_exists_variable(char * name)
{
	nodes * node = head_node_data;
	for(; node != NULL; node = node->next)
		if(is_equals_strs(name, node->name))
			return TRUE;
	return FALSE;
}
/* ****************************************************************************************** */