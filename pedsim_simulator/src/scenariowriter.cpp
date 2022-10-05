/**
* Copyright 2014 Social Robotics Lab, University of Freiburg
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*    # Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*    # Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*    # Neither the name of the University of Freiburg nor the names of its
*       contributors may be used to endorse or promote products derived from
*       this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* \author Billy Okal <okal@cs.uni-freiburg.de>
* \author Sven Wehner <mail@svenwehner.de>
*/

#include <pedsim_simulator/element/agent.h>
#include <pedsim_simulator/element/agentcluster.h>
#include <pedsim_simulator/element/areawaypoint.h>
#include <pedsim_simulator/element/attractionarea.h>
#include <pedsim_simulator/element/obstacle.h>
#include <pedsim_simulator/element/waitingqueue.h>
#include <pedsim_simulator/scenariowriter.h>

#include <QFile>
#include <iostream>

#include <ros/ros.h>

ScenarioWriter::ScenarioWriter() {
  // initialize values
  pedestrian_number = 0;
  count_agents = 0;
  currentAgents = nullptr;
  currentSpawnArea = nullptr;
}

bool ScenarioWriter::readFromFile(const QString& filename) {
  ROS_DEBUG("Loading scenario file '%s'.", filename.toStdString().c_str());

  // open file
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    ROS_DEBUG("Couldn't open scenario file!");
    return false;
  }

  // read input
  xmlReader.setDevice(&file);

  // count how many "agent" keywords are present in the scene.xml file (robot agent excluded)
  while (!xmlReader.atEnd()) {
    xmlReader.readNext();
    countAgent();
  }

  if (count_agents = 0) ROS_DEBUG("0 agents in the file, please make sure there is at least one");

  // now modify number of agents according to pedestrian_number.
  int i = 0;
  while (!xmlReader.atEnd() && i < count_agents) { 
    xmlReader.readNext();
    modifyData();
    i++;
  }

  // check for errors
  if (xmlReader.hasError()) {
    // TODO - fix qstring and std string issues here to show error lines
    ROS_DEBUG("Error while reading scenario file");
    return false;
  }

  // report success
  return true;
}

void ScenarioWriter::countAgent() {
  
  if (xmlReader.isStartElement()) {
    const QString elementName = xmlReader.name().toString();
    const QXmlStreamAttributes elementAttributes = xmlReader.attributes();

    if ((elementName == "scenario") || (elementName == "welcome")) {
      // nothing to do
    } else if (elementName == "obstacle") {
      // nothing to do
    } else if (elementName == "waypoint") {
      // nothing to do
    } else if (elementName == "queue") {
      // nothing to do
    } else if (elementName == "attraction") {
      // nothing to do
    } else if (elementName == "agent") {
      const int type = elementAttributes.value("type").toString().toInt();
      if (type != 2) count_agents++;  // increment counter only if agent is not of type 2 (i.e robot)
    } else if (elementName == "source") {
      // nothing to do
    } else if (elementName == "addwaypoint") {
      // nothing to do
    } else if (elementName == "addqueue") {
      // nothing to do
    } else {
      // inform the user about invalid elements
      ROS_DEBUG("Unknown element: <%s>", elementName.toStdString().c_str());
    }
  } else if (xmlReader.isEndElement()) {
    const QString elementName = xmlReader.name().toString();

    if (elementName == "agent") {
      const int type = elementAttributes.value("type").toString().toInt();
      if (type != 2) count_agents++;
    }
  }

}

// The computation adds 1 to each agent keyword (except those of type 2) one at a time until pedestrian_number becomes 0.
// Example: pedestrian_number = 3, agent keywords = 3, then add 1 to first, add 1 to second, add 1 to third.
// TODO: SET STREAM WRITER
void ScenarioWriter::modifyData() {
  if (xmlReader.isStartElement()) {
    const QString elementName = xmlReader.name().toString();
    const QXmlStreamAttributes elementAttributes = xmlReader.attributes();

    if ((elementName == "scenario") || (elementName == "welcome")) {
      // nothing to do
    } else if (elementName == "obstacle") {
      // nothing to do
    } else if (elementName == "waypoint") {
      // nothing to do
    } else if (elementName == "queue") {
      // nothing to do
    } else if (elementName == "attraction") {
      // nothing to do
    } else if (elementName == "agent") {
      const int type = elementAttributes.value("type").toString().toInt();
      const int n = elementAttributes.value("n").toString().toInt();
      if (type != 2) {

      }
      

      
    } else if (elementName == "source") {
      // nothing to do
    } else if (elementName == "addwaypoint") {
      // nothing to do
    } else if (elementName == "addqueue") {
      // nothing to do
    } else {
      // inform the user about invalid elements
      ROS_DEBUG("Unknown element: <%s>", elementName.toStdString().c_str());
    }
  } else if (xmlReader.isEndElement()) {
    const QString elementName = xmlReader.name().toString();

    if (elementName == "agent") {
      currentAgents = nullptr;
    }
  }
}
