#ifndef NODE_H
#define NODE_H

template <typename T>
class List
{

private:
	class Node
	{
	public:
		T element;
		Node *next;
		//konstuktor
		Node(T element = T())
		{
			this->element = element;
			next = nullptr;
		}
		virtual ~Node()
		{
		}
		//destruktor
	};

	int  nrOfNodes; //räknare = längd
	Node* first;
private:
	//hjälpfunktioner
	void freeMemory();
public:
	List();
	virtual ~List();
	List(const List& other);
	List& operator=(const List& other);
	T getAt(int pos) const throw(...);
	void removeAt(int pos) throw(...);
	bool removeElement(const T& element);
	bool findElement(const T& toFind) const;
	void getAll(T arr[], int cap) throw(...);

	void insertAt(int pos, const T& element) throw(...); //inte klar över 0;
	int length() const;

};

#endif // !NODE_H

template<typename T>
void List<T>::freeMemory()
{
	Node* walker = first;
	Node* temp =nullptr;

	for (int i = 0; i < nrOfNodes && walker->next != nullptr; i++)
	{
		temp = walker->next;
		delete walker;
		walker = temp;
	}
}

template<typename T>
List<T>::List()
{
	nrOfNodes = 0;
	first = nullptr;
}

template<typename T>
List<T>::~List()
{
	freeMemory();
}

template<typename T>
List<T>::List(const List & other)
{
	freeMemory();
	nrOfNodes = other.nrOfNodes;
	Node* otherNode = other.first;
	
	Node* walker = first;
	Node* node = first;
	for (int i = 0; i < other.nrOfNodes; i++)
	{
		node = new Node(otherNode->element); //other->first;
		node->next = first;
		if (i == 0)
		{
			first = node;
		}
		else
		{
			walker->next = node; //node next blir first;
		}
		walker = node;
		otherNode = otherNode->next;
	}
}

template<typename T>
List<T> & List<T>::operator=(const List & other)
{
	if (this != &other)
	{
		freeMemory();
		nrOfNodes = other.nrOfNodes;
		Node* otherNode = other.first;
		Node* walker = first;
		Node* node = first;
		for (int i = 0; i < other.nrOfNodes; i++)
		{
			node = new Node(otherNode->element);
			node->next = first;
			if (i == 0)
			{
				first = node;
			}
			else
			{
				walker->next = node;
			}
			walker = node;
			otherNode = otherNode->next;
		}
	}
	return *this;
}

template<typename T>
T List<T>::getAt(int pos) const throw(...)
{
	Node* temp = first;
	T result = T();

	if (pos == 0)
	{
		temp = first;
		return temp->element;
	}

	else if (pos <nrOfNodes && pos >= 0)
	{
		for (int i = 0; i < pos; i++)
		{
			temp = temp->next;
		}
		result = temp->element;
	}
	if (pos > nrOfNodes || pos <0)
	{
		throw"Invalid number is to big";
	}
	return result;
}

template<typename T>
void List<T>::removeAt(int pos) throw(...) //funkar inte helt
{
	Node* temp = nullptr;
	if (pos >= nrOfNodes || pos < 0)
	{
		throw "Invalid position to remove";
	}
	else if (pos == 0) 
	{
		temp = this->first;
		this->first = this->first->next;
		delete temp;
		this->nrOfNodes--;
	}
	else {
		Node* node = this->first;
		for (int i = 0; i < pos; i++) 
		{
			temp = node;
			node = node->next;
		}
		temp->next = node->next;
		delete node;
		this->nrOfNodes--;
	}
}

template<typename T>
bool List<T>::removeElement(const T & element)
{
	
	Node* temp = nullptr;
	Node* walker = this->first;
	for (int i = 0; i < nrOfNodes; i++)
	{
		if (walker->element == element)
		{
			if (i == 0)
			{
				Node* temp = this->first;
				this->first = this->first->next;
				delete temp;
			}
			else
			{
				temp->next = walker->next;
				delete walker;
			}
			this->nrOfNodes--;
			return true;
		}
		temp = walker;
		walker = walker->next;
	}
	return false;
}

template<typename T>
bool List<T>::findElement(const T & toFind) const //klar
{
	Node* temp = first;
	Node* test = new Node(toFind);
	bool found = false;
	for (int i = 0; i < nrOfNodes && !found; i++)
	{
		if (temp->element == test->element)
		{
			return found = true;
		}
		temp = temp->next;
	}
	return found;
}

template<typename T>
void List<T>::getAll(T arr[], int cap) throw(...)//klar
{
	if (cap < nrOfNodes)
	{
		throw "Capacity too small";
	}
	Node* temp = first;
	for (int i = 0; i < nrOfNodes; i++)
	{
		arr[i] = temp->element;
		temp = temp->next;
	}
}


template<typename T>
void List<T>::insertAt(int pos, const T & element) throw(...)
{
	/*Node* temp = new Node(element);
	Node* walker = first;
*/
	if (pos > nrOfNodes || pos<0)
	{
		throw "Invalid";
	}
	else if (pos == 0)
	{
		Node* temp = new Node(element);
		Node* walker = first;
		temp->next = first;
		first = temp;
		nrOfNodes++;
	}
	else if (pos >= 1 && pos <= nrOfNodes) //vene om det funkar
	{
		Node* temp = new Node(element);
		Node* walker = first;
		/*temp->next = first->next;*/
		for (int i = 0; i < pos - 1; i++)
		{
			walker = walker->next;//pos
		}
		temp->next = walker->next; //sista platsen till pos
		walker->next = temp; //
		nrOfNodes++;
	}

}

template<typename T>
inline int List<T>::length() const
{
	return this->nrOfNodes;
}