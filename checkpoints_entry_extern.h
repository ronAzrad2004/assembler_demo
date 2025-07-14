#ifndef CHECKPOINTS_ENTRY_EXTERN_H
#define CHECKPOINTS_ENTRY_EXTERN_H

/**********************************************************************
* Function: del_output_files_if_exists
* Description: Deletes output files if they already exist.
* Parameters: None.
* Returns: void
**********************************************************************/
void del_output_files_if_exists(void);

/**********************************************************************
* Function: create_checkpoint
* Description: Creates a new checkpoint with the specified name.
* Parameters:
*   - char *checkpoint_name: Name of the checkpoint to be created.
* Returns: void
**********************************************************************/
void create_checkpoint(char *checkpoint_name);

/**********************************************************************
* Function: status_extern
* Description: Marks a checkpoint as external.
* Parameters:
*   - char *checkpoint_name: Name of the checkpoint to be marked as external.
* Returns: void
**********************************************************************/
void status_extern(char *checkpoint_name);

/**********************************************************************
* Function: status_entry
* Description: Marks a checkpoint as an entry point.
* Parameters:
*   - char *checkpoint_name: Name of the checkpoint to be marked as an entry.
* Returns: void
**********************************************************************/
void status_entry(char *checkpoint_name);

/**********************************************************************
* Function: get_status_flag_of_type_checkpoint
* Description: Retrieves the status flag of a checkpoint.
* Parameters:
*   - char *checkpoint_name: Name of the checkpoint to retrieve the status for.
* Returns: The status flag of the checkpoint.
**********************************************************************/
int get_status_flag_of_type_checkpoint(char *checkpoint_name);

/**********************************************************************
* Function: set_number_line
* Description: Sets the line number associated with a checkpoint.
* Parameters:
*   - char *checkpoint_name: Name of the checkpoint.
*   - int line_number: Line number to set for the checkpoint.
* Returns: void
**********************************************************************/
void set_number_line(char *checkpoint_name, int line_number);

/**********************************************************************
* Function: get_number_line
* Description: Retrieves the line number associated with a checkpoint.
* Parameters:
*   - char *checkpoint_name: Name of the checkpoint.
* Returns: The line number associated with the checkpoint.
**********************************************************************/
int get_number_line(char *checkpoint_name);

/**********************************************************************
* Function: is_extern
* Description: Checks if a checkpoint is marked as external.
* Parameters:
*   - char *checkpoint_name: Name of the checkpoint to check.
* Returns: 1 if the checkpoint is external, 0 otherwise.
**********************************************************************/
int is_extern(char *checkpoint_name);

/**********************************************************************
* Function: is_entry
* Description: Checks if a checkpoint is marked as an entry point.
* Parameters:
*   - char *checkpoint_name: Name of the checkpoint to check.
* Returns: 1 if the checkpoint is an entry, 0 otherwise.
**********************************************************************/
int is_entry(char *checkpoint_name);

/**********************************************************************
* Function: free_checkpoints
* Description: Frees memory allocated for checkpoints.
* Parameters: None.
* Returns: void
**********************************************************************/
void free_checkpoints(void);

/**********************************************************************
* Function: print_checkpoints_we_have
* Description: Prints all currently stored checkpoints.
* Note: This is a temporary function for debugging and should be removed later.
* Parameters: None.
* Returns: void
**********************************************************************/
void print_checkpoints_we_have(void); /* Temporary function, remove later */

/**********************************************************************
* Function: write_entry_checkpoints_if_exists
* Description: Writes entry checkpoints to the output file if any exist.
* Parameters: None.
* Returns: void
**********************************************************************/
void write_entry_checkpoints_if_exists(void);

/**********************************************************************
* Function: is_has_any_extern
* Description: Checks if any external checkpoints are present.
* Parameters: None.
* Returns: 1 if external checkpoints exist, 0 otherwise.
**********************************************************************/
int is_has_any_extern(void);

#endif /* CHECKPOINTS_ENTRY_EXTERN_H */
