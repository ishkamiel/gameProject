#include "app/Config_Impl.h"

#include "utils/Logger.h"

#include <fstream>
#include <iostream>
#include <string>

namespace pdEngine
{

namespace fs =  boost::filesystem;
namespace po = boost::program_options;

std::shared_ptr<Config> Config::get(void) noexcept
{
    static auto raw = new Config_Impl();
    static auto pointer = std::shared_ptr<Config_Impl>(raw);
    return pointer;
}

Config_Impl::Config_Impl(void)
{
	m_engineConfigfile = boost::filesystem::path(getRootPath());
	m_engineConfigfile /= "config";
	m_engineConfigfile /= "engine.config";
}

Config_Impl::~Config_Impl(void)
{
	//reset();
}

bool Config_Impl::init(void) noexcept
{
	PDE_ASSERT(!m_isInitialized, "already initialized");

	po::options_description generic("Generic options");
	generic.add_options()
		("version,v", "print version string")
		("help", "produce help message")
		;

	po::options_description engine_config("Engine Config");
	engine_config.add_options()
		("engine.name", po::value<std::string>(), "engine name")
		;

	m_cmdlineOptions.add(generic);
	m_fileOptions.add(engine_config);

	if (!parseFile(m_engineConfigfile, true)) return false;

	m_isInitialized = true;
	return true;
}

void Config_Impl::reset(void) noexcept
{
	PDE_NOT_IMPLEMENTED_FATAL();
	//m_cmdlineOptions = po::options_description();
	//m_fileOptions = po::options_description();
	//m_Variables = po::variables_map();
	m_isInitialized = false;
}

bool Config_Impl::parseFile(const fs::path& file, bool allowUnknown) noexcept
{
	if (! fs::exists(file)) {
		PDE_ERROR << "Cannot find: " << file.string();
		return false;
	}

	if (! fs::is_regular(file)) {
		PDE_ERROR << "Not a regular file: " << file.string();
		return false;
	}

	std::ifstream fs(file.string());

	try {
		po::store(
			po::parse_config_file(fs, m_fileOptions, allowUnknown),
			m_Variables
		);
		po::notify(m_Variables);
		PDE_INFO << "Successfully read config file: " << file.string();
	}
	catch (const std::exception& ex)
	{
		if (fs.is_open()) fs.close();
		PDE_ERROR << "Parse error [" << file.string() << "]: " << ex.what();
		return false;
	}

	if (fs.is_open()) fs.close();
	return true;
}

bool Config_Impl::parseCommandLine(int ac, char** av) noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	po::store(po::parse_command_line(ac, av, m_cmdlineOptions), m_Variables);

	if (m_Variables.count("help")) {
		std::cout << m_cmdlineOptions << "\n";
		return false;
	}

	return true;
}


bool Config_Impl::addConfigFile(const std::string& filename) noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	auto path = getRootPath();
	path /= "config";
	path /= filename;
	return parseFile(path, true);
}


fs::path Config_Impl::getRootPath(void) const noexcept
{
	auto path = boost::filesystem::current_path();
	if (fs::exists(path / "bin")) return path.string();
	path = path.parent_path();
	if (fs::exists(path / "bin")) return path.string();
	return "";
}

bool Config_Impl::hasVariable(const std::string& var) const noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	if (m_Variables.count(var) != 0) {
		return true;
	}

	PDE_TRACE << "No such variable: '" << var << "'";
	return false;
}

std::string Config_Impl::getString(const std::string& var, std::string defaultValue) const noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	if (!hasVariable(var)) return defaultValue;

	try {
		return m_Variables[var].as<std::string>();
	}
	catch (const std::exception& e) {
		PDE_ERROR << "Failed to get value for '" << var << "', " << e.what();
	};
	return defaultValue;
}

bool Config_Impl::getBool(const std::string& var, bool defaultValue) const noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	if (!hasVariable(var)) return defaultValue;

	try {
		return m_Variables[var].as<bool>();
	}
	catch (const std::exception& e) {
		PDE_ERROR << "Failed to get value for '" << var << "', " << e.what();
	};
	return defaultValue;
}

int Config_Impl::getInt(const std::string& var, int defaultValue) const noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	if (!hasVariable(var)) return defaultValue;

	try {
		return m_Variables[var].as<int>();
	}
	catch (const std::exception& e) {
		PDE_ERROR << "Failed to get value for '" << var << "', " << e.what();
	};
	return defaultValue;
}

float Config_Impl::getFloat(const std::string& var, float defaultValue) const noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	if (!hasVariable(var)) return defaultValue;

	try {
		return m_Variables[var].as<float>();
	}
	catch (const std::exception& e) {
		PDE_ERROR << "Failed to get value for '" << var << "', " << e.what();
	};
	return defaultValue;
}

void Config_Impl::dump(std::ostream& os) const noexcept
{
	for (auto v : m_Variables) {
		os << v.first << "=" << v.second.as<std::string>() << std::endl;
	}
}


/*
void Config_Impl::set(const std::string& var, std::string val) noexcept
{
	PDE_NOT_IMPLEMENTED_FATAL();
	(void)var;
	(void)val;
}
 */

}
