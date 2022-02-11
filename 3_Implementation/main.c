/**
 * @file main.c
 * @author ravishekhar.singh@ltts.com
 * @brief 
 * @version 0.11
 *
 * @date 2022-02-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "main.h"

    char employeename[40]; /// string to store name of the employee
 
    long int record_size; /// size of each record of employee
    
     FILE *fp, *ft; /// file pointers
    char other, option;

 void List_Record(){
     rewind(fp); ///this will move the  file cursor to start of the file
                while(fread(&entity,record_size,1,fp)==1){ 
                    printf("\n%s %d %.2f\n",entity.name,entity.age,entity.bs); /// print the name, age and basic salary of the employee
                }
 }

 void Modify_Record(){
other = 'y';
                while(other == 'y'){
                    printf("Enter the employee name to modify: ");
                    scanf("%s", employeename);
                    rewind(fp);
                    while(fread(&entity,record_size,1,fp)==1){ /// fetch all record from text file 
                        if(strcmp(entity.name,employeename) == 0){ ///if entered name matches with that name in file
                            printf("\nEnter new employee name, age and bs: ");
                            scanf("%s%d%f",entity.name,&entity.age,&entity.bs);
                            fseek(fp,-record_size,SEEK_CUR); /// it will move the cursor 1 step back from current position
                            fwrite(&entity,record_size,1,fp); /// override the record
                            break;
                        }
                    }
                    printf("\nModify another record(y/n)");
                    fflush(stdin);
                    scanf("\n%c", &other);
                }

 }

 void Delete_Record(){
other = 'y';
                while(other == 'y'){
                    flush();
                    printf("\nEnter name of employee to delete: ");
                    fgets(employeename,40, stdin);
                    ft = fopen("Temp.dat","wb");  
                    rewind(fp); /// move record to starting of file
                    while(fread(&entity,record_size,1,fp) == 1){ /// read all records from file
                        if(strcmp(entity.name,employeename) != 0){ 
                            /// if the entered record match
                            fwrite(&entity,record_size,1,ft); /// move all records except the one that is to be deleted to temp file
                        }
                    }
                    fclose(fp);
                    fclose(ft);
                    remove("EMP.DAT"); /// remove the orginal file
                    rename("Temp.dat","EMP.DAT"); /// rename the temp file to original file name
                    fp = fopen("EMP.DAT", "rb+");
                    printf("Delete another record(y/n)");
                    fflush(stdin);
                    scanf("\n%c", &other);
                }
 }

 void Exit(){
             fclose(fp);  /// close the file
                exit(0); /// exit from the program
 }


int main(){

 
    /// sizeo of each record i.e. size of structure variable e
    record_size = sizeof(entity);

    /** open the file in binary read and write mode
    * if the file EMP.DAT already exists then it open that file in read write mode
    * if the file doesn't exit it simply create a new copy
    */
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL){
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL){
            printf("Connot open file");
            exit(1);
        }
    }
 
    /// infinite loop continues untile the break statement encounter
    while(1){
        printf("1. Add Record\n"); /// option for add record
        printf("2. List Records\n"); /// option for showing existing record
        printf("3. Modify Records\n"); /// option for editing record
        printf("4. Delete Records\n"); /// option for deleting record
        printf("5. Exit\n"); /// exit from the program
        printf("Your Choice: "); /// enter the choice 1, 2, 3, 4, 5
        fflush(stdin); /// flush the input buffer
        scanf("\n%c", &option); /// get the input from keyboard
        switch(option ){
            case '1':  /// if user press 1
                Add_Record();
                break;
            case '2':
                List_Record();
                break;
 
            case '3':  /// if user press 3 then do editing existing record
                Modify_Record();
                break;
            case '4':
                Delete_Record();
                break;
            case '5':
                Exit();
        }
    }
    return 0;
}