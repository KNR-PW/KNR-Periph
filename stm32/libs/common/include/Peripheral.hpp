#pragma once

class IPeripheral 
{
public:
    virtual ~IPeripheral() = default;
    virtual void init() = 0;
    virtual void update() = 0;

};