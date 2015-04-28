#pragma once

#include <cmath>
#include <string>
#include <memory>

// Forward declare so we don't need to include the boost headers.
namespace boost {
namespace program_options {
class options_description;
}
}

namespace pdEngine
{

class Config
{
protected:
	using OptionDescription = std::shared_ptr<boost::program_options::options_description>;

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
	virtual bool isInitialized(void) const noexcept = 0;

	virtual bool addConfigFile(const std::string&) noexcept = 0;

	virtual OptionDescription getOptionDescriptor(void) const noexcept = 0;

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
