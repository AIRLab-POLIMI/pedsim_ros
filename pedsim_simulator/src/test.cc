#include <pedsim_simulator/simulator.h>
#include <qdom.h>   //per utilizzare QDomDocument

QDomDocument doc("scene");
QFile file("scene.xml");
if (!file.open(QIODevice::ReadOnly))
    return;
if (!doc.setContent(&file)) {   //perform parsing of the document, returns false if parse error occurs
    file.close();
    return;
}
file.close();

// print out the element names of all elements that are direct children
// of the outermost element.
QDomElement docElem = doc.documentElement(); //returns the root of the document

QDomNode n = docElem.firstChild();  // returns node containing the root
while(!n.isNull()) {
    QDomElement e = n.toElement(); // try to convert the node to an element.
    if(!e.isNull()) {
        cout << qPrintable(e.tagName()) << '\n'; // the node really is an element.
    }
    n = n.nextSibling();
}

// Here we append a new element to the end of the document
QDomElement elem = doc.createElement("img");
elem.setAttribute("src", "myimage.png");
docElem.appendChild(elem);