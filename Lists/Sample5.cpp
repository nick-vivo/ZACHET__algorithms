#include "./DoubleCircleList.cc"
#include "./SingleNotCircleList.cc"

template<class T>
DoubleCircleList<T> returnDoubleListik(SingleNotCircleList_tools::Node<T>* ptr, SingleNotCircleList_tools::t_index size)
{
    DoubleCircleList_tools::Node<T>* two_list = nullptr;
    if(!ptr || size < 1)
    {
        return DoubleCircleList<T>(two_list);
    }

    two_list = new DoubleCircleList_tools::Node<T>(ptr->data);
    DoubleCircleList_tools::Node<T>* tail = two_list;

    ptr = ptr->next;

    while(ptr)
    {
        DoubleCircleList_tools::Node<T>* new_el = new DoubleCircleList_tools::Node<T>(ptr->data);
        tail->next = new_el;
        new_el->prev = tail;
        tail = new_el;
        ptr = ptr->next;
    }

    tail->next = two_list;
    two_list->prev = tail;

    return DoubleCircleList<T>(two_list);
}


int main()
{
    SingleNotCircleList<int> l1 = {3, 7, 5, 6, 13};

    DoubleCircleList<int> l2 = returnDoubleListik(l1.getHeadForSamples(), l1.size());

    std::cout << l1;

    std::cout << l2;
}