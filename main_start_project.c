#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/* ****************************************************************************************** */
#include "my_str_funcs.h"
#include "checkpoints_entry_extern.h"
#include "database_data_string.h"
#include "check_excepts.h"
#include "assembler.h" 
#include "macrs.h"
#include "pre_proccessor.h"
/* ****************************************************************************************** */
#define TRUE 1
#define FALSE 0
/* ****************************************************************************************** */
#define ERROR -1
#define OK 0
/* ****************************************************************************************** */
#define MAX_STR_LEN_MAIN 150
#define MAX_LENS_INPUT 4096
/* ****************************************************************************************** */
#define NAME_FUNC 5
#define NAME_VAR 10
#define NAME_REG 3
#define NAME_ENTRY 5
#define NAME_PTR 10
/* ****************************************************************************************** */
#define SIZE_LINE_CODE 4
#define MAX_ARGS_PARSING 4
/* ****************************************************************************************** */
/* for colors letters in output print */
#define RESET       "\x1b[0m"
#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"
#define YELLOW      "\x1b[33m"
#define BLUE        "\x1b[34m"
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define WHITE       "\x1b[37m"
/* ****************************************************************************************** */
#define MAX_SIZE_NAMES 32
#define MAX_SIZE_VALUES 90
/* ****************************************************************************************** */
int size_num_int(int num)
{
	if(num == 0)
		return 0;
	return 1 + size_num_int(num / 10);
}
/* ****************************************************************************************** */
void clean_buffer(void)
{
	char t = '\0';
	while((t = getc(stdin)) != '\n' && t != '\0' && t != EOF); /* when ';' in line command */
}
/* ****************************************************************************************** */
int is_has_comma(char * str)
{
	return is_exists(str, ',');
}
/* ****************************************************************************************** */
int get_index_of_comma(char * str)
{
	return find_first_index_of_char(str, ',');
}
/* ****************************************************************************************** */
int is_has_colon(char * str)
{
	return is_exists(str, ':');
}
/* ****************************************************************************************** */
int get_index_of_colon(char * str)
{
	return find_first_index_of_char(str, ':');
}
/* ****************************************************************************************** */
int is_has_dot(char * str)
{
	return is_exists(str, '.');
}
/* ****************************************************************************************** */
int get_index_of_dot(char * str)
{
	return find_first_index_of_char(str, '.');
}
/* ****************************************************************************************** */
int is_has_hashtag(char * str)
{
	return is_exists(str, '#');
}
/* ****************************************************************************************** */
int get_index_of_hashtag(char * str)
{
	return find_first_index_of_char(str, '#');
}
/* ****************************************************************************************** */
int is_get_number(char * str)
{
	if(str[0] == '-' || str[0] == '+')
		return isdigit(str[1]);
	return isdigit(str[0]);
}
/* ****************************************************************************************** */
int is_get_chars(char * str)
{
	return find_first_index_of_char(str, '"');
}
/* ****************************************************************************************** */
int end_of_string(char * str)
{
	return find_last_index_of_char(str, '"');
}
/* ****************************************************************************************** */
int is_has_star(char * str)
{
	return find_first_index_of_char(str, '*');
}
/* ****************************************************************************************** */
int is_has_two_stars(char * str)
{
	return find_first_index_of_char(str, '*') != find_last_index_of_char(str, '*');
}
/* ****************************************************************************************** */
int is_reg(char * str)
{
	if(str[0] == '*')
		return strlen(str) > 2 && str[1] == 'r' && isdigit(str[2]) && str[2] - '0' < 8;
	return strlen(str) > 1 && str[0] == 'r' && isdigit(str[1]) && str[1] - '0' < 8;
}
/* ****************************************************************************************** */
int get_index_end_of_word(char * str)
{
	int count = 0;
	int len = strlen(str);
	while(count < len && isalnum(*str++))count++;
	return count;
}
/* ****************************************************************************************** */
int get_index_end_of_number(char * str)
{
	int count = 0;
	int len = strlen(str);
	if(len && *str == '#')count++;
	if(len && (*str == '+' || *str == '-'))count++;
	while(count < len && isdigit(*str++))count++;
	return count;
}
/* ****************************************************************************************** */
int get_index_first_letter(char * str)
{
	int count = 0;
	while(!isalpha(*str++))count++;
	return count;
}
/* ****************************************************************************************** */
int currecting_number_line(char * cmd, int number_line)
{
	char copy_cmd[MAX_SIZE_VALUES];
	char delim[] = " ,\t\n\0";
	char * token;
	int flag_if_has_simple_reg = FALSE;
	int flag_if_has_reg_with_star = FALSE;
	if(is_has_only_whitespaces(cmd))return number_line;
	strs_copy(cmd, copy_cmd);
	if(is_get_chars(copy_cmd) != ERROR)
		return number_line + end_of_string(copy_cmd) - is_get_chars(copy_cmd) - 1;	
	for(token = strtok(copy_cmd, delim); token != NULL; token = strtok(NULL, delim)){
		if(check_is_name_of_registers(token))
			if(token[0] == '*'){
				number_line += flag_if_has_reg_with_star ? 0 : 1;
				flag_if_has_reg_with_star = TRUE;
			}
			else {
				number_line += flag_if_has_simple_reg ? 0 : 1;
				flag_if_has_simple_reg = TRUE;
			}
		else if(!(is_has_colon(token) || is_has_dot(token)))number_line++;
	}
	return number_line;
}
/* ****************************************************************************************** */
int check_name_checkpoint(char * name)
{
        FILE *file=fopen("ps.logs","a");
        if(file==NULL)
            file=fopen("ps.logs","w");
	if(check_is_name_of_registers(name))
	{
		fprintf(file,"ERROR!!! You cannot give a checkpointer a name {%s} equivalent to a processor register.\n", name);
                fclose(file);
		return ERROR;
	}
	if(is_this_name_equals_by_names_of_funcs(name))
	{
		fprintf(file,"ERROR!!! You cannot give a checkpointer a name {%s} equals as names of assembler functions.\n", name);
                fclose(file);
		return ERROR;
	}
	if(!is_valid_first_char_in_name_of_new_checkpoint(name))
	{
		fprintf(file,"ERROR!!! The checkpointer's name must begin with a letter.\n");
  		fclose(file);		
 		return ERROR;
	}
	if(!is_valid_size_name_of_new_checkpoint(name))
	{
		fprintf(file,"ERROR!!! The checkpointer name is too long.{%d characters} Make sure the size is no more than 31 characters.\n"
		, strlen(name));
                fclose(file);
		return ERROR;
	}
        fclose(file);
	return OK;
}
/* ****************************************************************************************** */
int check_number(char * number)
{
        FILE *file=fopen("ps.logs","a");
        if(file==NULL)
            file=fopen("ps.logs","w");
	if(check_is_valid_number_with_hashtag(number) || check_is_valid_number(number)){fclose(file);return OK;}
	fprintf(file,"ERROR!!! The {%s} isn't a real number.\n", number);
        fclose(file); 
	return ERROR;
}
/* ****************************************************************************************** */
int check_command_with_dot(char * cmd)
{
	FILE *file=fopen("ps.logs","a");
        if(file==NULL)
            file=fopen("ps.logs","w");
	if(is_it_entry_or_extern(cmd) || is_it_data_or_string(cmd)){fclose(file);return OK;}
	fprintf(file,"ERROR!!! This {%s} is an invalid command starting with a dot.\n", cmd);
	fprintf(file,"To correctly declare a new variable, {Integer: .data}/{String: .string}.\n");
	fprintf(file,"To announce new internal {.entry} or existing external {.extern} checkpoints.\n");
        fclose(file);
	return ERROR;
}
/* ****************************************************************************************** */
int check_opcode(char * opcode)
{
	FILE *file=fopen("ps.logs","a");
        if(file==NULL)
            file=fopen("ps.logs","w");
	if(is_this_name_equals_by_names_of_funcs(opcode)){fclose(file);return OK;}
	fprintf(file,"ERROR!!! Your opcode {%s} is wrong.\n", opcode);
	fclose(file);	
	return ERROR;
}
/* ****************************************************************************************** */
int parsing_and_check_cmd(char * cmd, int number_line)
{
	char checkpoint_name[MAX_SIZE_NAMES], opcode[MAX_SIZE_NAMES], first_param[MAX_SIZE_NAMES], second_param[MAX_SIZE_NAMES], name_with_dot[MAX_SIZE_NAMES];
	char array_values[MAX_SIZE_VALUES] = "";
	char delim[] = " ,\t\n\0";
	char * token;
	char copy_cmd[MAX_STR_LEN_MAIN];
	int status_check_result = 0;
	int start_str = is_get_chars(cmd);
	int end_str = end_of_string(cmd);
	str_clean(checkpoint_name);
	str_clean(opcode);
	str_clean(first_param);
	str_clean(second_param);
	str_clean(name_with_dot);
	strs_copy(cmd, copy_cmd);
	if(start_str == ERROR)start_str = MAX_SIZE_NAMES; /* like as Integer.MAX_VALUE form Java */
	
	for(token = strtok(copy_cmd, delim); token != NULL && !status_check_result; token = strtok(NULL, delim))
	{
		if(is_has_colon(token)){
			strs_subcopy(token, checkpoint_name, 0, strlen(token) - 1);
			if(check_name_checkpoint(checkpoint_name) || is_exists_macro(checkpoint_name))return ERROR;
            set_number_line(checkpoint_name, number_line);
		}
		else if(is_has_dot(token))
		{
			if(check_command_with_dot(token))return ERROR;
			if(strlen(opcode) != 0)return ERROR;
			switch(is_it_data_or_string(token)){
				case 1:for(token = strtok(NULL, delim); token != NULL; token = strtok(NULL, delim)){if(check_number(token))return ERROR;
				if(!is_has_hashtag(token))strcat(array_values, "#");
				strcat(array_values, token);
				}
				if(strlen(checkpoint_name))set_values(checkpoint_name, array_values, 1);
				break;
				case 2:
				if(start_str == end_str)return ERROR;
				strs_subcopy(cmd, array_values, start_str, end_str + 1);
				if(strlen(checkpoint_name))set_values(checkpoint_name, array_values, 2);
				break;
			}
			break;
		}
		else if(strlen(opcode) == 0)
		{
			strs_copy(token, opcode);
			if(strlen(checkpoint_name))set_number_line(checkpoint_name, number_line);
			if(check_opcode(opcode) == ERROR)return ERROR;
		}
		else if(strlen(first_param) == 0){
			strs_copy(token, first_param);
			if(is_exists_macro(first_param))return ERROR;
			if(check_number_of_opcode(first_param) != ERROR)return ERROR;
			if(is_it_data_or_string(first_param))return ERROR;
		}
		else {
			strs_copy(token, second_param);
			if(is_exists_macro(second_param))return ERROR;
			if(check_number_of_opcode(second_param) != ERROR)return ERROR;
			if(is_it_data_or_string(second_param))return ERROR;
		}
	}
	return OK;
}/* ****************************************************************************************** */
int check_cmd_entry_or_extern(char * cmd)
{
	char delim[] = " ,\t\n\0";
	char * token, * checkpoint_name;
	char copy_cmd[MAX_STR_LEN_MAIN];
	str_clean(copy_cmd);
	strs_copy(cmd, copy_cmd);
	token = strtok(copy_cmd, delim);
	checkpoint_name = strtok(NULL, delim);
	switch(is_it_entry_or_extern(token)){
		case 1: if(check_name_checkpoint(checkpoint_name))return ERROR; 
				status_entry(checkpoint_name); break;
		case 2: if(check_name_checkpoint(checkpoint_name))return ERROR; 
				status_extern(checkpoint_name); break;
		default: return FALSE;
	}
	return TRUE;
}
/* ****************************************************************************************** */
void write_extern_checkpoint(char * name, int number_line)
{
	FILE * file = fopen("ps.ext", "a");
	fprintf(file, "%s %d\n", name, number_line);
	fclose(file);
}
/* ****************************************************************************************** */
void check_is_exists_extern_checkpoints(char * cmd, int number_line)
{
	char delim[] = " ,\t\n\0";
	char * token;
	char copy_cmd[MAX_STR_LEN_MAIN];
	if(is_has_any_extern() == FALSE)return;
	str_clean(copy_cmd);
	strs_copy(cmd, copy_cmd);
	for(token = strtok(copy_cmd, delim); token != NULL; number_line += is_has_colon(token) ? 0 : 1, token = strtok(NULL, delim))
		if(is_extern(token))
			write_extern_checkpoint(token, number_line);
}

