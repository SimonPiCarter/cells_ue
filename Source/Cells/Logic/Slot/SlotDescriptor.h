#pragma once

/// @brief base class to create description for slots
class SlotDescriptor
{
    public:
    virtual ~SlotDescriptor() {}

    virtual std::string createDescription() const = 0;
    virtual std::string createLoreDescription() const = 0;
};
