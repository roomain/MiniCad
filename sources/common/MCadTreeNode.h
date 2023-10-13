#pragma once
/***********************************************
* @headerfile MCadTree.h
* @date 12 / 10 / 2023
* @author Roomain
************************************************/
#include <memory>
#include <vector>
#include <functional>

template<typename Type>
class MCadTreeNode;

template<typename Type>
using MCadTreeNodePtr = std::shared_ptr<MCadTreeNode<Type>;

template<typename Type>
using MCadTreeNodeWPtr = std::weak_ptr<MCadTreeNode<Type>;

template<typename Type>
using MCadChildrenNodes = std::vector<MCadTreeNodeWPtr<Type>>;

template<typename Type>
using MCadTree_Iterator = MCadChildrenNodes::iterator;

template<typename Type>
using MCadTree_const_Iterator = MCadChildrenNodes::const_iterator;

template<typename Type>
using MCadTreeSort = std::function<bool (const Type&, const Type&)>;

template<typename Type>
using MCadPredicate = std::function<bool (const Type&)>;

/*@brief Represents a tree node*/
template<typename Type>
class MCadTreeNode : public std::enable_shared_from_this<MCadTreeNode<Type>>
{
private:
    Type m_data;                            /*!< contained data*/
    MCadTreeNodePtr<Type> m_parent;         /*!< link to parent node*/ 
    MCadChildrenNodes<Type> m_children;     /*!< children nodes*/ 

    void attachToParent_internal(const MCadTreeNodePtr& a_parent)
    {
        //
    }
    
    void appendChild_internal(const MCadTreeNodePtr& a_child)
    {
        //
    }

    void detachToParent_internal(const MCadTreeNodePtr& a_parent)
    {
        //
    }
    
    void removeChild_internal(const MCadTreeNodePtr& a_child)
    {
        //
    }


public:
    MCadTreeNode() = default;
    MCadTreeNode(const Type& a_data);
    MCadTreeNode(const Type&& a_data);

    MCadTreeNode(const MCadTreeNodePtr& a_parent);
    MCadTreeNode(const MCadTreeNodePtr& a_parent, const Type& a_data);
    MCadTreeNode(const MCadTreeNodePtr& a_parent, const Type&& a_data);

    void attachToParent(const MCadTreeNodePtr& a_parent)
    {
        //
    }

    void appendChild(const MCadTreeNodePtr& a_child)
    {
        //
    }

    void removeChild(const MCadTreeNodePtr& a_child)
    {
        //
    }

    void sortChildren(MCadTreeSort& a_sort)
    {
        std::sort(m_children.begin(), m_children.end(), [&a_sort](auto&& a_first, auto&& a_second)
        {
            return a_sort(a_first.data(), a_second.data());
        });
    }

    [[nodiscard]] bool inline hasChild(const MCadTreeNodePtr<Type>& a_child)const
    {
        return std::any_of(m_children.begin(), m_children.end(), [&a_child](const auto& a_child)
        {
            return a_child.lock() == a_child;
        });
    }

    [[nodiscard]] MCadTreeNodePtr<Type> inline find(const MCadPredicate<Type>& a_predicate, const bool a_recursive)const
    {
        MCadTreeNodePtr<Type> ret;
        auto iter = std::find_if(m_children.begin(), m_children.end(), [&a_predicate](const auto& a_child)
        {
            return a_predicate(a_child.lock());
        });
        // TODO
        return ret;
    }

    [[nodiscard]] inline Type& data(){return m_data;}
    [[nodiscard]] inline const Type& data()const{return m_data;}
    [[nodiscard]] inline MCadTreeNodePtr<Type> parent()const {return m_parent;}

    MCadTree_Iterator<Type> begin(){return m_children.begin();}
    MCadTree_const_Iterator<Type> cbegin(){return m_children.cbegin();}
    MCadTree_Iterator<Type> rbegin(){return m_children.rbegin();}
    MCadTree_const_Iterator<Type> crbegin(){return m_children.crbegin();}

    MCadTree_Iterator<Type> end(){return m_children.end();}
    MCadTree_const_Iterator<Type> cend(){return m_children.cend();}
    MCadTree_Iterator<Type> rend(){return m_children.rend();}
    MCadTree_const_Iterator<Type> crend(){return m_children.crend();}

};