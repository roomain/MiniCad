#pragma once
/***********************************************
* @headerfile MCadScoped.h
* @date 01 / 08 / 2023
* @author Roomain
************************************************/

template<typename type>
class MCadScoped
{
private:
    Type& m_original;
    Type m_saved;

public:
    MCadScoped() = delete;
    MCadScoped(const Scoped&) = delete;
    MCadScoped(Scoped&&) = delete;
    MCadScoped& operator = (const Scoped& a_other) = delete;
    MCadScoped& operator = (Scoped&& a_other) = delete;

    explicit MCadScoped(Type& a_original) : m_original{ a_original }, m_saved{ a_original }
    {

    }

    ~MCadScoped()
    {
        std::swap(m_saved, m_original);
    }

    Type& operator = (const Type& a_other)
    {
        m_original = a_other;
        return m_original;
    }

    operator Type()
    {
        return m_original;
    }
};
