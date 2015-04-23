#pragma once

#include <memory>

namespace pdEngine
{

template<typename T> inline void safeDelete(T*& p)
{
    delete p;
    p = nullptr;
}

template<typename T> inline void safeDeleteArray(T*& p)
{
    delete[] p;
    p = nullptr;
}

}
