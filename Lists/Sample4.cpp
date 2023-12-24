#include "./SingleNotCircleList.cc"

template<class T>
bool listInList(SingleNotCircleList_tools::Node<T>* first, SingleNotCircleList_tools::t_index first_size, SingleNotCircleList_tools::Node<T>* second, SingleNotCircleList_tools::t_index second_size)
{
    if(first == second || !second)
    {
        return true;
    }

    if(second_size > first_size)
    {
        return false;
    }

    SingleNotCircleList_tools::t_index i = 0;

    bool flag;
    while(i < first_size && (first_size - second_size >= i) && !flag && first)
    {
        flag = true;

        if(first->data == second->data)
        {
            SingleNotCircleList_tools::Node<T>* tmp = first;
            SingleNotCircleList_tools::Node<T>* tmp2 = second;
            SingleNotCircleList_tools::t_index j = 0;
            
            while(j < second_size)
            {
                if(!(tmp->data == tmp2->data))
                {
                    flag = false;
                    break;
                }
                ++j;
                tmp = tmp->next;
                tmp2 = tmp2->next;
            }
        }
        else
        {
            flag = false;
        }

        first = first->next;
        ++i;
    }
    return flag;
}


int main()
{
    SingleNotCircleList<int> list1 = {1, 1, 3, 1, 2, 3};

    SingleNotCircleList<int> list2 = {4};

    std::cout << listInList(list1.getHeadForSamples(), list1.size(), list2.getHeadForSamples(), list2.size());
}