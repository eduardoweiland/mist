#include "abstractxmlreader.h"

AbstractXmlReader::AbstractXmlReader()
{
}

AbstractXmlReader::~AbstractXmlReader()
{
}

QString AbstractXmlReader::getError() const
{
    return QObject::tr("%1 (line %2, column %3)")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}
