#ifndef CHECK_EXCEPTS_H
#define CHECK_EXCEPTS_H

/**********************************************************************
* Function: check_is_name_of_registers
* Description: Checks if the given string is a valid register name.
* Parameters:
*   - char *str: Pointer to the string to be checked.
* Returns: 1 if the string is a register name, 0 otherwise.
**********************************************************************/
int check_is_name_of_registers(char *str);

/**********************************************************************
* Function: check_number_of_opcode
* Description: Checks if the given string is a valid opcode.
* Parameters:
*   - char *str: Pointer to the string to be checked.
* Returns: The opcode number if valid, -1 otherwise.
**********************************************************************/
int check_number_of_opcode(char *str);

/**********************************************************************
* Function: check_is_valid_number
* Description: Checks if the given string is a valid number.
* Parameters:
*   - char *str: Pointer to the string to be checked.
* Returns: 1 if the string is a valid number, 0 otherwise.
**********************************************************************/
int check_is_valid_number(char *str);

/**********************************************************************
* Function: check_is_valid_number_with_hashtag
* Description: Checks if the given string is a valid number preceded
*              by a hashtag (#).
* Parameters:
*   - char *str: Pointer to the string to be checked.
* Returns: 1 if the string is valid, 0 otherwise.
**********************************************************************/
int check_is_valid_number_with_hashtag(char *str);

/**********************************************************************
* Function: is_it_entry_or_extern
* Description: Checks if the given string represents an "entry" or
*              "extern" directive.
* Parameters:
*   - char *str: Pointer to the string to be checked.
* Returns: 1 if the string is "entry" or "extern", 0 otherwise.
**********************************************************************/
int is_it_entry_or_extern(char *str);

/**********************************************************************
* Function: is_it_data_or_string
* Description: Checks if the given string represents a ".data" or
*              ".string" directive.
* Parameters:
*   - char *str: Pointer to the string to be checked.
* Returns: 1 if the string is ".data" or ".string", 0 otherwise.
**********************************************************************/
int is_it_data_or_string(char *str);

/**********************************************************************
* Function: is_valid_str
* Description: Checks if the given string is a valid input string.
* Parameters:
*   - char *str: Pointer to the string to be checked.
* Returns: 1 if the string is valid, 0 otherwise.
**********************************************************************/
int is_valid_str(char *str);

/**********************************************************************
* Function: is_valid_first_char_in_name_of_new_checkpoint
* Description: Checks if the first character of a checkpoint name is valid.
* Parameters:
*   - char *str: Pointer to the string representing the checkpoint name.
* Returns: 1 if the first character is valid, 0 otherwise.
**********************************************************************/
int is_valid_first_char_in_name_of_new_checkpoint(char *str);

/**********************************************************************
* Function: is_valid_size_name_of_new_checkpoint
* Description: Checks if the size of the checkpoint name is within valid limits.
* Parameters:
*   - char *str: Pointer to the string representing the checkpoint name.
* Returns: 1 if the size is valid, 0 otherwise.
**********************************************************************/
int is_valid_size_name_of_new_checkpoint(char *str);

/**********************************************************************
* Function: is_this_name_equals_by_names_of_funcs
* Description: Checks if the given name matches any predefined function names.
* Parameters:
*   - char *str: Pointer to the string representing the name.
* Returns: 1 if the name matches, 0 otherwise.
**********************************************************************/
int is_this_name_equals_by_names_of_funcs(char *str);

/**********************************************************************
* Function: check_all_data_numbers
* Description: Checks if all numbers in a .data directive are valid.
* Parameters:
*   - char *str: Pointer to the string containing the numbers.
* Returns: 1 if all numbers are valid, 0 otherwise.
**********************************************************************/
int check_all_data_numbers(char *str);

#endif /* CHECK_EXCEPTS_H */
