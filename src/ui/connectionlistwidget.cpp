#include <QSettings>
#include <QMessageBox>

#include "connectionlistwidget.h"
#include "createconnectiondialog.h"

ConnectionListWidget::ConnectionListWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    model = new ConnectionModel(listView);
    listView->setModel(model);
}

void ConnectionListWidget::addConnection()
{
    CreateConnectionDialog *createConnection = new CreateConnectionDialog(model, this);
    createConnection->setAttribute(Qt::WA_DeleteOnClose);
    createConnection->exec();
}

void ConnectionListWidget::removeConnection()
{
    QMessageBox::StandardButton choice = QMessageBox::question(
                this,
                tr("Remove connection"),
                tr("Do you really want to remove this connection?"));

    if (choice == QMessageBox::StandardButton::Yes) {
        model->remove(listView->selectionModel()->selectedIndexes());
    }
}
