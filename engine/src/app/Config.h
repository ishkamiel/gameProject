#pragma once

#include <cmath>
#include <string>
#include <memory>

namespace pdEngine
{

class Config
{
public:
	/**
	 * @brief Returns a (possibly uninitialized Config object
	 */
	static std::shared_ptr<Config> get(void) noexcept;

	virtual ~Config(void) {}

	/**
	 * @brief initializes the Config object.
	 */
	virtual bool init(void) noexcept = 0;

	virtual bool addConfigFile(const std::string&) noexcept = 0;

	/**
	 * @brief Resets Config object and unloads any loaded files. Config object will need to be
	 * re-initialized.
	 */
	virtual void reset(void) noexcept = 0;

	virtual bool hasVariable(const std::string& var) const noexcept = 0;

	virtual std::string getString(const std::string& var, std::string defaultValue = "") const noexcept = 0;
	virtual bool getBool(const std::string& var, bool defaultValue = false) const noexcept = 0;
	virtual int getInt(const std::string& var, int defaultValue = -1) const noexcept = 0;
	virtual float getFloat(const std::string& var, float defaultValue = NAN) const noexcept = 0;

	virtual void dump(std::ostream& os) const noexcept = 0;

	/*
	virtual void set(const std::string& var, std::string val) noexcept = 0;
	*/

private:
};


}
