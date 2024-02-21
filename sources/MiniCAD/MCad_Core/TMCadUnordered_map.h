#pragma once
/***********************************************
* @headerfile TMCadUnordered_map.h
* @date 28 / 01 / 2024
* @author Roomain
************************************************/
#include <unordered_map>
#include <ranges>
#include "MCad_traits.h"
#include "MCadRef.h"

namespace UndoRedo
{
    template<typename Key, typename Type> requires ( is_MCadShared_base_of<MCadObject, Type>::value )
        class TMCadUnordered_map : public MCadRefObject, private std::unordered_map<Key, Type>
    {
    private:
        using unordered_mapBase = std::unordered_map<Key, Type>;

        // callback called if item changes
        void assertChange(const Type& a_object)
        {
            if (/*undo/redo is not running*/ )
            {
                auto iter = std::ranges::find(*this, a_object);
                // TODO
            }
        }

        void assertInsert(const Type& a_object, const Key& a_key)
        {
            if (/*undo/redo is not running*/ )
            {
                // pas de if constexpr car requires
            }
        }

        void assertErase(const Type& a_object, const Key& a_key)
        {
            if (/*undo/redo is not running*/ )
            {
                // pas de if constexpr car requires
            }
        }

    public:
        //
    };

}