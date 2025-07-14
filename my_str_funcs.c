#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* ****************************************************************************************** */
#define TRUE 1
#define FALSE 0
/* ****************************************************************************************** */
#define ERROR -1
#define OK 0
/* ****************************************************************************************** */


int str_len(char * str)
{
	int i = 0;
	for(; *(str + i); i++);
	return i;
}
/* ****************************************************************************************** */
void strs_copy(char * from, char * into)
{
    while((*into++=*from++));
}
/* ****************************************************************************************** */
void strs_subcopy(char * from, char * into, int start, int stop)
{
	int i = 0, j;
	for(j = start; j < stop;j++)
		into[i++] = from[j];
	into[i] = '\0';
}
/* ****************************************************************************************** */
/*void strs_subcopy(char * from, char * into, int start)
{
	strs_subcopy(from, into, start, strlen(into));
}*/
/* ****************************************************************************************** */
void strs_cat(char * from, char * into)
{
	strs_copy(from, into + str_len(into));
}
/* ****************************************************************************************** */
int is_empty(char * str)
{
	return *str == '\0' ? TRUE : FALSE;
}
/* ****************************************************************************************** */
void str_clean(char * str)
{
	for(; *str; ++str)*str = '\0';
}
/* ****************************************************************************************** */
/* ****************************************************************************************** */
void substring(char * from, char * into, int index_start, int index_end)
{
	if(index_end - index_start >= strlen(into))
		strs_subcopy(from, into, index_start, strlen(into) + index_start);
	else
		strs_subcopy(from, into, index_start, index_end);
}
/* ****************************************************************************************** */
int is_equals_strs(char * str1, char * str2)
{
	if(str_len(str1) != str_len(str2))return FALSE;
	for(; *str1; ++str1, ++str2)
		if(*str1 != *str2)
			return FALSE;
	return TRUE;
}
/* ****************************************************************************************** */
int str_num_to_int(char * str)
{
	int number = 0;
	int is_neg = FALSE;
	for(;*str;++str)
		if(*str == '-')
			is_neg = TRUE;
		else if(*str == '+')continue;
		else if(isdigit(*str))
			number = 10 * number + (*str - '0');
	return is_neg ? number * -1 : number;
}
/* ****************************************************************************************** */
int find_first_index_of_char(char * str, char ch)
{
	int i = 0;
	for(; *(str + i); i++)
		if(str[i] == ch)
			return i;
	return ERROR;
}
/* ****************************************************************************************** */
int find_last_index_of_char(char * str, char ch)
{
	int i = 0, index_found;
	index_found = ERROR;
	for(; *(str + i); i++)
		if(str[i] == ch)
			index_found = i;
	return index_found;
}
/* ****************************************************************************************** */
int count_char_in_str(char * str, char ch)
{
	int count = 0, i;
	for(i = 0; *(str + i); i++)
		if(str[i] == ch)
			count++;
	return count;
}
/* ****************************************************************************************** */
void del_whitespaces_in_left(char * str)
{
	int i = 0;
	if(is_empty(str))return;
	if(str[0] != ' ' && str[0] != '\t')return;
	for(; str[i] == ' ' || str[i] == '\t';i++);
	strs_copy(str + i, str);
}
/* ****************************************************************************************** */
int is_exists(char * str, char ch)
{
	for(;*str; ++str)
		if(*str == ch)
			return TRUE;
	return FALSE;
}
/* ****************************************************************************************** */
void del_all_whitespaces(char * str)
{
	int i, j;
	if(is_empty(str))return;
	if(!is_exists(str, ' '))return;
	for(i = 0, j = 1; str[j] != '\0';)
		if(i == j)j++;
	else if(str[i] != ' ')i++;
	else if(str[i] == ' ' && str[j] == ' ')j++;
	else if(str[i] == ' ' && str[j] != ' ')str[i++] = str[j++];
	str[i] = '\0';
}
/* ****************************************************************************************** */
int is_in_to(char * main_str, char * sub_str)
{
	int i = 0, j = 0;
	int size_main_str = str_len(main_str), size_sub_str = str_len(sub_str);
	if(is_empty(main_str) || is_empty(sub_str))return FALSE;
	while(size_main_str - i >= size_sub_str - j)
	{
		if(j > 0 && sub_str[j] != main_str[i])
		{
			j = 0;
			i++;
		}
		else if(sub_str[j] != main_str[i])i++;
		else if(sub_str[j] == main_str[i])
		{
			j++;
			i++;
		}
		if(j == size_sub_str)return TRUE;
	}
	return FALSE;
}
/* ****************************************************************************************** */
int is_has_only_whitespaces(char * str)
{
	int i = 0;
	/*char whitespace = ' ';
	char tab = '\t';
	char new_line = '\n';*/
	for(; *(str + i); i++)
		if(isalnum(str[i]))return FALSE;
		/*if(str[i] != whitespace && str[i] != tab && str[i] != new_line)return FALSE;*/
	return TRUE;
}
/* ****************************************************************************************** */