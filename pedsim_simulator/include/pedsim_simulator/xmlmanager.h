
#ifndef _xmlmanager_h_
#define _xmlmanager_h_

#include <pedsim_simulator/scene.h>

#include <QPair>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

class XmlManager {
  // Constructor and Destructor
 public:
  XmlManager();

  // Methods
 public:
  bool buildTree(const QString& filename);
  void editAgentNumber(int pedestrian_number);
  std::vector<int> saveAgentsNumber();
  QDomDocument document;
  
 protected:
  void processData();

  // Attributes
 private:
  
};

#endif