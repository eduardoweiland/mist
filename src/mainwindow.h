#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:

    //! \brief Shows a dialog containing information about MIST.
    void about(void);

    //! \brief Shows a dialog containing information about Qt version used.
    void aboutQt(void);
};

#endif // MAINWINDOW_H
