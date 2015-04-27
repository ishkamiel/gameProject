#include "app/Config_Impl.h"

#include "utils/Logger.h"

namespace pdEngine
{

namespace fs =  boost::filesystem;

Config_Impl::Config(void)
{ }

Config_Impl::~Config(void)
{
	reset();
}

bool Config_Impl::init(void) noexcept
{
	PDE_ASSERT(!m_isInitialized, "already initialized");

	auto filename = boost::filesystem::path(getRootPath());
	filename /= "config";
	filename /= "engine.config";

	auto engineConfig = fs:path(getEngineConfigfile());
	m_configfileEngine = std::make_shared<fs::path>(filename);

	if (! checkFile(m_configfileEngine)) return false;

	m_configEngine = loadFile(m_configfileEngine);


	m_isInitialized = true;
	return true;
}

void Config_Impl::reset(void) noexcept
{
	m_configfileEngine.reset();
	m_isInitialized = false;
}

std::string Config_Impl::getRootPath(void) const noexcept
{
	auto path = boost::filesystem::current_path();
	if (fs::exists(path / "bin")) return path.string();
	path = path.parent_path();
	if (fs::exists(path / "bin")) return path.string();
	return "";
}

std::string Config_Impl::get(const std::string& var) const noexcept
{
}

std::string Config_Impl::get(const std::string& var, const std::string& defaultVal) const noexcept
{
	PDE_NOT_IMPLEMENTED_FATAL();
	(void)var;
	(void)defaultVal;
	return "";
}

void Config_Impl::set(const std::string& var, std::string val) noexcept
{
	PDE_NOT_IMPLEMENTED_FATAL();
	(void)var;
	(void)val;
}

bool Config_Impl::checkFile(const fs::path& file) const noexcept
{
	if (! fs::exists(file)) {
		PDE_ERROR << "Unable to find config file " << file.string();
		return false;
	}

	if (! fs::is_regular(file)) {
		PDE_ERROR << "Config file " << file.string() << " is not a regular file";
		return false;
	}

	return true;
}

fs::path Config_Impl::getEngineConfigfilePath(void) const noexcept
{
	auto filename = boost::filesystem::path(getRootPath());
	filename /= "config";
	filename /= "engine.config";
	return filename;
}

}
