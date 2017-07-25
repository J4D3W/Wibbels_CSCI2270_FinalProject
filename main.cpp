// Erin "Jade" Wibbels
// CSCI 2270 - Professor Montero Quesada
// Final Project


//*****************************************************************************************************************
//                                   In House Book Locator 
//
// This program is designed for use in a bookstore.It is a quick reference for New York Times best sellers.These books
// are hard to keep on the shelf, so it allows employees to locate a book for a client and order it with the lowest 
// possible shipping cost.
// This program will use 2 different data structures. The first will be an RBT storing a list of New York Times best 
// selling books as structs. The second will be a graph of local book stores. The two data structures will be linked 
// by vectors of pointers. The books will have vectors of pointers at each bookstore which carries the book and the
// bookstores will have a vector of pointers showing which books are in the stores inventory. You will be able to print 
// the list of books(1), print the list of bookstores(2), search by book(3), search by bookstore(4), print the inventory 
// of a bookstore(4.1), print the list of bookstores which carry the book(3.1), find the bookstore which will have the 
// lowest shipping cost on the book you are looking for(3.2), order the book(3.3) (this will reduce the available quantity)
// if the available quantity goes to 0 the book will be removed from the stores inventory.
//
//*******************************************************************************************************************

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "Wibbels2270.hpp"

book* findMin(book *z, book *nil);

int main()
{

	std::string filename;
	int choice;
	bool finished = false;
	bookTree in_Tree;

	std::cout << std::setprecision(2) << std::fixed;

	std::cout << std::endl << std::endl;
	std::cout << "Welcome to the New York Best Seller Book Locator System" << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl << std::endl;

	filename = "StoreList.txt";
	std::ifstream inFile;
	inFile.open(filename);

	if (inFile.is_open())
		std::cout << " - Updating Store List" << std::endl;
	else
		std::cout << "error 1" << std::endl;

	while (inFile.good())
	{
		int storeNumber;
		std::string token, storeName;

		getline(inFile, token, ',');
		storeNumber = stoi(token);
		//std::cout << storeNumber << " ";
		getline(inFile, storeName, '\n');
		//std::cout << storeName << std::endl;

		in_Tree.insertStore(storeNumber, storeName);

		if (inFile.eof())
		{
			inFile.close();
			//std::cout << "Closing file" << std::endl;
			break;
		}
	}

	filename = "shippingInfo.txt";
	inFile.open(filename);
	if (inFile.is_open())
		std::cout << " - Updating Shipping Info" << std::endl;
	else
		std::cout << "error 2" << std::endl;

	while (inFile.good())
	{
		int start, finish;
		double cost;
		std::string token;

		getline(inFile, token, ',');
		start = stoi(token);
		getline(inFile, token, ',');
		finish = stoi(token);
		getline(inFile, token, '\n');
		cost = stod(token);

		in_Tree.insertEdge(start, finish, cost);
		if (inFile.eof())
		{
			inFile.close();
			//std::cout << "Closing file" << std::endl;
			break;
		}

	}

	filename = "NewYorkTimes.txt";
	inFile.open(filename);
	if (inFile.is_open())
		std::cout << " - Updating Best Sellers List" << std::endl << std::endl;
	else
		std::cout << "error 3" << std::endl;

	//cout << "new Movie Tree object created " << endl;

	while (inFile.good())
	{
		//std::cout << "in Read in" << std::endl;
		std::string token;
		std::string in_title;
		int in_ranking;
		std::string in_author;
		std::string in_publisher;
		int in_weeks;
		int store1;
		int store2;
		int store3;
		int store4;
		int store5;
		int store6;

		getline(inFile, token, ',');
		in_ranking = stoi(token);
		//std::cout << in_ranking << " ";
		getline(inFile, in_title, ',');
		//std::cout << in_title << " ";
		getline(inFile, in_author, ',');
		//std::cout << in_author << " ";
		getline(inFile, in_publisher, ',');
		//std::cout << in_publisher << ',';
		getline(inFile, token, ',');
		in_weeks = stoi(token);
		//std::cout << in_weeks << std::endl;
		getline(inFile, token, ',');
		store1 = stoi(token);
		getline(inFile, token, ',');
		store2 = stoi(token);
		getline(inFile, token, ',');
		store3 = stoi(token);
		getline(inFile, token, ',');
		store4 = stoi(token);
		getline(inFile, token, ',');
		store5 = stoi(token);
		getline(inFile, token, '\n');
		store6 = stoi(token);

		in_Tree.addBook(in_ranking, in_title, in_author, in_publisher, in_weeks, store1, store2, store3, store4, store5, store6);
		if (inFile.eof())
			inFile.close();
	}

	bool valid = false;
	valid = in_Tree.isValid();
	//if (valid == true)
	//std::cout << "this is a red black tree" << std::endl;
	//else
	//std::cout << "Problem with balancing" << std::endl;

	while (finished == false)
	{
		std::cout << "=========Main Menu=========" << std::endl;
		std::cout << "1. Print Best Sellers List" << std::endl;
		std::cout << "2. Print List of Local Stores" << std::endl;
		std::cout << "3. Search by Book" << std::endl;
		std::cout << "4. Search by Store" << std::endl;
		std::cout << "5. Order a Book" << std::endl;
		std::cout << "6. Exit" << std::endl;

		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			in_Tree.printBookList();
			break;
		}
		case 2:
		{
			in_Tree.printChain();
			break;
		}
		case 3:
		{
			int order;
			book *result;
			std::string _title;
			std::cout << "Enter title:" << std::endl;
			std::cin.ignore();
			std::getline(std::cin, _title);
			result = in_Tree.findBook(_title);
			if (result != nullptr)
			{
				std::cout << std::endl << "Would you like to:\n 1. Order this book \n 2. Return to main menu \n" << std::endl;
				std::cin >> order;
				if (order == 1)
				{
					in_Tree.orderBook(result);
				}
			}
			break;
		}
		case 4:
		{
			bookStore *result;
			std::string _name;
			std::cout << "Enter Store Name" << std::endl;
			std::cin.ignore();
			getline(std::cin, _name);
			result = in_Tree.findStore(_name);
			in_Tree.storeInfo(result);
			break;
		}
		case 5:
		{
			book* result;
			std::string _title;
			std::cout << "Enter book title" << std::endl;
			std::cin.ignore();
			std::getline(std::cin, _title);
			result = in_Tree.findBook(_title);
			if (result == nullptr)
			{
				break;
			}
			else
			{
				std::cout << result->title << std::endl;
				in_Tree.orderBook(result);
			}
			break;
		}

		case 6:
		{
			std::cout << "Goodbye!" << std::endl;
			finished = true;
			break;
		}
		default:
		{
			std::cout << "Please enter a valid option" << std::endl;
			break;
		}
		}
	}
	return 0;
}


