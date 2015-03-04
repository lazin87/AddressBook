#include "newaddresstab.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "adddialog.h"

NewAddressTab::NewAddressTab(QWidget *parent)
{
    Q_UNUSED(parten);

    descriptionLabel = new QLabel( tr("There are currently no contacts in your address book. "
                                      "\nClick Add to add new contacts."
                                      )
                                 );

    addButton = new QPushButton(tr("Add") );
    connect(addButton, SIGNAL(clicked() ), this, SLOT(addEntry() ) );

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(addButton, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}

NewAddressTab::~NewAddressTab()
{

}

void NewAddressTab::addEntry()
{
    AddDialog aDialog;

    if( 0 != aDialog.exec() )
    {
        QString name = aDialog.nameText->text();
        QString address = aDialog.addressText->toPlainText();

        emit sendDetalis(name, address);
    }
}
