#include "mainwindow.h"
#include "addresswidget.h"
#include <QMenu>
#include <QFileDialog>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    addressWidget = new AddressWidget;
    setCentralWidget(addressWidget);
    createMenus();
    setWindowTitle(tr("Address Book") );
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File") );

    openAct = new QAction( tr("&Open..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered() ), this, SLOT(openFile() ) );

    saveAct = new QAction( tr("&Save As..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered() ), this, SLOT(saveFile() ) );

    fileMenu->addSeparator();

    exitAct = new QAction( tr("E&xit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, SIGNAL(triggered() ), this, SLOT(close() ) );

    toolMenu = menuBar()->addMenu(tr("&Tools") );

    addAct = new QAction(tr("&Add Entry..."), this);
    toolMenu->addAction(addAct);
    connect(addAct, SIGNAL(triggered() ), addressWidget, SLOT(addEntry() ) );

    editAct = new QAction( tr("&Edit Entry..."), this);
    editAct->setEnabled(false);
    toolMenu->addAction(editAct);
    connect(editAct, SIGNAL(triggered() ), addressWidget, SLOT(editEntry() ) );

    toolMenu->addSeparator();

    removeAct = new QAction(tr("&Remove Entry"), this);
    removeAct->setEnabled(false);
    toolMenu->addAction(removeAct);
    connect(removeAct, SIGNAL(triggered() ), addressWidget, SLOT(removeEntry() ) );

    connect(addressWidget, SIGNAL(selectionChanged(QItemSelection) ), this, SLOT(updateActions(QItemSelection) ) );
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);

    if(false == fileName.isEmpty() )
    {
        addressWidget->readFromFile(fileName);
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);

    if(false == fileName.isEmpty() )
    {
        addressWidget->writeToFile(fileName);
    }
}

void MainWindow::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

    if(false == indexes.isEmpty() )
    {
        removeAct->setEnabled(true);
        editAct->setEnabled(true);
    }
    {
        removeAct->setEnabled(false);
        editAct->setEnabled(false);
    }
}
