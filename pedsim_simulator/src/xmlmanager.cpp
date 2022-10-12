#include <QFile>
#include <iostream>

#include <ros/ros.h>
#include <pedsim_simulator/xmlmanager.h>



XmlManager::XmlManager() {
    //
}

bool XmlManager::buildTree(const QString& filename) {
    QDomDocument doc("scene");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    if (!doc.setContent(&file)) {   //perform parsing of the document, returns false if parse error occurs
        file.close();
        return false;
    }
    file.close();
    document = doc;

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = document.documentElement(); //returns the root of the document
    cout << qPrintable(docElem.tagName()) << '\n'; // print root
    QDomNode n = docElem.firstChild();  // returns first child of the root

    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            if (e.tagName().toStdString() == "agent") cout << qPrintable(e.tagName()) << " type: " << qPrintable(e.attribute("type")) << " n: " << qPrintable(e.attribute("n")) << '\n'; 
            else {
                //cout << qPrintable(e.tagName()) << '\n'; // the node really is an element.
            }
        }
        n = n.nextSibling();
    }

    return true;
}

// look for "agent" keywords in the QDomDocument file and add its occurrences to a vector 
std::vector<int> XmlManager::saveAgentsNumber() {
    int n_agent = 0;
    std::vector<int> vectorAgents;

    QDomElement docElem = document.documentElement(); //returns the root of the document
    QDomNode n = docElem.firstChild();  // returns first child of the root
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            if (e.tagName().toStdString() == "agent" && e.attribute("type").toInt() != 2) {
                n_agent = e.attribute("n").toInt();
                //cout << n_agent << '\n';
                vectorAgents.push_back(n_agent);
            }
        }
        n = n.nextSibling();
    }

    for (auto v : vectorAgents)
        std::cout << "[" << v << "] ";
    cout << '\n';

    return vectorAgents;
}

// pedestrian_number is the number of peds the user wishes to use
// agent_number is the number of agent keywords found in the scene.xml file
void XmlManager::editAgentNumber(int pedestrian_number) {
    //cout << pedestrian_number << '\n';
    std::vector<int> v = saveAgentsNumber();
    int size = v.size();
    
    int temp = pedestrian_number;
    for(int i=0;  ;i=(i+1)%size) { // here I add 1 to every agent cyclically until I reach the number of pedestrians
        v[i]++;
        temp--;
        if(temp == 0) break;
    }

    for(int i=0; i < v.size(); i++) {
        cout << "[" << v[i] << "] "; 
    }
    cout << '\n';

    // now add these new values to the QDomDocument document

    QDomElement docElem = document.documentElement(); //returns the root of the document
    QDomNode n = docElem.firstChild();  // returns first child of the root
    int j = 0;
    while(!n.isNull()) {
        QDomElement e = n.toElement(); 
        if(!e.isNull()) {
            if (e.tagName().toStdString() == "agent" && e.attribute("type").toInt() != 2) {
                e.setAttribute("n", v[j]);
                j++;
            }
        }
        n = n.nextSibling();
    }

    // n = docElem.firstChild();  // returns first child of the root
    // while(!n.isNull()) {
    //     QDomElement e = n.toElement(); // try to convert the node to an element.
    //     if(!e.isNull()) {
    //         if (e.tagName().toStdString() == "agent") cout << qPrintable(e.tagName()) << " type: " << qPrintable(e.attribute("type")) << " n: " << qPrintable(e.attribute("n")) << '\n'; 
    //         else {
    //             //cout << qPrintable(e.tagName()) << '\n'; // the node really is an element.
    //         }
    //     }
    //     n = n.nextSibling();
    // }
    
}


