#pragma once

#include "app/Config.h"
#include "utils/Logger.h"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <string>

namespace pdEngine
{


class Config_Impl : public Config
{
	boost::filesystem::path m_engineConfigfile;

	std::unique_ptr<boost::program_options::variables_map> m_Variables;
	OptionDescription m_cmdlineOptions;
	OptionDescription m_fileOptions;

	bool m_isInitialized{false};
	bool m_initFailed { false };

public:
	Config_Impl(void);
	virtual ~Config_Impl(void);

	bool init(int arc = 0, char **argv = nullptr) noexcept override;

	bool isInitialized(void) const noexcept
	{ return m_isInitialized; }

	bool addConfigFile(const std::string &filename, bool allowUnrecognized=true) noexcept override;

	OptionDescription getOptionDescriptor(void) const noexcept override;

	bool hasVariable(const std::string &var) const noexcept override;

	std::string getString(
		const std::string &var, std::string defaultValue = "") const noexcept override;
	bool getBool(const std::string &var, bool defaultValue = false) const noexcept override;
	int getInt(const std::string &var, int defaultValue = -1) const noexcept override;
	float getFloat(const std::string &var, float defaultValue = NAN) const noexcept override;

	virtual void dump(std::ostream &os) const noexcept override;

private:
	boost::filesystem::path getRootPath(void) const noexcept;
	void loadEngineConfig(void) noexcept;
	bool parseCommandLine(int ac, char **av) noexcept;
	bool parseFile(const boost::filesystem::path &filename, bool allowUnknown = false) noexcept;
};

}
