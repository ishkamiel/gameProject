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
	boost::program_options::variables_map m_Variables;
	boost::program_options::options_description m_cmdlineOptions;
	boost::program_options::options_description m_fileOptions;
	boost::filesystem::path m_engineConfigfile;

	bool m_isInitialized { false };

public:
	Config_Impl(void);
	virtual ~Config_Impl(void);

	bool init(void) noexcept override;
	void reset(void) noexcept override;

	bool addConfigFile(const std::string& filename) noexcept override;

	bool hasVariable(const std::string& var) const noexcept override;

	std::string getString(const std::string& var, std::string defaultValue) const noexcept override;
	bool getBool(const std::string& var, bool defaultValue) const noexcept override;
	int getInt(const std::string& var, int defaultValue) const noexcept override;
	float getFloat(const std::string& var, float defaultValue) const noexcept override;

	virtual void dump(std::ostream& os) const noexcept override;

private:
	boost::filesystem::path getRootPath(void) const noexcept;
	bool parseCommandLine(int ac, char**av) noexcept;
	bool parseFile(const boost::filesystem::path& filename, bool allowUnknown = false) noexcept;
};

}
