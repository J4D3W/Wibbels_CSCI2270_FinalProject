#Erin "Jade" Wibbels 
## CSCI 2270 - Professor Montero Quesada 
### Final Project Phase 2 

Project Summary

Book locator- This program is designed for use in a bookstore. It is a quick reference for New York Times best sellers. These books are hard to keep on the shelf, so it allow employees to locate a book for a client and order it with the lowest possible shipping cost.

   This program will use 2 different data structures. The first will be an RBT storing a list of New York Times best selling books as structs. The second will be a graph of local book stores. The two data structures will be linked by vectors of pointers. The books will have vectors of pointers at each bookstore which carries the book and the bookstores will have a vector of pointers showing which books are in the stores inventory. You will be able to print the list of books, print the list of bookstores, search by book, search by bookstore, print the inventory of a bookstore, print the list of bookstores which carry the book, find the bookstore which will have the lowest shipping cost on the book you are looking for, order the book (this will reduce the available quantity) if the available quantity goes to 0 the book will be removed from the stores inventory. If ALL copies of a book have been bought from all linked stores, the program will tell the user that the book is sold out.

How to Run

   the main.cpp file will include the header file and is hard coded to read in the three text files. The user should just have store all associated files in the same directory and then run main.

Dependencies

All files need to be in the same directory, and called by the compiler. The user does not need to know any of the filenames to run. Main will call the text files on its own.

System Requirements

This program was written as a win 32 console application. It should run in any console on mac and windows.

Erin "Jade" Wibbels

Open issues/bugs

None that I am aware of. 

