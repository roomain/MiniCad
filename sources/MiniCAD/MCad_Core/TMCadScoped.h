#pragma once
/***********************************************
* @headerfile TMCadScoped.h
* @date 01 / 08 / 2023
* @author Roomain
************************************************/

template<typename Type>
class TMCadScoped
{
private:
    Type& m_original;
    Type m_saved;

public:
    TMCadScoped( ) = delete;
    TMCadScoped(const TMCadScoped<Type>&) = delete;
    TMCadScoped(TMCadScoped<Type>&& a_other) : m_original{ a_other.m_original },
        m_saved{ std::move(a_other.m_saved) } {}
    TMCadScoped& operator = (const TMCadScoped<Type>& a_other) = delete;
    TMCadScoped& operator = (TMCadScoped<Type>&& a_other)
    {
        m_original = a_other.m_original;
        m_saved = std::move(a_other.m_saved);
    }

    explicit TMCadScoped(Type& a_original) : m_original{ a_original }, m_saved{ a_original }
    {

    }

    ~TMCadScoped( )
    {
        std::swap(m_saved, m_original);
    }

    Type& operator = (const Type& a_other)
    {
        m_original = a_other;
        return m_original;
    }

    operator Type( )
    {
        return m_original;
    }
};
