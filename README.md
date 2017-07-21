# Wibbels_CSCI2270_FinalProject

// Erin "Jade" Wibbels

// CSCI 2270 - Professor Montero Quesada

// Final Project Phase 1 - Due 7/21 5pm


// Objectives:(with brainstorming comments)

// - Implement algorithms for standard operations on common data structures and discuss complexity of the operations.

// - Comment on the features of different traversal methods for graphs and other data structures.

// - Formulate and implament solutions to problems using fundamental graph algorithms (ie depth first/breadthfirst searches
// and shortest path algorithms.




// Phase 1 design plan::

// Book locator- 

// This program will use 2 different data structures. The first will be an RBT storing a list of New York Times best 
// selling books as structs. The second will be  a graph of local book stores. The two data structures will be linked by 
// vectors of pointers. The books will have vectors of pointers at each bookstore which carries the book and the bookstores
// will have a vector of pointers showing which books are in the stores inventory. You will be able to print the list of
// books, print the list of bookstores, search by book, 
search by bookstore, print the inventory of a bookstore, print the
// list of bookstores which carry the book, find the bookstore  which will have the lowest shipping cost on the book you 
// are looking for, order the book (this will reduce the available quantity) if the available quantity goes to 0 the book 
// will be removed from the stores inventory. 



// struct book        
// nodes in RBT

//{

//     string title;

//     string author;

//     string publisher;

//     vector<store> available; // this will contain pointers to all the book stores which have this book on hand.

//     bool isRed;


//     book *parent;

//     book *left;

//     book *right;     

//};

 


//struct bookStore     // vertices in graph

//{

//      string name;

//      vector<adjacent> adj; // vector of structs of adjacent vertices
        
//	vector <inventory> onHand;

//      bool visited;

//      int distance;

//};


// struct adjacent

//{

//    bookstore *v; 
// pointer to a book store

//    int weight; 
// cost to ship from v

//};


//struct inventory

//{

//    book *b;

//    int quantity;

//};



Class StoreMap
{

private: 
	
	bookStore start;
      
	bookStore end;
      
	book Root;


public:
	
	StoreMap(); 
	// constructor
	insertVertex(string name); 
	
	insertEdge( bookStore *start, bookStore *end, int weight); // between v1 and v2 weight = 40 (ex)
      
	void printStoreList(value);
      
	void printInventory(value);
	
	book* searchBook(value); // This will provide info on book and where to purchase it
      
	bookStore* searchStore(value); // This will return a pointer to a store.
      
	~StoreMap(); // deconstructor
      

};

// The Final project has the following requirements:

// - Contains at least 1 class : Graph Class, potentially another class for the flight price storage, BST maybe

// - Contains at least one graph and one other data structure: see above

// - Class should contain 7 public methods: 


// - Contains a well documented driver to run your code (Will need for testing anyhow)


