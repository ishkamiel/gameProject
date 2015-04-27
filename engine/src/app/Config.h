#pragma once

#include <memory>
#include <string>

namespace pdEngine
{

class Config_Impl;

class Config
{
public:
	/**
	 * @brief Returns a (possibly uninitialized Config object
	 */
	static std::shared_ptr<Config> get(void) noexcept;

	virtual ~Config(void) = 0;

	/**
	 * @brief initializes the Config object.
	 */
	virtual bool init(void) noexcept = 0;

	/**
	 * @brief Resets Config object and unloads any loaded files. Config object will need to be
	 * re-initialized.
	 */
	virtual void reset(void) noexcept = 0;

	virtual std::string getRootPath(void) const noexcept =0;

	virtual std::string get(const std::string& var) const noexcept = 0;
	virtual std::string get(const std::string& var, const std::string& defaultVal) const noexcept = 0;

	virtual void set(const std::string& var, std::string val) noexcept = 0;

private:
};


}
