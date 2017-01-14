#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <alljoyn/cdm/common/LogModule.h>
#include <sstream>


org_alljoyn_SmartSpaces_Operation_Timer_GetTime::org_alljoyn_SmartSpaces_Operation_Timer_GetTime(QWidget* parent, const char* label, int32_t time)
{
    time_ = time;
    label_ = label;

    dialog_ = new QDialog(parent);
    auto* dlgLayout_ = new QVBoxLayout(dialog_);

    dlgLayout_->addWidget(new QLabel(label_));
    timeSpin_ = new QSpinBox();
    dlgLayout_->addWidget(timeSpin_);
    timeSpin_->setValue(time_);
    QObject::connect(timeSpin_, SIGNAL(valueChanged(int)), this, SLOT(changed()));

    auto* buttons = new QDialogButtonBox();
    dlgLayout_->addWidget(buttons);

    auto* cancel = buttons->addButton(QDialogButtonBox::Cancel);
    QObject::connect(cancel, SIGNAL(clicked(bool)), dialog_, SLOT(reject()));

    auto* ok = buttons->addButton(QDialogButtonBox::Ok);
    QObject::connect(ok, SIGNAL(clicked(bool)), dialog_, SLOT(accept()));
}



org_alljoyn_SmartSpaces_Operation_Timer_GetTime::~org_alljoyn_SmartSpaces_Operation_Timer_GetTime()
{
    delete dialog_;
}



int org_alljoyn_SmartSpaces_Operation_Timer_GetTime::run()
{
    // This is always modal
    return dialog_->exec();
}



void org_alljoyn_SmartSpaces_Operation_Timer_GetTime::changed()
{
    time_ = timeSpin_->value();
}



static bool DialogGetTime(QWidget* parent, const char* label, int32_t& time)
{
    auto* dialog = new org_alljoyn_SmartSpaces_Operation_Timer_GetTime(parent, label, time);
    auto code = dialog->run();
    bool ok = code == QDialog::Accepted;

    if (ok)
    {
        time = dialog->time_;
    }

    delete dialog;
    return ok;
}



