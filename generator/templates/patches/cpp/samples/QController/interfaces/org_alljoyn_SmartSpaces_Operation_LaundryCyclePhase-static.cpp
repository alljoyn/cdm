#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <sstream>


org_alljoyn_SmartSpaces_Operation_LaundryCyclePhase_GetLang::org_alljoyn_SmartSpaces_Operation_LaundryCyclePhase_GetLang(QWidget* parent, const QString& lang)
{
    lang_ = lang;

    dialog_ = new QDialog(parent);
    auto* dlgLayout_ = new QVBoxLayout(dialog_);

    dlgLayout_->addWidget(new QLabel("Language"));
    langEdit_ = new QLineEdit();
    dlgLayout_->addWidget(langEdit_);
    langEdit_->setText(lang_);
    QObject::connect(langEdit_, SIGNAL(returnPressed()), this, SLOT(changed()));

    auto* buttons = new QDialogButtonBox();
    dlgLayout_->addWidget(buttons);

    auto* cancel = buttons->addButton(QDialogButtonBox::Cancel);
    QObject::connect(cancel, SIGNAL(clicked(bool)), dialog_, SLOT(reject()));

    auto* ok = buttons->addButton(QDialogButtonBox::Ok);
    QObject::connect(ok, SIGNAL(clicked(bool)), dialog_, SLOT(accept()));
}



org_alljoyn_SmartSpaces_Operation_LaundryCyclePhase_GetLang::~org_alljoyn_SmartSpaces_Operation_LaundryCyclePhase_GetLang()
{
    delete dialog_;
}



int org_alljoyn_SmartSpaces_Operation_LaundryCyclePhase_GetLang::run()
{
    // This is always modal
    return dialog_->exec();
}



void org_alljoyn_SmartSpaces_Operation_LaundryCyclePhase_GetLang::changed()
{
    lang_ = langEdit_->text();
}



static bool DialogGetLang(QWidget* parent, QString& lang)
{
    auto* dialog = new org_alljoyn_SmartSpaces_Operation_LaundryCyclePhase_GetLang(parent, lang);
    auto code = dialog->run();
    bool ok = code == QDialog::Accepted;

    if (ok)
    {
        lang = dialog->lang_;
    }

    delete dialog;
    return ok;
}



