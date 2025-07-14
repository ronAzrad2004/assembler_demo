#ifndef MY_STR_FUNCS_H
#define MY_STR_FUNCS_H

/* ****************************************************************************************** */
/* 
 * Computes the length of a string.
 * 
 * str:     A pointer to the input string.
 * 
 * Returns: The length of the string.
 */
int str_len(char *);

/* ****************************************************************************************** */
/* 
 * Copies the contents of one string to another.
 * 
 * dest:    A pointer to the destination string.
 * src:     A pointer to the source string.
 */
void strs_copy(char *, char *);

/* ****************************************************************************************** */
/* 
 * Copies a substring from one string to another.
 * 
 * dest:    A pointer to the destination string.
 * src:     A pointer to the source string.
 * start:   The starting index of the substring in the source string.
 * length:  The number of characters to copy from the source string.
 */
void strs_subcopy(char *, char *, int, int);

/* ****************************************************************************************** */
/* 
 * Concatenates one string to the end of another.
 * 
 * dest:    A pointer to the destination string.
 * src:     A pointer to the source string to be appended.
 */
void strs_cat(char *, char *);

/* ****************************************************************************************** */
/* 
 * Checks if a string is empty (i.e., it is NULL or contains no characters).
 * 
 * str:     A pointer to the input string.
 * 
 * Returns: 1 if the string is empty, 0 otherwise.
 */
int is_empty(char *);

/* ****************************************************************************************** */
/* 
 * Removes leading and trailing whitespace from a string.
 * 
 * str:     A pointer to the string to be cleaned.
 */
void str_clean(char *);

/* ****************************************************************************************** */
/* 
 * Extracts a substring from a string.
 * 
 * dest:    A pointer to the destination string.
 * src:     A pointer to the source string.
 * start:   The starting index of the substring in the source string.
 * length:  The number of characters to extract.
 */
void substring(char *, char *, int, int);

/* ****************************************************************************************** */
/* 
 * Checks if two strings are equal.
 * 
 * str1:    A pointer to the first string.
 * str2:    A pointer to the second string.
 * 
 * Returns: 1 if the strings are equal, 0 otherwise.
 */
int is_equals_strs(char *, char *);

/* ****************************************************************************************** */
/* 
 * Converts a string representing a number to an integer.
 * 
 * str:     A pointer to the string representing the number.
 * 
 * Returns: The integer value of the string.
 */
int str_num_to_int(char *);

/* ****************************************************************************************** */
/* 
 * Finds the first occurrence of a character in a string.
 * 
 * str:     A pointer to the input string.
 * ch:      The character to search for.
 * 
 * Returns: The index of the first occurrence of the character, or -1 if not found.
 */
int find_first_index_of_char(char *, char);

/* ****************************************************************************************** */
/* 
 * Finds the last occurrence of a character in a string.
 * 
 * str:     A pointer to the input string.
 * ch:      The character to search for.
 * 
 * Returns: The index of the last occurrence of the character, or -1 if not found.
 */
int find_last_index_of_char(char *, char);

/* ****************************************************************************************** */
/* 
 * Counts the number of occurrences of a character in a string.
 * 
 * str:     A pointer to the input string.
 * ch:      The character to count.
 * 
 * Returns: The number of occurrences of the character in the string.
 */
int count_char_in_str(char *, char);

/* ****************************************************************************************** */
/* 
 * Removes leading whitespace from a string.
 * 
 * str:     A pointer to the string to be modified.
 */
void del_whitespaces_in_left(char *);

/* ****************************************************************************************** */
/* 
 * Checks if a character exists in a string.
 * 
 * str:     A pointer to the input string.
 * ch:      The character to search for.
 * 
 * Returns: 1 if the character exists in the string, 0 otherwise.
 */
int is_exists(char *, char);

/* ****************************************************************************************** */
/* 
 * Removes all whitespace characters from a string.
 * 
 * str:     A pointer to the string to be modified.
 */
void del_all_whitespaces(char *);

/* ****************************************************************************************** */
/* 
 * Checks if one string is a substring of another.
 * 
 * str1:    A pointer to the potential substring.
 * str2:    A pointer to the string to search in.
 * 
 * Returns: 1 if str1 is a substring of str2, 0 otherwise.
 */
int is_in_to(char *, char *);

/* ****************************************************************************************** */
/* 
 * Checks if a string contains only whitespace characters.
 * 
 * str:     A pointer to the string to check.
 * 
 * Returns: 1 if the string contains only whitespace, 0 otherwise.
 */
int is_has_only_whitespaces(char *);

#endif /* MY_STR_FUNCS_H */
