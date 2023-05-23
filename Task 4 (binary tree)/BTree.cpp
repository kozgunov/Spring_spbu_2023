#include "BTree.h"
#include <queue>


void BTree::Clear(Node*& node)
{
    if (node == nullptr) return;
    Clear(node->left);
    Clear(node->right);
    delete node;
}

void BTree::Insert(Node*& node, Node* dataNode)
{
    if (node == nullptr)
    {
        node = dataNode;
    }
    else if (node->data < dataNode->data)
    {
        Insert(node->right, dataNode);
    }
    else if (node->data > dataNode->data)
    {
        Insert(node->left, dataNode);
    }
    else
    {
        delete dataNode;
    }
}

void BTree::Insert(int data)
{
    Insert(root, new Node(data));
}

void BTree::Print(Node*& node, std::ostream& stream)
{
    if (node == nullptr)
    {
        return;
    }
    Print(node->left, stream);
    stream << node->data << " ";
    Print(node->right, stream);
}

void BTree::PrintH(Node*& node, std::ostream& stream, int depth)
{
    if (node == nullptr)
    {
        return;
    }
    PrintH(node->right, stream, depth + 1);
    for (int i = 0; i < depth; ++i)
    {
        stream << "\t";
    }
    stream << node->data << std::endl;
    PrintH(node->left, stream, depth + 1);
}

int BTree::depth_maximal(Node* node) // define maximal depth 
{
    if (node != nullptr) // we have to translate every numbers w.r.t. their posiitions.
    {
        int r = depth_maximal(node->left);
        int l = depth_maximal(node->right);
        if (l >= r)
        {
            return(r + 1);
        }
        else return(l + 1);
    }
    else // trivial case
    {
        return 0;

    }
}

void BTree::PrintV(Node*& node, std::ostream& stream)
{
    int max_poss_width = 3; // quite compact for 3, but maybe changed till inf
    int max_poss_depth = BTree::depth_maximal(node);
    std::queue<std::pair<Node*, int>> que;

    if (node == nullptr) return; // trivial case

    que.push({ node, max_poss_width * (1 << max_poss_depth) }); // here we're pushing the root in queue q & denote the placements

    while (!que.empty()) 
    {
        int level = que.size(); 

        for (int i = 0; i < level; i++) 
        {
            Node* the_number = que.front().first; 
            int white_spaces = que.front().second;
            que.pop();

            for (int i = 0; i < white_spaces / 2; i++) // we have to write blank spaces between the numbers (it's necessary for tree structure, no more)
                stream << " ";                         

            if (the_number) // if it doesn't exist we'll automatically finish
            {
                stream << the_number->data; // looking for the placement of new number
                if (the_number->left) 
                { 
                    que.push({ the_number->left, white_spaces / 2 }); 
                }  
                if (the_number->right) 
                {
                    que.push({ the_number->right, white_spaces / 2 }); 
                }

            for (int i = 0; i < white_spaces / 2; i++) // also for tree structure we have to write white spaces after the number (actually it's not so improtant)
                stream << " ";
            }
        }

        if (max_poss_depth > 0) // bias in the lower string if it's possible
        {
            stream << "\n";
            max_poss_depth--;
        }

    }
}

BTree::~BTree() 
{
    Clear(root);
    root = nullptr;
}

std::ostream& operator<<(std::ostream& stream, BTree& tree)
{
    //stream << "print" << std::endl;
    //tree.Print(tree.root, stream);

    //stream << std::endl << "print horizontal" << std::endl;
    //tree.PrintH(tree.root, stream);

    stream << std::endl << "print vertical" << std::endl;
    tree.PrintV(tree.root, stream);

    return stream;
}


