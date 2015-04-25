#include "app/Config.h"

#include <boost/filesystem.hpp>

namespace pdEngine
{

std::shared_ptr<Config> Config::get(void) noexcept
{
    static auto raw = new Config();
    static auto pointer = std::shared_ptr<Config>(raw);
    return pointer;
}

Config::Config(void)
{}

Config::~Config(void)
{}

std::string Config::getBinaryPath(void) const noexcept
{
    auto path = boost::filesystem::current_path();
    return path.string();
}

const std::string& Config::get(const std::string& var) const noexcept
{
    // TODO
    static auto retval = "";
    (void)var;
    return retval;
}

void Config::set(const std::string& var, std::string val) noexcept
{
    // TODO
    (void)var;
    (void)val;
}

}