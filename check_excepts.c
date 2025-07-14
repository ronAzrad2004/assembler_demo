#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/* ****************************************************************************************** */
#include "my_str_funcs.h"
/* ****************************************************************************************** */
#define ERROR -1
#define OK 0
/* ****************************************************************************************** */
#define TRUE 1
#define FALSE 0
/* ****************************************************************************************** */
#define REGS 8
#define AMOUND_FUNCS 16
/* ****************************************************************************************** */
#define FIRST_OPTION 1
#define SECOND_OPTION 2
#define NONE 0
/* ****************************************************************************************** */
#define MAX_SIZE_NAME_CHECKPOINT 31
/* ****************************************************************************************** */
int check_is_name_of_registers(char * name)
{
	char *regs_name[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};
	int i = 0;
	for(; i < REGS; i++)
		if(is_equals_strs(*(regs_name + i), name))
			return ERROR;
	return OK;
}
/* ****************************************************************************************** */
int check_number_of_opcode(char * opcode)
{
	char * opcode_names[] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", 
	"inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
	int i = 0;
	for(; i < AMOUND_FUNCS; i++)
		if(is_equals_strs(*(opcode_names + i), opcode))
			return i;
	return ERROR;
}
/* ****************************************************************************************** */
int check_is_valid_number(char * number)
{
	int i = 0;
	int len = strlen(number);
	if(number[i] == '+' || number[i] == '-')i++;
	while(i < len)
		if(!isdigit(number[i++]))
			return FALSE;
	return TRUE;
}
/* ****************************************************************************************** */
int check_is_valid_number_with_hashtag(char * number)
{
	return *number == '#' && check_is_valid_number(number + 1);
}
/* ****************************************************************************************** */
int is_it_entry_or_extern(char * name) /* if entry return 1 if extern return 2 else return 0 */
{
	if(is_equals_strs(name, ".entry"))return FIRST_OPTION;
	if(is_equals_strs(name, ".extern"))return SECOND_OPTION;
	return NONE;
}
/* ****************************************************************************************** */
int is_it_data_or_string(char * name)
{
	if(is_equals_strs(name, ".data"))return FIRST_OPTION;
	if(is_equals_strs(name, ".string"))return SECOND_OPTION;
	return NONE;
}
/* ****************************************************************************************** */
int is_valid_str(char * str)
{
	return str[strlen(str) - 1] == '\"';
}
/* ****************************************************************************************** */
int is_valid_first_char_in_name_of_new_checkpoint(char * name)
{
	return isalpha(*name);
}
/* ****************************************************************************************** */
int is_valid_size_name_of_new_checkpoint(char * name)
{
	return strlen(name) <= MAX_SIZE_NAME_CHECKPOINT;
}
/* ****************************************************************************************** */
int is_this_name_equals_by_names_of_funcs(char * name)
{
	return check_number_of_opcode(name) != ERROR;
}
/* ****************************************************************************************** */
int check_all_data_numbers(char * str)
{
	int flag_plus = FALSE, flag_minus = FALSE, flag_hashtag = FALSE;
	int j = strlen(str) - 1;
	for(; j >= 0; j--)
		if(str[j] == '+')
			if(flag_plus)return ERROR;
			else flag_plus = TRUE;
		else if(str[j] == '-')
			if(flag_minus)return ERROR;
			else flag_minus = TRUE;
		else if(str[j] == '#')
			if(flag_hashtag)return ERROR;
			else flag_hashtag = TRUE;
		else if(str[j] == ',')
			flag_hashtag = flag_minus = flag_plus = FALSE;
		else if(str[j] != ' ' && !isdigit(str[j]))return ERROR;
	return OK;
}
/* ****************************************************************************************** */