#ifndef ABSTRACTXMLREADER_H
#define ABSTRACTXMLREADER_H

#include <QStringList>
#include <QXmlStreamReader>

class AbstractXmlReader
{
public:
    AbstractXmlReader();
    virtual ~AbstractXmlReader();

    virtual bool parse(QIODevice *file) = 0;
    QString getError() const;

protected:
    QXmlStreamReader xml;
};

#endif // ABSTRACTXMLREADER_H
