#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

enum QtMsgType;

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

    void startServer(void);

private slots:
    void logHandler(const QString &msg);
};

#endif // MAINWINDOW_H
