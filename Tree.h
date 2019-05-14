#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Syntax.h"


class Tree;
using namespace std;

struct TreeVectNode
{
	char *str;
	int id;
	int ipos;
	int jpos;

	TreeVectNode* next;
	TreeVectNode* prev;

    TreeVectNode* down;
    TreeVectNode* up;
};

class Tree
{
private:
	TreeVectNode* Up;
	TreeVectNode* Head;
	TreeVectNode* Tail;
	int List_size;
	int Last_Id;

public:

	Tree(void);
	~Tree(void) {};

	//Head/Tail Access 
	const TreeVectNode* GetHead();//Returns the head element of the list 
	const TreeVectNode* GetTail();//Returns the tail element of the list 

	//Operations 
	void AddHead(const char *value, int input_id, int ipos, int jpos);
	void Add_Down_Pointer(Tree* temp, TreeVectNode* node);
	void AddTail(const char *value, int input_id, int ipos, int jpos);
	//Adds an element to the head of the list (makes a new head).
	void AddHead(const char *value, int input_id);
	//Adds all the elements in another list to the head of the list (makes a new head).
	void AddHead(const Tree *List, int input_id);
	//Adds an element to the tail of the list (makes a new tail).
	void AddTail(const char *value, int input_id);
	//Adds all the elements in another list to the tail of the list (makes a new tail).
	void AddTail(const Tree *List, int input_id);

	//Gets the element at a given position.
	const char* GetAt(int count)const;

	//Searching 
//Gets the position of an element specified by string value.
	const TreeVectNode* Find(const char *elem);

	//Status 
//Returns the number of elements in this list.
	int Getsize()const;
	//Tests for the empty list condition (no elements).
	bool IsEmpty()const;
	//Print all list
	void PrintList();

	const TreeVectNode* Find(const char elem);

	int GetLastId();
};
