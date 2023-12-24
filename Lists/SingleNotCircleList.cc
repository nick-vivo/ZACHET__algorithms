#include <iostream>
#include <initializer_list>

namespace SingleNotCircleList_tools
{
    using t_index = long int;

    template<class T>
    void swap(T& first, T& second)
    {
        T tmp = first;
        first = second;
        second = tmp;
    }

    template<class Ti>
    class Node
    {
    public:

        Node(const Ti data = Ti(), Node<Ti>* const next = nullptr, Node<Ti>* const prev = nullptr): data(data), next(next), prev(prev) {}
        
        Node(const Node& other): data(other.data), next(other.next), prev(other.prev) {}
        
        void swap(Node& other)
        {
            SingleNotCircleList_tools::swap(this->data, other.data);
            SingleNotCircleList_tools::swap(this->next, other.next);
            SingleNotCircleList_tools::swap(this->prev, other.prev);
        }

        Ti data;
        Node<Ti>* next;
        Node<Ti>* prev;

    };

}


template<class T>
class SingleNotCircleList
{

protected:


    SingleNotCircleList_tools::Node<T>* head;
    SingleNotCircleList_tools::Node<T>* tail;
    SingleNotCircleList_tools::t_index _size;


public:


    SingleNotCircleList(): head(nullptr), _size(0) {}

    SingleNotCircleList(const T value): head( new SingleNotCircleList_tools::Node<T>(value) ), _size(1) {}

    SingleNotCircleList(const SingleNotCircleList<T>& other):
                        head(nullptr),
                        _size(other._size) 
    {
       SingleNotCircleList_tools::Node<T>* tmp_copy = other.head;

        if(tmp_copy)
        {
            head = new SingleNotCircleList_tools::Node<T>(tmp_copy->data);
        }
        
        SingleNotCircleList_tools::Node<T>* tmp = head;

        while(tmp_copy->next)
        {
            tmp->next = new SingleNotCircleList_tools::Node<T>(tmp_copy->next->data);
            tmp = tmp->next;
            tmp_copy = tmp_copy->next;
        }
        
    }

    SingleNotCircleList(const std::initializer_list<T> list): head(nullptr), _size(0)
    {
        for(auto element : list)
        {
            this->push_back(element);
        }
    }

    ~SingleNotCircleList()
    {
        SingleNotCircleList_tools::Node<T>* tmp;
        while(head)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    
    void clear()
    {
        SingleNotCircleList_tools::Node<T>* tmp;
        while(head)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        this->_size = 0;
    }

    T& operator[](const SingleNotCircleList_tools::t_index index)
    {
        if(index >= this->_size || index < 0)
        {
            throw -1;
        }
        SingleNotCircleList_tools::Node<T>* tmp = head;

        for(SingleNotCircleList_tools::t_index i = 0; i < index; ++i)
        {
            tmp = tmp->next;    
        }

        return tmp->data;
    }
    
    SingleNotCircleList& operator=(const SingleNotCircleList<T>& other)
    {

        this->clear();

        SingleNotCircleList_tools::Node<T>* tmp_copy = other.head;

        if(tmp_copy)
        {
            head = new SingleNotCircleList_tools::Node<T>(tmp_copy->data);
        }
        
        SingleNotCircleList_tools::Node<T>* tmp = head;

        while(tmp_copy->next)
        {
            tmp->next = new SingleNotCircleList_tools::Node<T>(tmp_copy->next->data);
            tmp = tmp->next;
            tmp_copy = tmp_copy->next;
        }

        this->_size = other._size;
        return *this;
        
    }

    void swap(SingleNotCircleList<T>& other)
    {
        SingleNotCircleList_tools::swap(this->head, other.head);
        SingleNotCircleList_tools::swap(this->_size, other._size);
    }

    void push_back(const T value)
    {
        if(head)
        {
            SingleNotCircleList_tools::Node<T>* tmp = head;
            
            while(tmp->next) tmp = tmp->next;
            
            tmp->next = new SingleNotCircleList_tools::Node<T>(value);
        }
        else head = new SingleNotCircleList_tools::Node<T>(value, head);
        
        ++this->_size;
        
    }

    void push_front(const T value)
    {
        head = new SingleNotCircleList_tools::Node<T>(value, head);
        ++this->_size;
    };

    bool pop_back()
    {
        if(!head)
            return false;
        
        --this->_size;
    
        SingleNotCircleList_tools::Node<T>* endPrev = head;
        if(!head->next)
        {
            head = head->next;
            delete endPrev;
            return true;
        }

        while(endPrev->next->next) endPrev = endPrev->next;
        delete endPrev->next;
        endPrev->next = nullptr;
        return true;
    }

    bool isEmpty()
    {
        return !head;
    }

    bool pop_front()
    {
        if(!head)
            return false;
        SingleNotCircleList_tools::Node<T>* tmp = head;
        head = head->next;
        delete tmp;
        --this->_size;
        return true;
    }

    SingleNotCircleList_tools::t_index size() const
    {
        return this->_size;
    }

    SingleNotCircleList_tools::Node<T>* getHeadForSamples()
    {
        return this->head;
    }

};

template<class T>
std::ostream& operator<<(std::ostream& stream, SingleNotCircleList<T>& list)
{
    stream << "\nList = {";
    for(SingleNotCircleList_tools::t_index i = 0; i < list.size(); ++i)
    {
        stream << list[i];
        
        if(!(i == list.size() - 1)) stream << ", ";
    }
    stream << "};";
    std::cout << "\nsize: " << list.size() << ";\n\n";
    return stream;
}

// int main()
// {

//     SingleNotCircleList<int> list = {1, 2, 3, 3};


//     std::cout << list.getHeadForSamples()->data;

// }