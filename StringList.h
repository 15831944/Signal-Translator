#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

struct ListNode 
{
	char *str;
	int id;
	int ipos;
	int jpos;

	ListNode* next;
	ListNode* prev;
};

typedef const ListNode* POSITION;

class StringList {
private:

	ListNode *Head;
	ListNode *Tail;
	ListNode *id;
	int List_size;
	int Last_Id;

public:
	//Constructs an empty list for ListNode objects.
	StringList(void);
    ~StringList(void){};

	//Head/Tail Access 
	const ListNode* GetHead();//Returns the head element of the list 
	const ListNode* GetTail();//Returns the tail element of the list 

		//Operations 
	void AddHead(const char *value, int input_id, int ipos, int jpos);
	void AddTail(const char *value, int input_id, int ipos, int jpos);
	//Adds an element to the head of the list (makes a new head).
	void AddHead(const char *value, int input_id);
	//Adds all the elements in another list to the head of the list (makes a new head).
	void AddHead(const StringList *List, int input_id);
	//Adds an element to the tail of the list (makes a new tail).
	void AddTail(const char *value, int input_id);
	//Adds all the elements in another list to the tail of the list (makes a new tail).
	void AddTail(const StringList *List, int input_id);
	//Removes all the elements from this list.
	void RemoveAll();
	//Removes the element from the head of the list.
	void RemoveHead();
	//Removes the element from the tail of the list.
	void RemoveTail();

	//Iteration 
    //Gets the next element for iterating.
    POSITION GetNext();
    //Gets the previous element for iterating.
    POSITION GetPrev();

	//Retrieval/Modification
	POSITION GetHeadPosition();


	//Gets the element at a given position.
	const char* GetAt(int count)const;
	//Removes an element from this list as specified by position.
	void RemoveAt(int count);

	//Searching 
    //Gets the position of an element specified by string value.
	const ListNode* Find(const char *elem);
	//Gets the position of an element specified by a zero-based index.
	int FindIndex(char *elem)const;

	//Status 
    //Returns the number of elements in this list.
	int Getsize()const;
	//Tests for the empty list condition (no elements).
	bool IsEmpty()const;
	//Print node
	void Printnode(POSITION p);
	//Print all list
	void PrintList();

    const ListNode* Find(const char elem);
    //Gets the position of an element specified by string value.
    //Searching starts since current element "pos"
    ListNode* Find(const char* elem, ListNode* pos);

	int GetLastId();
};
