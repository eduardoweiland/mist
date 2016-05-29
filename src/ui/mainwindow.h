#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>

#include "ui_mainwindow.h"
#include "tablelistwidget.h"

#include "../entity/schema.h"
#include "../entity/query.h"

enum QtMsgType;
class AbstractXmlReader;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private slots:

    //! \brief Shows a dialog containing information about MIST.
    void about(void);

    //! \brief Shows a dialog containing information about Qt version used.
    void aboutQt(void);

    void loadLogFile(void);
    void loadSchemaFile(void);
    void generateCandidates(void);

    void startServer(void);
    void stopServer(void);

private slots:
    void logHandler(const QString &msg);

private:
    bool selectAndParseFile(const QString &title, const QString &filter, AbstractXmlReader *parser);

    Schema schema;
    QList<Query> queries;
};

#endif // MAINWINDOW_H
