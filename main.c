#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "lib.h"
 
void loadmenu()
{
  printf("***************************************************************\n");
  printf("*\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t*\n");
  printf("*\tDEPARTMENT OF COMPUTER ENGINEERING LIBRARY\t\t\t\t\t\t\t*\n");
  printf("*\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t*\n");
  printf("***************************************************************\n");

} 



void menud()
{
  printf("1.To get the list of books\n");
  printf("2.To get the assigned books to students\n");
  printf("3.To get the students in the library\n");
  printf("4.To delete the student from library on book return\n");
  printf("5.To add new book in the library\n");
  printf("6.To issue book to the student\n");
  printf("7.To update student weekly\n");
  printf("8.To Delete unavailable books \n");
  printf("9.To exit from the library\n\n");

}
int main()
{
    LIBRARY *lib;
    int loop=1;
    int menu;
    loadmenu();
    menud();
    printf("\n");
    lib = initDB();

    while(loop)
    {
      scanf("%d",&menu);
      switch(menu)
      {
          case 1:
               listBook(lib->btree);
            break;

          case 2:
              lib = getBooksofStudent(lib);
            break;

          case 3:
              lib->stree = loadStudents();
            break;
        
          case 4:
              lib = deleteStudentonReturn(lib);
            break;

          case 5:
               lib=addNewBooks(lib);
            break;

          case 6:
               lib=BookIssueRequest(lib);
            break;

          case 7:
               lib=updateStudentlistWeekly(lib);
            break;

          case 8:
                lib=deleteUnavailableBooks(lib);
            break;
          
          case 9:
                loop=0;
                break;
         
          default:
                 break;

      }
    }
    if(lib)
    {
    if(lib->stree)
      free(lib->stree);
    if(lib->btree)
      free(lib->btree);
    if(lib->bstree)
      free(lib->bstree);
    if(lib->brequest)
      free(lib->brequest);
    free(lib);
  }
  return 0;
}