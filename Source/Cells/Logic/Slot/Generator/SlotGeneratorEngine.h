#pragma once

#include <list>
#include "SlotGenerator.h"

class ALogicEngine;
class USlot;

/// @brief generate slots based on the registered generators
class SlotGeneratorEngine
{
public:
    ~SlotGeneratorEngine();

    /// @brief generate count_p slots using a slot level baseLevel_p
    std::list<USlot *> generateSlots(unsigned int count_p, ALogicEngine *logic_p, float minLevel_p, float maxLevel_p);

    /// @brief add a new generator
    void addGenerator(unsigned int frequency_p, unsigned int lvlMin_p, std::string const &blueprint_p);

protected:
    std::list<SlotGenerator *> _listGenerators;
};
