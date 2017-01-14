#include <QLineEdit>
#include <QDialog>

namespace CDMQtWidgets {
//======================================================================

class org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase_GetLang : public QWidget
{
    Q_OBJECT
public:
    org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase_GetLang(QWidget* parent, const QString& lang);
    ~org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase_GetLang();

    int run();

private slots:
    void changed();

public:
    QString lang_;

private:
    QString label_;
    QDialog* dialog_;
    QLineEdit* langEdit_;
};

//======================================================================
} // of namespace CDMQtWidgets
