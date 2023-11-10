//#include "MCadAngle.h"
//#include "glm/glm.hpp"

#ifdef PROPERTY_DEF_DEFAULT_INIT
PROPERTY_DEF_DEFAULT_INIT(glm::dvec3, USER_ORIGIN)
PROPERTY_DEF_DEFAULT_INIT(glm::quat, USER_ORIENTATION)
#endif

#ifdef PROPERTY_DEF
PROPERTY_DEF(AngleUnit, ANGLE_UNIT, AngleUnit::unit_degree)
#endif

#ifdef PROPERTY_DEF_ENUM
//#define PROPERTY_DEF_ENUM(Type, Name, DefaultValue)
#endif

#ifdef PROPERTY_READ_ONLY_DEF
//#define PROPERTY_READ_ONLY_DEF(Type, Name, DefaultValue)
#endif

#ifdef PROPERTY_VALID_DEF
//#define PROPERTY_VALID_DEF(Type, Name, Valid, DefaultValue)
#endif
