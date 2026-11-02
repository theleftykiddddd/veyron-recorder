#include "veyron/FormatIO.hpp"
#include <fstream>
#include <iomanip>
#include <sstream>
namespace veyron {
IoResult exportVpr(const Macro& m, const std::string& path) {
    if (!m.isValid()) return {false,"Macro validation failed."};
    std::ofstream f(path); if(!f) return {false,"Cannot open output file."};
    f << "VEYRON_MACRO 1\n" << std::quoted(m.metadata.title) << ' ' << std::quoted(m.metadata.author) << '\n'
      << m.metadata.levelId << ' ' << std::quoted(m.metadata.levelName) << ' ' << std::setprecision(12) << m.metadata.gameVersion << ' ' << m.metadata.tickRate << '\n'
      << m.inputs.size() << '\n';
    for (const auto& e:m.inputs) f << e.frame << ' ' << e.button << ' ' << e.player2 << ' ' << e.down << '\n';
    return f ? IoResult{true,"VPR exported."} : IoResult{false,"Write failed."};
}
IoResult importVpr(const std::string& path, Macro& out) {
    std::ifstream f(path); if(!f) return {false,"Cannot open input file."};
    std::string magic; int version=0; f>>magic>>version;
    if(magic!="VEYRON_MACRO" || version!=1) return {false,"Unsupported VPR header/version."};
    Macro tmp; f >> std::quoted(tmp.metadata.title) >> std::quoted(tmp.metadata.author);
    f >> tmp.metadata.levelId >> std::quoted(tmp.metadata.levelName) >> tmp.metadata.gameVersion >> tmp.metadata.tickRate;
    std::size_t n=0; f>>n; if(!f || n>5000000) return {false,"Invalid or excessive event count."};
    tmp.inputs.reserve(n);
    for(std::size_t i=0;i<n;++i) { InputEvent e; f>>e.frame>>e.button>>e.player2>>e.down; if(!f) return {false,"Truncated or malformed event list."}; tmp.inputs.push_back(e); }
    if(!tmp.isValid()) return {false,"Imported macro failed validation."};
    out=std::move(tmp); return {true,"VPR imported."};
}
IoResult importExternal(std::string_view format,const std::string&,Macro&) { return {false,"Adapter for '"+std::string(format)+"' is not implemented yet. Use VPR until a spec-verified adapter is added."}; }
IoResult exportExternal(std::string_view format,const Macro&,const std::string&) { return {false,"Adapter for '"+std::string(format)+"' is not implemented yet. No incompatible file was written."}; }
}
