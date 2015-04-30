#include "app/Config_Impl.h"

#include "utils/Logger.h"

#include <fstream>
#include <ostream>
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
	:
	m_Variables(new boost::program_options::variables_map()),
	m_cmdlineOptions(new boost::program_options::options_description()),
	m_fileOptions(new boost::program_options::options_description())
{
	m_engineConfigfile = boost::filesystem::path(getRootPath());
	m_engineConfigfile /= PDE_BUILDOPT_CONFIG_DIR;
	m_engineConfigfile /= PDE_BUILDOPT_CONFIG_FILENAME;

	loadEngineConfig();
}

Config_Impl::~Config_Impl(void)
{
	//reset();
}

bool Config_Impl::init(int argc, char **argv) noexcept
{
	PDE_ASSERT(!m_isInitialized, "already initialized");

	if (!parseFile(m_engineConfigfile, false)) {
		m_initFailed = true;
		return false;
	}

	m_isInitialized = true;

	if (argc > 0) {
		if (!parseCommandLine(argc, argv)) return false;
	}

	return true;
}

auto Config_Impl::getOptionDescriptor(void) const noexcept -> OptionDescription
{
	if (m_isInitialized) {
		PDE_WARN << "Config getOptionDescriptor called after init";
		//exit(EXIT_FAILURE);
	}
	return m_fileOptions;
}


bool Config_Impl::addConfigFile(const std::string &filename, bool allowUnrecognized) noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	auto path = getRootPath();
	path /= "config";
	path /= filename;
	return parseFile(path, allowUnrecognized);
}


bool Config_Impl::hasVariable(const std::string &var) const noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	if (m_Variables->count(var) != 0) {
		return true;
	}

	PDE_TRACE << "hasVariable(" << var << ") -> false";
	return false;
}

std::string Config_Impl::getString(const std::string &var, std::string defaultValue) const noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	if (!hasVariable(var)) return defaultValue;

	try {
		return (*m_Variables)[var].as<std::string>();
	}
	catch (const std::exception &e) {
		PDE_ERROR << "Failed to get value for '" << var << "', " << e.what();
	};
	return defaultValue;
}

bool Config_Impl::getBool(const std::string &var, bool defaultValue) const noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	if (!hasVariable(var)) return defaultValue;

	try {
		return (*m_Variables)[var].as<bool>();
	}
	catch (const std::exception &e) {
		PDE_ERROR << "Failed to get value for '" << var << "', " << e.what();
	};
	return defaultValue;
}

int Config_Impl::getInt(const std::string &var, int defaultValue) const noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	if (!hasVariable(var)) return defaultValue;

	try {
		return (*m_Variables)[var].as<int>();
	}
	catch (const std::exception &e) {
		PDE_ERROR << "Failed to get value for '" << var << "', " << e.what();
	};
	return defaultValue;
}

float Config_Impl::getFloat(const std::string &var, float defaultValue) const noexcept
{
	PDE_ASSERT(m_isInitialized, "not initialized");
	if (!hasVariable(var)) return defaultValue;

	try {
		return (*m_Variables)[var].as<float>();
	}
	catch (const std::exception &e) {
		PDE_ERROR << "Failed to get value for '" << var << "', " << e.what();
	};
	return defaultValue;
}

void Config_Impl::dump(std::ostream &os) const noexcept
{
	for (const auto &it  : *m_Variables) {
		os << it.first << "=";

		auto &value = it.second.value();
		if (auto v = boost::any_cast<float>(&value)) {
			os << *v;
		}
		else if (auto v = boost::any_cast<int>(&value)) {
			os << *v;
		}
		else if (auto v = boost::any_cast<std::string>(&value)) {
			os << *v;
		}
		else {
			PDE_ERROR << "Config::dump, Unable to recognize value for '" << it.first << "'";
			os << "<<UNKNOWN>>";
		}

		os << std::endl;
	}
}


/***************************************************************************************************
 * Private functions
 */

fs::path Config_Impl::getRootPath(void) const noexcept
{
	auto path = boost::filesystem::current_path();
	if (fs::exists(path / "bin")) return path.string();
	path = path.parent_path();
	if (fs::exists(path / "bin")) return path.string();
	return "";
}

void Config_Impl::loadEngineConfig(void) noexcept
{
	if (!m_initFailed && !m_isInitialized) {
		// kind of redundant, but keeps error messages cleaner
	po::options_description generic("Generic options");
	generic.add_options()
		("version,v", "print version string")
		("help", "produce help message");

	po::options_description engine_config("Engine Config");
	engine_config.add_options()
		("engine.version", po::value<std::string>(), "engine verison")
		("engine.build_type", po::value<std::string>(), "engine build type")
		("engine.name", po::value<std::string>(), "engine name");

	m_cmdlineOptions->add(generic);
	m_fileOptions->add(engine_config);
}
}

bool Config_Impl::parseCommandLine(int ac, char **av) noexcept
{
	try {
		po::store(po::parse_command_line(ac, av, *m_cmdlineOptions), *m_Variables);
	}
	catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		return false;
	}

	if (m_Variables->count("help")) {
		std::cout << *m_cmdlineOptions << "\n";
		return false;
	}

	if (m_Variables->count("version")) {
		std::cout << getString("engine.name") << " " << getFloat("engine.version");
		std::cout << " (" << getString("engine.build_type") << " build)";
		std::cout << std::endl;
		return false;
	}

	return true;
}


bool Config_Impl::parseFile(const fs::path &file, bool allowUnknown) noexcept
{
	if (!fs::exists(file)) {
		PDE_ERROR << "Cannot find: " << file.string();
		return false;
	}

	if (!fs::is_regular(file)) {
		PDE_ERROR << "Not a regular file: " << file.string();
		return false;
	}

	std::ifstream fs(file.string());


	auto retval = false;

	try {
		po::store(
			po::parse_config_file(fs, *m_fileOptions, allowUnknown),
			*m_Variables
		);
		po::notify(*m_Variables);
		retval = true;
		PDE_INFO << "Successfully read config file: " << file.string();
	}
	catch (const std::exception &e) {
		PDE_ERROR << "Parse error [" << file.string() << "]: " << e.what();
	}

	if (fs.is_open()) fs.close();
	return retval;
}

}
