#include <stdio.h>
#include <malloc.h>

#define NUM_NODE 1
#define ADD_NODE 2
#define MULT_NODE 3

struct Node
{
    int type;
};

struct NumNode
{
    int type;
    double val;
};

struct BinNode
{
    int type;
    Node* pLeft;
    Node* pRight;
};

double Calc (Node * pNode)
{
    switch (pNode->type)
    {
        case NUM_NODE:
            return ((NumNode *)pNode)->val;
        case ADD_NODE:
        {
            BinNode * pN = (BinNode *) pNode;
            return Calc (pN->pLeft) + Calc (pN->pRight);
        }
        case MULT_NODE:
        {
            BinNode * pN = (BinNode *) pNode;
            return Calc (pN->pLeft) * Calc (pN->pRight);
        }
        default:
            printf ("Bad node type\n");
    }
    return 0;
}

Node * CreateNumNode (double value)
{
    NumNode * pNode = (NumNode *) malloc (sizeof (NumNode));
    pNode->type = NUM_NODE;
    pNode->val = value;
    return (Node *) pNode;
}

Node* CreateBinNode (int type, Node * pLeft, Node * pRight)
{
    BinNode * pNode;

    pNode = (BinNode *) malloc (sizeof (BinNode));
    pNode->type = type;
    pNode->pLeft = pLeft;
    pNode->pRight = pRight;
    return (Node *) pNode;
}
    
void main ()
{
    Node * p1 = CreateNumNode (2);
    Node * p2 = CreateNumNode (3);
    Node * p3 = CreateNumNode (4);
    Node * p4 = CreateBinNode (ADD_NODE, p1, p2);
    Node * p5 = CreateBinNode (MULT_NODE, p3, p4);
    double x = Calc (p5);
    printf ( "(2 + 3) * 4 = %lf\n", x );
}
    