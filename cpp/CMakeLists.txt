cmake_minimum_required(VERSION 3.10)
project(TechTest)

# Default to C++17, but candidates may change to 20 or 23 if preferred
set(CMAKE_CXX_STANDARD 20)

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
if(ENABLE_ASAN)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g)
    add_link_options(-fsanitize=address -fno-omit-frame-pointer)
endif()

option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)
if(ENABLE_TSAN)
    add_compile_options(-fsanitize=thread -fno-omit-frame-pointer -g)
    add_link_options(-fsanitize=thread -fno-omit-frame-pointer)
endif()

if(ENABLE_ASAN AND ENABLE_TSAN)
    message(FATAL_ERROR "Both ASAN & TSAN are enlabled.")
endif()

option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE "clang-tidy")
    if(CLANG_TIDY_EXE)
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
    else()
        message(WARNING "clang-tidy was not found.")
    endif()
endif()

option(ENABLE_IWYU "Enable include-what-you-use" OFF)
if(ENABLE_IWYU)
    find_program(IWYU_EXE "include-what-you-use")
    if(IWYU_EXE)
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
        set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_EXE})
    else()
        message(WARNING "include-what-you-use was not found.")
    endif()
endif()

# Models library
# Make Models a static library so translation-unit implementations
# (e.g. ScalarResults.cpp) are compiled and linked.
add_library(Models STATIC
    Models/ScalarResults.cpp
)

target_include_directories(Models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Loaders library
add_library(Loaders STATIC
    Loaders/ITradeLoader.h
    Loaders/ITradeLoader.cpp
    Loaders/BondTradeLoader.h
    Loaders/BondTradeLoader.cpp
    Loaders/FxTradeLoader.h
    Loaders/FxTradeLoader.cpp
)

target_include_directories(Loaders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Loaders Models)

# Pricers library
add_library(Pricers STATIC
    Pricers/BasePricingEngine.h
    Pricers/BasePricingEngine.cpp
    Pricers/GovBondPricingEngine.h
    Pricers/CorpBondPricingEngine.h
    Pricers/FxPricingEngine.h
    Pricers/IPricingEngine.h
)

target_include_directories(Pricers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Pricers Models)

# RiskSystem library
add_library(RiskSystem STATIC
    RiskSystem/PricingEngineConfigItem.h
    RiskSystem/PricingEngineConfig.h
    RiskSystem/PricingConfigLoader.h
    RiskSystem/PricingConfigLoader.cpp
    RiskSystem/SerialPricer.h
    RiskSystem/SerialPricer.cpp
    RiskSystem/SerialTradeLoader.h
    RiskSystem/SerialTradeLoader.cpp
    RiskSystem/StreamingTradeLoader.h
    RiskSystem/StreamingTradeLoader.cpp
    RiskSystem/ParallelPricer.h
    RiskSystem/ParallelPricer.cpp
    RiskSystem/ScreenResultPrinter.h
    RiskSystem/ScreenResultPrinter.cpp
    RiskSystem/BaseLoaderTrades.h
    RiskSystem/BaseLoaderTrades.cpp
    RiskSystem/BasePricer.h
    RiskSystem/BasePricer.cpp
)

target_include_directories(RiskSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(RiskSystem Models Loaders Pricers)

# XML parser for Exercise 3
find_package(pugixml REQUIRED)
target_link_libraries(RiskSystem pugixml::pugixml)

# Find and link threading library (required for Exercise 8)
find_package(Threads REQUIRED)
target_link_libraries(RiskSystem Threads::Threads)

# ConsoleApp executable
add_executable(ConsoleApp
    ConsoleApp/main.cpp
)

target_link_libraries(ConsoleApp Models Loaders Pricers RiskSystem)

# Tests executable
# Note: Test .cpp files are included in main.cpp, so they shouldn't be listed here
add_executable(Tests
    Tests/TestFramework.h
    Tests/main.cpp
)

target_link_libraries(Tests Models Loaders Pricers RiskSystem)

# Copy data files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/Loaders/TradeData DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Loaders/TradeData DESTINATION ${CMAKE_BINARY_DIR}/Loaders)
file(COPY ${CMAKE_SOURCE_DIR}/RiskSystem/PricingConfig DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/RiskSystem/PricingConfig DESTINATION ${CMAKE_BINARY_DIR}/RiskSystem)

