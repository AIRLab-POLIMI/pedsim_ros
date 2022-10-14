#include <QFile>
#include <iostream>

#include <ros/ros.h>
#include <pedsim_simulator/xmlmanager.h>



XmlManager::XmlManager() {
    //
}


// look for "agent" keywords in the QDomDocument file and add its occurrences to a vector 
int XmlManager::countAgents() {
    int n_agent = 0;

    QDomElement docElem = document.documentElement(); //returns the root of the document
    QDomNode n = docElem.firstChild();  // returns first child of the root
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            if (e.tagName().toStdString() == "agent" && e.attribute("type").toInt() != 2) {
                n_agent++;
            }
        }
        n = n.nextSibling();
    }

    return n_agent;
}

// pedestrian_number is the number of peds the user wishes to use
// agents_number is the number of agent keywords found in the scene.xml file
bool XmlManager::editAgentNumber(const QString& filename, int pedestrian_number) {
    QDomDocument doc("scene");
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite))
        return false;
    if (!doc.setContent(&file)) {   //perform parsing of the document, returns false if parse error occurs
        file.close();
        return false;
    }
    document = doc;

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = document.documentElement(); //returns the root of the document
    //cout << qPrintable(docElem.tagName()) << '\n'; // print root
    QDomNode n = docElem.firstChild();  // returns first child of the root

    // used for printing the data saved from the xml for debugging
    /* while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            if (e.tagName().toStdString() == "agent") {
                cout << qPrintable(e.tagName()) << " type: " << qPrintable(e.attribute("type")) << " n: " << qPrintable(e.attribute("n")) << '\n'; 
            } 
        }
        n = n.nextSibling();
    } */

    int agents_number = countAgents();
    std::vector<int> v(agents_number, 0); // define a vector of int of length agents_number and fill it with zeros
    
    int temp = pedestrian_number;
    for(int i=0;  ;i=(i+1)%agents_number) { // here I add 1 to every member of the list cyclically until I reach the number of pedestrians
        v[i]++;
        temp--;
        if(temp == 0) break;
    }

    /* for(int i=0; i < v.size(); i++) {   // print the list for debugging purposes
        cout << "[" << v[i] << "] "; 
    }
    cout << '\n'; */

    // now add these new values to the QDomDocument document
    //n = docElem.firstChild();  // decomment if you also decomment lines 52-60
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

    // Write changes to same file
    file.resize(0);
    QTextStream stream;
    stream.setDevice(&file);
    document.save(stream, 4);

    file.close();
    return true;
}

