#include <stdio.h>
#include <malloc.h>

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
        return pNode->val;
    case ADD_NODE:
        return Calc (pNode->pLeft) + Calc (pNode->pRight);
    case MULT_NODE:
        return Calc (pNode->pLeft) * Calc (pNode->pRight);
    }
    return 0;
}

Node* CreateNode (int type, double value, Node * pLeft, Node * pRight)
{
    Node * pNode;
    pNode = (Node *) malloc (sizeof (Node));
    pNode->type = type;
    pNode->val = value;
    pNode->pLeft = pLeft;
    pNode->pRight = pRight;
    return pNode;
}
    
void main ()
{
    Node * p1 = CreateNode (NUM_NODE, 2, 0, 0);
    Node * p2 = CreateNode (NUM_NODE, 3, 0, 0);
    Node * p3 = CreateNode (NUM_NODE, 4, 0, 0);
    Node * p4 = CreateNode (ADD_NODE, 0, p1, p2);
    Node * p5 = CreateNode (MULT_NODE, 0, p3, p4);
    double x = Calc (p5);
    printf ( "(2 + 3) * 4 = %lf\n", x );
}
    