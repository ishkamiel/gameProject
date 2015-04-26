#include "app/Config.h"

#include "utils/Logger.h"

#include "pugixml.hpp"
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
{
}

Config::~Config(void)
{
    reset();
}

bool Config::init(void) noexcept
{
    PDE_ASSERT(!m_isInitialized, "already initialized");
    auto filename = boost::filesystem::path(getRootPath());
    filename /= PDE_DEFAULT_CONFIG_PATH;
    filename /= PDE_DEFAULT_ENGINE_CONFIG_FILENAME;

    m_configfileEngine = std::make_shared<fs::path>(filename);

    if (! checkFile(m_configfileEngine)) return false;

    m_configEngine = loadFile(m_configfileEngine);


    m_isInitialized = true;
    return true;
}

void Config::reset(void) noexcept
{
    m_configfileEngine.reset();
    m_isInitialized = false;
}

std::string Config::getEngineConfigFilename(void) const noexcept
{
    PDE_ASSERT(m_isInitialized, "not initialized");
    return m_configfileEngine->string();
}

bool Config::foundEngineConfig(void) const noexcept
{
    PDE_ASSERT(m_isInitialized, "not initialized");
    return fs::exists(*m_configfileEngine);
}


std::string Config::getRootPath(void) const noexcept
{
    auto path = boost::filesystem::current_path();
    if (fs::exists(path / "bin")) return path.string();
    path = path.parent_path();
    if (fs::exists(path / "bin")) return path.string();
    return "";
}

std::string Config::get(const std::string& var) const noexcept
{
    try {
        auto node = m_configEngine->first_element_by_path(var.c_str());
        if (node.text()) {
            PDE_TRACE << "Returning config value for " << var;
            return node.child_value();
        }

        PDE_ERROR << "Did not find config option for " << var;
        PDE_ASSERT(node.text(), "config not found");
    }
    catch (const pugi::xpath_exception& e) {
        PDE_ERROR << "Select failed: " << e.what();
    }

    return "";
}

std::string Config::get(const std::string& var, const std::string& defaultVal) const noexcept
{
    try {
        auto node = m_configEngine->first_element_by_path(var.c_str());
        if (node.text()) {
            PDE_TRACE << "Returning config value for " << var;
            return node.child_value();
        }
		PDE_INFO <<"Found no config value for " << var << ", returning provided default";
    }
    catch (const pugi::xpath_exception& e) {
        PDE_ERROR << "Select failed: " << e.what();
    }

    return defaultVal;
}

void Config::set(const std::string& var, std::string val) noexcept
{
    PDE_NOT_IMPLEMENTED_FATAL();
    (void)var;
    (void)val;
}

bool Config::checkFile(Filename file) const noexcept
{
    if (! fs::exists(*file)) {
        PDE_ERROR << "Unable to find config file " << file->string();
        return false;
    }

    if (! fs::is_regular(*file)) {
        PDE_ERROR << "Config file " << file->string() << " is not a regular file";
        return false;
    }

    return true;
}

auto Config::loadFile(Filename file) const noexcept -> ConfigXML
{
    auto doc =  std::make_shared<pugi::xml_document>();
    auto result = doc->load_file(file->string().c_str());

    if (result) {
        PDE_INFO << "Successfully read configuration from XML file " << file->string();
    }
    else {
        PDE_ERROR << "Error parsing config file " << file->string() << ": " << result.description();
        return ConfigXML();
    }

    return doc;
}

}