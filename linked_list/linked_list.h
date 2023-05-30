// 1. dynamic size (every node can be easily removed or added)
// 2. Memory efficiency (Nodes are allocated dynamically)
// 3. Efficient insertion and deletion ( every node is pointed to each other w.r.t. structure => we can insert or delete everyone by after pointers)

#pragma once
#include<ostream>

struct Node 
{
	int data;
	Node* next;
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {} // constructor
	Node(const Node& node) : data(node.data), next(nullptr) {}
	~Node() { next = nullptr; }
};

class LinkedList
{
private:
	Node* head;
	Node* tail;
	int elcount;

	int IndexValid(int pos);
	void removeData(Node* node);
	Node* copyData(Node* node) const;
	int nan = 0;

public:
	LinkedList() : head(nullptr), tail(nullptr), elcount(0) {}; // constructor
	LinkedList(const LinkedList& list);
	~LinkedList();
	LinkedList& push_forward(int el); // adding the element
	LinkedList& push_back(int el);
	LinkedList& insert(int el, int pos);
	int extract_forward(); // extraction
	int extract_back();
	int extract(int pos);
	LinkedList& remove_forward(); // removing the element
	LinkedList& remove_back();
	LinkedList& remove(int pos);
	void clear(); // removing all elements
	LinkedList& operator=(LinkedList& list);
	int& operator[](int index);
	int len() { return elcount; };
	friend std::ostream& operator<<(std::ostream& stream, const LinkedList& list); // output
};

struct Stack : private LinkedList // stack has only adding elems from the beginning and deleting from the beginning as well
{
	void push(int el) { push_forward(el); };
	int pop() { return extract_forward(); };
};

struct Queue : private LinkedList // queue has only adding from the back elem and delelting from the beginning&output
{
	void enqueue(int el) { push_back(el); };
	int dequeue() { return extract_forward(); };
};

struct Deck : private LinkedList // deck can add/delete every elem from every side
{
	void push_front(int el) { push_front(el); };
	void push_back(int el) { push_back(el); };
	int pop_front() { return extract_forward(); };
	int pop_back() { return extract_back(); };
};

struct List : private LinkedList // list can add/delete every elem from every side
{
	void push_front(int el) { push_front(el); };
	void push_back(int el) { push_back(el); };
	int pop_front() { return extract_forward(); };
	int pop_back() { return extract_back(); };
};

