#pragma once

#include "utils/fwd_BoostOpts.h"
#include "build_options.h"

#include <cmath>
#include <string>
#include <memory>

namespace pdEngine
{

/*! \brief Global configuration object to manage program config
 *
 * The Config singleton manages configuration settings from .ini type config
 * files and command line arguments. Config is a list of simple key/value pairs,
 * but [categories] can be introduced for some hierarchy for variables:
 * "category.variables=value".
 */
class Config
{
protected:
	using OptionDescription = std::shared_ptr<boost::program_options::options_description>;

public:
	/*! \brief Returns a (possibly uninitialized) Config object singleton.
	 *
	 * Config initialization should probably be handled in the program entry main function. If
	 * program specific command line options are required these will need to be registered before
	 * initializing.
	 */
	static std::shared_ptr<Config> get(void) noexcept;

	virtual ~Config(void)
	{ }

	/*! \brief Initializes the Config object.
	 *
	 * If command line arguments are used these should be processed by forwarding them to the
	 * init function. In order for program specific arguments to be recognized they need to be
	 * registered before initialization.
	 *
	 * \param argc argument count
	 * \param argv argument array
	 * \return true if everything wen't okay
	 */
	virtual bool init(int argc = 0, char **argv = nullptr) noexcept = 0;

	/*! \brief Check if Config has been successfully initialized.
	 *
	 * \return False if either init has not been called, or it has failed.
	 */
	virtual bool isInitialized(void) const noexcept = 0;

	/*! \brief Adds and parses a configuration file.
	 *
	 * \param filename A filename, without directory, for configuration file.
	 * \param allowUnrecognized If false, unrecognized options will cause failure.
	 */
	virtual bool addConfigFile(const std::string &filename, bool allowUnrecognized=true) noexcept = 0;

	/*! \brief Provides access to the option descriptiors.
	 */
	virtual OptionDescription getOptionDescriptor(void) const noexcept = 0;

	/*! \brief Checks whether a variable has been configured in any file or on the command
	 * line
	 */
	virtual bool hasVariable(const std::string &var) const noexcept = 0;

	virtual std::string getRootDirectoryPath(void) const noexcept = 0;

	virtual std::string getString(
		const std::string &var, std::string defaultValue = "") const noexcept = 0;
	virtual bool getBool(const std::string &var, bool defaultValue = false) const noexcept = 0;
	virtual int getInt(const std::string &var, int defaultValue = -1) const noexcept = 0;
	virtual float getFloat(const std::string &var, float defaultValue = NAN) const noexcept = 0;

	/*! \brief dumps current configuration to given ostream
	 */
	virtual void dump(std::ostream &os) const noexcept = 0;

	/*
	virtual void set(const std::string& var, std::string val) noexcept = 0;
	*/

protected:
	/*! \brief Registers engine specific options to the provided options_descriptions
	 */
	static void addEngineOptionDescriptions(
		boost::program_options::options_description *cmdlineOpts,
		boost::program_options::options_description *fileOpts) noexcept;
};


}
