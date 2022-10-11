/**
* Copyright 2022 Politecnico di Milano
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
* \author Emanuele Vivani 
*/

#ifndef _scenariowriter_h_
#define _scenariowriter_h_

#include <pedsim_simulator/scene.h>

#include <QPair>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class ScenarioWriter {
  // Constructor and Destructor
 public:
  ScenarioWriter();

  // Methods
 public:
  bool readFromFile(const QString& filename);
  int pedestrian_number;  // this is the number of pedestrian(=agents) the user wants to have in the simulation
  int count_agents;       // this is the number of pedestrian(=agents) that are written in the scene.xml file

 protected:
  void modifyData();
  void countAgent();

  // Attributes
 private:
  QXmlStreamReader xmlReader;
  QXmlStreamWriter xmlWriter;

  AgentCluster* currentAgents;
  SpawnArea* currentSpawnArea;
};

#endif
