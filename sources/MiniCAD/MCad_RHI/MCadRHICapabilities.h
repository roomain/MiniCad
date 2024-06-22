#pragma once
/***********************************************
* @headerfile MCadRHICapabilities.h
* @date 02 / 03 / 2024
* @author Roomain
************************************************/
#include <string>
#include <memory>
#include <vector>

class MCadIRHICapabilityInspector;

/*@brief interface for inspected*/
class MCadIRHIInspected
{
public:
	virtual void inspected(const MCadIRHICapabilityInspector& a_inspector)const = 0;
	virtual std::string name( ) const = 0;
};

/*@brief simple capability*/
class MCadIRHICapability : public MCadIRHIInspected
{
public:
    virtual std::string value( )const = 0;
};

/*@brief group of capabilities*/
class MCadRHICapabilityGroup : public MCadIRHIInspected
{
protected:
    std::vector<std::unique_ptr<MCadIRHIInspected>> m_capabilities;
    std::string m_groupName;

public:
    MCadRHICapabilityGroup( ) = delete;
    explicit MCadRHICapabilityGroup(const std::string& a_name);
    std::string name( )const final { return m_groupName; }
    virtual void inspected(const MCadIRHICapabilityInspector& a_inspector)const override;
};

/*@brief capabilities of a device*/
class MCadIRHIDeviceCapabilities : public MCadRHICapabilityGroup
{
protected:
    //
public:
    virtual void inspected(const MCadIRHICapabilityInspector& a_inspector)const override;
};


/*********************************************
* General Capabilities
* |
* -- Devices capabilities
*    |
*    -- A capability
**********************************************/

/*@brief capabilities inspector*/
class MCadIRHICapabilityInspector
{
public:
    virtual void inspect(std::unique_ptr<MCadIRHICapability>&& a_capability)const = 0;
    virtual void inspect(std::unique_ptr<MCadRHICapabilityGroup>&& a_capability)const = 0;
    virtual void inspect(std::unique_ptr<MCadIRHIDeviceCapabilities>&& a_capability)const = 0;
};