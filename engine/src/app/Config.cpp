#include "app/Config.h"

#include "utils/Logger.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <cassert>

namespace pdEngine
{

namespace fs =  boost::filesystem;

std::shared_ptr<Config> Config::get(void) noexcept
{
    static auto raw = new Config();
    static auto pointer = std::shared_ptr<Config_Impl>(raw);
    return pointer;
}

}
