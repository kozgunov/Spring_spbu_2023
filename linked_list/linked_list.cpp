#include "linked_list.h"


int LinkedList::IndexValid(int pos)
{
	return (pos >= 0 && pos < elcount);
}

Node* LinkedList::copyData(Node* node) const
{
	if (node == nullptr)
	{
		return nullptr;
	}
	Node* newNode = new Node(node->data);

	Node* tempNode = newNode;
	Node* temp = head->next;
	while (temp != nullptr)
	{
		tempNode->next = new Node(temp->data);
		temp = temp->next;
		tempNode = tempNode->next;
	}

	return newNode;
}

void LinkedList::removeData(Node* node)
{
	while (node != nullptr)
	{
		Node* temp = node;
		node = node->next;
		delete temp;
	}
}

void LinkedList::clear()
{
	if (head != nullptr)
	{
		removeData(head);
	}
	tail = nullptr;
	elcount = 0;
}

LinkedList& LinkedList::operator=(LinkedList& list)
{
	clear();
	elcount = list.elcount;
	head = list.copyData(list.head);
	tail = head;
	if (tail != nullptr)
	{
		while (tail->next != nullptr)
		{
			tail = tail->next;
		}
	}
	return *this;
}

int& LinkedList::operator[](int index)
{
	if (!IndexValid(index))
	{
		return nan;
	}
	Node* node = head;
	while (index > 0)
	{
		--index;
		node = node->next;
	}
	return node->data;
}

LinkedList::LinkedList(const LinkedList& list)
{
	elcount = list.elcount;
	head = list.copyData(list.head);
	tail = head;
	if (tail != nullptr)
	{
		while (tail->next != nullptr)
		{
			tail = tail->next;
		}
	}
}

LinkedList::~LinkedList()
{
	clear();
}

LinkedList& LinkedList::push_forward(int el)
{
	head = new Node(el, head);
	if (tail == nullptr)
	{
		tail = head;
	}
	++elcount;
	return *this;
}

LinkedList& LinkedList::push_back(int el)
{
	if (elcount == 0)
	{
		return push_forward(el);
	}
	tail->next = new Node(el);
	tail = tail->next;
	++elcount;
	return *this;
}

LinkedList& LinkedList::insert(int el, int pos)
{
	if (!IndexValid(pos))
	{
		return *this;
	}
	if (pos == 0)
	{
		return push_forward(el);
	}
	if (pos == elcount)
	{
		return push_back(el);
	}
	Node* temp = head;
	while (pos > 1)
	{
		temp = temp->next;
		--pos;
	}
	temp->next = new Node(el, temp->next);
	++elcount;
	return *this;
}

int LinkedList::extract_forward()
{
	if (head == nullptr)
	{
		return 0;
	}
	if (elcount == 1)
	{
		tail = nullptr;
	}
	int result = head->data;
	Node* oldHead = head;
	head = head->next;
	delete oldHead;
	--elcount;
	return result;
}

int LinkedList::extract_back()
{
	if (elcount < 2)
	{
		return extract_forward();
	}

	int result = tail->data;

	Node* temp = head;
	while (temp->next->next != nullptr)
	{
		temp = temp->next;
	}
	delete temp->next;
	temp->next = nullptr;
	tail = temp;

	--elcount;
	return result;
}

int LinkedList::extract(int pos)
{
	if (!IndexValid(pos))
	{
		return 0;
	}
	if (pos == 0)
	{
		return extract_forward();
	}
	if (pos == elcount - 1)
	{
		return extract_back();
	}

	Node* temp = head;
	while (pos > 1)
	{
		temp = temp->next;
		--pos;
	}
	Node* toDelete = temp->next;
	temp->next = temp->next->next;
	int result = toDelete->data;
	delete toDelete;
	--elcount;
	return result;
}

LinkedList& LinkedList::remove_forward()
{
	extract_forward();
	return *this;
}

LinkedList& LinkedList::remove_back()
{
	extract_back();
	return *this;
}

LinkedList& LinkedList::remove(int pos)
{
	extract(pos);
	return *this;
}

std::ostream& operator<<(std::ostream& stream, const LinkedList& list)
{
	Node* temp = list.head;
	stream << "{" << list.elcount << "}[ ";
	if (temp == nullptr)
	{
		stream << "EMPTY ";
	}
	while (temp != nullptr)
	{
		stream << temp->data << " ";
		temp = temp->next;
	}
	stream << "]";
	return stream;
}

