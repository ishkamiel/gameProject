#pragma once

#include <memory>
#include <string>

namespace pdEngine
{


class Config
{
public:
	static std::shared_ptr<Config> get(void) noexcept;

	virtual ~Config(void);

	std::string getBinaryPath() const noexcept;

	const std::string& get(const std::string& var) const noexcept;
	void set(const std::string& var, std::string val) noexcept;

private:
	Config();
};


}
