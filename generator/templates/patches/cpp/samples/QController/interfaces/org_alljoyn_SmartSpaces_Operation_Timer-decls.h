#include <QSpinBox>
#include <QMessageBox>
#include <QDialog>

namespace CDMQtWidgets {
//======================================================================

class org_alljoyn_SmartSpaces_Operation_Timer_GetTime : public QWidget
{
    Q_OBJECT
public:
    org_alljoyn_SmartSpaces_Operation_Timer_GetTime(QWidget* parent, const char* label, int32_t time);
    ~org_alljoyn_SmartSpaces_Operation_Timer_GetTime();

    int run();

private slots:
    void changed();

public:
    int32_t time_;

private:
    QString label_;
    QDialog* dialog_;
    QSpinBox* timeSpin_;
};

//======================================================================
} // of namespace CDMQtWidgets
