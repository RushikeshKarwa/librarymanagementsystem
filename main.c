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
  printf("7.To get total book count in the library\n");
  printf("8.To get student list with issued books \n");
  printf("9.To get students by Book Title\n");
  printf("10.To exit from the library\n\n");

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
              system("clear");
              loadmenu();
              printf("BOOK AVAILABLE IN THE LIBRARY:\n\n");
               listBook(lib->btree);
               printf("\n\n");
               menud();
            break;

          case 2:
              system("clear");
              loadmenu();
              printf("BOOKs ASSIGNED RECORD:\n\n");
              lib = getBooksofStudent(lib);
              printf("\n\n");
              menud();
            break;

          case 3:
              system("clear");
              loadmenu();
              lib->stree = loadStudents();
              printf("\n\n");
              menud();
            break;
        
          case 4:
              system("clear");
              loadmenu();
              lib = deleteStudentonReturn(lib);
              printf("\n\n");
              menud();
            break;

          case 5:
               system("clear");
               loadmenu();
               lib=addNewBooks(lib);
               printf("\n\n");
               menud();
            break;

          case 6:
               system("clear");
               loadmenu();
               lib=BookIssueRequest(lib);
               printf("\n\n");
               menud();
            break;

          case 7:
               system("clear");
               loadmenu();
               getBookCount(lib);
               printf("\n\n");
               menud();
            break;

          case 8:
                system("clear");
                loadmenu();
                getStudentBookIssues(lib);
                printf("\n\n");
                menud();
            break;

          case 9:     
                system("clear");
                loadmenu();
                getBooksIssuedbyTitle(lib);
                printf("\n\n");
                menud();
                break;
          
          case 10:
                system("clear");
                loadmenu();
                getBooksIssuedbyTitle(lib);
                loop=0;
                printf("Thank You for using this software :) !!!");
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