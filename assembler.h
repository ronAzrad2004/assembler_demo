#ifndef ASSEMBLER_H
#define ASSEMBLER_H

/**********************************************************************
* Constants
**********************************************************************/
#define MAX_LENGTH 30    /* Maximum length for a single token */
#define MAX_SIZE 81      /* Maximum line size for input */
#define KEY -999         /* Special key identifier */
#define SEC -10          /* Secondary key identifier */

/**********************************************************************
* File paths
**********************************************************************/
#define OUTPUT_1 "ps.ob"   /* Output file path for object code */
#define EXT_PATH "ps.ext"  /* File path for external references */
#define ENT_PATH "ps.ent"  /* File path for entry points */
#define LOGS "ps.logs"     /* Log file path */

/**********************************************************************
* Function Declarations
**********************************************************************/

/**********************************************************************
* Function: removeFirstChar
* Description: Removes the first character from a string.
* Parameters:
*   - char *str: Pointer to the string from which the first character
*                will be removed.
**********************************************************************/
void removeFirstChar(char *str);

/**********************************************************************
* Function: opCode
* Description: Returns the opcode corresponding to a given string.
* Parameters:
*   - char *str: Pointer to the string containing the operation code.
* Returns: The corresponding opcode as an integer.
**********************************************************************/
int opCode(char *str);

/**********************************************************************
* Function: check_sort
* Description: Identifies the sort type of the given operand string.
* Parameters:
*   - char *str: Pointer to the operand string.
* Returns: An integer indicating the sort type.
**********************************************************************/
int check_sort(char *str);

/**********************************************************************
* Function: del_extern_file
* Description: Deletes the external references file (ps.ext).
**********************************************************************/
void del_extern_file(void);

/**********************************************************************
* Function: del_entry_file
* Description: Deletes the entry points file (ps.ent).
**********************************************************************/
void del_entry_file(void);

/**********************************************************************
* Function: del_octal_file
* Description: Deletes the object code file (ps.ob).
**********************************************************************/
void del_octal_file(void);

/**********************************************************************
* Function: del_Log_file
* Description: Deletes the log file (ps.logs).
**********************************************************************/
void del_Log_file(void);

/**********************************************************************
* Function: clear_all
* Description: Clears all generated files (object code, externals,
*              entries, and logs).
**********************************************************************/
void clear_all(void);

/**********************************************************************
* Function: split
* Description: Splits a line of input into up to three tokens.
* Parameters:
*   - char *str: Pointer to the input string.
*   - char s[][MAX_LENGTH]: Array to hold the split tokens.
**********************************************************************/
void split(char *str, char s[][MAX_LENGTH]);

/**********************************************************************
* Function: checkLine
* Description: Validates the syntax of a line of input.
* Parameters:
*   - char *str: Pointer to the line of input to be checked.
* Returns: 1 if the line is valid, 0 otherwise.
**********************************************************************/
int checkLine(char *str);

/**********************************************************************
* Function: code_compiled
* Description: Checks if the operation code and sort codes are valid.
* Parameters:
*   - int first_socode: The sort code for the first operand.
*   - int opcode: The operation code.
*   - int second_socode: The sort code for the second operand.
* Returns: 1 if the combination is valid, 0 otherwise.
**********************************************************************/
int code_compiled(int first_socode, int opcode, int second_socode);

/**********************************************************************
* Function: short_int_to_octal
* Description: Converts a short integer to an octal string.
* Parameters:
*   - unsigned short int decimalNumber: The decimal number to convert.
*   - char *octalString: Pointer to the resulting octal string.
**********************************************************************/
void short_int_to_octal(unsigned short int decimalNumber, char *octalString);

/**********************************************************************
* Function: write_Octal_values_by_d
* Description: Writes octal values for a ".data" directive to the object
*              code file.
* Parameters:
*   - int *i: Pointer to the current row index in the object file.
*   - char *str: Pointer to the string containing data values.
**********************************************************************/
void write_Octal_values_by_d(int *i, char *str);

/**********************************************************************
* Function: write_Octal_values_by_s
* Description: Writes octal values for a ".string" directive to the object
*              code file.
* Parameters:
*   - int *i: Pointer to the current row index in the object file.
*   - char *str: Pointer to the string containing the string values.
**********************************************************************/
void write_Octal_values_by_s(int *i, char *str);

/**********************************************************************
* Function: write_octal_values
* Description: Writes the octal values corresponding to machine code to
*              the object code file.
* Parameters:
*   - int i: The starting row index.
*   - int j: The ending row index.
*   - unsigned short int arr[3]: The array containing the octal values.
**********************************************************************/
void write_octal_values(int i, int j, unsigned short int arr[3]);

/**********************************************************************
* Function: getString
* Description: Extracts the data string from the input for processing.
* Parameters:
*   - char *target: Pointer to the resulting extracted string.
*   - char *str_data: Pointer to the input string containing data.
**********************************************************************/
void getString(char *target, char *str_data);

/**********************************************************************
* Function: input_data
* Description: Processes and compiles a line of assembly input.
* Parameters:
*   - char *str_data: Pointer to the input string.
*   - int *row: Pointer to the current row index.
*   - int code_line: The line number for logging errors.
*   - int *error_occured: Pointer to an error flag (1 if an error occurs).
**********************************************************************/
void input_data(char *str_data, int *row, int code_line, int *error_occured);

#endif /* ASSEMBLER_H */
