#include "app/Config.h"
#include "app/Config_Impl.h"

#include <boost/program_options.hpp>

namespace pdEngine
{

namespace po = boost::program_options;

std::shared_ptr<Config> Config::get(void) noexcept
{
	static auto raw = new Config_Impl();
	static auto pointer = std::shared_ptr<Config_Impl>(raw);
	return pointer;
}

void Config::addEngineOptionDescriptions(
	po::options_description *cmdlineOptions,
	po::options_description *fileOptions) noexcept
{
	po::options_description generic("Generic options");
	generic.add_options()
		("version,v", "print version string")
		("help", "produce help message");

	po::options_description engine_config("Engine Config");
	engine_config.add_options()
		("engine.version", po::value<std::string>(), "engine verison")
		("engine.build_type", po::value<std::string>(), "engine build type")
		("engine.name", po::value<std::string>(), "engine name")
		("resources.root", po::value<std::string>(), "realtive reource root");

	cmdlineOptions->add(generic);
	fileOptions->add(engine_config);
}

}
