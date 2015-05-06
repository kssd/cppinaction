#include <stdio.h>

#define NUM_NODE 1
#define ADD_NODE 2
#define MULT_NODE 3

struct Node
{
    int type;
    double val;
    Node* pLeft;
    Node* pRight;
};

double Calc (Node * pNode)
{
    switch (pNode->type)
    {
    case NUM_NODE:
        return val;
    case ADD_NODE:
        return Calc (pLeft) + Calc (pRight);
    case MULT_NODE:
        return Calc (pLeft) * Calc (pRight);
    }
}

Node * CreateNode (int type, double value, Node * pLeft, Node * pRight)
{
    Node * pNode;
    pNode = (Node *) malloc (sizeof (Node));
    pNode->type = type;
    pNode->val = value;
    pNode->pLeft = pLeft;
    pNode->pRight = pRight;
    return pNode;
}
    
     