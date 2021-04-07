// C program to implement student creation and other supporting functions


#include "lib.h"



// A utility function to get height of the tree

int heightStudent(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers

int max(int a, int b)
{
    return (a > b)? a : b;
}


/* Helper function that allocates a new node with the given key and   NULL left and right pointers. */

STUDENT_TREE *newStudentNode(student *key)
{
    STUDENT_TREE *node = (STUDENT_TREE *)malloc(sizeof(STUDENT_TREE));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}
 
// A utility function to right rotate subtree rooted with y

STUDENT_TREE *rightRotateStudent(STUDENT_TREE *y)
{
    STUDENT_TREE *x = y->left;
    STUDENT_TREE *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(heightStudent(y->left), heightStudent(y->right))+1;
    x->height = max(heightStudent(x->left), heightStudent(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x

STUDENT_TREE *leftRotateStudent(STUDENT_TREE *x)
{
    STUDENT_TREE *y = x->right;
    STUDENT_TREE *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(heightStudent(x->left), heightStudent(x->right))+1;
    y->height = max(heightStudent(y->left), heightStudent(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalanceStudent(STUDENT_TREE *N)
{
    if (N == NULL)
        return 0;
    return heightStudent(N->left) - heightStudent(N->right);
}


void readStudentRecords()
{
  FILE *fp;
  student *key;
  key=(student *)malloc(sizeof(student));
  fp=fopen(studentDB,"rb"); //opening binary file in read mode
  if(fp==NULL)
  {
          printf("student database open error\n");
           exit(1);
   }
  while((fread(key,sizeof(student),1,fp))!=0)
  {
    if(key->sid!=0)
    printf(" %ld\t%s\n",key->sid,key->sname);
    memset(key,0,sizeof(student));
  }
  fclose(fp);
  
}

STUDENT_TREE *getStudentDB()
{
  
  FILE *fp;
  STUDENT_TREE *tree=NULL;
  student *key,*tmp;
   key=(student *)malloc(sizeof(student));
  fp=fopen(studentDB,"rb"); //opening binary file in read mode
  if(fp==NULL)
  {
          printf("student database open error\n");
           exit(1);
   }
  while((fread(key,sizeof(student),1,fp))!=0)
  {
    if(key->sid==0)continue;
    tmp=(student *)malloc(sizeof(student));
    tmp->sid=key->sid;
    strcpy(tmp->sname,key->sname);
    tree = insertStudent(tree,tmp);
  }
  fclose(fp);
  return tree;  
}


void insertStudentRecord(student *key)
{
  FILE *fp;
  fp=fopen(studentDB,"ab+"); //opening binary file in writing mode
  if(fp==NULL)
  {
          printf("student database open error\n");
           exit(1);
   }
  fwrite(key,sizeof(student),1,fp);  
  fclose(fp);
  
}
 
// Recursive function to insert key in subtree rooted with node and returns new root of subtree.
STUDENT_TREE *insertStudent(STUDENT_TREE *node,student *key)
{
    
    int balance;
    
    // 1.  Perform the normal BST insertion 
    if (node == NULL)
    {
       node = newStudentNode(key);
       return node;
    }
    else
    { 
       if(key->sid < node->key->sid)
           node->left  = insertStudent(node->left, key);
       else if(key->sid > node->key->sid)
          node->right = insertStudent(node->right, key);
       else // Equal keys are not allowed in BST
       {
	 printf("Duplicate records are not allowed..please enter differnt values\n");
         return node;
       } 
      
       /* 2. Update height of this ancestor node */
        node->height = 1 + max(heightStudent(node->left),heightStudent(node->right));
 
        /* 3. Get the balance factor of this ancestor node to check whether this node became  unbalanced */
        balance = getBalanceStudent(node);
 
       // If this node becomes unbalanced, then there are 4 cases
 
       // Left Left Case
    
        if (balance > 1 && (key->sid < node->left->key->sid))
           return rightRotateStudent(node);
 
       // Right Right Case
	
        if (balance < -1 && (key->sid > node->right->key->sid))
          return leftRotateStudent(node);
 
       // Left Right Case
        if (balance > 1 && (key->sid > node->left->key->sid))
        {
           node->left =  leftRotateStudent(node->left);
           return rightRotateStudent(node);
        }
 
        // Right Left Case
         if (balance < -1 && (key->sid < node->right->key->sid))
         {
            node->right = rightRotateStudent(node->right);
            return leftRotateStudent(node);
         }
      return node;
      }
}
  
//Function to create student records in .dat file. Function traverses the AVL tree created and then inserts in .dat file. This is to avoid duplicate records in file.

void createStudentRecords(STUDENT_TREE *root)
{
  if(root!=NULL)
  {
    createStudentRecords(root->left);
    insertStudentRecord(root->key);
    createStudentRecords(root->right);
  }
}


// A utility function to print preorder traversal of the tree.

void inOrderStudent(STUDENT_TREE *root)
{
    if(root!= NULL)
    {
        inOrderStudent(root->left);
	printf("%ld \t%s\n", root->key->sid,root->key->sname);
        inOrderStudent(root->right);
    }
}

int searchStudentById(int id)
{
    FILE *fp;
    student *s;
    int flag=0;
    
    fp=fopen(studentDB,"rb"); //opening binary file in reading mode
    if(fp==NULL)
    {
           printf("student database open error\n");
           exit(1);
    }
    fseek(fp,0,SEEK_SET);
    s=(student *)malloc(sizeof(student));
    memset(s,0,sizeof(student));
         
    while((fread(s,sizeof(student),1,fp))!=0)
    {          
          if(s->sid == id)  //Record found,return
	  {
	    flag=1;
	    break;
	  }	  
     }   
    fclose(fp); 
    return flag;
}

STUDENT_TREE *createStudentDB(char *input)
{ 
   STUDENT_TREE *root=NULL;  
   FILE *fp1;
   student *s;
   char str[100];
   char ch;
   int num,i,j,len;
   char word[2][40];
   char *ptr;
  
   fp1=fopen(input,"r"); //opening text file in read mode
   if(fp1==NULL)
   {
      return NULL;
   }

   num=1;
   i=j=0;
   while((fscanf(fp1,"%[^\n]s",str))==1)
   {     
      ch=fgetc(fp1);      
      len=strlen(str);
      if(ch!=EOF)
	 str[len-1]='\0';
      else
	str[len]='\0';
      
      //writing to database now
      s=(student *)malloc(sizeof(student));
      //s->sid=rand()%1000+0;
       i=0;j=0;
      ptr=strtok(str,",");
      strcpy(word[i++],ptr);
       
      while((ptr=strtok(NULL,","))!=NULL)
      {
	strcpy(word[i++],ptr);	  
      }
      
     // len=strlen(word[1]);
     // word[1][len-1]='\0';
      s->sid = atoi(word[j++]);
      
      strcpy(s->sname,word[j]);
      i=j=0;
      root = insertStudent(root, s);
      //insertStudentRecord(s);
      memset(str,0,sizeof(str));     
    }

   //printf("completed DB creation\n");
   fclose(fp1);
   createStudentRecords(root);
   return root;
}

//Function used to print the list of books

void listBook(BOOK_TREE *l)
{
  //printf("\nBook Id	Book Title	Author Name		Course		Cost		Qunatity	Genre\n");	
  inOrderBook(l);
}

//Function to traverse book tree in inorder and print the details of book
void inOrderBook(BOOK_TREE *root)
{
    if(root != NULL)
    {
        inOrderBook(root->left);
	printf("%5d\t%-40s\t%4d\n", root->key->book_id,root->key->title,/*root->key->author_name,root->key->course,root->key->cost,
  */root->key->quantity/*root->key->genre*/);
        inOrderBook(root->right);
    }
}



//Function to get the list of student ids
void getStudentlist(ISSUE_TREE *root,int a[SIZE])
{
  static int i=0;
  if(root!=NULL)
  {
    if( root->key->bookissue_id !=0 )
    a[i++]=root->key->sid;
    getStudentlist(root->left,a);
    getStudentlist(root->right,a);
  }
}

//Funtion to list the issue details for given student id

void listBooksbyStudent(ISSUE_TREE *root,int id,int *n)
{
  if(root!=NULL)
  {    
    listBooksbyStudent(root->left,id,&(*n));
    if( root->key->sid == id)
    {
      (*n)++;
       printf("%d\t%d\t\t%s\t\t%s\n",id,root->key->book_id,root->key->issue_date,root->key->expiry_date);
    }
    listBooksbyStudent(root->right,id,&(*n));
  }
}




//Function to get the list of books issued for a student.

LIBRARY *getBooksofStudent(LIBRARY *root)
{
  
  int count,i,j,k,flag=0;
  LIBRARY *ptr=NULL;
  int ids[SIZE],final[SIZE];  
  int bcount;  
  ptr=root;
  count=SIZE;
  ptr->bstree = getBookIssueDB(); //Load latest issue details in tree
  
  for(i=0;i<SIZE;i++)
    ids[i]=0;
  
  getStudentlist(ptr->bstree,ids);     //get list of students for various books issued
    
  //Reove duplicated from id list  because one student can take more than one book
  
  for (i = 0; i<count-1; i++)
  {
    for(j=i+1;j<count;j++)
    {
      if (ids[i]==ids[j])
      {
        count=count-1;
        for(k=j;k<count;k++)
	   ids[k]=ids[k+1];
         flag=1;
        j = j-1;
      }
    }
  }
  
  //Now list the books issued to student
  bcount=0;
  printf("Student Id \tBook Id\t\tIssue Date\t\tExpiry Date\n");
  for(i=0;i<SIZE;i++)
  {
    if(ids[i]>0)
    {
    //printf("%d\t",ids[i]);
    listBooksbyStudent(ptr->bstree,ids[i],&bcount);
    if(bcount==0)
      printf("No books issued to student with id %d\n",ids[i]);
    }
  }  
  
  return ptr;
}
