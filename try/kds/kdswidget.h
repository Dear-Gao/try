#ifndef KDSWIDGET_H
#define KDSWIDGET_H

#include <QWidget>
#include <QButtonGroup>

#include <KF5/KScreen/kscreen/output.h>
#include <KF5/KScreen/kscreen/edid.h>
#include <KF5/KScreen/kscreen/mode.h>
#include <KF5/KScreen/kscreen/config.h>
#include <KF5/KScreen/kscreen/getconfigoperation.h>
#include <KF5/KScreen/kscreen/setconfigoperation.h>

namespace Ui {
class KDSWidget;
}

class QDBusInterface;

class KDSWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KDSWidget(QWidget *parent = nullptr);
    ~KDSWidget();

    void beginSetupKF5();
    QPoint getWinPos();
    QString getCurrentPrimaryScreenName();
    double getCurrentScale();

    void setupComponent();
    void setupConnect();

    int getCurrentStatus();

    void setCurrentUIStatus(int id);
    void setCurrentFirstOutputTip();

    void syncPrimaryScreenData(QString pName);

    QString id() const;

    QDBusInterface * ukcciface;

public:
    void setConfig(const KScreen::ConfigPtr &config);
    KScreen::ConfigPtr currentConfig() const;

    void setCloneModeSetup();
    void setExtendModeSetup();
    void setFirstModeSetup();
    void setOtherModeSetup();
    void setLeftExtendModeSetup();

    bool writeFile(const QString &filePath);
    void writeGlobal(const KScreen::OutputPtr &output);
    bool writeGlobalPart(const KScreen::OutputPtr &output, QVariantMap &info,
                         const KScreen::OutputPtr &fallback);
    QString globalFileName(const QString &hash);
    QVariantMap getGlobalData(KScreen::OutputPtr output);


private:
    QString findFirstOutput();
    QSize findBestCloneSize();
    bool turnonSpecifiedOutput(const KScreen::OutputPtr &output, int x, int y);

    int turnonAndGetRightmostOffset(const KScreen::OutputPtr &output, int x);

    QString filePath() const;

    static QString configsDirPath();

    int currentid;

private:
    Ui::KDSWidget *ui;
    QButtonGroup * btnsGroup;

private:
    KScreen::ConfigPtr mConfig = nullptr;
    KScreen::ConfigPtr mPreConfig = nullptr;

    static QString mConfigsDirName;

public:
    enum DisplaySwitchAction {
        TurnOffExternal= 0,
        Clone = 1,
        ExtendToRight = 2,
//        ExtendToLeft = 3,
        TurnOffEmbedded = 3,
        None = 4,
    };

private:
    void cloneScreens(KScreen::OutputList &connectedOutputs);
    void singleOutput(KScreen::OutputList &connectedOutputs);
    void extendToRight(KScreen::OutputList &connectedOutputs);

    KScreen::OutputPtr embeddedOutput(const KScreen::OutputList &connectedOutputs);

    static KScreen::ModePtr biggestMode(const KScreen::ModeList &modes);

    KScreen::ModePtr bestModeForSize(const KScreen::ModeList &modes, const QSize &size);
    KScreen::ModePtr bestModeForOutput(const KScreen::OutputPtr &output);

    KScreen::ConfigPtr displaySwitch(DisplaySwitchAction action);

    void initializeOutput(const KScreen::OutputPtr &output);

    void doApplyConfig(const KScreen::ConfigPtr &config);


public slots:
    void msgReceiveAnotherOne(const QString &msg);

private slots:
    void nextSelectedOption();
    void lastSelectedOption();
    void confirmCurrentOption();
    void receiveButtonClick(int x, int y);
    void closeApp();

Q_SIGNALS:
    void tellBtnClicked(int id);

};

#endif // KDSWIDGET_H
