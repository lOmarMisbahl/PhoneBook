#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define StrSize 20

typedef struct{
    char Day[10];
    char Month[10];
    char Year[10];
}Date;

typedef struct{
  char FirstName[20];
  char LastName[20];
  Date BirthDate;
  char Address[20];
  char City[20];
  char PhoneNumber[20];
}Entry;

int n = 100;
Entry Directory[100]={ {"Marwan","B",{"22","2","1998"},"Happy Street","Alexandria","12345"},
    {"Marwan","Z",{"22","2","1998"},"Happy Street","Alexandria","12345"},
      {"John","A",{"31","12","2019"},"31 Random Street","NY","9874"}};

void Modify(){
  char TempStr[20];
  printf("Enter Last Name of The Entry you want to modify : " );
  scanf("%s",TempStr);
  int i = 0;
  /* Handle Multiple Entries with same last name problem*/
  while (strcmp(TempStr,Directory[i].LastName)) {
    i++;
    if (i == n) {
      printf("Entry Not Found Please Check The Entered Last Name\n");
      return;
    }
  }
  /*
  * Add Validation for entered data for bonus !
  * Add Press Enter for the Value to stay the same feature
  */

  printf("Enter New FirstName :");
  scanf("%s",Directory[i].FirstName );
  printf("Enter New LastName :");
  scanf("%s",Directory[i].LastName );
  printf("Enter Date of Birth in DD-MM-YYYY format :");
  scanf("%s-%s-%s",&Directory[i].BirthDate.Day,&Directory[i].BirthDate.Month,&Directory[i].BirthDate.Year );
  printf("Enter New Address :");
  scanf("%s",Directory[i].Address );
  fflush(stdin);
  printf("Enter New City Name :");
  scanf("%s",Directory[i].City );
  printf("Enter New PhoneNumber:");
  scanf("%d",&Directory[i].PhoneNumber );
}
void PrintSeparator(){
  int i = 20;
  while (i--)
    printf("+-");
  printf("\n" );
}
void Print(){
    int i = 0;
    char Empty = 1;
    char ID[100];
    for (size_t i = 0; i < 100; i++)
      ID[i]=i;
    //NORMALIZE letter to small first
    /*
    for(int i = 0; str[i]; i++){
  str[i] = tolower(str[i]);
}
*/
    //Bubble Sort
    for (size_t i = 0; i < n-1; i++) {
      for (size_t j = 0; j < n-i-1; j++){
        if(strcmp(Directory[ID[j]].LastName,Directory[ID[j+1]].LastName)>0){
          int temp = ID[j];
          ID[j] = ID[j+1];
          ID[j+1] = temp;
        }
      }
    }
    //printf("%d\n",strcmp(Directory[0].LastName,Directory[1].LastName ));

    int Num = 0 ;
    while (Num <100) {
      int i =ID[Num];

      if(*Directory[i].FirstName){
        PrintSeparator();
        printf("ID : %d\n"
          "First Name : %s\n"
          "Last Name : %s\n"
          "Birth Date : %s-%s-%s\n"
          "Address : %s\n"
          "City : %s\n"
          "Phone Number : %d \n",i,
          Directory[i].FirstName,Directory[i].LastName,Directory[i].BirthDate.Day,
          Directory[i].BirthDate.Month,Directory[i].BirthDate.Year,Directory[i].Address,
          Directory[i].City, Directory[i].PhoneNumber);
          PrintSeparator();
          Empty = 0;
        }
        Num++;
    }
    if (Empty) {
      printf("The Telephone Book Directory Has No Entries\n");
    }
  }
void Save(){/**/
  FILE *Data;
  Data = fopen("Data.txt","w");
  /*Format
    Sami,Ahmed,10-06-1989,26 Elhoreya Street,Alexandria,4876321
  */
  int i =0;
  while (i<n) {
    if(*Directory[i].FirstName){
      fprintf(Data, "%s,%s,%s-%s-%s,%s,%s,%d\n",
        Directory[i].FirstName,Directory[i].LastName,Directory[i].BirthDate.Day,
        Directory[i].BirthDate.Month,Directory[i].BirthDate.Year,Directory[i].Address,
        Directory[i].City, Directory[i].PhoneNumber);
      }
      i++;
    }
    fclose(Data);
    printf("Telephone Book Directory Successfully Saved\n" );
}
void Quit(){
  printf("All of your changes will be discarded if you quit without saving\n" );
  printf("Do you want to save the directory before quitting?(y/n)[y] ");

  char c = getch();
  printf("%c\n",c );
  if((c==13)||(c=='y')){

    Save();
  }

  exit(0);
}


int main(int argc, char const *argv[]) {

  while (1) {//Main loop
    Print();
    Modify();
    Save();
    Quit();
  }

  return 0;
}
