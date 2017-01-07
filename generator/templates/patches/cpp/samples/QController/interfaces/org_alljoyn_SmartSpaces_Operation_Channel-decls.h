#include <QSpinBox>
#include <QMessageBox>
#include <QDialog>

namespace CDMQtWidgets {
//======================================================================

class org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList : public QWidget
{
    Q_OBJECT
public:
    org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList(QWidget* parent, uint16_t startingRecord, uint16_t numRecords);
    ~org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList();

    int run();

private slots:
    void changed();

public:
    uint16_t startingRecord_;
    uint16_t numRecords_;

private:
    QDialog* dialog_;
    QSpinBox* startSpin_;
    QSpinBox* numSpin_;
};



class org_alljoyn_SmartSpaces_Operation_Channel_ShowChannelList : public QWidget
{
    Q_OBJECT
public:
    org_alljoyn_SmartSpaces_Operation_Channel_ShowChannelList(QWidget* parent, const char* text);
    ~org_alljoyn_SmartSpaces_Operation_Channel_ShowChannelList();

    int run();

private:
    QMessageBox* dialog_;
};

//======================================================================
} // of namespace CDMQtWidgets
