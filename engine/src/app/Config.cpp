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
    static auto pointer = std::shared_ptr<Config>(raw);
    return pointer;
}

Config::Config(void)
: m_Impl(new Config_Impl())
{}

Config::~Config(void)
{}

bool Config::init(void) noexcept
{
    m_Impl->init();
}

void Config::reset(void) noexcept
{
    m_Impl->reset();
}

std::string Config::getRootPath(void) const noexcept
{
    m_Impl->getRootPath();
}

std::string Config::get(const std::string& var) const noexcept
{
    m_Impl->get(var);
}

std::string Config::get(const std::string& var, const std::string& defaultVal) const noexcept
{
    m_Impl->get(var, defaultVal);
}

void Config::set(const std::string& var, std::string val) noexcept
{
    PDE_NOT_IMPLEMENTED_FATAL();
    (void)var;
    (void)val;
}

}