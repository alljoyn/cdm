#include <QDialogButtonBox>
#include <QVBoxLayout>


org_alljoyn_SmartSpaces_Operation_CycleControl_Execute::org_alljoyn_SmartSpaces_Operation_CycleControl_Execute(QWidget* parent)
{
    command_ = CycleControlInterface::OPERATIONAL_COMMANDS_START;

    dialog_ = new QDialog(parent);
    auto* dlgLayout_ = new QVBoxLayout(dialog_);

    dlgLayout_->addWidget(new QLabel("Command"));

    commandBox_ = new QComboBox();
    commandBox_->setEditable(false);

    commandBox_->addItem("Start", QVariant(CycleControlInterface::OPERATIONAL_COMMANDS_START));
    commandBox_->addItem("Stop", QVariant(CycleControlInterface::OPERATIONAL_COMMANDS_STOP));
    commandBox_->addItem("Pause", QVariant(CycleControlInterface::OPERATIONAL_COMMANDS_PAUSE));
    commandBox_->addItem("Resume", QVariant(CycleControlInterface::OPERATIONAL_COMMANDS_RESUME));

    dlgLayout_->addWidget(commandBox_);
    QObject::connect(commandBox_, SIGNAL(currentIndexChanged(int)), this, SLOT(changed()));

    auto* buttons = new QDialogButtonBox();
    dlgLayout_->addWidget(buttons);

    auto* cancel = buttons->addButton(QDialogButtonBox::Cancel);
    QObject::connect(cancel, SIGNAL(clicked(bool)), dialog_, SLOT(reject()));

    auto* ok = buttons->addButton(QDialogButtonBox::Ok);
    QObject::connect(ok, SIGNAL(clicked(bool)), dialog_, SLOT(accept()));
}



org_alljoyn_SmartSpaces_Operation_CycleControl_Execute::~org_alljoyn_SmartSpaces_Operation_CycleControl_Execute()
{
    delete dialog_;
}



int org_alljoyn_SmartSpaces_Operation_CycleControl_Execute::run()
{
    // This is always modal
    return dialog_->exec();
}



void org_alljoyn_SmartSpaces_Operation_CycleControl_Execute::changed()
{
    QVariant var = commandBox_->currentData();
    command_ = static_cast<CycleControlInterface::OperationalCommands>(var.toInt());
}



static bool DialogGetCommand(QWidget* parent, CycleControlInterface::OperationalCommands& command)
{
    auto* dialog = new org_alljoyn_SmartSpaces_Operation_CycleControl_Execute(parent);
    auto code = dialog->run();
    bool ok = code == QDialog::Accepted;

    if (ok)
    {
        command = dialog->command_;
    }

    delete dialog;
    return ok;
}
