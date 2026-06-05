#include "PricingConfigLoader.h"
#include "PricingEngineConfig.h"
#include "PricingEngineConfigItem.h"
#include <stdexcept>
#include <pugixml.hpp>
#include <format>
#include <string>

std::string PricingConfigLoader::getConfigFile() const {
    return configFile_;
}

void PricingConfigLoader::setConfigFile(const std::string& file) {
    configFile_ = file;
}

PricingEngineConfig PricingConfigLoader::loadConfig() {

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(configFile_.c_str());

    if (result.status != pugi::status_ok){
        throw std::runtime_error(std::format("Pugi failed to parse XML file: {}\n", result.description()));
    }

    PricingEngineConfig pricing_engine_config = PricingEngineConfig();
    pugi::xml_node pricing_engines = doc.child("PricingEngines");

    for (pugi::xml_node engine = pricing_engines.first_child(); engine; engine = engine.next_sibling())
    {
        PricingEngineConfigItem item;
        item.setTradeType(engine.attribute("tradeType").value());
        item.setAssembly(engine.attribute("assembly").value());
        item.setTypeName(engine.attribute("pricingEngine").value());
        pricing_engine_config.push_back(item);
    }
    return pricing_engine_config;
}
