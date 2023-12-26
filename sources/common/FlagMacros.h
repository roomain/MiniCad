/***********************************************
* @headerfile CadFlagMacros.h
* @date 31 / 07 / 2021
* @author Romain Crespel
************************************************/

/*@brief macro definitions for enum class flags*/
//------------------------------------------------------------------

#define ENUM_FLAG_AND_OPERATOR(enumflag) \
constexpr enumflag operator & (const enumflag &first, const enumflag &second)\
{\
    return static_cast<enumflag>(static_cast<unsigned int>(first) & static_cast<unsigned int>(second));\
}\
\
constexpr enumflag operator & (const enumflag &&first, const enumflag &&second)\
{\
    return static_cast<enumflag>(static_cast<unsigned int>(first) & static_cast<unsigned int>(second));\
}\

/// \macro define boolean OR operator for enum class
#define ENUM_FLAG_OR_OPERATOR(enumflag) \
constexpr enumflag operator | (const enumflag &first, const enumflag &second)\
{\
    return static_cast<enumflag>(static_cast<unsigned int>(first) | static_cast<unsigned int>(second));\
}\
\
constexpr enumflag operator | (const enumflag &&first, const enumflag &&second)\
{\
    return static_cast<enumflag>(static_cast<unsigned int>(first) | static_cast<unsigned int>(second));\
}\

#define ENUM_FLAG_NOT_OPERATOR(enumflag) \
constexpr enumflag operator ~ (const enumflag value)\
{\
    return static_cast<enumflag>(~static_cast<unsigned int>(value));\
}


/// \macro define boolean AND and OR operators for enum class
#define ENUM_FLAG_OPERATORS(enumflag) \
ENUM_FLAG_AND_OPERATOR(enumflag) \
ENUM_FLAG_OR_OPERATOR(enumflag) \
ENUM_FLAG_NOT_OPERATOR(enumflag)

//-----------------------------------------------------
#define ENUM_FLAG_FRIEND_AND_OPERATOR(enumflag) \
friend constexpr enumflag operator & (const enumflag &first, const enumflag &second)\
{\
    return static_cast<enumflag>(static_cast<unsigned int>(first) & static_cast<unsigned int>(second));\
}\
\
friend constexpr enumflag operator & (const enumflag &&first, const enumflag &&second)\
{\
    return static_cast<enumflag>(static_cast<unsigned int>(first) & static_cast<unsigned int>(second));\
}\

/// \macro define boolean OR operator for enum class
#define ENUM_FLAG_FRIEND_OR_OPERATOR(enumflag) \
friend constexpr enumflag operator | (const enumflag &first, const enumflag &second)\
{\
    return static_cast<enumflag>(static_cast<unsigned int>(first) | static_cast<unsigned int>(second));\
}\
\
friend constexpr enumflag operator | (const enumflag &&first, const enumflag &&second)\
{\
    return static_cast<enumflag>(static_cast<unsigned int>(first) | static_cast<unsigned int>(second));\
}\

#define ENUM_FLAG_FRIEND_NOT_OPERATOR(enumflag) \
friend constexpr enumflag operator ~ (const enumflag &value)\
{\
    return static_cast<enumflag>(~static_cast<unsigned int>(value));\
}\
\
friend constexpr enumflag operator ~ (const enumflag &&value)\
{\
    return static_cast<enumflag>(~static_cast<unsigned int>(value));\
}\


/// \macro define boolean AND and OR operators for enum class
#define ENUM_FLAG_FRIEND_OPERATORS(enumflag) \
ENUM_FLAG_FRIEND_AND_OPERATOR(enumflag) \
ENUM_FLAG_FRIEND_OR_OPERATOR(enumflag) \
ENUM_FLAG_FRIEND_NOT_OPERATOR(enumflag)
