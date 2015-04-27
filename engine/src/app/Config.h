#pragma once

#include <memory>
#include <string>

namespace pdEngine
{

class Config_Impl;

class Config
{
	std::unique_ptr<Config_Impl> m_Impl;
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

	std::string get(const std::string& var) const noexcept;
	std::string get(const std::string& var, const std::string& defaultVal) const noexcept;

	void set(const std::string& var, std::string val) noexcept;

private:
	Config(void);
};


}
