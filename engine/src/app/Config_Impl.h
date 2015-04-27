#pragma once

#include "app/Config.h"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

namespace pdEngine
{

namespace fs = boost::filesystem;

class Config_Impl : public Config
{
public:
	Config_Impl;
	virtual Config_Impl;

	virtual bool init(void) noexcept override;

	/**
	 * @brief Resets Config object and unloads any loaded files. Config object will need to be
	 * re-initialized.
	 */
	virtual void reset(void) noexcept override;

	virtual std::string getRootPath(void) const noexcept override;

	virtual std::string get(const std::string& var) const noexcept override;
	virtual std::string get(const std::string& var, const std::string& defaultVal) const noexcept override;

	virtual void set(const std::string& var, std::string val) noexcept override;

private:
	bool checkFile(const fs::path& file) const noexcept
	fs::path getEngineConfigfilePath(void) const noexcept;
	bool checkFile(const fs::path& path) const noexcept;

};

}
