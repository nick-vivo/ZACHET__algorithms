#include "./DoubleCircleList.cc"

template<class T>
void deleteDublicates( DoubleCircleList_tools::Node<T>* begin, DoubleCircleList_tools::t_index& size )
{
    if(!begin || size == 0)
    {
        throw "fail";
    }

    DoubleCircleList_tools::t_index i = 0;
    DoubleCircleList_tools::Node<T>* tmp = begin;
    DoubleCircleList_tools::Node<T>* tmp2 = begin;
    

    while(i < size - 1)
    {
        DoubleCircleList_tools::t_index j = i + 1;
        DoubleCircleList_tools::Node<T>* tmp2 = tmp->next;

        while(j < size)
        {
            if(tmp2->data == tmp->data)
            {
                DoubleCircleList_tools::Node<T>* tmp3 = tmp2;
                tmp2 = tmp2->next;
                tmp2->prev = tmp3->prev;
                tmp3->prev->next = tmp2;
                delete tmp3; 
                --size;
            }
            else
            {
                tmp2 = tmp2->next;
                ++j;
            }
        }
        ++i;
        tmp = tmp->next;
    }
}

int main()
{
    DoubleCircleList<int> list = {3, 3, 3};

    std::cout << list;

    deleteDublicates(list.getHeadForSamples(), list._size);

    std::cout << list;
}