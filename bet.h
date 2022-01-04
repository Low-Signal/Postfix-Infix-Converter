#ifndef BET_H
#define BET_H

#include <iostream>
#include <list>
#include <stack>
#include "token.h"

using namespace std;

template <typename T>
class BET {
    private:
    // Structure to create a binary node
    struct BinaryNode{
        T element;
        BinaryNode *leftChild;
        BinaryNode *rightChild;

        // Constructors for the binary node
        BinaryNode( const T & theElement, BinaryNode *left = nullptr, BinaryNode *right = nullptr )
          : element{ theElement }, leftChild{ left }, rightChild{ right } { }
        
        BinaryNode( T && theElement, BinaryNode *left = nullptr, BinaryNode *right = nullptr )
          : element{ std::move( theElement ) }, leftChild{ left }, rightChild{ right } { }
    };

    public:

    BET();                                  // Starts the tree with a null root node. (empty tree)
    BET(const list<Token> & postfix);       // Builds the postifix expression tree with the private function

    BET(const BET& rhs);                    // Makes a deep copy of the rhs tree.
    const BET & operator=(const BET& rhs);  // Copy assignment operator
    ~BET();                                 // Destructor

    // Builds the expression tree from the postfix expression and returns true or false if it was successful
    bool buildFromPostfix(const list<Token> & postfix);

    void printPostfixExpression();    // Calls on private function to print postfix expression
    void printInfixExpression();      // Calls on private function to print infix expression
    
    size_t size();                    // Returns the number of nodes in the expression tree
    size_t leaf_nodes();              // Returns the number of leaf nodes in the expression tree

    bool empty();                     // Checks if the tree is logically empty.

    private:

    // Deletes all nodes in the subtree that t points to
    void makeEmpty(BinaryNode* &t);

    // Clones all nodes in the subtree that t points to.
    BinaryNode* clone(BinaryNode *t) const;

    // Used by the public funtion to print the postfix expression
    void printPostfixExpression(BinaryNode *t);

    // Used by the public funtion to print the infix expression
    void printInfixExpression(BinaryNode *t);

    // Used by the public funtion to give the total number of nodes in the tree
    size_t size(BinaryNode *t);

    // Used by the public funtion to give the total number of leaf nodes in the tree
    size_t leaf_nodes(BinaryNode *t);\

    // Returns the precedence value of an operator
    int getPrecedence(const int & value);

    stack <BinaryNode*> theStack;   // Stack for the expression tree
    BinaryNode *root;               // Points to the root node.
};

#include "bet.hpp"

#endif