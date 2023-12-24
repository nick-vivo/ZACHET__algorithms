#include "./SingleNotCircleList.cc"

using namespace SingleNotCircleList_tools;

template<class T>
Node<T>* premaxSimpleList(SingleNotCircleList_tools::Node<T>* ptr, SingleNotCircleList_tools::t_index size)
{
    if(!ptr || size < 2)
    {
        throw -1;
    }



    Node<T>* preMax = nullptr;
    Node<T>* max = ptr;

    t_index index = 1;
    ptr = ptr->next;

    while(index < size)
    {
        if(ptr->data > max->data)
        {
            preMax = max;
            max = ptr;
        }
        else if(!preMax)
        {
            if(max->data > ptr->data)
            {
                preMax = ptr;
            }
        }
        else if(ptr->data < max->data && ptr->data > preMax->data)
        {
            preMax = ptr;
        }

        ++index;
        ptr = ptr->next;
    }

    return preMax;
    
}

int main()
{
    SingleNotCircleList<int> list = {454, 5, 4, 2, 44};
    
    std::cout << premaxSimpleList(list.getHeadForSamples(), 5)->data;
}