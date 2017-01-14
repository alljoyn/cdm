#include <QComboBox>
#include <QDialog>

namespace CDMQtWidgets {
//======================================================================

class org_alljoyn_SmartSpaces_Operation_CycleControl_Execute : public QWidget
{
    Q_OBJECT
public:
    org_alljoyn_SmartSpaces_Operation_CycleControl_Execute(QWidget* parent);
    ~org_alljoyn_SmartSpaces_Operation_CycleControl_Execute();

    int run();

private slots:
    void changed();

public:
    CycleControlInterface::OperationalCommands command_;

private:
    QDialog* dialog_;
    QComboBox* commandBox_;
};

//======================================================================
} // of namespace CDMQtWidgets
