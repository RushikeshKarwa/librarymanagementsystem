# librarymanagementsystem





<h3>Brief of LMS Application:</h3>


During startup, application creates dat files by considering sample data provided in txt files. Creation of dat files is one time operation and in subsequent sessions of application, data is preloaded from existing dat files. This was considered to avoid manual data entry of initial data and create initial data in efficient manner. LMS application uses AVL tree to store data in memory and perform various search operations. Self balancing AVL tree is chosen in this application since majority of tasks need searching. Queue data structue is used to store pending book requests for a specific book so that requests can be enqueued and dequeued in an efficient manner. Queue is implemented using linked lists.
so that memory management is dynamic in nature. Using dat files(external data structure) data persistance is met and data of different elements like book, book issues, book requests and student are stored in different dat files. Each insert, update andl delete operation data is recorded in dat file along with internal tree structure changes so tha dat file data is permanent and accurate. Data of each element i..e Student, Book, Book Issue are loaded into separate AVL trees during program execution.Book Request details are loaded into Queue. Data of all elements are stored in a Structure (Student tree, Book tree, Book Issue tree and Book Request Queues).





<h3>Detailed Description of application:</h3>

During application startup, initDB() function is invoked.

Functionality of initDB() : This function checks if dat files of Student, Book, Book Issue exists or not. If any of them are not present, During creation of initial data is first loaded into AVL tree. In impementation of AVL tree creation, duplicate data is not allowed. This property is used to store unique data in dat files and avoid any duplicate data in dat files as well.
initial dat file be created using respective .txt files(input files). If dat file exists, it loads data in file into respective data structure.

On return from initDB(), main invokes a menu driven interactive session to perform various library management sub tasks. It waits for user input and perfors requested operation as per the choice of user. Details of sub tasks are described below. Application will be running and in active state till user wishes to exit from the application. Once the user choses to exit, application performs clean up of memory and quits.
