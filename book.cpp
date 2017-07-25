#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "Wibbels2270.hpp"


bookTree::bookTree()
{
	nil = new book();
	nil->title = "NILPTR";
	nil->parent = nullptr;
	nil->leftChild = nil;
	nil->rightChild = nil;
	nil->isRed = false;
	root = nil;
	return;
}
bookTree::~bookTree()
{
	// 1 clear bookstore vectors
	// - adj 
	// - on shelf
	// 2 clear book vectors
	// - on hand
	// 3 clear graph vector (chain)
	int i = 0;
	int j = 0;
	while(!chain.empty())
	{
		bookStore *closing = &chain[i];
		while(!closing->onShelf.empty())
		{
			stock *bc = &closing->onShelf[0];
			closing->onShelf.erase(closing->onShelf.begin()+j);
		}
		while (!closing->adj.empty())
		{
			adjacent *erase = &closing->adj[0];
			closing->adj.erase(closing->adj.begin() + j);
		}
		chain.erase(chain.begin());
	}
	std::cout << "- Cleared Stores inventory and Shipping information \n";
	// 4 delete RBT (done below)
	DeleteAll(root);
	std::cout << "- Cleared Best Seller List " << std::endl;
	delete root;

}

bool bookTree::isValid()
{
	bool valid = rbValid(root);
	return valid;
}

void bookTree::addBook(int in_ranking, std::string in_title, std::string in_author, std::string in_publisher, int in_weeks, int store1, int store2, int store3, int store4, int store5, int store6)
{
	book *temp = new book(in_ranking, in_title, in_author, in_publisher, in_weeks);
	temp->leftChild = nil;
	temp->rightChild = nil;
	temp->isRed = true;

	stores inventory;
	stock tome;
	tome.b = temp;

	if (store1 != 0)
	{
		inventory.v = &chain[0];
		inventory.qty = store1;
		temp->onHand.push_back(inventory);
		tome.qty = store1;
		chain[0].onShelf.push_back(tome);
	}
	if (store2 != 0)
	{
		inventory.v = &chain[1];
		inventory.qty = store2;
		temp->onHand.push_back(inventory);
		tome.qty = store2;
		chain[1].onShelf.push_back(tome);
	}
	if (store3 != 0)
	{
		inventory.v = &chain[2];
		inventory.qty = store3;
		temp->onHand.push_back(inventory);
		tome.qty = store3;
		chain[2].onShelf.push_back(tome);
	}
	if (store4 != 0)
	{
		inventory.v = &chain[3];
		inventory.qty = store4;
		temp->onHand.push_back(inventory);
		tome.qty = store4;
		chain[3].onShelf.push_back(tome);
	}
	if (store5 != 0)
	{
		inventory.v = &chain[4];
		inventory.qty = store5;
		temp->onHand.push_back(inventory);
		tome.qty = store5;
		chain[4].onShelf.push_back(tome);
	}
	if (store6 != 0)
	{
		inventory.v = &chain[5];
		inventory.qty = store6;
		temp->onHand.push_back(inventory);
		tome.qty = store6;
		chain[5].onShelf.push_back(tome);
	}


	book *walker;
	walker = root;
	//cout << "Movie node " << temp->title << " created" << endl;
	while (walker != nil)
	{
		//cout << "walker is " << walker->title << endl;
		temp->parent = walker;
		if (temp->title < walker->title)
		{
			walker = walker->leftChild;
		}
		else
		{
			walker = walker->rightChild;
		}

	}
	walker = temp->parent;
	if (root == nil)
	{
		root = temp;
		root->parent = nullptr;
		//cout << root->title << " is root" << endl;
	}
	else if (temp->title< walker->title)
	{
		walker->leftChild = temp;
		temp->parent = walker;
		//cout << temp->title << " is left child of " << temp->parent->title << endl;
	}
	else
	{
		walker->rightChild = temp;
		temp->parent = walker;
		//cout << temp->title << " is right child of " << temp->parent->title << endl;
	}

	//std::cout << temp->title << " added to tree with " << root->title << " as root " << std::endl;
	rbAddFixup(temp);
}

void bookTree::printBookList()
{
	printBooks(root);
}

void bookTree::printBooks(book * node)
{
	if (node == nil) // end the recursion if walker == nullptr
		return;
	printBooks(node->leftChild);            // display the left subtree
	std::cout << "Title: " << node->title << " Weeks on List: " << node->weeksOnList << std::endl; // display the current node
	printBooks(node->rightChild);
}

