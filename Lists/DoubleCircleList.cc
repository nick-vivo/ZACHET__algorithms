#include <iostream>
#include <initializer_list>

namespace DoubleCircleList_tools
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
           DoubleCircleList_tools::swap(this->data, other.data);
           DoubleCircleList_tools::swap(this->next, other.next);
           DoubleCircleList_tools::swap(this->prev, other.prev);
        }

        Ti data;
        Node<Ti>* next;
        Node<Ti>* prev;

    };

}


template<class T>
class DoubleCircleList
{

public:


   DoubleCircleList_tools::Node<T>* head;
   DoubleCircleList_tools::Node<T>* tail;
   DoubleCircleList_tools::t_index _size;


public:


   DoubleCircleList(): head(nullptr), tail(head), _size(0) {}

   DoubleCircleList(const T value): head( new DoubleCircleList_tools::Node<T>(value) ), tail(head), _size(1)
   {
        head->next = head;
        head->prev = head;
   }

    DoubleCircleList( DoubleCircleList_tools::Node<T>* head): head(head), tail(head->prev)
    {
        DoubleCircleList_tools::t_index index = 0;
        DoubleCircleList_tools::Node<T>* tmp = head;
        if(!head)
        {
            _size = 0;
        }
        else
        {
        while(tmp != tail)
        {
            tmp = tmp->next;
            ++index;
        }
        ++index;
        _size = index;
        }
            
    }

   DoubleCircleList(const DoubleCircleList<T>& other):  
                        _size(other._size) 
    {
        DoubleCircleList_tools::Node<T>* tmp_copy = other.head;

        if(tmp_copy)
        {
            head = new DoubleCircleList_tools::Node<T>(tmp_copy->data);
            tail = head;
            head->next = head;
            tail->prev = head;
            head->prev = head;
            tail->next = head;

            DoubleCircleList_tools::Node<T>* tmp = head;
            tmp_copy = tmp_copy->next;
            
            while(tmp_copy != other.head)
            {
                tmp->next = new DoubleCircleList_tools::Node<T>(tmp_copy->data, head, tmp);
                tmp_copy = tmp_copy->next;
                tmp = tmp->next;
            }
            head->prev = tmp;
            tail = tmp;
        }
        else
        {
            head = nullptr;
            tail = head;
        }

    }

   DoubleCircleList(const std::initializer_list<T> list): head(nullptr), _size(0)
    {
        for(auto element : list)
        {
            this->push_back(element);
        }
    }

    ~DoubleCircleList()
    {
       DoubleCircleList_tools::Node<T>* tmp;
        while(head != tail)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        if(head)
        {
            tmp = head;
            head = nullptr;
            tail = nullptr;
            delete tmp;    
        }
    }
    
    void clear()
    {
       DoubleCircleList_tools::Node<T>* tmp;
        while(head != tail)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        if(head)
        {
            tmp = head;
            head = nullptr;
            tail = nullptr;
            delete tmp;    
        }
        this->_size = 0;
    }

    T& operator[](const DoubleCircleList_tools::t_index index)
    {
        if(index >= this->_size || index < -this->_size)
        {
            throw -1;
        }

        DoubleCircleList_tools::Node<T>* tmp = head;

        if(index >= 0)
        {
            for(DoubleCircleList_tools::t_index i = 0; i < index; ++i)
            {
                tmp = tmp->next;    
            }
        }
        else
        {
            for(DoubleCircleList_tools::t_index i = 0; -i > index; ++i)
            {
                tmp = tmp->prev;
            }
        }

        return tmp->data;
    }
    
   DoubleCircleList& operator=(const DoubleCircleList<T>& other)
    {

        this->clear();

        DoubleCircleList_tools::Node<T>* tmp_copy = other.head;

        if(tmp_copy)
        {
            head = new DoubleCircleList_tools::Node<T>(tmp_copy->data);
            tail = head;
            head->next = head;
            tail->prev = head;
            head->prev = head;
            tail->next = head;

            DoubleCircleList_tools::Node<T>* tmp = head;
            tmp_copy = tmp_copy->next;
            
            while(tmp_copy != other.head)
            {
                tmp->next = new DoubleCircleList_tools::Node<T>(tmp_copy->data, head, tmp);
                tmp_copy = tmp_copy->next;
                tmp = tmp->next;
            }
            head->prev = tmp;
            tail = tmp;
        }
        else
        {
            head = nullptr;
            tail = head;
        }
    }

    void swap(DoubleCircleList<T>& other)
    {
       DoubleCircleList_tools::swap(this->head, other.head);
       DoubleCircleList_tools::swap(this->tail, other.tail);
       DoubleCircleList_tools::swap(this->_size, other._size);
    }

    void push_back(const T value)
    {
        if(head)
        {
           DoubleCircleList_tools::Node<T>* tmp = new DoubleCircleList_tools::Node<T>(value, head, tail);
           tail->next = tmp;
           head->prev = tmp;
           tail = tmp;
        }
        else
        {
            head = new DoubleCircleList_tools::Node<T>(value);
            tail = head;
            head->next = head;
            head->prev = head;
        }    
        ++this->_size;
    }

    void push_front(const T value)
    {
        if(head)
        {
           DoubleCircleList_tools::Node<T>* tmp = new DoubleCircleList_tools::Node<T>(value, head, tail);
           tail->next = tmp;
           head->prev = tmp;
           head = tmp;
        }
        else
        {
            head = new DoubleCircleList_tools::Node<T>(value);
            tail = head;
            head->next = head;
            head->prev = head;
        }
        ++this->_size;
    };

    bool pop_back()
    {
        if(!head)
            return false;
        
        --this->_size;
        
        if(tail == head)
        {
            delete head;
            tail = nullptr;
            head = nullptr;
        }
        else
        {
            DoubleCircleList_tools::Node<T>* tmp = tail;
            tail = tail->prev;
            head->prev = tail;
            tail->next = head;
            delete tmp;
        }
        return true;
    }

    bool pop_front()
    {
        if(!head)
            return false;
        
        --this->_size;
        
        if(tail == head)
        {
            delete head;
            tail = nullptr;
            head = nullptr;
        }
        else
        {
            DoubleCircleList_tools::Node<T>* tmp = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete tmp;
        }
        return true;
    }

    bool isEmpty()
    {
        return !head;
    }


   DoubleCircleList_tools::t_index size() const
    {
        return this->_size;
    }

   DoubleCircleList_tools::Node<T>* getHeadForSamples()
    {
        return this->head;
    }

    DoubleCircleList_tools::Node<T>* getTailForSamples()
    {
        return this->tail;
    }

};

template<class T>
std::ostream& operator<<(std::ostream& stream, DoubleCircleList<T>& list)
{
    stream << "\nList = {";
    for(DoubleCircleList_tools::t_index i = 0; i < list.size(); ++i)
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

//    DoubleCircleList<int> list = {1, 44, 3, 664, 32};


//     std::cout << list;

//     std::cout << list[4];
// }