#pragma once

#include <memory>
#include <string>

#define PDE_DEFAULT_CONFIG_PATH "config"
#define PDE_DEFAULT_ENGINE_CONFIG_FILENAME "engine.xml";

namespace boost {
namespace filesystem {
class path;
}
}

namespace pugi {
class xml_document;
}

namespace pdEngine
{


class Config
{
	using Filename = std::shared_ptr<boost::filesystem::path>;
	using ConfigXML = std::shared_ptr<pugi::xml_document>;

	bool m_isInitialized { false };

	Filename m_configfileEngine;
	ConfigXML m_configEngine;

public:
	/**
	 * @brief Returns a (possibly uninitialized Config object
	 */
	static std::shared_ptr<Config> get(void) noexcept;

	virtual ~Config(void);

	/**
	 * @brief initializes the Config object.
	 */
	bool init(void) noexcept;

	/**
	 * @brief Resets Config object and unloads any loaded files. Config object will need to be
	 * re-initialized.
	 */
	void reset(void) noexcept;

	std::string getRootPath(void) const noexcept;

	std::string getEngineConfigFilename(void) const noexcept;
	bool foundEngineConfig(void) const noexcept;

	std::string get(const std::string& var) const noexcept;
	std::string get(const std::string& var, const std::string& defaultVal) const noexcept;
	void set(const std::string& var, std::string val) noexcept;

private:
	Config(void);

	bool checkFile(Filename file) const noexcept;
	ConfigXML loadFile(Filename file) const noexcept;
};


}
