// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#pragma once

#include <veins/modules/mobility/traci/subscriptionManagement/RemoteSimulationObject.h>
#include <veins/modules/mobility/traci/subscriptionManagement/SubscriptionManager.h>
#include "veins/veins.h"
#include "veins/base/utils/Coord.h"
#include "veins/modules/mobility/traci/TraCIBuffer.h"
#include "veins/base/utils/Heading.h"

using veins::TraCIBuffer;

namespace veins {
namespace TraCISubscriptionManagement {

class VaderePersonSubFactory : public SubscriptionManagerFactory {
    virtual std::shared_ptr<ISubscriptionManager> createSubscriptionManager(std::vector<std::uint8_t> varCodes,
                                                                            std::shared_ptr<TraCIConnection>& c,
                                                                            std::shared_ptr<TraCICommandInterface>& cIfc) const override;
};


/**
 * @brief remote simulation object representing a vadere agent.
 *
 * differences to sumo pedestrian:
 *   - no roadId
 *   - targetList for navigation
 */
class VaderePerson : public RemoteSimulationObject, public IMobileAgent {
public:
    VaderePerson();
    VaderePerson(std::shared_ptr<TraCIConnection> connection, std::shared_ptr<TraCICommandInterface> commandInterface);
    virtual ~VaderePerson();
    template<typename T>
    friend class RSOFactory;

    std::set<std::string> getIdList();
    int getIdCount();
    const std::string& getId() const override; // RemoteSimulationObject|IMobileAgent
    simtime_t getTime() const override; // RemoteSimulationObject|IMobileAgent
    double getAngel() const override; // IMobileAgent
    const Coord& getPosition() const override; // IMobileAgent
    double getSpeed() const override; // IMobileAgent
    const std::string& getTypeId() const override; // IMobileAgent
    double getX() const override; // IMobileAgent
    double getY() const override; // IMobileAgent
    std::vector<std::string> getTargetList() const;

    Heading getHeading() const override; // IMobileAgent

protected:
    void initVariableMap() override;

    void setIdList(TraCIBuffer& buffer);
    void setIdCount(TraCIBuffer& buffer);

    void setAngel(TraCIBuffer& buffer);
    virtual void setTypeId(TraCIBuffer& buffer) override; // IMobileAgent
    void setSpeed(TraCIBuffer& buffer);
    void setPosition(TraCIBuffer& buffer) override; // IMobileAgent
    void setPositionXXX(TraCIBuffer& buffer); // IMobileAgent

    void setTargetList(TraCIBuffer& buffer);

private:

    void copy(const VaderePerson& other);

    static std::set<std::string> idList;
    static int idCount;

    double angel;
    Coord position;
    double x;
    double y;
    double speed;
    std::string typeID;
    std::vector<std::string> targetList;
    Heading heading;
};

} /* namesapce TraCISubscriptionManagement */
} /* namespace veins */

