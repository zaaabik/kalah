#include"tree.h"
#define COUNT_OF_CHILDRENS 6
Tree::Tree()
{
    last_node = head = new Tree_node(0, COUNT_OF_CHILDRENS);
    head->set_value(0);

}
Tree::~Tree()
{
    delete head;
    delete last_node;
}
void Tree::add(int value)
{
    Tree_node* tmp = new Tree_node(value,COUNT_OF_CHILDRENS);
    tmp->set_parent(last_node);
    last_node = tmp;
}
void delete_list()
{

}

void Tree::delete_node(Tree_node* node)
{
    if(node->get_children() == nullptr)
    {
        delete node;
    }
    else
    {
        Tree_node* tmp = node;

    }
}
