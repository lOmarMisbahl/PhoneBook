#include<stdio.h>
#include<string.h>
#include <windows.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define COLOR CYAN

#define clearscreen system("cls");

#define HALT while (1);

void getScreenSize();
int ColumnsSize,RowsSize;

char **myScreen;

void PrintTitle(char *ItemStr){

  char shift = 0;
  int Width = ColumnsSize - shift;
  for (size_t i = 0; i < strlen(ItemStr); i++) {
    myScreen[(Width/2)- (strlen(ItemStr)/2)-1+i][1] =ItemStr[i];
  }
}
void PrintItems(char Items[][10],int n,int CursorPos){
  char Line = 5;
  char shift = 0;
  int Width = ColumnsSize - shift;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < strlen(Items[i]); j++) {
      myScreen[(Width/2)- (strlen(Items[i])/2)-1+j][Line] =Items[i][j];
      if(CursorPos == i){
        myScreen[(Width/2)- (strlen(Items[i])/2)-2][Line] =175;
        myScreen[(Width/2)+ (strlen(Items[i])/2)][Line] =174;
      }
    }
    Line++;
  }
}

void InitPrint();
void PrintScreen();
void AddFrame();
void Menu(){
    char CursorPos = 0;
    char N = 2;
    char Items[][10] = {"Load","Query","Add","Delete","Modify","Print","Save","Quit"};

    getScreenSize(&ColumnsSize,&RowsSize);

    myScreen = (char **)calloc(ColumnsSize, sizeof(char *));
    for (int i=0; i<ColumnsSize; i++)
         myScreen[i] = (char *)calloc(RowsSize , sizeof(char));

    clearscreen

  while (1) {

    InitPrint();
    AddFrame();
    PrintTitle("Telephone Book");
    PrintItems(Items,sizeof(Items)/10,CursorPos);
    PrintScreen(myScreen);
    fflush(stdout);
    int Key =0;
    if(Key =getch())
    if (Key == 13) {
      switch (CursorPos) {
        case 0:
            //dosmth
            break;
      }
    }else if(Key ==  224){
      Key = getch();
      if(Key == 80)
        if(CursorPos <(sizeof(Items)/10)-1){
          CursorPos++;
        }else{
          CursorPos = 0;
        }
      else if(Key == 72)
      if(CursorPos >0){
        CursorPos--;
      }else{
        CursorPos = (sizeof(Items)/10)-1;
      }
    }else{

    }

    system("cls");
  }


}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define StrSize 20

typedef struct
{
    unsigned char Day;
    unsigned char Month;
    unsigned int Year;
} Date;
typedef struct
{
    char FirstName[20];
    char LastName[20];
    Date BirthDate;
    char Address[20];
    char City[20];
    unsigned int PhoneNumber;
} Entry;
int n = 100;
Entry Directory[100];
void Delete(){
    char LastNameDelete[20];
    char FirstNameDelete[20];
    printf("Enter First Name of The Entry you want to delete : ");
    scanf("%[^\n]s",FirstNameDelete);
    printf("Enter Last Name of The Entry you want to delete : " );
    scanf("\n%[^\n]s",LastNameDelete);
    int i;
    int c;
    char found=1;
    for (i=0;i<n;i++)
    {
        if((!strcmp(LastNameDelete,Directory[i].LastName))&&(!strcmp(FirstNameDelete,Directory[i].FirstName)))
        {
            for(c=i;c<n;c++)
            Directory[c]=Directory[c+1];
            found=0;
            i=-1;
        }
    }
    if (found)
        printf("Your Entry Hasn't Been Found\n");
}
void Read(){
    int i=0;
    FILE *file;
    file=fopen( "MyPhoneBook.txt", "r" );
    if (file==NULL)
        printf("File Doesn't Exist\n");
    else
        while(!feof(file))
        {
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

    while (i<n)
    {
        if(*Directory[i].FirstName)
        {
            PrintSeparator();
            printf("ID : %d\n"
                   "First Name : %s\n"
                   "Last Name : %s\n"
                   "Birth Date : %d-%d-%d\n"
                   "Address : %s\n"
                   "City : %s\n"
                   "Phone Number : %d \n",i,
                   Directory[i].FirstName,Directory[i].LastName,Directory[i].BirthDate.Day,
                   Directory[i].BirthDate.Month,Directory[i].BirthDate.Year,Directory[i].Address,
                   Directory[i].City, Directory[i].PhoneNumber);
            PrintSeparator();
            Empty = 0;
        }
        i++;
    }
    if (Empty)
    {
        printf("The Telephone Book Directory Has No Entries\n");
    }
}

int main(int argc, char const *argv[]) {


  Menu();
  getch();
  return 0;
}
void getScreenSize(int *Columns,int *Rows){
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns, rows;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

  *Columns = columns;
  *Rows = rows;

}
void PrintScreen(){

  int j,i;

  for ( j = 0; j < RowsSize; j++) {
    for ( i = 0; i < ColumnsSize; i++) {
    //  printf(COLOR "%c""\x1b[0m",myScreen[i][j] );
    printf("%c",myScreen[i][j] );

    }
  }

}
void InitPrint(){
  int j,i;
  for ( j = 0; j < RowsSize; j++) {
    for ( i = 0; i < ColumnsSize; i++) {

      myScreen[i][j] =32;//219

    }
  }
}
void AddFrame(){
  for (int i = 0; i < ColumnsSize; i++) {
     myScreen[i][0] = 205;
  }
  for (int i = 0; i < ColumnsSize; i++) {
     myScreen[i][RowsSize-1] = 205;
  }
  for (int i = 0; i < RowsSize; i++) {
     myScreen[0][i] = 186;
  }
  for (int i = 0; i < RowsSize; i++) {
     myScreen[ColumnsSize-1][i] = 186;
  }
  myScreen[0][0] = 201;
  myScreen[ColumnsSize-1][0] = 187;
  myScreen[ColumnsSize-1][RowsSize-1] = 188;
  myScreen[0][RowsSize-1] = 200;

}