void bookTree::rbAddFixup(book * node)
{
	book *uncle;
	//std::cout << "In fix up" << std::endl;
	while (node != root && node->parent->isRed == true)
	{
		if (node->parent == node->parent->parent->leftChild)
		{
			uncle = node->parent->parent->rightChild;
			if (uncle->isRed == true)
			{
				//cout << "Case 1 " << node->title << endl;
				//case 1 (left)
				node->parent->isRed = false;
				uncle->isRed = false;
				node->parent->parent->isRed = true;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->rightChild)
				{
					//cout << "Case 2 " << node->title << endl;
					// Case 2 see below node is now left child
					node = node->parent;
					leftRotate(node);
				}
				node->parent->isRed = false;
				node->parent->parent->isRed = true;
				rightRotate(node->parent->parent);
			}
		}
		else
		{
			uncle = node->parent->parent->leftChild;
			if (uncle->isRed == true)
			{
				//cout << "Case 1 " << node->title << endl;
				//case 1 (left)
				node->parent->isRed = false;
				uncle->isRed = false;
				node->parent->parent->isRed = true;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->leftChild)
				{
					node = node->parent;
					rightRotate(node);
					//cout << "Case 2 " << node->title << endl;
					// now can use Case 3 left
				}
				//node = node->leftChild;
				node->parent->isRed = false;
				node->parent->parent->isRed = true;
				leftRotate(node->parent->parent);
			}
		}
	}
	root->isRed = false;
	//std::cout << "in fix up " << root->title << " is black" << std::endl;
	return;
}
void bookTree::leftRotate(book * x)
{
	book *y;
	y = x->rightChild;
	x->rightChild = y->leftChild;
	if (y->leftChild != nil)
		y->leftChild->parent = x;
	y->parent = x->parent;
	if (x->parent == nullptr)
		root = y;
	else if (x == x->parent->leftChild)
		x->parent->leftChild = y;
	else
		x->parent->rightChild = y;
	y->leftChild = x;
	x->parent = y;
	//cout << "rotating root = " << root->title << endl;
}

void bookTree::rightRotate(book * y)
{
	book *x;
	x = y->leftChild;
	y->leftChild = x->rightChild;
	if (x->rightChild != nil)
		x->rightChild->parent = y;
	x->parent = y->parent;
	if (y->parent == nullptr)
		root = x;
	else if (y == (y->parent->leftChild))
		y->parent->leftChild = x;
	else
		y->parent->rightChild = x;
	x->rightChild = y;
	y->parent = x;
}

// Returns 0 if the tree is invalid, otherwise returns the black node height. 
int bookTree::rbValid(book * node)
{
	int lh = 0;
	int rh = 0;

	// If we are at a nil node just return 1
	if (node == nil)
		return 1;

	else
	{
		// First check for consecutive red links. 
		if (node->isRed)
		{
			if (node->leftChild->isRed || node->rightChild->isRed)
			{
				//cout << "This tree contains a red violation" << endl;
				return 0;
			}
		}

		// Check for valid binary search tree. 
		if ((node->leftChild != nil && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != nil && node->rightChild->title.compare(node->title) < 0))
		{
			//cout << "This tree contains a binary tree violation" << endl;
			return 0;
		}

		// Deteremine the height of let and right children. 
		lh = rbValid(node->leftChild);
		rh = rbValid(node->rightChild);

		// black height mismatch 
		if (lh != 0 && rh != 0 && lh != rh)
		{
			//cout << "This tree contains a black height violation" << endl;
			return 0;
		}

		// If neither height is zero, incrament if it if black. 
		if (lh != 0 && rh != 0)
		{
			if (node->isRed)
				return lh;
			else
				return lh + 1;
		}

		else
			return 0;

	}
}

book* bookTree::findBook(std::string title)
{
	book *result = searchBookTree(root, title);
	if (result == nullptr)
	{
		std::cout << "Book not found." << std::endl;
	}
	else
	{
		std::cout << "Book Info:" << std::endl;
		std::cout << "===========" << std::endl;
		std::cout << "Ranking: " << result->ranking << std::endl;
		std::cout << "Title:" << result->title << std::endl;
		std::cout << "Author:" << result->author << std::endl;
		std::cout << "Publiher:" << result->publisher << std::endl;
		std::cout << "Weeks on Best Seller List: " << result->weeksOnList << std::endl;
		//std::cout << "Locations Where this book is available: " << std::endl;
		// for(int i = 0; i< result->onHand.size; i++)
		//{
		//cout << result->onHand[i].name << std::endl;
		//}
		//cout << "children are " << result->leftChild->title << " " << result->rightChild->title << endl;
		//if (result == result->parent->leftChild)
		//cout << "Left child of " << result->parent->title << endl;
		//else
		//cout << "Right child of " << result->parent->title << endl;
	}
	return result;
}

