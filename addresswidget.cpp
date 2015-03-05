#include "addresswidget.h"
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QFile>
#include <QHeaderView>
#include <QLineEdit>
#include<QTextEdit>
#include "adddialog.h"
#include "tablemodel.h"
#include "newaddresstab.h"

AddressWidget::AddressWidget(QWidget *parent)
    :QTabWidget(parent)
{
    table = new TableModel(this);
    newAddressTab = new NewAddressTab(this);

    connect( newAddressTab
           , SIGNAL(sendDetalis(QString, QString) )
           , this
           , SLOT(addEntry(QString,QString) )
           );
    addTab(newAddressTab, "Address Book");

    setupTabs();
}

AddressWidget::~AddressWidget()
{

}

void AddressWidget::setupTabs()
{
    QStringList groups;

    groups << "ABC" << "DEF" << "GHI" << "JKL" << "MNO" << "PQR" << "STU" << "VW" << "XYZ";

    for(int i = 0; i < groups.size(); ++i)
    {
        QString str = groups.at(i);
        QString regExp = QString("^[%1].*").arg(str);

        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);
        proxyModel->setFilterRegExp(QRegExp(regExp, Qt::CaseInsensitive) );
        proxyModel->setFilterKeyColumn(0);

        QTableView *tableView = new QTableView;
        tableView->setModel(proxyModel);

        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        tableView->setSortingEnabled(true);

        connect( tableView->selectionModel()
               , SIGNAL(selectionChanged(QItemSelection, QItemSelection) )
               , this
               , SIGNAL(selectionChanged(QItemSelection) )
               );

        addTab(tableView, str);
    }
}

void AddressWidget::addEntry()
{
    AddDialog aDialog;

    if( aDialog.exec() )
    {
        QString name = aDialog.nameText->text();
        QString address = aDialog.addressText->toPlainText();

        addEntry(name, address);
    }
}

void AddressWidget::addEntry(QString name, QString address)
{
    TableModel::ListDataType list = table->getList();
    TableModel::DataType pair(name, address);

    if( !list.contains(pair) )
    {
        table->insertRows(0, 1, QModelIndex() );

        QModelIndex index = table->index(0, 0, QModelIndex() );
        table->setData(index, name, Qt::EditRole);
        index = table->index(0, 1, QModelIndex() );
        table->setData(index, address, Qt::EditRole);
        removeTab( indexOf(newAddressTab) );
    }
    else
    {
        QMessageBox::information( this
                                , tr("Duplicate Name")
                                , tr("The Name \"%1\" already exists.").arg(name)
                                );
    }
}

void AddressWidget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget() );
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model() );
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QString name;
    QString address;
    int row = -1;

    foreach(QModelIndex index, indexes)
    {
        row = proxy->mapToSource(index).row();
        QModelIndex nameIndex = table->index(row, 0, QModelIndex() );
        QVariant varName = table->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex addressIndex = table->index(row, 1, QModelIndex() );
        QVariant varAddr = table->data(addressIndex, Qt::DisplayRole);
        address = varAddr.toString();
    }

    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edit a Contact") );

    aDialog.nameText->setReadOnly(true);
    aDialog.nameText->setText(name);
    aDialog.addressText->setText(address);

    if( 0 != aDialog.exec() )
    {
        QString newAddress = aDialog.addressText->toPlainText();

        if(newAddress != address)
        {
            QModelIndex index = table->index(row, 1, QModelIndex() );
            table->setData(index, newAddress, Qt::EditRole);
        }
    }
}

void AddressWidget::removeEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget() );
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model() );
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach(QModelIndex index, indexes)
    {
        int row = proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex() );
    }

    if(table->rowCount(QModelIndex() ) == 0)
    {
        insertTab(0, newAddressTab, "Address Book");
    }
}

void AddressWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly) )
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString() );
        return;
    }

    TableModel::ListDataType pairs = table->getList();
    QDataStream out(&file);
    out << pairs;
}

void AddressWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if( !file.open(QIODevice::ReadOnly) )
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString() );
        return;
    }

    TableModel::ListDataType pairs = table->getList();
    QDataStream in(&file);
    in >> pairs;

    if(pairs.isEmpty() )
    {
        QMessageBox::information(this, tr("No contacts in file"), tr("The file yoe are attempting to open contains no contacts.") );
    }
    else
    {
        for(int i = 0; i < pairs.size(); ++i)
        {
            TableModel::DataType p = pairs.at(i);
            addEntry(p.first, p.second);
        }
    }
}
