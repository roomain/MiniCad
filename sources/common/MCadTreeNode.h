#pragma once
/***********************************************
* @headerfile MCadTree.h
* @date 12 / 10 / 2023
* @author Roomain
************************************************/
#include <memory>
#include <vector>
#include <ranges>
#include <functional>

class MCadTreeNode;


using MCadTreeNodePtr = std::shared_ptr<MCadTreeNode>;

using MCadTreeNodeWPtr = std::weak_ptr<MCadTreeNode>;

using MCadChildrenNodes = std::vector<MCadTreeNodePtr>;

using MCadTree_Iterator = MCadChildrenNodes::iterator;

using MCadTree_ReverseIterator = MCadChildrenNodes::reverse_iterator;

using MCadTree_const_Iterator = MCadChildrenNodes::const_iterator;
using MCadTree_const_ReverseIterator = MCadChildrenNodes::const_reverse_iterator;


/*@brief Represents a tree node*/
class MCadTreeNode : public std::enable_shared_from_this<MCadTreeNode>
{
private:
    MCadTreeNodeWPtr m_parent;         /*!< link to parent node*/ 
    MCadChildrenNodes m_children;     /*!< children nodes*/ 

    void attachToParent_internal(MCadTreeNodePtr a_parent)
    {
        if(auto pParent = m_parent.lock())
        {
            if(pParent != a_parent)
                return;

            pParent->removeChild_internal(this);
        }
        m_parent = a_parent;
        if(a_parent)
            a_parent->appendChild_internal(this);
    }
    
    void appendChild_internal(MCadTreeNode* const a_child)
    {
        m_children.push_back(a_child->shared_from_this());
    }
    
    void removeChild_internal(MCadTreeNode* const a_child)
    {
        auto iter = std::ranges::find_if(m_children, [a_child](auto&& a_node){return a_child == a_node.get();});
        if(iter != m_children.end())
            m_children.erase(iter);
    }


public:
    MCadTreeNode() = default;

    MCadTreeNode(const MCadTreeNodePtr& a_parent)
    {
        m_parent = a_parent;
        if(a_parent)
            a_parent->appendChild_internal(this);
    }

    MCadTreeNodeWPtr parent()const
    {
        return m_parent;
    }
        
    void attachToParent(const MCadTreeNodePtr& a_parent)
    {
        attachToParent_internal(a_parent);
    }

    void appendChild(const MCadTreeNodePtr& a_child)
    {
        a_child->attachToParent_internal(shared_from_this());
    }

    void removeChild(const MCadTreeNodePtr& a_child)
    {
        removeChild_internal(a_child.get());
    }

    [[nodiscard]] constexpr size_t childCount()const noexcept
    {
        return m_children.size();
    }
    
    [[nodiscard]] MCadTreeNodePtr operator[](const size_t& a_index)
    {
        return m_children[a_index];
    }

    [[nodiscard]] MCadTreeNodePtr at(const size_t& a_index)const
    {
        return m_children.at(a_index);
    }

    MCadTree_Iterator begin(){return m_children.begin();}
    MCadTree_const_Iterator cbegin(){return m_children.cbegin();}
    MCadTree_ReverseIterator rbegin(){return m_children.rbegin();}
    MCadTree_const_ReverseIterator crbegin(){return m_children.crbegin();}

    MCadTree_Iterator end(){return m_children.end();}
    MCadTree_const_Iterator cend(){return m_children.cend();}
    MCadTree_ReverseIterator rend(){return m_children.rend();}
    MCadTree_const_ReverseIterator crend(){return m_children.crend();}

    //

};