void get_new_macro_name(char * cmd)
{
	char delim[] = " \t\n\0";
	char * token = strtok(cmd, delim);
	token = strtok(NULL, delim);
	if(!isalpha(token[0]) || check_is_name_of_registers(token) || is_it_entry_or_extern(token) || is_it_data_or_string(token)
		|| check_number_of_opcode(token) != ERROR || is_exists_macrs(token))
		printf(RED "ERROR!!! name " WHITE "{%s}" RED " is already taken or is invalid name." RESET "\n", token);
	else
		create_macrs(token);
}

int is_macro_name(char * cmd)
{
	char delim[] = " ,\t\n\0";
	char copy_cmd[MAX_STR_LEN_MAIN];
	char * name_token;
	str_clean(copy_cmd);
	if(is_has_only_whitespaces(cmd))return FALSE;
	strs_copy(cmd, copy_cmd); /* to keep the original string unchanged (the strtok function changes it) */
	name_token = strtok(copy_cmd, delim);
	return is_exists_macrs(name_token);
}

int input_macro_lines_code(char str_main[][MAX_STR_LEN_MAIN], int i)
{
	char delim[] = " ,\t\n\0";
	char copy_name[MAX_STR_LEN_MAIN];
	int lines = 0, j;
	char * name_token;
	str_clean(copy_name);
	strs_copy(str_main[i], copy_name);
	name_token = strtok(copy_name, delim);
	lines = get_count_lines_code_from_macro(name_token);
	for(j = 0; j < lines; j++)
		strs_copy(get_macrs_line_code(name_token, j), str_main[i++]);
	return lines;
}
/* ****************************************************************************************** */
int main(void)
{
	char str[MAX_LENS_INPUT][MAX_STR_LEN_MAIN];
	int i = 0, j = 0;
	int check_lines_macro = FALSE;
	int status_result_parsing = 0;
	int number_line = 100;
	int number_current_line = 100;
	int number_line_semantica = 100; /* for Roi */
	int flag_error_semantica = FALSE; /* for Roi */
	int flag_get_str = FALSE;
	int flag_get_macr = FALSE;
	char c = '\0';
	FILE *file=fopen("ps.logs","a");
        if(file==NULL)
            file=fopen("ps.logs","w");
	del_output_files_if_exists();
	remove("errors.am");
	if(pre_proccess())return ERROR;

	file = fopen("pre_proccessing_file", "r");
	if(file == NULL)
	{
		fprintf(file,"ERROR!!! cannot open file for reading.\n");
		return ERROR;
	}
	for(; i < MAX_LENS_INPUT; i++, j = 0, flag_get_str = FALSE)
	{
		if(check_lines_macro){
			check_lines_macro--;
			goto chks;
		}
		while((c = getc(file)) != '\n' && c != '\0' && c != EOF && (c != ';' || flag_get_str) && j < MAX_STR_LEN_MAIN - 1){
			if(c == '"')
				flag_get_str = flag_get_str ? FALSE : TRUE;
			str[i][j++] = c;
		}
		if(c == ';')
			while((c = getc(file)) != '\n' && c != '\0' && c != EOF);
		str[i][j] = '\0';
		if(j == 0 && c == EOF)break;
		del_whitespaces_in_left(str[i]);
		if(is_macro_name(str[i]))
		{
			check_lines_macro = input_macro_lines_code(str, i--);
			continue;
		}
chks:	if(is_has_only_whitespaces(str[i]))
			str_clean(str[i--]);
		else if(is_equals_strs(str[i], "endmacr"))
			if(flag_get_macr == FALSE){
				fprintf(file,"ERROR!!! You can't use endmacr not started with declaration for macr.\n" );
				status_result_parsing = ERROR;
			}
			else {
				flag_get_macr = FALSE;
				str_clean(str[i--]);
			}
		else if(is_in_to(str[i], "macr"))
			if(flag_get_macr == TRUE){
				fprintf(file,"ERROR!!! You can't open a macro inside a macro.\n");
				status_result_parsing = ERROR;
			}
			else {
				flag_get_macr = TRUE;
				get_new_macro_name(str[i]);
				str_clean(str[i--]);
			}
		else if(flag_get_macr){
			set_macrs_line_code(str[i]);
			str_clean(str[i--]);
		}
		else if(is_has_dot(str[i]) && check_cmd_entry_or_extern(str[i]) > 0)
				str_clean(str[i--]);	
		else if(is_equals_strs(str[i], "stop") || c == '\0' || c == EOF)break;
		else if(parsing_and_check_cmd(str[i], number_line) == ERROR)status_result_parsing = ERROR;
		else number_line = currecting_number_line(str[i], number_line);
	}
	fclose(file);
	write_entry_checkpoints_if_exists();
	for(j = 0; j < i; number_current_line = currecting_number_line(str[j++], number_current_line))
		check_is_exists_extern_checkpoints(str[j], number_current_line);
	number_current_line = 100;
	if(status_result_parsing != ERROR){
		file=fopen("ps.ob","w");
		fprintf(file,"	32  9\n");
		fclose(file);
		for(remove("errors.am"), j = 0; j < i; j++)
			input_data(str[j], &number_line_semantica, number_current_line++, &flag_error_semantica);
	}
	 if(flag_error_semantica)clear_all();
	 else del_Log_file();
	free_checkpoints();
	free_all_nodes();
	free_macrs();
	freeLocal();
	return OK;
}
