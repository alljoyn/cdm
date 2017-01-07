#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <alljoyn/cdm/common/LogModule.h>
#include <sstream>


org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList::org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList(QWidget* parent, uint16_t startingRecord, uint16_t numRecords)
{
    startingRecord_ = startingRecord;
    numRecords_ = numRecords;

    dialog_ = new QDialog(parent);
    auto* dlgLayout_ = new QVBoxLayout(dialog_);

    auto* top = new QWidget();
    dlgLayout_->addWidget(top);

    auto* topLayout_ = new QGridLayout(top);

    auto* startLabel = new QLabel("Starting Record");
    topLayout_->addWidget(startLabel, 0, 0);

    startSpin_ = new QSpinBox();
    topLayout_->addWidget(startSpin_, 0, 1);
    startSpin_->setValue(startingRecord_);
    QObject::connect(startSpin_, SIGNAL(valueChanged(int)), this, SLOT(changed()));

    auto* numLabel = new QLabel("Num Records");
    topLayout_->addWidget(numLabel, 1, 0);

    numSpin_ = new QSpinBox();
    topLayout_->addWidget(numSpin_, 1, 1);
    numSpin_->setValue(numRecords_);
    QObject::connect(numSpin_, SIGNAL(valueChanged(int)), this, SLOT(changed()));

    auto* buttons = new QDialogButtonBox();
    dlgLayout_->addWidget(buttons);

    auto* cancel = buttons->addButton(QDialogButtonBox::Cancel);
    QObject::connect(cancel, SIGNAL(clicked(bool)), dialog_, SLOT(reject()));

    auto* ok = buttons->addButton(QDialogButtonBox::Ok);
    QObject::connect(ok, SIGNAL(clicked(bool)), dialog_, SLOT(accept()));
}



org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList::~org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList()
{
    delete dialog_;
}



int org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList::run()
{
    // This is always modal
    return dialog_->exec();
}



void org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList::changed()
{
    startingRecord_ = startSpin_->value();
    numRecords_ = numSpin_->value();
}



static bool DialogGetChannelList(QWidget* parent, uint16_t& startingRecord, uint16_t& numRecords)
{
    auto* dialog = new org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList(parent, startingRecord, numRecords);
    auto code = dialog->run();
    bool ok = code == QDialog::Accepted;

    if (ok)
    {
        startingRecord = dialog->startingRecord_;
        numRecords = dialog->numRecords_;
    }

    delete dialog;
    return ok;
}



org_alljoyn_SmartSpaces_Operation_Channel_ShowChannelList::org_alljoyn_SmartSpaces_Operation_Channel_ShowChannelList(QWidget* parent, const char* text)
{
    dialog_ = new QMessageBox(parent);
    dialog_->setInformativeText(text);
}



org_alljoyn_SmartSpaces_Operation_Channel_ShowChannelList::~org_alljoyn_SmartSpaces_Operation_Channel_ShowChannelList()
{
    delete dialog_;
}



int org_alljoyn_SmartSpaces_Operation_Channel_ShowChannelList::run()
{
    // This is always modal
    return dialog_->exec();
}
