#ifndef NEWADDRESSTAB_H
#define NEWADDRESSTAB_H
#include <QWidget>

class QLabel;
class QPushButton;
class QVBoxLayout;

class NewAddressTab: public QWidget
{
    Q_OBJECT
public:
    NewAddressTab(QWidget *parent = 0);
    ~NewAddressTab();

public slots:
    void addEntry();

signals:
    void sendDetalis(QString name, QString address);

private:
    QLabel *descriptionLabel;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;
};

#endif // NEWADDRESSTAB_H
