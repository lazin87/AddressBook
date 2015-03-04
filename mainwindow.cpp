#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "addresswidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
   // , ui(new Ui::MainWindow)
{
   // ui->setupUi(this);
    addressWidget = new AddressWidget;
    setCentralWidget(addressWidget);
    createMenus();
    setWindowsTitle(tr("Address Book") );
}

MainWindow::~MainWindow()
{
   // delete ui;
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File") );

    openAct = new QAction( tr("&Open..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered() ), this, SLOT(openFile() ) );

    //

    editAct = new QAction( tr("&Edit Entry..."), this);
    editAct->setEnabled(false);
    toolMenu->addAction(editAct);
    connect(editAct, SIGNAL(triggered() ), addressWidget, SLOT(editEntry() ) );
}