book* bookTree::searchBookTree(book* node, std::string title)
{
	book *walker = root;

	while (walker != nil)
	{
		if (walker->title == title)
		{
			return walker;
		}
		else if (title < walker->title)
		{
			walker = walker->leftChild;
		}
		else
		{
			walker = walker->rightChild;
		}
	}
	if (walker == nil)
	{
		return nullptr;
	}
	return nullptr;
}

book* findMin(book *z, book *nil)
{
	book *walker = z;
	while (walker->leftChild != nil)
		walker = walker->leftChild;
	return walker;
}

void bookTree::DeleteAll(book * node)
{
	book *empty = root;
	while (root->leftChild != nil || root->rightChild != nil)
	{
		//cout << "In while loop " << empty->title << endl;
		while (empty->leftChild != nil || empty->rightChild != nil)
		{
			//cout << "In inner while loop" << endl;
			if (empty->leftChild != nil)
			{
				//cout << empty->title << " to " << empty->leftChild->title << endl;
				empty = empty->leftChild;
			}
			else if (empty->rightChild != nil)
			{
				//cout << empty->title << " to " << empty->rightChild->title << endl;
				empty = empty->rightChild;

			}

		}
		if (empty->leftChild == nil && empty->rightChild == nil)
		{
			//cout << empty->parent->title << endl;
			//cout << empty->parent->rightChild->title << endl;
			//std::cout << "Clearing: " << empty->title << std::endl;
			if (empty == (empty->parent->leftChild))
			{
				//cout << empty->parent->title << endl;
				empty->parent->leftChild = nil;
			}
			else if (empty == (empty->parent->rightChild))
			{
				//cout << empty->parent->title << endl;
				empty->parent->rightChild = nil;
			}
			delete empty;
			//cout << "empty deleted" << endl;
			empty = root;
		}
	}
	return;
}

void bookTree::insertStore(int storeNumber, std::string _name)
{
	bookStore temp;
	temp = bookStore(storeNumber, _name);

	bool found = false;
	for (unsigned int i = 0; i < chain.size(); i++)
	{
		if (chain[i].number == temp.number)
		{
			found = true;
			break;
		}
	}
	if (found == false)
	{
		chain.push_back(temp); // vertex created
							   //std::cout << "adding " << temp.name << std::endl;
	}
}

void bookTree::insertEdge(int start, int finish, double cost)
{
	for (unsigned int i = 0; i < chain.size(); i++)
	{
		if (chain[i].number == start)
		{
			for (unsigned int j = 0; j < chain.size(); j++)
			{
				if (chain[j].number == finish)
				{
					adjacent av, av2;
					av.v = &chain[j];
					av.weight = cost;
					chain[i].adj.push_back(av);  // adds edge from start to finish
					av2.v = &chain[i];
					av2.weight = cost;
					chain[j].adj.push_back(av2); // adds same edge from finish to start
				}
			}
		}
	}
}

