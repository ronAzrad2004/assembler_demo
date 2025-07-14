#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*********************************************************************/
#include "checkpoints_entry_extern.h"
#include "database_data_string.h"
/*********************************************************************/
#define MAX_LENGTH 30
#define MAX_SIZE 81
#define KEY -999
#define SEC -10
/*********************************************************************/
#define OUTPUT_1 "ps.ob"
#define EXT_PATH "ps.ext"
#define ENT_PATH "ps.ent"
#define LOGS "ps.logs"

/*********************************************************************/
void removeFirstChar(char *str) {
    if (str == NULL || *str == '\0') return;
    memmove(str, str + 1, strlen(str));
}
/*********************************************************************/
int opCode(char *str) {
    if (str == NULL)
        return -1;
    else if (!strcmp(str, "mov")) return 0;
    else if (!strcmp(str, "cmp")) return 1;
    else if (!strcmp(str, "add")) return 2;
    else if (!strcmp(str, "sub")) return 3;
    else if (!strcmp(str, "lea")) return 4;
    else if (!strcmp(str, "clr")) return 5;
    else if (!strcmp(str, "not")) return 6;
    else if (!strcmp(str, "inc")) return 7;
    else if (!strcmp(str, "dec")) return 8;
    else if (!strcmp(str, "jmp")) return 9;
    else if (!strcmp(str, "bne")) return 10;
    else if (!strcmp(str, "red")) return 11;
    else if (!strcmp(str, "prn")) return 12;
    else if (!strcmp(str, "jsr")) return 13;
    else if (!strcmp(str, "rts")) return 14;
    else if (!strcmp(str, "stop")) return 15;
    else if (!strcmp(str, ".data") || !strcmp(str, ".string")) return KEY;
    return -1;
}
/*********************************************************************/
int check_sort(char *str) {
    if (strlen(str)==0)
        return SEC;
    if (str[0] == '#')
        return 0;
    else if (get_status_flag_of_type_checkpoint(str) != -1 || is_exists_variable(str))
        return 1;
    else if (!strcmp(str, "r0") || !strcmp(str, "r1") || !strcmp(str, "r2") || !strcmp(str, "r3") || !strcmp(str, "r4") || !strcmp(str, "r5") || !strcmp(str, "r7") || !strcmp(str, "r6"))
        return 3;
    else if (!strcmp(str, "*r0") || !strcmp(str, "*r1") || !strcmp(str, "*r2") || !strcmp(str, "*r3") || !strcmp(str, "*r4") || !strcmp(str, "*r5") || !strcmp(str,"*r7") || !strcmp(str, "*r6"))
        return 2;
    return -1;
}
/*********************************************************************/
void del_extern_file(){
  remove(EXT_PATH);
}
void del_entry_file(){
 remove(ENT_PATH);
}
void del_octal_file(){
remove(OUTPUT_1);
}
void del_Log_file(){
remove(LOGS);
}
void clear_all(){
del_octal_file();
del_extern_file();
del_entry_file();
}
/*********************************************************************/
void split(char *str, char s[][MAX_LENGTH]) {
    int i = 0;
    int j = 0;

    /* Skip leading spaces and tabs */
    while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t')) i++;

    /* Extract the first substring */
    while (str[i] != '\0' && str[i] != ' ' && str[i] != '\n'&& str[i] != '\t') {
        s[0][j++] = str[i++];
    }
    s[0][j] = '\0';

    /* Skip spaces, tabs, and commas */
    while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t' || str[i] == ',')) i++;

    j = 0;
    /* Extract the second substring */
    while (str[i] != '\0' && str[i] != ' ' && str[i] != '\n'&& str[i] != '\t' && str[i] != ',') {
        s[1][j++] = str[i++];
    }
    s[1][j] = '\0';

    /* Skip spaces, tabs, and commas */
    while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t' || str[i] == ',')) i++;

    j = 0;
    /* Extract the third substring */
    while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t'&& str[i] != '\n' && str[i] != ',' && str[i] != '\n') {
        s[2][j++] = str[i++];
    }
        s[2][j] = '\0';
    
}
/*********************************************************************/
int checkLine(char *str) {
    int i = 0, j = 0;
    char temp[MAX_LENGTH];
    while (str[0] == ' ' && str[0] != '\0')
        removeFirstChar(str);
    for (; i < strlen(str); i++) {
        if (str[i] == ' ')
            break;
        temp[i] = str[i];
    }
    temp[i] = '\0';
     if(temp[strlen(temp)-1]==':')
       temp[strlen(temp)-1]='\0';
    if (i < strlen(str)) {
        if ((get_status_flag_of_type_checkpoint(temp) != -1)||is_exists_variable(temp)) {
            for (; j < i; j++){
                removeFirstChar(str);
            }
        }
        else{
            if(opCode(temp)==-1)
              return 0;
        }
    }
    return 1;
}
/*********************************************************************/
int code_compiled(int first_socode, int opcode, int second_socode) {
    if (opcode == 0 || opcode == 2 || opcode == 3) {
        if (!second_socode)
            return 0;
    }
    if (opcode == 4) {
        if (first_socode != 1 || second_socode == 0)
            return 0;
    }
    if (opcode == 5 || opcode == 6 || opcode == 7 || opcode == 8 || opcode == 11) {
        if (first_socode == 0)
            return 0;
    }
    if (opcode == 9 || opcode == 10 || opcode == 13) {
        if (first_socode != 1 && first_socode != 2)
            return 0;
    }
    if (opcode == 12)
        if (first_socode < 0)
            return 0;
    if (opcode == 14 || opcode == 15)
        if (first_socode != SEC)
            return 0;
    return 1;
}
/*********************************************************************/
void short_int_to_octal(unsigned short int decimalNumber, char *octalString) {
    int index = 0;
    int remainder;
    char temp[10]; 
    int i=0,j;
    if (decimalNumber == 0) {
        octalString[index++] = '0';
        octalString[index] = '\0';
        return;
    }

    
    while (decimalNumber > 0) {
        remainder = decimalNumber % 8;
        temp[index++] = '0' + remainder;
        decimalNumber /= 8;
    }
     for(i=0;i<5;i++)
        octalString[i]='0';
        for (j = 0; j < index; i++,j++) {
            octalString[i] = temp[index - j - 1];
        }
    while(strlen(octalString)>5){
       removeFirstChar(octalString);
    }
    octalString[index-i] = '\0';
}
/*********************************************************************/
void write_Octal_values_by_d(int *i, char *str) {
    FILE *fptr = fopen("ps.ob", "a");
    char temp[5];
    char res_str[13];
    int j = 0;
    short int res = 0;
    int index = 0;
    if(fptr==NULL)fptr = fopen("ps.ob", "w");
    for (; j < strlen(str); j++,(*i)++) {
        index = 0;
		 memset(res_str,0,sizeof(res_str));
		while(*(str+j)!='-'&&!isdigit(*(str+j))&&j<strlen(str))
			  j++;
        while ((*(str+j)=='-'||isdigit(*(str+j)))&& index < 5 && j < strlen(str)) {
            temp[index] = *(str + j);
            j++;
            index++;
        }
        temp[index] = '\0';
        res = atoi(temp);
		if(strlen(temp)>0&&res==0)
			 goto point;
        short_int_to_octal(res,res_str);
        if (*i <= 999){
            fprintf(fptr,"0%d  %s\n", *i, res_str);
        }    
        else{
            fprintf(fptr,"%d  %s\n", *i, res_str);
        }
        

    }
point:
    fclose(fptr);
}
/*********************************************************************/
void write_Octal_values_by_s(int *i, char *str) {
    FILE *fptr = fopen("ps.ob", "a");
    int j = 0;
    char res[13];
    if(fptr==NULL)fptr = fopen("ps.ob", "w");
    for (; j < strlen(str); j++) {
		 memset(res,0,sizeof(res));
        if(*(str+j)!='"'){
        short_int_to_octal((short int)(*(str + j)),res);
        if (*i <= 999)
            fprintf(fptr,"0%d  %s\n", *i, res);
        else
            fprintf(fptr,"%d  %s\n", *i, res);
        (*i)++;
        }
    }
    if(*i<=999)
      fprintf(fptr,"0%d  %s\n", *i,"00000");
    else 
      fprintf(fptr,"%d  %s\n", *i,"00000");
  (*i)++;
    fclose(fptr);
}
void write_octal_values(int i, int j, unsigned short int arr[3]) {
    FILE *fptr = fopen("ps.ob", "a");
    char res[13];
    int c = 0;
    if(fptr==NULL)fptr = fopen("ps.ob", "w");
    for (; i <= j; i++, c++){
		 memset(res,0,sizeof(res));
        short_int_to_octal(arr[c],res); 
        if(i<=999){      
		fprintf(fptr,"0%d  %s\n",i,res);
		}
        else 
          fprintf(fptr,"%d  %s\n", i, res);
    }
    fclose(fptr);
}
/**********************************************************************/
void getString(char *target,char *str_data){
    while(str_data[0]!='-'&&!isdigit(str_data[0])&&str_data[0]!='"'&&str_data[0]!='\0')removeFirstChar(str_data);
    strcpy(target,str_data);
    
}
/**********************************************************************/
void input_data(char *str_data, int *row,int code_line ,int *error_occured) {
    FILE *file = fopen(LOGS, "a");
    char str[3][MAX_LENGTH];
    int current_row = *row;
    unsigned short int word[3];
    int opcode, sort_code,sec_soC;
    if(str_data[strlen(str_data)-1]=='\n')
      str_data[strlen(str_data)-1]='\0';
    if(!checkLine(str_data)){
     *error_occured = 1;
        fprintf(file,"unkown checkpointer in line: %d\n", code_line);
    }
    split(str_data, str);
    opcode = opCode(str[0]);
    if (opcode == -1) {
        *error_occured = 1;
        fprintf(file,"invalid operation code in line: %d\n", code_line);
    }
    if (opcode == KEY) {
        if ((*error_occured)==0) {
            getString(str[1],str_data);
            if (!strcmp(str[0], ".string"))
                write_Octal_values_by_s(row, str[1]);
            else
                write_Octal_values_by_d(row, str[1]);
            fclose(file);
        }

        return;
    }
    word[0] = 1 << 2;
    word[0] |= opcode << 11;
    sort_code = check_sort(str[1]);
    if (sort_code == -1) {
        *error_occured = 1;
        fprintf(file,"invalid operand in line: %d\n", code_line);
    }
    if(sort_code==SEC){
        if(opcode!=14&&opcode!=15) { 
           *error_occured = 1;
	    fprintf(file,"not enough operands for this operation.ERROR IN LINE: %d\n",code_line);
         }
            
    }
    
    if (sort_code == 0) {
        removeFirstChar(str[1]);
        if (atoi(str[1]) >= 0)
            word[1] = atoi(str[1]) << 3;
        else
            word[1] |= ((~((atoi(str[1]))*-1)) + 1) << 3;
        word[1] = word[1] << 1;
        word[1] = word[1] >> 1;
        word[1] |= 1 << 2;
    } else if (sort_code == 1) {
        word[1] = (get_status_flag_of_type_checkpoint(str[1]) > 1 ? 1 : 1 << 1);
        if (get_status_flag_of_type_checkpoint(str[1]) != 2) {
            word[1] |= get_number_line(str[1]) << 3;
        }
    } else if (sort_code == 2) {
        word[1] = (str[1][2] - '0') << 6;
        word[1] |= 1 << 2;
    } else {
        word[1] = (str[1][1] - '0') << 6;
        word[1] |= 1 << 2;
    }
    sec_soC = check_sort(str[2]);
    if (sec_soC == SEC) {
        word[0] |= 1 << (3 + sort_code);
        if (sort_code == 0) {
        if (atoi(str[1]) >= 0)
            word[1] = atoi(str[1]) << 3;
        else
            word[1] |= ((~((atoi(str[1]))*-1)) + 1) << 3;
        word[1] = word[1] << 1;
        word[1] = word[1] >> 1;
        word[1] |= 1 << 2;
       } else if (sort_code == 1) {
        word[1] = (get_status_flag_of_type_checkpoint(str[1]) > 1 ? 1 : 1 << 1);
          if (get_status_flag_of_type_checkpoint(str[1]) != 2) {
            word[1] |= get_number_line(str[1]) << 3;
          }
        } else if (sort_code == 2) {
        word[1] = (str[1][2] - '0') << 3;
        word[1] |= 1 << 2;
        } else {
        word[1] = (str[1][1] - '0') << 3;
        word[1] |= 1 << 2;
        }
        goto end;
    }
    word[0] |= 1 << (7 + sort_code);
    word[0] |= 1 << (3 + sec_soC);
    if (((sort_code == 2)||(sort_code == 3))&&(sec_soC==2||sec_soC==3)) {
        if (sec_soC == 2) {
            word[1] |= (str[2][2] - '0') << 3;
        } else {
            word[1] |= (str[2][1] - '0') << 3;
        }
        goto end;
    }
    word[2] = 1 << 2;
	   if(sec_soC==SEC)
		    goto end;
	    else if (sec_soC == 0) {
        removeFirstChar(str[2]);
        if (atoi(str[2]) >= 0)
            word[2] |= atoi(str[1]) << 3;
        else{
           
            word[2] |= ((~((atoi(str[2]))*-1)) + 1) << 3;
        }
        word[2] = word[2] << 1;
        word[2] = word[2] >> 1;
    } else if (sec_soC == 1) {
        word[2] = (get_status_flag_of_type_checkpoint(str[2]) > 1 ? 1 : 1 << 1);
        if (get_status_flag_of_type_checkpoint(str[2]) != 2) {
            word[2] |= get_number_line(str[2]) << 3;
        }
    } else if (sec_soC == 2) {
        word[2] |= (str[2][2] - '0') << 3;
    } else if (sec_soC == 3) {
        word[2] |= (str[2][1] - '0') << 3;
    } else {
        *error_occured = 1;
        fprintf(file,"12)invalid operand in line: %d\n", code_line);
    }
end:
    if (code_compiled(sort_code, opcode, sec_soC) && !(*error_occured)) {

		fclose(file);
        if(opcode!=14&&opcode!=15){
        if ((((sort_code == 2)||(sort_code == 3))&&(sec_soC==2||sec_soC==3))|| opcode > 4)
            *row += 1;
        else
            *row += 2;
        }
        write_octal_values(current_row, *row, word);
        (*row)++;
        return;
    } else{
        if (*error_occured == 0) {
            *error_occured = 1;
        }
        if(!code_compiled(sort_code, opcode, sec_soC))
           fprintf(file,"Line %d is ilegal",code_line);
         
    }
    fclose(file);
    return;
}
