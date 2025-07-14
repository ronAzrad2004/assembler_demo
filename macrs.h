#ifndef MACRS_H
#define MACRS_H

/* ****************************************************************************************** */
/* 
 * Checks if a macro with the given name exists.
 * 
 * name:    A pointer to the macro name string.
 * 
 * Returns: 1 if the macro exists, 0 otherwise.
 */
int is_exists_macrs(char *);

/* ****************************************************************************************** */
/* 
 * Creates a new macro with the given name.
 * 
 * name:    A pointer to the macro name string.
 */
void create_macrs(char *);

/* ****************************************************************************************** */
/* 
 * Sets the line code for a given macro.
 * 
 * line_code: A pointer to the line code string.
 */
void set_macrs_line_code(char *);

/* ****************************************************************************************** */
/* 
 * Gets the count of line codes associated with a given macro.
 * 
 * name:    A pointer to the macro name string.
 * 
 * Returns: The count of line codes associated with the macro.
 */
int get_count_lines_code_from_macro(char *);

/* ****************************************************************************************** */
/* 
 * Retrieves a specific line code from a macro.
 * 
 * name:    A pointer to the macro name string.
 * index:   The index of the line code to retrieve.
 * 
 * Returns: A pointer to the line code string at the specified index, or NULL if the index is invalid.
 */
char * get_macrs_line_code(char *, int);

/* ****************************************************************************************** */
/* 
 * Frees all resources associated with macros and releases allocated memory.
 */
void free_macrs(void);

#endif /* MACRS_H */
