#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#define SIZE 9999


#define studentfile "student.txt"
#define studentDB "student.dat"

#define bookReqDB "bookreqs.dat"

#define bookfile "book.txt"
#define newbooks "newbook.txt"  

#define bookDB "book.dat"


#define bookissuefile "book_issue.txt"
#define bookissueDB "book_issue.dat"


typedef struct req_node
{
    int book_id;
    int sid;
    char req_date[50];
    struct req_node *next;
    struct req_node *front;
    struct req_node *rear;
}bookrequest;


typedef struct Que
{
  int num_queues;
  bookrequest **req;   
 }Queue;


typedef struct dt
{
  int day;
  int month;
  int year;
}date;


typedef struct bookissue_node
{
    int bookissue_id;
    int book_id;
   int sid;
    char issue_date[40];
    char expiry_date[40];
}book_issue;


typedef struct issuetree
{
    book_issue *key;
    int height;    
    struct issuetree *left;
    struct issuetree *right;
}ISSUE_TREE;


typedef struct studentNode
{
  long int sid;
  char sname[100];
}student;

typedef struct Node
{
    student *key;
    struct Node *left;
    struct Node *right;
    int height;
}STUDENT_TREE;


typedef struct book_node
{
    int book_id;
    char title[50];
    int quantity;
}book;


typedef struct booktree
{
    book *key;
    int height;    
    struct booktree *left;
    struct booktree *right;
}BOOK_TREE;


typedef struct systemNode
{
     STUDENT_TREE *stree;  
     BOOK_TREE *btree;
     ISSUE_TREE *bstree;
     Queue *brequest;
}LIBRARY;


Queue *createQ();
 
void deleteQ(Queue *q);
 
int isEmpty(Queue *q,int n);
 
Queue *Enqueue(Queue *q,bookrequest *ptr);
 
void Dequeue(Queue *q,int n);

Queue *getBookReqDB(Queue *q);

static int days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int day, month, year,next_update;
unsigned short day_counter;


int is_leap(int);

void skip_days(int x);

void set_date(int m,int n,int p);

void next_day();

date *convertDate(char *str);

void readBookRequestRecords();
 
void insertBookRequestRecord(bookrequest *key);
 
void updateBookRequestDB(bookrequest *key);
 
void deleteBookRequestRecord(bookrequest *key);

LIBRARY *initDB();

STUDENT_TREE *loadStudents();

LIBRARY *deleteStudentonReturn(LIBRARY *tmp);

LIBRARY *deleteStudentById(LIBRARY *root,int studentid,int bid);

void getBookRecordById(BOOK_TREE *root,int id,book **b);

void searchBookIssueByRecord(ISSUE_TREE *root,int id,int bid,book_issue **b);

LIBRARY *BookIssueRequest(LIBRARY *);

LIBRARY *updateStudentlistWeekly(LIBRARY *root);
LIBRARY *deleteUnavailableBooks(LIBRARY *root);

LIBRARY *addNewBooks(LIBRARY *lib);

void updateBookAvailability(book *b,int x);

ISSUE_TREE *newIssueNode(book_issue *key);

ISSUE_TREE *createBookIssueDB(char *str);

ISSUE_TREE *rightRotateBookKIssue(ISSUE_TREE *y);

ISSUE_TREE *leftRotateBookIssue(ISSUE_TREE *x);

int getBalanceIssue(ISSUE_TREE *N);

void readBookIssueRecords();

ISSUE_TREE *getBookIssueDB();

void insertBookIssueRecord(book_issue *key);

ISSUE_TREE *insertBookIssue(ISSUE_TREE *node,book_issue *key);


ISSUE_TREE *minValueBookIssueNode(ISSUE_TREE *node);

void updateBookIssueDB(book_issue *key);

void deleteBookIssueRecord(book_issue *key);

ISSUE_TREE *deleteBookIssueNode(ISSUE_TREE *root, book_issue *key);

void createIssueRecords(ISSUE_TREE *root);

void inOrderBookIssue(ISSUE_TREE *root);

void  getBooksIssuedbyTitle(LIBRARY *root);

void listBooksbyId(ISSUE_TREE *root,int id,int *x); 
int getBookIssueRecordCount();

int max(int a, int b);

STUDENT_TREE *createStudentDB(char *str);

STUDENT_TREE *newStudentNode(student *key);

int heightStudent(STUDENT_TREE *N);

STUDENT_TREE *rightRotateStudent(STUDENT_TREE *y);

STUDENT_TREE *leftRotateStudent(STUDENT_TREE *x);

int getBalanceStudent(STUDENT_TREE *N);

void readStudentRecords();

STUDENT_TREE *getStudentDB();

int searchStudentById(int id);

void insertStudentRecord(student *key);  

STUDENT_TREE *insertStudent(STUDENT_TREE *node,student *key);

void createStudentRecords(STUDENT_TREE *root);

void inOrderStudent(STUDENT_TREE *root);

void listBook(BOOK_TREE *x);
void inOrderBook(BOOK_TREE *root);

LIBRARY *getBooksofStudent(LIBRARY *root);
void getStudentlist(ISSUE_TREE *tmp,int a[]);
void listBooksbyStudent(ISSUE_TREE *root,int id,int *x);

int heightBook(BOOK_TREE *N);
BOOK_TREE *newBookNode(book *key);

BOOK_TREE *createBookDB(char *str);

BOOK_TREE *rightRotateBook(BOOK_TREE *y);

BOOK_TREE *leftRotateBook(BOOK_TREE *x);

int getBalanceBook(BOOK_TREE *N);


void readBookRecords();

BOOK_TREE *getBookDB();

void createBookRecords(BOOK_TREE *root);

BOOK_TREE *insertBook(BOOK_TREE *node,book *key);


BOOK_TREE *minValueBookNode(BOOK_TREE *node);


void updateBookDB(book *key);

void deleteBookRecord(book *key);

void searchBookById(BOOK_TREE *b,int id,int *p);

void searchBookByTitle(BOOK_TREE *r,char *name,book **b);

int searchBookAvailabilityById(int id);

BOOK_TREE *deleteBookNode(BOOK_TREE *root, book *key);

void getStudentRecordById(STUDENT_TREE *root,int id,student **s);

void getStudentBookIssues(LIBRARY *lib);

void getBookCount(LIBRARY *lib);

void getBookById(BOOK_TREE *root,int id,book **b);

void insertBookRecord(book *key);

