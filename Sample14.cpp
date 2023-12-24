#include <vector>
#include <iostream>

    template<class Ti>
    class Node
    {
    public:

        Node(const Ti data = Ti(), Node<Ti>* const left = nullptr, Node<Ti>* const right = nullptr): data(data), left(left), right(right), inLeft(true) {}
        
        Node(const Node& other): data(other.data), left(other.left), right(other.right) {}
        
        void swap(Node& other)
        {
           swap(this->data, other.data);
           swap(this->next, other.next);
           swap(this->prev, other.prev);
        }

        Ti data;
        Node<Ti>* left;
        Node<Ti>* right;

        bool inLeft;

        void createTreeAsVector(std::vector<Ti>& vec)
        {

            this->data = vec[0];
            for(int i = 1; i < vec.size(); ++i)
            {
                insertValue(this, vec[i]);
            }
        }

        void print()
        {
            
            if(this->left)
            {
                this->left->print();
            }
            if(this->right)
            {
                this->right->print();
            }
            std::cout << " " << this->data << " ";
        }

        bool isBalance()
        {
            if(left && right)
                return left->isBalance() && right->isBalance();
            
            return left == right;
        }

    };
    
    template<class T>
    void insertValue(Node<T>* tree, T value)
    {
        if(!tree)
        {
           tree = new Node<T>(value); 
            return;
        }

        if(tree->inLeft)
        {
            if(!tree->left)
            {
                tree->left = new Node<T>(value);
            }
            else
            {
                insertValue(tree->left, value);
            
            }
            tree->inLeft = false;
            return;
        }
        else
        {
            if(!tree->right)
            {
                tree->right = new Node<T>(value);
            }
            else
            {
                insertValue(tree->right, value);
            }
            tree->inLeft = true;
            return;
        }
    }

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 4, 4};

    Node<int> abs;

    abs.createTreeAsVector(vec);

    // abs.print();

    std::cout << abs.isBalance();

}