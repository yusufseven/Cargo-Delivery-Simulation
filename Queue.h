#pragma once
/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);
*/


template<typename T>
class Queue {
public:
	Queue();
	~Queue();
	bool isEmpty() const;
	int size() const;
	//Enqueue: Items are added to the back of the queue
	void enqueue(const T& newItem);
	//Dequeue: Items are removed from the front of the queue
	void dequeue();
	//Get Front: Take a look at the first item
	void getFront(T& queueTop) const;
	
private:
	struct QueueNode {
		T item;
		QueueNode* next;
	};
	int _size;
	/* to avoid the traversal to the last node,
	 an additional pointer to the last node is defined*/
	QueueNode* _lastNode;  // head
	QueueNode* _frontNode; // tail			
						   //               ======================== Queue Visualized =========================
};						   // enqueue(item) -->[frontNode][someNode][someNode][someNode][someNode][lastNode]--> dequeue()

template <typename T>
Queue<T>::Queue()
{
	_size = 0;
	this->_lastNode = nullptr;
	this->_frontNode = nullptr;
}

template <typename T>
Queue<T>::~Queue()
{
	while(!isEmpty())
	{
		dequeue();
	}
}

template <typename T>
bool Queue<T>::isEmpty() const
{
	return _lastNode == nullptr;
}

template <typename T>
int Queue<T>::size() const
{
	return this->_size;
}

template <typename T>
void Queue<T>::enqueue(const T& newItem)
{
	QueueNode* temp = new QueueNode();
	temp->item = newItem;
	
	if(isEmpty())
	{
		_frontNode = _lastNode = temp;
		_size++;
		return;
	}
	
	_frontNode->next = temp;
	_frontNode = temp;
	_size++;
}

template <typename T>
void Queue<T>::dequeue()
{
	QueueNode* temp;

	temp = _lastNode;
	_lastNode = _lastNode->next;
	delete temp;
	_size--;
}

template <typename T>
void Queue<T>::getFront(T& queueTop) const
{
	queueTop = _lastNode->item;
}


