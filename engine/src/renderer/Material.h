#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Color.h"

namespace pdEngine
{

enum class AlphaType
{
    Opaque,
    Transparent
};

class Material
{
public:
    Material ();
    virtual ~Material ();

    void setDiffuse(const Color&);

    bool hasAlpha() const;
    float getAlpha() const;
    void setAlpha(const float);
};

}
#endif /* MATERIAL_H_ */
