#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "my_str_funcs.h"

#define TRUE 1
#define FALSE 0

#define ERROR -1
#define OK 0

#define MAX_LINES_FOR_MACRS 150
#define MAX_LEN_NAME_MACRS 16
#define MAX_LINES_INTO_MACRO 15

typedef struct macrs_story {
	struct macrs_story * next;
	char name_macrs[MAX_LEN_NAME_MACRS];
	char lines_code[MAX_LINES_INTO_MACRO][MAX_LINES_FOR_MACRS];
	int index_line_code;
}macrs;

macrs * head_macrs = NULL;
macrs * last_macrs = NULL;

macrs * get_macrs_by_name(char * name)
{
	macrs * node = NULL;
	for(node = head_macrs; node != NULL; node = node->next)
		if(is_equals_strs(name, node->name_macrs))
			return node;
	return NULL;
}

int is_exists_macrs(char * name)
{
	return get_macrs_by_name(name) != NULL;
}

void create_macrs(char * name)
{
	macrs * node = NULL, * prev_node = NULL;
	if(is_exists_macrs(name))return;
	for(node = head_macrs; node != NULL; prev_node = node, node = node->next);
	node = (macrs *)malloc(sizeof(macrs));
	strs_copy(name, node->name_macrs);
	node->index_line_code = 0;
	last_macrs = node;
	if(head_macrs == NULL)
		head_macrs = node;
	else 
		prev_node->next = node;
}

void set_macrs_line_code(char * line_code)
{
	macrs * node = last_macrs;
	strs_copy(line_code, node->lines_code[node->index_line_code++]);
}

int get_count_lines_code_from_macro(char * name)
{
	macrs * node = NULL;
	for(node = head_macrs; node != NULL ; node = node->next)
		if(is_equals_strs(node->name_macrs, name))return node->index_line_code;
	return 0;
}

char * get_macrs_line_code(char * name, int index_line)
{
	macrs * node = NULL;
	for(node = head_macrs; node != NULL ; node = node->next)
		if(is_equals_strs(node->name_macrs, name))return node->lines_code[index_line];
	return NULL;
}

void free_macrs(void)
{
	macrs * current_node = NULL, * del_node = NULL;
	for(current_node = head_macrs; current_node != NULL; del_node = current_node, current_node = current_node->next, free(del_node));
	del_node = NULL;
	head_macrs = NULL;
	last_macrs = NULL;
}