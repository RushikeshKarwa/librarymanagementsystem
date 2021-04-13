#include "lib.h"

int heightStudent(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

STUDENT_TREE *newStudentNode(student *key)
{
    STUDENT_TREE *node = (STUDENT_TREE *)malloc(sizeof(STUDENT_TREE));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

STUDENT_TREE *rightRotateStudent(STUDENT_TREE *y)
{
    STUDENT_TREE *x = y->left;
    STUDENT_TREE *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(heightStudent(y->left), heightStudent(y->right))+1;
    x->height = max(heightStudent(x->left), heightStudent(x->right))+1;

    return x;
}


STUDENT_TREE *leftRotateStudent(STUDENT_TREE *x)
{
    STUDENT_TREE *y = x->right;
    STUDENT_TREE *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max(heightStudent(x->left), heightStudent(x->right))+1;
    y->height = max(heightStudent(y->left), heightStudent(y->right))+1;

    return y;
}
 
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
  fp=fopen(studentDB,"rb"); 
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
  fp=fopen(studentDB,"rb"); 

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
  fp=fopen(studentDB,"ab+");

  if(fp==NULL)
  {
          printf("student database open error\n");
           exit(1);
   }
  fwrite(key,sizeof(student),1,fp);  
  fclose(fp);
  
}

STUDENT_TREE *insertStudent(STUDENT_TREE *node,student *key)
{
    
    int balance;

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
       else 
       {
	 printf("ID Already exists!!\n");
         return node;
       } 
  
        node->height = 1 + max(heightStudent(node->left),heightStudent(node->right));

        balance = getBalanceStudent(node);

        if (balance > 1 && (key->sid < node->left->key->sid))
           return rightRotateStudent(node);

        if (balance < -1 && (key->sid > node->right->key->sid))
          return leftRotateStudent(node);
 

        if (balance > 1 && (key->sid > node->left->key->sid))
        {
           node->left =  leftRotateStudent(node->left);
           return rightRotateStudent(node);
        }
 
         if (balance < -1 && (key->sid < node->right->key->sid))
         {
            node->right = rightRotateStudent(node->right);
            return leftRotateStudent(node);
         }
      return node;
      }
}


void createStudentRecords(STUDENT_TREE *root)
{
  if(root!=NULL)
  {
    createStudentRecords(root->left);
    insertStudentRecord(root->key);
    createStudentRecords(root->right);
  }
}


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
    
    fp=fopen(studentDB,"rb"); 

    if(fp==NULL)
    {
           printf("student database open error\n");
           exit(1);
    }
    fseek(fp,0,SEEK_SET);//search from start
    s=(student *)malloc(sizeof(student));
    memset(s,0,sizeof(student));
         
    while((fread(s,sizeof(student),1,fp))!=0)
    {          
          if(s->sid == id)  
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
  
   fp1=fopen(input,"r"); 
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

      s=(student *)malloc(sizeof(student));
      i=0;j=0;
      ptr=strtok(str,",");
      strcpy(word[i++],ptr);
       
      while((ptr=strtok(NULL,","))!=NULL)
      {
          	strcpy(word[i++],ptr);	  
      }

      s->sid = atoi(word[j++]);  
      strcpy(s->sname,word[j]);
      i=j=0;
      root = insertStudent(root, s);
      memset(str,0,sizeof(str));     
    }

   fclose(fp1);
   createStudentRecords(root);
   return root;
}

void listBook(BOOK_TREE *l)
{	
  inOrderBook(l);
}

//Function to traverse book tree in inorder and print the details of book
void inOrderBook(BOOK_TREE *root)
{
    if(root != NULL)
    {
        inOrderBook(root->left);
	printf("%5d\t%-40s\t%4d\n", root->key->book_id,root->key->title,root->key->quantity);
        inOrderBook(root->right);
    }
}

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
