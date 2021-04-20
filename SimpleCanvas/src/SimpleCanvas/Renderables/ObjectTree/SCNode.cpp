#include "SCNode.h"

namespace sc
{
SCNode::SCNode() 
{
    parentNode = childNode = nullptr;
    prevNode = nextNode = this;
}

SCNode::SCNode(SCNode *node) 
{
    parentNode = childNode = nullptr;
    prevNode = nextNode = this;
    attachTo(node);
}

SCNode::~SCNode() 
{
    detach();

    while (childNode)
    {
        delete childNode;
    }
}

bool SCNode::hasParent() const
{
    return parentNode != nullptr;
}

bool SCNode::hasChild() const
{
    return childNode != nullptr;
}

bool SCNode::isFirstChild() const
{
    if (parentNode == nullptr)
        return false;    
    
    return parentNode->childNode == this;
}

bool SCNode::isLastChild() const
{
    if (parentNode == nullptr)
        return false;

    return parentNode->childNode->prevNode == this;    
}

void SCNode::attachTo(SCNode *newParent) 
{
    if (parentNode != nullptr)
        detach();
    
    parentNode = newParent;

    if (parentNode->childNode)
    {
        prevNode = parentNode->childNode->prevNode;
        nextNode = parentNode->childNode;
        parentNode->childNode->prevNode->nextNode = this;
        parentNode->childNode->prevNode = this;
    }
    else
        parentNode->childNode = this;
}

void SCNode::attach(SCNode *newChild) 
{
    if (newChild->hasParent())
        newChild->detach();

    newChild->parentNode = this;

    if (childNode)
    {
        newChild->prevNode = childNode->prevNode;
        newChild->nextNode = childNode;
        childNode->prevNode->nextNode = newChild;
        childNode->prevNode = newChild;
    }
    else
        childNode = newChild;
}

void SCNode::detach() 
{
    if (parentNode != nullptr && parentNode->childNode == this)
    {
        if (nextNode != this)
            parentNode->childNode = nextNode;
        else
            parentNode->childNode = nullptr;
    }

    prevNode->nextNode = nextNode;
    nextNode->prevNode = prevNode;

    prevNode = this;
    nextNode = this;
}

int SCNode::countNodes() const
{
    if (childNode != nullptr)
        return childNode->countNodes() + 1;
    
    return 1;
}
} // namespace sc