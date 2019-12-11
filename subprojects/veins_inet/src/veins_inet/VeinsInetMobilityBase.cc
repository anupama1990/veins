/*
 * VeinsInetMobilityBase.cc
 *
 *  Created on: Oct 2, 2019
 *      Author: stsc
 */

#include "VeinsInetMobilityBase.h"

namespace veins {

Register_Abstract_Class(VeinsInetMobilityBase);
const simsignal_t VeinsInetMobilityBase::mobility_pre_ini = registerSignal("veins_inet_mobility_base_mobility_pre_init");


VeinsInetMobilityBase::VeinsInetMobilityBase() {
    // TODO Auto-generated constructor stub

}

VeinsInetMobilityBase::~VeinsInetMobilityBase() {
    // TODO Auto-generated destructor stub
}


void VeinsInetMobilityBase::initialize(int stage)
{
    MobilityBase::initialize(stage);

    // We patch the OMNeT++ Display String to set the initial position. Make sure this works.
    ASSERT(hasPar("initFromDisplayString") && par("initFromDisplayString"));
}


inet::Coord VeinsInetMobilityBase::getCurrentPosition()
{
    return lastPosition;
}

inet::Coord VeinsInetMobilityBase::getCurrentVelocity()
{
    return lastVelocity;
}

inet::Coord VeinsInetMobilityBase::getCurrentAcceleration()
{
    throw cRuntimeError("Invalid operation");
}

inet::Quaternion VeinsInetMobilityBase::getCurrentAngularPosition()
{
    return lastOrientation;
}

inet::Quaternion VeinsInetMobilityBase::getCurrentAngularVelocity()
{
    return lastAngularVelocity;
}

inet::Quaternion VeinsInetMobilityBase::getCurrentAngularAcceleration()
{
    throw cRuntimeError("Invalid operation");
}

void VeinsInetMobilityBase::setInitialPosition()
{
    subjectModule->getDisplayString().setTagArg("p", 0, lastPosition.x);
    subjectModule->getDisplayString().setTagArg("p", 1, lastPosition.y);
    MobilityBase::setInitialPosition();
}

void VeinsInetMobilityBase::handleSelfMessage(cMessage* message)
{
}

TraCIGenericScenarioManager* VeinsInetMobilityBase::getManager() const
{
    if (!manager) manager = TraCIScenarioManagerAccess().get();
    return manager;
}

TraCICommandInterface* VeinsInetMobilityBase::getCommandInterface() const
{
    if (!commandInterface) commandInterface = getManager()->getCommandInterface();
    return commandInterface;
}

void VeinsInetMobilityBase::setExternalId(std::string id)
{
    external_id = id;
}

std::string VeinsInetMobilityBase::getExternalId() const
{
    if (external_id == "") throw cRuntimeError("TraCIMobility::getExternalId called with no external_id set yet");
    return external_id;
}

} /* namespace veins */
