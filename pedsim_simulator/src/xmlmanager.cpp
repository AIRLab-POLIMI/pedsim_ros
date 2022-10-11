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
    // // print out the element names of all elements that are direct children
    // // of the outermost element.
    // QDomElement docElem = doc.documentElement(); //returns the root of the document
    // cout << qPrintable(docElem.tagName()) << '\n'; // print root

    // QDomNode n = docElem.firstChild();  // returns first child of the root
    // while(!n.isNull()) {
    //     QDomElement e = n.toElement(); // try to convert the node to an element.
    //     if(!e.isNull()) {
    //         cout << qPrintable(e.tagName()) << '\n'; // the node really is an element.
    //     }
    //     n = n.nextSibling();
    // }

    // // Here we append a new element to the end of the document
    // QDomElement elem = doc.createElement("img");
    // elem.setAttribute("src", "myimage.png");
    // docElem.appendChild(elem);

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = document.documentElement(); //returns the root of the document
    cout << qPrintable(docElem.tagName()) << '\n'; // print root

    QDomNode n = docElem.firstChild();  // returns first child of the root
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            cout << qPrintable(e.tagName()) << '\n'; // the node really is an element.
        }
        n = n.nextSibling();
    }

    return true;
}

void XmlManager::editAgentNumber(int n) {
    

}

// count how many "agent" keywords are present in the scene.xml file (robot agent, i.e type 2, excluded)
int XmlManager::countAgents() {
    int count = 0;

    QDomElement docElem = document.documentElement(); //returns the root of the document
    QDomNode n = docElem.firstChild();  // returns first child of the root
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            if (e.tagName().toStdString() == "agent" && e.attribute("type").toInt() != 2) {
                //cout << qPrintable(e.attribute("type")) << '\n';
                count++;
            }
        }
        n = n.nextSibling();
    }

    return count;
}