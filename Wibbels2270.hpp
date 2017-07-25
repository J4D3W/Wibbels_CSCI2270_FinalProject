#ifndef MOVIETREE_HPP
#define MOVIETREE_HPP
struct adjacent;
struct bookStore;
struct stores;
struct book;
struct stock;

struct adjacent
{
	bookStore *v;
	double weight; // shipping cost
};

struct stock
{
	book *b;
	int qty;
};

struct bookStore
{
	std::string name;
	int number;
	std::vector<adjacent>adj; //vector of structs containing adjacent vertices
	std::vector<stock>onShelf;
	bool visited;
	double cost;
	bookStore *parent;

	bookStore() {};
	bookStore(int _number, std::string _name)
	{
		name = _name;
		number = _number;
		visited = false;
		cost = 0;
		parent = nullptr;
	}
};

struct stores
{
	bookStore *v;
	int qty;
};
struct book {
	int ranking;
	std::string title;
	std::string author;
	std::string publisher;
	int weeksOnList;
	bool isRed;
	std::vector<stores>onHand;

	book *parent;
	book *leftChild;
	book *rightChild;

	book() {};

	book(int in_ranking, std::string in_title, std::string in_author, std::string in_publisher, int in_weeks)
	{
		ranking = in_ranking;
		title = in_title;
		author = in_author;
		publisher = in_publisher;
		weeksOnList = in_weeks;
		// Now that we are using nil these NULL's should be overwritten in addMovieNode.
		leftChild = nullptr;
		rightChild = nullptr;
		parent = nullptr;
		isRed = true;
	}

};

class bookTree
{

public:
	bookTree();
	void insertStore(int storeNumber, std::string name);
	void insertEdge(int startVal, int endVal, double weight);
	void printChain();
	virtual ~bookTree();
	void printBookList();
	void addBook(int in_ranking, std::string in_title, std::string in_author, std::string in_publisher, int in_weeks, int store1, int store2, int store3, int store4, int store5, int store6);
	book* findBook(std::string title);
	void orderBook(book* orderme);
	bool isValid();
	double dijkstra(bookStore *start, bookStore *end);
	bookStore *findStore(std::string name);
	void storeInfo(bookStore* result);

protected:

private:
	std::vector<bookStore>chain;
	void DeleteAll(book * node); //use this for the post-order traversal deletion of the tree
	void printBooks(book * node);
	void rbAddFixup(book * node); // called after insert to fix tree
	void leftRotate(book * x); //rotate the tree left with x as the root of the rotation
	//void rbDelete(book * z); //delete a node. Call this from deleteMovieNode, the actual delete functionality happens here.
	void rightRotate(book * x); //rotate the tree right with x as the root of the rotation
	int rbValid(book * node); //check if the tree is valid, with node as the root of the tree
	book* searchBookTree(book * node, std::string title);
	book *root;
	book *nil;


};

#endif // MOVIETREE_HPP



