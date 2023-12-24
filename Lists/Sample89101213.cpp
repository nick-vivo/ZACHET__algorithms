#include <iostream>


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

        Node(const Ti data = Ti(), Node<Ti>* const left = nullptr, Node<Ti>* const right = nullptr): data(data), left(left), right(right) {}
        
        Node(const Node& other): data(other.data), left(other.left), right(other.right) {}
        
        void swap(Node& other)
        {
           swap(this->data, other.data);
           swap(this->next, other.next);
           swap(this->prev, other.prev);
        }


        Ti findMin()
        {
            Ti min = data;

            if(left != nullptr)
            {
               Ti minLeft = left->findMin();

               if(minLeft < min)
               {
                    min = minLeft;
               } 
            }
            if(right != nullptr)
            {
               Ti minRight = right->findMin();

               if(minRight < min)
               {
                    min = minRight;
               } 
            }

            return min;
        }

        Ti data;
        Node<Ti>* left;
        Node<Ti>* right;


        void printLeavs()
        {
            if(left != nullptr)
            {
                left->printLeavs();
            }
            if(right != nullptr)
            {
                right->printLeavs();
            }
            
            if(!right && !left)
                std::cout << "\n\n" << data << "\n\n"; 
        }

        bool isBalance()
        {
            if(left && right)
                return left->isBalance() && right->isBalance();
            
            return left == right;
        }

        Node<Ti>* findMax()
        {
            Node<Ti>* tmpMax = this;

            if(this->left)
            {
                Node<Ti>* tmp = left->findMax();
                if(tmpMax->data < tmp->data)
                {
                    tmpMax = tmp;
                }
            }
            if(this->right)
            {
                Node<Ti>* tmp = right->findMax();
                if(tmpMax->data < tmp->data)
                {
                    tmpMax = tmp;
                }
            }

            return tmpMax;
        }


    };
        
        template<class T>
        Node<T>* findValue(Node<T>* tree, const T& value)
        {

            if(tree && tree->data == value)
            {
                return tree;
            }
            else if (tree->left || tree->right)
            {
                return findValue(tree->left, value) ? findValue(tree->left, value) : findValue(tree->right, value);
            }
            return nullptr;
        }

    int maxi(int a, int b)
    {
        if (a > b)
            return a;
        else
            return b;
    }

    template<class T>
    int height(Node<T>* tree)
    {
        if(!tree)
        {
            return 0;
        }
        else
        {
            return 1 + maxi(height(tree->left), height(tree->right));
        }
    }    


int main()
{
    Node<int>* head = new Node<int>(8);;

    
    head->left = new Node<int>(8);

    head->left->left = new Node<int>(3);
    head->left->right = new Node<int>(1);


    head->right = new Node<int>(7);

    head->right->left = new Node<int>(4);
    head->right->left->left = new Node<int>(8);

    // std::cout << head.findMin();

    // head.printLeavs();

    // std::cout << head.findMax()->data;

    std::cout << findValue(head, 4)->data;
    
    // Node<int> head(5);

    
    // head.left = new Node<int>(8);

    // head.left->left = new Node<int>(3);
    // head.left->right = new Node<int>(1);


    // head.right = new Node<int>(7);

    // head.right->left = new Node<int>(4);
    // // head.right->right = new Node<int>(8);

    // std::cout << head.isBalance();

}


