#pragma once
/***********************************************
* @headerfile MCadMemory.h
* @date 01 / 09 / 2023
* @author Roomain
************************************************/
#include <memory>
#include <functional>
#include <type_traits>
#include "MCadRecordAssertion.h"

class MCadObject;

template<typename Type>
class MCadShared_ptr;

template<typename Type>
using AffectCB = std::function<void(const MCadShared_ptr<Type>)>;

/*@brief special smart pointer for MCad undo/redo*/
template<typename Type>
class MCadShared_ptr : public std::shared_ptr<Type>
{
private:
    AffectCB<Type> m_affectationCallback;

public:
    using std::shared_ptr<Type>::shared_ptr;

    MCadShared_ptr(const MCadShared_ptr<Type>& a_other) : std::shared_ptr<Type>(a_other) {}
    MCadShared_ptr(MCadShared_ptr<Type>&& a_other)noexcept : std::shared_ptr<Type>(a_other) {}
    explicit MCadShared_ptr(const std::shared_ptr<Type>& a_other) : std::shared_ptr<Type>(a_other) {}
    explicit MCadShared_ptr(std::shared_ptr<Type>&& a_other)noexcept : std::shared_ptr<Type>(a_other) {}
    explicit MCadShared_ptr(const std::weak_ptr<Type>& a_other) : std::shared_ptr<Type>(a_other) {}
    explicit MCadShared_ptr(std::weak_ptr<Type>&& a_other) : std::shared_ptr<Type>(a_other) {}
    template<typename U>
    explicit MCadShared_ptr(std::shared_ptr<Type>&& a_other, Type* a_ptr) noexcept : std::shared_ptr<Type>(a_other, a_ptr) {}
    ~MCadShared_ptr()
    {
        if constexpr ( std::is_base_of_v<MCadObject, Type> )
        {
            // is last use and pointer not null
            if (std::shared_ptr<Type>::use_count() == 1 && std::shared_ptr<Type>::get())
                UndoRedo::assertDeletion(std::shared_ptr<Type>::get());
        }
    }
    MCadShared_ptr<Type>& operator = (const MCadShared_ptr<Type>& a_other)
    {
        if ( m_affectationCallback )
            m_affectationCallback(*this);
        std::shared_ptr<Type>::operator = (a_other);
        return *this;
    }
    MCadShared_ptr<Type>& operator = (const MCadShared_ptr<Type>&& a_other)noexcept
    {
        if ( m_affectationCallback )
            m_affectationCallback(*this);
        std::shared_ptr<Type>::operator = (a_other);
        return *this;
    }
    MCadShared_ptr<Type>& operator = (const std::shared_ptr<Type>& a_other)
    {
        if ( m_affectationCallback )
            m_affectationCallback(*this);
        std::shared_ptr<Type>::operator = (a_other);
        return *this;
    }
    MCadShared_ptr<Type>& operator = (std::shared_ptr<Type>&& a_other)noexcept
    {
        if ( m_affectationCallback )
            m_affectationCallback(*this);
        std::shared_ptr<Type>::operator = (a_other);
        return *this;
    }
    void setCallback(const AffectCB<Type>& a_callback)
    {
        m_affectationCallback = a_callback;
    }
};

template<typename Type>
class MCadShared_from_this
{
    template<typename U, typename ...Args>
    friend MCadShared_ptr<U> make_MShared(Args&& ...);

private:
    std::weak_ptr<Type> m_Wptr; /*!< weak pointer on this*/

public:
    constexpr MCadShared_from_this() : m_Wptr{} {}
    MCadShared_from_this(MCadShared_from_this<Type>& a_other) : m_Wptr(a_other.m_Wptr) {}
    explicit MCadShared_from_this(MCadShared_from_this<Type>&& a_other)noexcept : m_Wptr(a_other.m_Wptr) {}
    virtual ~MCadShared_from_this() = default;

    [[nodiscard]] MCadShared_ptr<Type> shared_from_this()
    {
        if (!m_Wptr.lock())
            throw std::bad_weak_ptr{};
        return MCadShared_ptr<Type>(m_Wptr);
    }

    [[nodiscard]] MCadShared_ptr<const Type> shared_from_const_this()const
    {
        if (!m_Wptr.lock())
            throw std::bad_weak_ptr{};
        return MCadShared_ptr<const Type>(m_Wptr);
    }

    [[nodiscard]] std::weak_ptr<Type> weak_from_this()const
    {
        return m_Wptr;
    }

    [[nodiscard]] std::weak_ptr<const Type> weak_from_const_this()
    {
        return m_Wptr;
    }

    [[nodiscard]] bool isShared( )const noexcept
    {
        return !m_Wptr.expired( );
    }
};

template<typename Type>
struct is_enable_shared
{
private:
    using TrueType = char;
    using FalseType = short;

    // template used for compile time evaluation
    template<typename C>
    static TrueType& is_enable(decltype( &C::isShared ));

    template<typename C>
    static FalseType& is_enable(...);

public:
    enum { value = sizeof(is_enable<Type>(0)) == sizeof(TrueType) };
};

template<typename Type>
constexpr auto is_enable_shared_v = is_enable_shared<Type>::value;

template<typename Type, typename ...Args>
MCadShared_ptr<Type> make_MShared(Args&& ...arg)
{
    MCadShared_ptr<Type> pObj = std::make_shared<Type>(arg...);
    if constexpr ( is_enable_shared_v<Type>)
        pObj->m_Wptr = pObj;
    return pObj;
}


template<typename T, typename U>
MCadShared_ptr<T> MStatic_pointer_cast(MCadShared_ptr<U>&& a_other)noexcept
{
    const auto ptr = static_cast< T* >( a_other.get( ) );
    return MCadShared_ptr<T>(std::move(a_other), ptr);
}

template<typename T, typename U>
MCadShared_ptr<T> MStatic_pointer_cast(const MCadShared_ptr<U>& a_other)noexcept
{
    const auto ptr = static_cast< T* >( a_other.get( ) );
    return MCadShared_ptr<T>(a_other, ptr);
}