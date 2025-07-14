#ifndef DATABASE_DATA_STRING_H
#define DATABASE_DATA_STRING_H

/* ****************************************************************************************** */
/* 
 * Sets or updates the value and status associated with a given key.
 * 
 * key:     A pointer to the key string.
 * value:   A pointer to the value string.
 * status:  An integer representing the status flag.
 */
void set_values(char *, char *, int);

/* ****************************************************************************************** */
/* 
 * Retrieves the value associated with a given key.
 * 
 * key:     A pointer to the key string.
 * 
 * Returns: A pointer to the value string if the key exists, or NULL if the key is not found.
 */
char * get_values(char *);

/* ****************************************************************************************** */
/* 
 * Retrieves the status flag associated with a given key.
 * 
 * key:     A pointer to the key string.
 * 
 * Returns: An integer representing the status flag if the key exists, or -1 if the key is not found.
 */
int get_status_flag_of_type_var(char *);

/* ****************************************************************************************** */
/* 
 * Frees all nodes in the data structure and releases allocated memory.
 */
void free_all_nodes(void);

/* ****************************************************************************************** */
/* 
 * Prints all key-value pairs and their statuses. This function is intended for debugging and
 * should be removed after testing.
 */
void temp_function_print_results(void);

/* ****************************************************************************************** */
/* 
 * Checks if a variable (key) exists in the data structure.
 * 
 * key:     A pointer to the key string.
 * 
 * Returns: 1 if the key exists, 0 otherwise.
 */
int is_exists_variable(char *);

#endif /* DATABASE_DATA_STRING_H */
