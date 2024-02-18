/***********************************************
* @headerfile MCad_traits.h
* @date 28 / 01 / 2024
* @author Roomain
************************************************/
#include <type_traits>
#include "MCadMemory.h"

/*@ brief Type is shared_ptr*/
template<typename Type> struct is_shared_ptr : std::false_type {};
template<typename Type> struct is_shared_ptr<std::shared_ptr<Type>> : std::true_type {};

/*@brief Type is shared_ptr and base of U*/
template<typename Base, typename Type> struct is_shared_base_of : std::false_type {};
template<typename Base, typename Type> struct is_shared_base_of<Base , std::shared_ptr<Type>> 
{
    static constexpr auto value = std::is_base_of_v<Base, Type> ||
    std::is_same_v<std::shared_ptr<Base>, std::shared_ptr<Type>>;
};


/*@ brief Type is MCadShared_ptr*/
template<typename Type> struct is_MCadShared_ptr : std::false_type {};
template<typename Type> struct is_shared_ptr<MCadShared_ptr<Type>> : std::true_type {};

/*@brief Type is MCadShared_ptr and base of U*/
template<typename Base, typename Type> struct is_MCadShared_base_of : std::false_type {};
template<typename Base, typename Type> struct is_MCadShared_base_of<Base , MCadShared_ptr<Type>> 
{
    static constexpr auto value = std::is_base_of_v<Base, Type> ||
    std::is_same_v<MCadShared_ptr<Base>, MCadShared_ptr<Type>>;
};