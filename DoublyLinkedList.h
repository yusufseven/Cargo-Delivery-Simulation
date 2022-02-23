#pragma once

template <class T>
class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	
	void addItem(T item);
	void removeItem(T item);

	void removeItemAtIndex(int index);	
	T getItemAtIndex(int index);
	
	int size;
	
	
private:
	struct Node
	{
		Node* next, *prev;
		T val;	// item
	};
	Node* head;
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	size = 0;
	this->head = nullptr;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	while(size != 0)
	{
		removeItemAtIndex(0);
	}
}

template <class T>
void DoublyLinkedList<T>::addItem(T item)
{
	size++;
	Node* newNode = new Node();
	newNode->val = item;
	
	if(head == nullptr)
	{		
		head = newNode;
		newNode->prev = nullptr;
		newNode->next = nullptr;
	}
	else
	{
		Node* temp = head;
		while(temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = newNode;
		newNode->prev = temp;
		newNode->next = nullptr;
	}
}

template <class T>
void DoublyLinkedList<T>::removeItem(T item)
{
	size--;
	if(head->next == nullptr && item == head->val)
	{
		delete head;
		head = nullptr;
	}
	else
	{
		Node* temp = head;
		while(item != temp->val)
		{
			if (temp->next == nullptr)
			{
				return;						// such item does not exist
			}
			temp = temp->next;
		}
		if (temp==head)
		{
			head = head->next;
			head->prev = nullptr;
			delete temp;
		}
		else if(temp->next == nullptr)
		{
			(temp->prev)->next = nullptr;
			delete temp;
		}
		else
		{
			(temp->prev)->next = temp->next;
			(temp->next)->prev = temp->prev;
			delete temp;
		}
	}
}

template <class T>
void DoublyLinkedList<T>::removeItemAtIndex(int index)
{
	size--;
	if (head->next == nullptr && index == 0)
	{
		delete head;
		head = nullptr;
	}
	else
	{
		Node* temp = head;
		for (int i = 0; i != index; i++)
		{
			temp = temp->next;
		}
		if (temp == head)
		{
			head = head->next;
			head->prev = nullptr;
			delete temp;
		}
		else if (temp->next == nullptr)
		{
			(temp->prev)->next = nullptr;
			delete temp;
		}
		else
		{
			(temp->prev)->next = temp->next;
			(temp->next)->prev = temp->prev;
			delete temp;
		}
	}
}


template <class T>
T DoublyLinkedList<T>::getItemAtIndex(int index)
{
	Node* temp = head;
	for(int i = 0 ; i != index; i++)
	{
		temp = temp->next;
	}
	return temp->val;				
}
