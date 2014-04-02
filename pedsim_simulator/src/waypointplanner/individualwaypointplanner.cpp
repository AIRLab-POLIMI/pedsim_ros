// Simulating Group Dynamics in Crowds of Pedestrians (SGDiCoP)
// Author: Sven Wehner <mail@svenwehner.de>
// Copyright (c) 2013 by Sven Wehner

// Includes
#include "individualwaypointplanner.h"
// → SGDiCoP
#include "logging.h"
#include "element/agent.h"
#include "element/areawaypoint.h"
#include "element/waitingqueue.h"


IndividualWaypointPlanner::IndividualWaypointPlanner() {
	// initialize values
	agent = nullptr;
	destination = nullptr;
}

bool IndividualWaypointPlanner::setAgent(Agent* agentIn) {
	agent = agentIn;

	return true;
}

Waypoint* IndividualWaypointPlanner::getDestination() const {
	return destination;
}

void IndividualWaypointPlanner::setDestination(Waypoint* waypointIn) {
	destination = waypointIn;
}

Waypoint* IndividualWaypointPlanner::getCurrentWaypoint() {
	return destination;
}

bool IndividualWaypointPlanner::hasCompletedDestination() const {
	if(destination == nullptr) {
		WARN_LOG("IndividualWaypointPlanner: No destination set!");
		return true;
	}

	// check whether group has reached waypoint
	AreaWaypoint* areaWaypoint = dynamic_cast<AreaWaypoint*>(destination);
	if(areaWaypoint != nullptr) {
		return areaWaypoint->isWithinArea(agent->getPosition());
	}
	else {
		ERROR_LOG("Unknown Waypoint type: %1", destination->toString());
		return true;
	}
}

QString IndividualWaypointPlanner::name() const {
	return tr("IndividualWaypointPlanner");
}

QString IndividualWaypointPlanner::toString() const {
	return tr("%1 (%2)").arg(name()).arg((agent==nullptr)?"null":agent->toString());
}
