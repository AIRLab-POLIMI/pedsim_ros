
#ifndef _xmlmanager_h_
#define _xmlmanager_h_

#include <pedsim_simulator/scene.h>

#include <QPair>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QTextStream>

class XmlManager {
  // Constructor and Destructor
 public:
  XmlManager();

  // Methods
 public:
  bool editAgentNumber(const QString& filename, int pedestrian_number);
  int countAgents();

  // Attributes
 public:
  QDomDocument document;

};

#endif