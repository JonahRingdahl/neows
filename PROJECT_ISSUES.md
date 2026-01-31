# NEOws Project Issues

## Critical Issues
1. **API Integration** - API code not yet implemented (pending strategy development)
2. **Unsafe Return Types** - `NeosCurrier::GetSelectedNeo()` returns dangerous reference to shared_ptr
3. **Testing** - Only placeholder tests exist, need comprehensive unit tests

## High Priority Issues
1. **Architecture** - Classes have mixed responsibilities (data, logic, presentation)
2. **Performance** - Inefficient string concatenation in render loops
3. **Modern C++** - Not using C++20/23 features (std::optional, std::span, concepts, std::format)

## Medium Priority Issues
1. **Documentation** - Missing Doxygen comments for classes and APIs
2. **Security** - API key handling needs environment variables and config files
3. **Build Quality** - Missing sanitizers and extended compiler warnings

## Code Style & Naming Issues
1. ~~Typo~~ `Neo.hpp:57` - **FIXED** `is_sentry_object` (correct spelling)
2. ~~Typo~~ `OrbitalData.hpp:23` - **FIXED** `eccentricity` (correct spelling)
3. ~~Enum~~ `Menu.hpp:7` - **FIXED** `MINIMAL/FULL` (proper UPPER_CASE)
4. **Include order** - System → External → Local ordering needed in multiple files