void bookTree::printChain()
{
	int shipping;
	std::cout << "Print Options \n";
	std::cout << "======================== \n";
	std::cout << "1. Print Store List Only" << std::endl;
	std::cout << "2. Print Store List with Current Shipping Charges \n";
	std::cin >> shipping;

	if (shipping == 1 || shipping == 2)
	{
		std::cout << "======Stores in Network======" << std::endl;
		for (unsigned int x = 0; x < chain.size(); x++)
		{
			std::cout << x + 1 << ". " << chain[x].name << " Store Number: " << chain[x].number << std::endl;
			if (shipping == 2)
			{
				std::cout << "Shipping Rates:" << std::endl;
				std::cout << "--------------------------------------------" << std::endl;
				for (unsigned int y = 0; y < chain[x].adj.size(); y++)
				{
					std::cout << chain[x].adj[y].v->name << " $" << chain[x].adj[y].weight << std::endl;
				}
				std::cout << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Invalid entry. \n Exiting to main menu. \n";
		return;
	}
}

void bookTree::orderBook(book *orderme)
{
	int store_number;
	double cost = 100000.00;
	double minCost = 0;
	bookStore *end;
	bookStore *start = nullptr;
	bookStore *min;

	if (orderme->onHand.empty())
	{
		std::cout << "Sorry this book is sold out at all stores in network. \n Please try again next week.\n";
			return;
	}
	std::cout << "Enter current store number \n";
	std::cin >> store_number;
	for (unsigned int j = 0; j < chain.size(); j++)
	{
		if (chain[j].number == store_number)
		{
			start = &chain[j];
		}
	}
	if (start == nullptr)
	{
		std::cout << "Invalid Store Number \n";
		return;
	}
	for (unsigned int i = 0; i < orderme->onHand.size(); i++)
	{
		end = orderme->onHand[i].v;
		minCost = dijkstra(start, end);
		if (minCost == 0)
		{
			std::cout << "Great News! That book is in stock at your current location!\n" <<
				"Please refer to the fiction section under " << orderme->author << std::endl;
			return;
		}
		if (minCost < cost)
		{
			cost = minCost;
			min = orderme->onHand[i].v;
		}
		for (unsigned int f = 0; f < chain.size(); f++)
		{
			chain[f].cost = 0;
			chain[f].visited = false;
		}
	}
	if (start->number != end->number)
	{
		std::cout << "Lowest shipping rate found: \n";
		std::cout << "Ordered " << orderme->title << " from " << min->name << " for $" << cost << std::endl;
	}
	for (unsigned int r = 0; r < min->onShelf.size(); r++)
	{
		if (min->onShelf[r].b->title == orderme->title)
		{
			min->onShelf[r].qty--;
			if (min->onShelf[r].qty == 0)
			{
				stock *eraseMe = &min->onShelf[r];
				min->onShelf.erase(min->onShelf.begin() + r);
				for (unsigned int q = 0; q < orderme->onHand.size(); q++)
				{
					if (orderme->onHand[q].v == min)
					{
						stores *erase = &orderme->onHand[q];
						orderme->onHand.erase(orderme->onHand.begin() + q);
					}
				}
			}
		}
	}
}

double bookTree::dijkstra(bookStore *start, bookStore *end)
{
	for (int j = 0; j < chain.size(); j++)
	{
		chain[j].cost = 0;
		chain[j].visited = false;
		chain[j].parent = nullptr;
	}
	start->visited = true;
	start->cost = 0;
	std::vector<bookStore*>solved;
	//std::vector<bookStore*>path;
	solved.push_back(start);
	//path.push_back(start);
	adjacent *v;
	bookStore *u;
	bookStore *minVertex;
	bookStore *prev;
	//double orderCost = 0;

	while (end->visited == false)
	{
		double minCost = 100000.00;
		for (unsigned int i = 0; i < solved.size(); i++)
		{
			//std::cout << "in first for loop \n";
			u = solved[i];
			for (unsigned int j = 0; j < u->adj.size(); j++)
			{
				//std::cout << "in second for loop \n";
				v = &solved[i]->adj[j];
				if (v->v->visited == false)
				{
					//std::cout << "in first if \n";
					double cost = u->cost + v->weight;
					//std::cout << " cost is " << cost << std::endl ;
					if (cost < minCost)
					{
						//std::cout << "in second if \n";
						minCost = cost;
						minVertex = v->v;
						prev = u;
					}
				}
			}
		}
		solved.push_back(minVertex);
		minVertex->cost = minCost;
		//std::cout << minVertex->name << " " << minVertex->cost << std::endl;
		minVertex->parent = prev;
		minVertex->visited = true;
		//orderCost = minCost;
	}
	//std::cout << solved[solved.size() - 1]->cost << "returning \n";
	return solved[solved.size() - 1]->cost;
}

bookStore* bookTree::findStore(std::string name)
{
	for (unsigned int i = 0; i < chain.size(); i++)
	{
		if (chain[i].name == name)
		{
			return &chain[i];
		}
	}
	std::cout << "Store not found. \n";
	return nullptr;
}

void bookTree::storeInfo(bookStore* result)
{
	int printinv = 0;
	std::cout << "=========STORE INFO========= \n";
	std::cout << "Store Name: " << result->name << std::endl;
	std::cout << "Store Number: " << result->number << std::endl;
	std::cout << "\n1. Print list of all best sellers available at this location. \n";
	std::cout << "2. Return to main menu. \n";

	std::cin >> printinv;
	switch (printinv)
	{
	case 1:
	{
		std::cout << "Best Sellers Available at your location: \n";
		std::cout << "====================================\n";
		for (unsigned int w = 0; w < result->onShelf.size(); w++)
		{
			std::cout << std::endl << w + 1 << ". Title: " << result->onShelf[w].b->title << std::endl;
			std::cout << "Quantity on Hand: " << result->onShelf[w].qty << std::endl;
		}
	}
	case 2:
	{
		return;
	}
	default:
		std::cout << "Invalid option selected. \n Exiting search. \n";
		return;
	}

}

