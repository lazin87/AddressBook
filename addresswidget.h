#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H
#include <QTableWidget>

class TableModel;
class NewAddressTab;
class QSortFilterProxyModel;

class AddressWidget : public QTabWidget
{
    Q_OBJECT

public:
    AddressWidget(QWidget *parent = 0);
    ~AddressWidget();

    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

public slots:
    void addEntry();
    void addEntry(QString name, QString address);
    void editEntry();
    void removeEntry();

signals:
    void selectionChanged(const QItemSelection &selected);

private:
    void setupTabs();

    TableModel *table;
    NewAddressTab *newAddressTab;
    QSortFilterProxyModel *proxyModel;
};

#endif // ADDRESSWIDGET_H
