#include "StringList.h"

StringList::StringList()
{
	Head = nullptr;
	Tail = nullptr;
	List_size = 0;
}

const ListNode * StringList::GetHead()
{
	return Head;
}

const ListNode * StringList::GetTail()
{
	return Tail;
}

void StringList::AddTail(const char *value, int input_id, int ipos, int jpos)
{
	if (value == nullptr)
	{
		return;
	}

	ListNode *temp = new ListNode;

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

void StringList::AddHead(const char *value, int input_id, int ipos, int jpos)
{
	if (value == nullptr)
	{
		return;
	}
	ListNode *temp = new ListNode;
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

void StringList::AddHead(const char *value, int input_id)
{
	if (value == nullptr)
	{
		return;
	}
	ListNode *temp = new ListNode;
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

void StringList::AddHead(const StringList *List, int input_id)
{
	if (List->Head == nullptr || List->Tail == nullptr || List == nullptr)
	{
		return;
	}
	ListNode *temp;
	temp = List->Tail;
	while (temp != nullptr)
	{
		this->AddHead(temp->str, input_id);
		temp = temp->prev;
	}

}

void StringList::AddTail(const char *value, int input_id)
{
	if (value == nullptr)
	{
		return;
	}

	ListNode *temp = new ListNode;

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

void StringList::AddTail(const StringList *List, int input_id)
{
	if (List->Head == nullptr || List->Tail == nullptr || List == nullptr)
	{
		return;
	}
	ListNode *temp;
	temp = List->Head;
	while (temp != nullptr)
	{
		this->AddTail(temp->str, input_id);
		temp = temp->next;
	}
}

void StringList::RemoveAll()
{
	if (Head == nullptr)
		return;

	while (Head->next != nullptr)
	{
		Head = Head->next;
		delete[] Head->prev->str;
		delete[] Head->prev;
	}
	delete[] Head->str;
	delete[] Head;

	Head = nullptr;
	Tail = nullptr;
	List_size = 0;
}

void StringList::RemoveHead()
{
	if (Head != nullptr)
	{
		delete[] Head->str;
		Head = Head->next;
		delete[] Head->prev;
		List_size--;
	}
}

void StringList::RemoveTail()
{
	if (Tail != nullptr)
	{
		delete[] Tail->str;
		Tail = Tail->prev;
		delete[] Tail->next;
		Tail->next = nullptr;
		List_size--;
	}
}

POSITION StringList::GetNext()
{
	if (id != nullptr)
		id = id->next;
	return POSITION(id);
}

POSITION StringList::GetPrev()
{
	if (id != nullptr)
		id = id->prev;
	return POSITION(id);
}

POSITION StringList::GetHeadPosition()
{
	id = Head;
	return POSITION(Head);
}

const char * StringList::GetAt(int count) const
{
	ListNode *temp = Head;
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

void StringList::RemoveAt(int count)
{
	if (count > List_size || count < 0)
	{
		return;
	}
	int i = 0;
	ListNode *tail, *ptr1, *ptr2 = Head;

	while (i < count)
	{
		ptr2 = ptr2->next;
		i++;
	}
	tail = ptr2->prev;
	ptr1 = ptr2->next;
	if (tail == nullptr) {
		this->RemoveHead();
		return;
	}
	if (ptr1 == nullptr) {
		this->RemoveTail();
		return;
	}
	tail->next = ptr1;
	ptr1->prev = tail;
	List_size--;

	delete[] ptr2;
}

const ListNode * StringList::Find(const char *elem)
{
	if (elem == nullptr) return nullptr;

	ListNode * temp = Head;
	string temp_ = (char*)elem;
	
	while (temp != nullptr)
	{
		if (strcmp((const char *)temp->str, (const char *)elem) == 0)
		{
			break;
		}
		else if (strcmp(temp->str, temp_.c_str())== 0)
		{
			break;
		}
		temp = temp->next;
	}
	return temp;
}

const ListNode * StringList::Find(const char elem)
{
    if (elem == '\0') return nullptr;

    ListNode * temp = Head;
    string temp_ = "";
    temp_ += elem;

    while (temp != nullptr)
    {
        if (strcmp(temp->str, temp_.c_str())== 0)
        {
            break;
        }
        temp = temp->next;
    }
    return temp;
}

ListNode* StringList::Find(const char* elem, ListNode* pos)
{
    if (elem == nullptr) return nullptr;

    ListNode* temp = Head;
    string temp_ = (char*)elem;

    while (temp != nullptr)
    {
        if (strcmp((const char *)temp->str, (const char *)elem) == 0)
        {
            if (temp->ipos == pos->ipos && temp->jpos == pos->jpos)
            {
                return nullptr;
            }
            else
            {
                break;
            }

        }
        else if (strcmp(temp->str, temp_.c_str())== 0)
        {
            if (temp->ipos == pos->ipos && temp->jpos == pos->jpos)
            {
                return nullptr;
            }
            else
            {
                break;
            }
        }
        temp = temp->next;
    }
    return temp;
}

int StringList::FindIndex(char *elem) const
{
	if (elem == nullptr) return -1;
	ListNode * temp = Head;
	int i = 0;
	while (temp != nullptr)
	{
		if (strcmp(temp->str, elem) == 0)
		{
			return i;
		}
		i++;
		temp = temp->next;
	}
	return -1;
}

int StringList::Getsize() const
{
	return List_size;
}

bool StringList::IsEmpty() const
{
	return List_size == 0;
}

void StringList::Printnode(POSITION p)
{
	if (p == nullptr || p->str == nullptr)
	{
		cout << "NULL" << endl;
		return;
	}
	cout << p->str << " ";
}

void StringList::PrintList()
{
	ListNode *temp = (ListNode*)GetHead();
	while (temp != nullptr)
	{
		this->Printnode(temp);
		temp = temp->next;
	}
	cout << endl;
}

int StringList::GetLastId()
{
	return Last_Id;
}
