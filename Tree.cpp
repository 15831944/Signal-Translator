#include "Tree.h"

Tree::Tree()
{
	Head = nullptr;
	Tail = nullptr;
	List_size = 0;
	Last_Id = 0;
}

const TreeVectNode * Tree::GetHead()
{
	return Head;
}

const TreeVectNode * Tree::GetTail()
{
	return Tail;
}

void Tree::AddTail(const char *value, int input_id, int ipos, int jpos)
{
	if (value == nullptr)
	{
		return;
	}

	TreeVectNode *temp = new TreeVectNode;

	temp->str = new char[strlen(value) + 1];
	strcpy(temp->str, value);
	temp->id = input_id;
	temp->ipos = ipos;
	temp->jpos = jpos;
	List_size++;
	Last_Id = input_id;

	if (Head == nullptr)
	{
		Head = temp;
		temp->prev = nullptr;
		Tail = Head;
	}
	else
	{
		Tail->next = temp;
		Tail->next->prev = Tail;
		Tail = Tail->next;
	}

	Tail->next = nullptr;
	Head->prev = nullptr;
}

void Tree::Add_Down_Pointer(Tree* temp, TreeVectNode* node)
{
   // node->Down = temp;
}

void Tree::AddHead(const char *value, int input_id, int ipos, int jpos)
{
	if (value == nullptr)
	{
		return;
	}
	TreeVectNode *temp = new TreeVectNode;
	temp->str = new char[strlen(value) + 1];
	strcpy(temp->str, value);
	temp->id = input_id;
	temp->ipos = ipos;
	temp->jpos = jpos;
	List_size++;
	Last_Id = input_id;

	if (Head == nullptr)
	{
		Head = temp;
		temp->prev = nullptr;
		Tail = Head;
		Tail->next = nullptr;
	}
	else
	{
		Head->prev = temp;
		temp->next = Head;
		Head = temp;
	}
	Head->prev = nullptr;
}

void Tree::AddHead(const char *value, int input_id)
{
	if (value == nullptr)
	{
		return;
	}
	TreeVectNode *temp = new TreeVectNode;
	temp->str = new char[strlen(value) + 1];
	strcpy(temp->str, value);
	temp->id = input_id;
	List_size++;
	Last_Id = input_id;

	if (Head == nullptr)
	{
		Head = temp;
		temp->prev = nullptr;
		Tail = Head;
		Tail->next = nullptr;
	}
	else
	{
		Head->prev = temp;
		temp->next = Head;
		Head = temp;
	}
	Head->prev = nullptr;
}

void Tree::AddHead(const Tree *List, int input_id)
{
	if (List->Head == nullptr || List->Tail == nullptr || List == nullptr)
	{
		return;
	}
	TreeVectNode *temp;
	temp = List->Tail;
	while (temp != nullptr)
	{
		this->AddHead(temp->str, input_id);
		temp = temp->prev;
	}

}

void Tree::AddTail(const char *value, int input_id)
{
	if (value == nullptr)
	{
		return;
	}

	TreeVectNode *temp = new TreeVectNode;

	temp->str = new char[strlen(value) + 1];
	temp->str = new char[strlen(value) + 1];
	strcpy(temp->str, value);
	temp->id = input_id;
	List_size++;
	Last_Id = input_id;

	if (Head == nullptr)
	{
		Head = temp;
		temp->prev = nullptr;
		Tail = Head;
	}
	else
	{
		Tail->next = temp;
		Tail->next->prev = Tail;
		Tail = Tail->next;
	}
	Tail->next = nullptr;
	Head->prev = nullptr;
}

void Tree::AddTail(const Tree *List, int input_id)
{
	if (List->Head == nullptr || List->Tail == nullptr || List == nullptr)
	{
		return;
	}
	TreeVectNode *temp;
	temp = List->Head;
	while (temp != nullptr)
	{
		this->AddTail(temp->str, input_id);
		temp = temp->next;
	}
}



const char * Tree::GetAt(int count) const
{
	TreeVectNode *temp = Head;
	int i = 0;
	while (i < count)
	{
		temp = temp->next;
		i++;
		if (temp == nullptr)
		{
			return "NULL";
		}
	}
	return temp->str;
}

const TreeVectNode* Tree::Find(const char *elem)
{
	if (elem == nullptr) return nullptr;

	TreeVectNode * temp = Head;
	string temp_ = (char*)elem;

	while (temp != nullptr)
	{
		if (strcmp((const char *)temp->str, (const char *)elem) == 0)
		{
			break;
		}
		else if (strcmp(temp->str, temp_.c_str()) == 0)
		{
			break;
		}
		temp = temp->next;
	}
	return temp;
}

const TreeVectNode * Tree::Find(const char elem)
{
	if (elem == '\0') return nullptr;

	TreeVectNode * temp = Head;
	string temp_ = "";
	temp_ += elem;

	while (temp != nullptr)
	{
		if (strcmp(temp->str, temp_.c_str()) == 0)
		{
			break;
		}
		temp = temp->next;
	}
	return temp;
}

int Tree::Getsize() const
{
	return List_size;
}

bool Tree::IsEmpty() const
{
	return List_size == 0;
}

int Tree::GetLastId()
{
	return Last_Id;
}
