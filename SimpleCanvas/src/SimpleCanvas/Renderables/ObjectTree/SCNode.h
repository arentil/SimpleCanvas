#pragma once

namespace sc 
{
/**
 * @brief SCNode represents nodes of cyclic list tree 
 * 
 */
class SCNode
{
public:
    SCNode();
    SCNode(SCNode *node);
    virtual ~SCNode();

    bool hasParent() const;
    bool hasChild() const;
    bool isFirstChild() const;
    bool isLastChild() const;

    void attachTo(SCNode *newParent);
    void attach(SCNode *newChild);
    void detach();
    int countNodes() const;

protected:
    SCNode *parentNode;
    SCNode *childNode;
    SCNode *prevNode;
    SCNode *nextNode;
};
} // namespace sc