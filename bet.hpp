    #include <list>
    #include <iostream>

    #include "opnum.h"
    #include "token.h"
    #include "bet.h"

    using namespace std;

    // Starts the tree with a null root node. (empty tree)
    template <typename T>
    BET<T>::BET(): root{ nullptr }
    {
    }

    // Constructs the expression tree.
    template <typename T>
    BET<T>::BET(const list<Token> & postfix)
    {
       buildFromPostfix(postfix);
    }

    // Makes a deep copy of the rhs tree.
    template <typename T>
    BET<T>::BET(const BET& rhs): root{ nullptr }
    {
        root = clone(rhs.root);
    }

    // Copy assignment operator.
    template <typename T>
    const BET<T>& BET<T>::operator=(const BET& rhs)
    {
        if(this != &rhs)
        {
            makeEmpty(root);
            root = clone(rhs.root);
        }
        return *this;
    }

    // Destructor
    template <typename T>
    BET<T>::~BET()
    {
        makeEmpty(root);
    }

    template <typename T>
    bool BET<T>::buildFromPostfix(const list<Token> & postfix)
    {
        // If the tree contains nodes before the function is called, clear the tree;
        if(!empty())
            makeEmpty(root);

        bool error = false;     // Flag for operand error
        
        // Loops through the postfix list and creates a binary expression tree placed into the stack "theStack"
        for(auto i = postfix.begin(); i != postfix.end(); i++)
        {
            if((*i).getType() >= SYM_NAME && (*i).getType() <= SYM_NUMBER)
            {
                Token var((*i).getValue(), (*i).getType());     // Creates a copy of the *i token
                BinaryNode *newNode = new BinaryNode(var);      // Creates a new node with that token
                theStack.push(newNode);                         // Pushes the token to the stack.
            }
            else if((*i).getType() >= SYM_OPCODE && (*i).getType() <= SYM_DIV)
            {
                BinaryNode *firstOperand = theStack.top();  //Makes a copy of the top of theStack
                theStack.pop();         
                
                // If the stack is empty then there is not another operand to pair with.
                if(theStack.empty())
                {
                    cout << "Error: Operator [" << (*i).getValue() << "] has only one operand: [" << firstOperand->element.getType() << "]: " << firstOperand->element.getValue() << ";" << endl;
                    error = true;
                    break;
                }
                
                BinaryNode *secondOperand = theStack.top(); //Makes a copy of the top of theStack
                theStack.pop();

                Token var((*i).getValue(), (*i).getType());     // Creates a copy of the *i token
                BinaryNode *newNode = new BinaryNode(var, secondOperand, firstOperand);     // Creates a new node that points to each operand
                theStack.push(newNode);                         // Adds that node to the stack
            }
        }

        if(error)
                return false;
        
        this->root = theStack.top();
        theStack.pop();

        // If the stack is not empty then there is an unpaired opcode.
        if(!theStack.empty())
        {
            this->root = theStack.top();
            cout << "Unpaired opcode: [" << root->element.getType() << "]: " << root->element.getValue() << ";" << endl;
            return false;
        }

        return true;
    }

    // Prints the postfix expression
    template <typename T>
    void BET<T>::printPostfixExpression()
    {
        if(empty( ))
            cout << "Empty tree" << endl;
        else
            printPostfixExpression(root);
        cout << endl;
    }

    // Prints the infix expression
    template <typename T>
    void BET<T>::printInfixExpression()
    {
        if(empty( ))
            cout << "Empty tree" << endl;
        else
            printInfixExpression(root);
        cout << endl;
    }
    
    // Returns the number of nodes in the expression tree
    template <typename T>
    size_t BET<T>::size()
    {
        return size(root);
    }

    // Returns the number of leaf nodes in the expression tree
    template <typename T>
    size_t BET<T>::leaf_nodes()
    {
        return leaf_nodes(root);
    }

    // Checks if the tree is logically empty.
    template <typename T>
    bool BET<T>::empty()
    {
        return root == nullptr;
    }

    // Deletes all nodes in the subtree that t points to
    template <typename T>
    void BET<T>::makeEmpty(BinaryNode* &t)
    {   if( t != nullptr )
        {
            makeEmpty( t->leftChild );
            makeEmpty( t->rightChild );
            delete t;
        }
        t = nullptr;
    }

    // Clones all nodes in the subtree that t points to.
    template <typename T>
    typename BET<T>::BinaryNode* BET<T>::clone(BinaryNode *t) const
    {   
        // If t is not set then it does not have a subtree.
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->leftChild ), clone( t->rightChild ) }; // Returns a clone of the nodes in the subtree.
    }

    // These do not have ostream as a parameter like the binary search tree? Also not const
    template <typename T>
    void BET<T>::printPostfixExpression(BinaryNode *t)
    {       
        if( t != nullptr )
        {
            printPostfixExpression(t->leftChild);
            printPostfixExpression( t->rightChild);
            cout << t->element.getValue() << " ";
        }
        
    }

    template <typename T>
    void BET<T>::printInfixExpression(BinaryNode *t)
    {
        if( t != nullptr )
        {   
            // If it is a leaf node print (operand)
            if(t->leftChild == nullptr && t->rightChild == nullptr)
            {
                cout<< t->element.getValue() << " ";
            }
            else
            {   
                // If the left child is a number skip the parentheses, if its an operator check the precedence to determine parentheses.
                if( t->leftChild->element.getType() < SYM_OPCODE || (t->leftChild->element.getType() >= SYM_OPCODE && getPrecedence(t->leftChild->element.getType()) >= getPrecedence(t->element.getType())))
                    printInfixExpression(t->leftChild);
                else
                {
                    cout << "( ";
                    printInfixExpression(t->leftChild);
                    cout << ") ";
                }

                // For the operator
                cout << t->element.getValue() << " ";

                // Checks if the right child is also an operator and if it is checks the precedence to print parentheses.
                if(t->rightChild->element.getType() >= SYM_OPCODE && t->element.getType() >= SYM_OPCODE && getPrecedence(t->element.getType()) >= getPrecedence(t->rightChild->element.getType()))
                    cout << "( "; 

                printInfixExpression(t->rightChild);

                // Checks if the right child is also an operator and if it is checks the precedence to print parentheses.
                if(t->rightChild->element.getType() >= SYM_OPCODE && t->element.getType() >= SYM_OPCODE && getPrecedence(t->element.getType()) >= getPrecedence(t->rightChild->element.getType()))
                    cout << ") "; 

            }   
        }
    }

    // Checks the number of nodes in the expression tree.
    template <typename T>
    size_t BET<T>::size(BinaryNode *t)
    {   
        //If null don't add to the counter, otherwise add the node to the counter and check its left and right child.
        if( t == nullptr )
            return 0; 
        else
            return size(t->leftChild) + size(t->rightChild) + 1;
    }

    // Checks the number of leafs in the expression tree.
    template <typename T>
    size_t BET<T>::leaf_nodes(BinaryNode *t)
    {   
        // Adds up all of the leaf nodes by returning 1 if both childeren are null poiners then adding them all up.
        if ( t == nullptr )
            return 0;
        else if (t->leftChild == nullptr && t->rightChild == nullptr)
            return 1;
        else
        {
            return (leaf_nodes(t->leftChild) + leaf_nodes(t->rightChild));
        }
        
    }

    // Returns the precedence of the operator
    template <typename T>
    int BET<T>::getPrecedence(const int & value)
    {
        if(value == SYM_ADD || value == SYM_SUB)
            return 1;
        else
            return 2;
    }