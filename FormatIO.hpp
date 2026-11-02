#pragma once
#include "Macro.hpp"
#include <string>
#include <string_view>
namespace veyron {
struct IoResult { bool ok=false; std::string message; };
// VPR is Veyron's documented, line-oriented interchange format (not a third-party format).
IoResult exportVpr(const Macro&, const std::string& path);
IoResult importVpr(const std::string& path, Macro& out);
// Explicit adapters prevent a false claim of compatibility. Implement each only
// after validating against that format's public spec and real sample files.
IoResult importExternal(std::string_view format, const std::string& path, Macro& out);
IoResult exportExternal(std::string_view format, const Macro&, const std::string& path);
}
