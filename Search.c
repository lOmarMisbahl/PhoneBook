#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define StrSize 20

typedef struct{
    unsigned char Day;
    unsigned char Month;
    unsigned int Year;
}Date;
typedef struct{
  char FirstName[20];
  char LastName[20];
  Date BirthDate;
  char Address[20];
  char City[20];
  unsigned int PhoneNumber;
}Entry;
int n = 100;
Entry Directory[100];
void PrintSeparator(){
  int i = 20;
  while (i--)
    printf("+-");
  printf("\n" );
}
void Search(){
  char TempStr[20];
  printf("Enter Last Name of The Entry you want to search for : " );
  scanf("%s",TempStr);
  int i;
  char found=1;
  for (i=0;i<n;i++){
        if(!strcmp(TempStr,Directory[i].LastName)){
           printf("ID : %d\n"
          "First Name : %s\n"
          "Birth Date : %d-%d-%d\n"
          "Address : %s\n"
          "City : %s\n"
          "Phone Number : %d \n",i,
          Directory[i].FirstName,Directory[i].BirthDate.Day,
          Directory[i].BirthDate.Month,Directory[i].BirthDate.Year,Directory[i].Address,
          Directory[i].City, Directory[i].PhoneNumber);
          PrintSeparator();
          found=0;
}
  }
  if (found)
    printf("Your Entry Hasn't Been Found");
}
void Read(){
    int i=0;
    FILE *file;
    file=fopen( "MyPhoneBook.txt" , "r" );
    if (file==NULL)
            printf("File Doesn't Exist\n");
   else
   while(!feof(file)){
        fscanf(file,"%[^,],",Directory[i].FirstName);
        fscanf(file,"%[^,],",Directory[i].LastName);
        fscanf(file,"%d-",&Directory[i].BirthDate.Day);
        fscanf(file,"%d-",&Directory[i].BirthDate.Month);
        fscanf(file,"%d,",&Directory[i].BirthDate.Year);
        fscanf(file,"%[^,],",Directory[i].Address);
        fscanf(file,"%[^,],",Directory[i].City);
        fscanf(file,"%d\n",&Directory[i].PhoneNumber);
        i++;
   }
}
void main(){
    Read();
    Search();
}
