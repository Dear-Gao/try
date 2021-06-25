#include "kdswidget.h"
#include "ui_kdswidget.h"

#include <QScreen>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QtDBus/QtDBus>

#include <QJsonDocument>

#include <kwindowsystem.h>

#include "expendbutton.h"

#define TITLEHEIGHT 90
#define OPTIONSHEIGHT 70
#define BOTTOMHEIGHT 60


enum {
    FIRSTSCREEN,
    CLONESCREEN,
    EXTENDSCREEN,
//    LEXTENDSCREEN,
    OTHERSCREEN,
    ALLMODES,
};

bool operator<(const QSize &s1, const QSize &s2)
{
    return s1.width() * s1.height() < s2.width() * s2.height();
}

template<>
bool qMapLessThanKey(const QSize &s1, const QSize &s2)
{
    return s1 < s2;
}

QString KDSWidget::mConfigsDirName = QStringLiteral("" /*"configs/"*/); // TODO: KDE6 - move these files into the subfolder

KDSWidget::KDSWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KDSWidget)
{
    ui->setupUi(this);
}

KDSWidget::~KDSWidget()
{
    delete ui;

    delete ukcciface;
}

void KDSWidget::beginSetupKF5(){
    QObject::connect(new KScreen::GetConfigOperation(), &KScreen::GetConfigOperation::finished,
                     [&](KScreen::ConfigOperation *op) {
        setConfig(qobject_cast<KScreen::GetConfigOperation*>(op)->config());
    });

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground, true);

    /* 不在任务栏显示图标 */
    KWindowSystem::setState(winId(), NET::SkipTaskbar | NET::SkipPager);

    btnsGroup = new QButtonGroup;

    ukcciface = new QDBusInterface("org.ukui.ukcc.session",
                                   "/",
                                   "org.ukui.ukcc.session.interface",
                                   QDBusConnection::sessionBus());

    QDBusConnection::systemBus().connect(QString(), \
                                         QString(), \
                                         "org.ukui.kds.interface", \
                                         "signalNextOption", \
                                         this, SLOT(nextSelectedOption()));

    QDBusConnection::systemBus().connect(QString(), \
                                         QString(), \
                                         "org.ukui.kds.interface", \
                                         "signalLastOption", \
                                         this, SLOT(lastSelectedOption()));

    QDBusConnection::systemBus().connect(QString(), \
                                         QString(), \
                                         "org.ukui.kds.interface", \
                                         "signalCloseApp", \
                                         this, SLOT(closeApp()));

    QDBusConnection::systemBus().connect(QString(), \
                                         QString(), \
                                         "org.ukui.kds.interface", \
                                         "signalMakeClicked", \
                                         this, SLOT(confirmCurrentOption()));


    QDBusConnection::systemBus().connect(QString(), \
                                         QString(), \
                                         "org.ukui.kds.interface", \
                                         "signalButtonClicked", \
                                         this, SLOT(receiveButtonClick(int,int)));
}

QString KDSWidget::getCurrentPrimaryScreenName(){
    QDBusInterface usdiface("org.ukui.SettingsDaemon",
                            "/org/ukui/SettingsDaemon/wayland",
                            "org.ukui.SettingsDaemon.wayland",
                            QDBusConnection::sessionBus());

    if (usdiface.isValid()){
        QDBusReply<QString> reply = usdiface.call("priScreenName");
        if (reply.isValid()){
            return reply.value();
        }
    }

    const KScreen::ConfigPtr &config = this->currentConfig();

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
        if (output.data()->isPrimary()){
            return output.data()->name();
        }
    }

    return QString("");
}

double KDSWidget::getCurrentScale(){
    QDBusInterface usdiface("org.ukui.SettingsDaemon",
                            "/org/ukui/SettingsDaemon/wayland",
                            "org.ukui.SettingsDaemon.wayland",
                            QDBusConnection::sessionBus());

    if (usdiface.isValid()){
        QDBusReply<double> reply = usdiface.call("scale");
        if (reply.isValid()){
            return reply.value();
        }
    }

    return 1.0;
}

QPoint KDSWidget::getWinPos(){
    QString pName = getCurrentPrimaryScreenName();
    if (!pName.isEmpty()){

        const KScreen::ConfigPtr &config = this->currentConfig();

        Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
            if (QString::compare(output.data()->name(), pName) == 0){
                QRect rect = output.data()->geometry();
                return rect.center();
            }
        }
    }

    QScreen * pScreen = QGuiApplication::screens().at(0);
    return pScreen->geometry().center();
}

void KDSWidget::setupComponent(){

    ui->outputPrimaryTip->hide();
//    setCurrentFirstOutputTip();

    for (int i = 0; i < ALLMODES; i++){
        ExpendButton * btn = new ExpendButton();
        btn->setFixedHeight(70);
        btnsGroup->addButton(btn, i);

        switch (i) {
        case FIRSTSCREEN:
            btn->setSign(FIRSTSCREEN % 2);
            btn->setBtnText(tr("First Screen"));
            btn->setBtnLogo(":/img/main.png");
            break;
        case CLONESCREEN:
            btn->setSign(CLONESCREEN % 2);
            btn->setBtnText(tr("Clone Screen"));
            btn->setBtnLogo(":/img/clone.png");
            break;
        case EXTENDSCREEN:
            btn->setSign(EXTENDSCREEN % 2);
            btn->setBtnText(tr("Extend Screen"));
            btn->setBtnLogo(":/img/extend.png");
            break;
//        case LEXTENDSCREEN:
//            btn->setSign(LEXTENDSCREEN % 2);
//            btn->setBtnText(tr("Left Extend Screen"));
//            btn->setBtnLogo(":/img/extend.png");
//            break;
        case OTHERSCREEN:
            btn->setSign(OTHERSCREEN % 2);
            btn->setBtnText(tr("Vice Screen"));
            btn->setBtnLogo(":/img/vice.png");
            break;
        default:
            break;
        }

        ui->btnsVerLayout->addWidget(btn);
    }

    int h = TITLEHEIGHT + OPTIONSHEIGHT * ALLMODES + BOTTOMHEIGHT;
    setFixedWidth(400);
    setFixedHeight(h);

    /// QSS
    ui->titleFrame->setStyleSheet("QFrame#titleFrame{background: #A6000000; border: none; border-top-left-radius: 24px; border-top-right-radius: 24px;}");
    ui->bottomFrame->setStyleSheet("QFrame#bottomFrame{background: #A6000000; border: none; border-bottom-left-radius: 24px; border-bottom-right-radius: 24px;}");

    ui->splitFrame->setStyleSheet("QFrame#splitFrame{background: #99000000; border: none;}");

    ui->titleLabel->setStyleSheet("QLabel{color: #FFFFFF; font-size: 24px;}");
    ui->outputPrimaryTip->setStyleSheet("QLabel{color: #60FFFFFF; font-size: 18px;}");
    ui->outputName->setStyleSheet("QLabel{color: #60FFFFFF; font-size: 18px;}");
    ui->outputDisplayName->setStyleSheet("QLabel{color: #60FFFFFF; font-size: 18px;}");
}

void KDSWidget::setupConnect(){
    connect(btnsGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, [=](int id){

        if (currentid != id){

        switch (id) {
        case TurnOffExternal:
            ukcciface->call("setScreenMode", "first");
            doApplyConfig(displaySwitch(DisplaySwitchAction::TurnOffExternal));
            setCurrentUIStatus(TurnOffExternal);
            break;
        case Clone:
            ukcciface->call("setScreenMode", "copy");
            doApplyConfig(displaySwitch(DisplaySwitchAction::Clone));
            setCurrentUIStatus(Clone);
            break;
        case ExtendToRight:
            ukcciface->call("setScreenMode", "expand");
            doApplyConfig(displaySwitch(DisplaySwitchAction::ExtendToRight));
            setCurrentUIStatus(ExtendToRight);
            break;
        case TurnOffEmbedded:
            ukcciface->call("setScreenMode", "second");
            doApplyConfig(displaySwitch(DisplaySwitchAction::TurnOffEmbedded));
            setCurrentUIStatus(TurnOffEmbedded);
            break;
        default:
            break;
        }

        } else {
            close();
        }




        /* 获取旧选项 */
        /*for (QAbstractButton * button : btnsGroup->buttons()){
            ExpendButton * btn = dynamic_cast<ExpendButton *>(button);
//            qDebug() << "old index: " << btn->getBtnChecked();
            int index = btnsGroup->id(button);
            if (index == id && btn->getBtnChecked()){
                    goto closeapp;
            }
        }

        switch (id) {
        case FIRSTSCREEN:
            setFirstModeSetup();
            setCurrentUIStatus(FIRSTSCREEN);
            break;
        case CLONESCREEN:
            setCloneModeSetup();
            setCurrentUIStatus(CLONESCREEN);
            break;
        case EXTENDSCREEN:
            setExtendModeSetup();
            setCurrentUIStatus(EXTENDSCREEN);
            break;
//        case LEXTENDSCREEN:
//            setLeftExtendModeSetup();
//            setCurrentUIStatus(LEXTENDSCREEN);
//            break;
        case OTHERSCREEN:
            setOtherModeSetup();
            setCurrentUIStatus(OTHERSCREEN);
            break;
        default:
            break;
        }


closeapp:
//        close();
        QTimer::singleShot(3000, this, [=]{
            close();
        });*/

    });
}

void KDSWidget::doApplyConfig(const KScreen::ConfigPtr &config){

    auto *op = new KScreen::SetConfigOperation(config);

    op->exec();

    hide();

    QTimer::singleShot(1000, this, [=](){
        writeFile(filePath());

        close();
    });
}

int KDSWidget::getCurrentStatus(){

    QString firstOutputName;

    QList<QPoint> allpos;

    const KScreen::ConfigPtr &config = this->currentConfig();

    const KScreen::OutputList &outputs = config->connectedOutputs();

    firstOutputName = findFirstOutput();

    if (outputs.count() < 2){
        return FIRSTSCREEN;
    } else {
        /* output.data()->clones().isEmpty() is not valid */
        Q_FOREACH(const KScreen::OutputPtr &output, outputs) {

//            if (!output.data()->clones().isEmpty()){
//                return CLONESCREEN;
//            }
            QPoint p = output.data()->pos();
            allpos.append(p);

            if (QString::compare(firstOutputName, output.data()->name()) == 0){
                if (!output.data()->isEnabled()){
                    return OTHERSCREEN;
                }
            }

            if (!output.data()->isEnabled()){
                return FIRSTSCREEN;
            }
        }

        Q_FOREACH(QPoint tmp, allpos) {
            if (tmp.x() != 0 || tmp.y() != 0){
                return EXTENDSCREEN;
            }
        }

//        Q_FOREACH(const KScreen::OutputPtr &output, outputs) {
//            if (output.data()->pos().x() != 0){
//                return EXTENDSCREEN;
//            }
//        }

        return CLONESCREEN;
    }

//    Q_FOREACH(const KScreen::OutputPtr &output, outputs) {

//        if (QString::compare(firstOutputName, output.data()->name()) == 0){
//            QPoint pPos = output.data()->pos();
//            if (pPos.x() > 0){
//                return LEXTENDSCREEN;
//            } else {
//                return REXTENDSCREEN;
//            }
//        }
//    }


}

void KDSWidget::setCurrentUIStatus(int id){
    //set all no checked
    currentid = id;
    for (QAbstractButton * button : btnsGroup->buttons()){
        ExpendButton * btn = dynamic_cast<ExpendButton *>(button);

        btn->setBtnChecked(false);

        if (id == btnsGroup->id(button)){
            btn->setBtnChecked(true);
            btn->setChecked(true);
        }
    }

    // status == -1
    if (id == -1){
        ExpendButton * btn1 = dynamic_cast<ExpendButton *>(btnsGroup->button(FIRSTSCREEN));
//        btn1->setBtnChecked(true);
        btn1->setChecked(true);
    }
}

void KDSWidget::setConfig(const KScreen::ConfigPtr &config) {

    mConfig = config;


    //获取主屏位置
    QPoint point = getWinPos();
    move(point.x() - width()/2, point.y() - height()/2);

    setupComponent();
    setupConnect();

    setCurrentUIStatus(getCurrentStatus());
}

KScreen::ConfigPtr KDSWidget::currentConfig() const {

    return mConfig;
}

void KDSWidget::setCurrentFirstOutputTip(){

    const KScreen::ConfigPtr &config = this->currentConfig();

    QString firstOutputName = findFirstOutput();

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
        QString opName = output.data()->name();
        QString opDisName = output.data()->edid()->name();

        if (QString::compare(firstOutputName, output.data()->name()) == 0){
            ui->outputName->setText(opName);
            ui->outputDisplayName->setText(""/*opDisName*/);

            return;
        }
    }

    ui->outputName->setText(tr("N/A"));

}

QString KDSWidget::findFirstOutput(){

    int firstopID = -1;
    QString firstopName;

    const KScreen::ConfigPtr &config = this->currentConfig();

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
        if (firstopID == -1){
            firstopID = output.data()->id();
            firstopName = output.data()->name();
        }
        if (firstopID > output.data()->id()){
            firstopID = output.data()->id();
            firstopName = output.data()->name();
        }
    }

    return firstopName;
}

void KDSWidget::setCloneModeSetup(){

    QString pName = getCurrentPrimaryScreenName();

    QList<int> clones;

    const KScreen::ConfigPtr &config = this->currentConfig();

    mPreConfig = this->currentConfig()->clone();

    QSize cloneSize = findBestCloneSize();

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {

        float bestRate = 0.0;
        QString bestID;

        output.data()->setEnabled(true);

        Q_FOREACH (const KScreen::ModePtr &mode, output->modes()) {

            if (mode.data()->size() == cloneSize){

                float r = mode.data()->refreshRate();
                if (bestRate < r){
                    bestRate = r;
                    bestID = mode.data()->id();
                }

            }
        }

        if (bestRate > 0){

            output.data()->setCurrentModeId(bestID);
            output.data()->setRotation(KScreen::Output::None);
            output.data()->setPos(QPoint(0, 0));

            if (!output.data()->isPrimary()){
                clones.append(output.data()->id());
            }
        }

    }

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {


        if (QString::compare(pName, output.data()->name()) == 0){
            output.data()->setClones(clones);
        } else {
            output.data()->setClones(QList<int>());
        }

    }



    if (!KScreen::Config::canBeApplied(config)) {
//        qDebug() << "Can not apply!";
        return;
    }

    auto *op = new KScreen::SetConfigOperation(config);

    op->exec();

    syncPrimaryScreenData(pName);

    QTimer::singleShot(1000, this, [=](){

    });

}

void KDSWidget::setExtendModeSetup(){
    const KScreen::ConfigPtr &config = this->currentConfig();

    mPreConfig = this->currentConfig()->clone();

    QString pName = getCurrentPrimaryScreenName();

    int x = 0;

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
        if (QString::compare(pName, output.data()->name()) != 0){
            continue;
        }

        output.data()->setEnabled(true);
        output.data()->setClones(QList<int>());

        x = turnonAndGetRightmostOffset(output, x);

    }

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
        if (QString::compare(pName, output.data()->name()) == 0){
            continue;
        }

        output.data()->setEnabled(true);
        output.data()->setClones(QList<int>());

        x = turnonAndGetRightmostOffset(output, x);

    }

    if (!KScreen::Config::canBeApplied(config)) {
//        qDebug() << "Can not apply!";
        return;
    }

    auto *op = new KScreen::SetConfigOperation(config);

    op->exec();

    //
    syncPrimaryScreenData(pName);
}

void KDSWidget::setLeftExtendModeSetup(){
    const KScreen::ConfigPtr &config = this->currentConfig();

    int x = 0;


    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
        if (output.data()->isPrimary()){
            continue;
        }

        output.data()->setEnabled(true);
        output.data()->setClones(QList<int>());

        x = turnonAndGetRightmostOffset(output, x);

    }

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
        if (!output.data()->isPrimary()){
            continue;
        }

        output.data()->setEnabled(true);
        output.data()->setClones(QList<int>());

        x = turnonAndGetRightmostOffset(output, x);

    }

    if (!KScreen::Config::canBeApplied(config)) {
//        qDebug() << "Can not apply!";
        return;
    }

    auto *op = new KScreen::SetConfigOperation(config);

    op->exec();

}

void KDSWidget::setFirstModeSetup(){
    const KScreen::ConfigPtr &config = this->currentConfig();

    QString firstName = findFirstOutput();

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
        /* 取消镜像模式标志位 */
        output.data()->setClones(QList<int>());

        if (QString::compare(output.data()->name(), firstName) == 0){
            turnonSpecifiedOutput(output, 0, 0);
        } else {
            output.data()->setEnabled(false);
        }

    }

    if (!KScreen::Config::canBeApplied(config)) {
//        qDebug() << "Can not apply!";
        return;
    }

    auto * op = new KScreen::SetConfigOperation(config);
    op->exec();

    syncPrimaryScreenData(firstName);
}

void KDSWidget::setOtherModeSetup(){
    const KScreen::ConfigPtr &config = this->currentConfig();

    QString firstName = findFirstOutput();
    QString otherName;

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {

        /* 取消镜像模式标志位 */
        output.data()->setClones(QList<int>());

        if (QString::compare(output.data()->name(), firstName) == 0){
            output.data()->setEnabled(false);
        } else {
//            output.data()->setEnabled(true);
            turnonSpecifiedOutput(output, 0, 0);
        }

        //获取非主屏的Name。TODO:多屏(>2)情况下呢？
        if (QString::compare(output.data()->name(), firstName) == 0){

        } else {
            otherName = output.data()->name();
        }

    }

    if (!KScreen::Config::canBeApplied(config)) {
//        qDebug() << "Can not apply!";
        return;
    }

    auto * op = new KScreen::SetConfigOperation(config);

    op->exec();

    syncPrimaryScreenData(otherName);
}

int KDSWidget::turnonAndGetRightmostOffset(const KScreen::OutputPtr &output, int x){

    turnonSpecifiedOutput(output, x, 0);

    int width;
//    width = output.data()->size().width();
    width = output.data()->preferredMode().data()->size().width();

//    qDebug() << output.data()->name() << "width is " << output.data()->size() << output.data()->preferredMode().data()->size();
//    Q_FOREACH (const KScreen::ModePtr &mode, output->modes()) {
//        qDebug() << "mode is: " << mode.data()->id() << mode.data()->size();
//    }

    x += width;

    return x;
}

bool KDSWidget::turnonSpecifiedOutput(const KScreen::OutputPtr &output, int x, int y){

    output->setEnabled(true);
    output->setCurrentModeId(output.data()->preferredModeId());
    output->setRotation(KScreen::Output::None);
    output->setPos(QPoint(x, y));

    return true;

}

QSize KDSWidget::findBestCloneSize(){

    const KScreen::ConfigPtr &config = this->currentConfig();

    QMap<QSize, int> commonSizes;

    Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
        QList<QSize> pSizes;
        Q_FOREACH (const KScreen::ModePtr &mode, output->modes()) {

            QSize s = mode.data()->size();
            if (pSizes.contains(s))
                continue;

            pSizes.append(s);

            if (commonSizes.contains(s)){
                commonSizes[s]++;
            } else {
                commonSizes.insert(s, 1);
            }

        }
    }

    QList<QSize> commonResults = commonSizes.keys(config->connectedOutputs().count());

    QSize smallestSize;

    /* TODO: */
    if (commonSizes.isEmpty()){
//        Q_FOREACH (const KScreen::OutputPtr &output, config->connectedOutputs()) {
//            if (!smallestSize.isValid() || output->preferredMode()->size() < smallestSize) {
//                smallestSize = output->preferredMode()->size();
//            }
//        }
    } else {

        Q_FOREACH(QSize s1, commonResults){
            if (!smallestSize.isValid() || smallestSize < s1){
                smallestSize = s1;
            }
        }

    }

    return smallestSize;

}

void KDSWidget::nextSelectedOption(){
    int current = btnsGroup->checkedId();
    int next;

    /* no button checked */
//    if (current == -1)
//        ;

    next = current == ALLMODES - 1 ? 0 : current + 1;

    ExpendButton * btn = dynamic_cast<ExpendButton *>(btnsGroup->button(next));
    btn->setChecked(true);
}

void KDSWidget::lastSelectedOption(){
    int current = btnsGroup->checkedId();
    int last;

    /* no button checked */
    if (current == -1)
        current = ALLMODES;

    last = current == 0 ? ALLMODES - 1 : current - 1;

    ExpendButton * btn = dynamic_cast<ExpendButton *>(btnsGroup->button(last));
    btn->setChecked(true);
}

void KDSWidget::confirmCurrentOption(){
    int current = btnsGroup->checkedId();
//    qDebug() << "current checked" << current;

    if (current == -1)
        return;

    ExpendButton * btn = dynamic_cast<ExpendButton *>(btnsGroup->button(current));
//    btn->click();
    btn->animateClick();
}

void KDSWidget::closeApp(){
    close();
}

void KDSWidget::receiveButtonClick(int x, int y){
//    qDebug() << "receive button press " << x << y;
    if (!this->geometry().contains(x, y)){
        close();
    }

}


void KDSWidget::msgReceiveAnotherOne(const QString &msg){
//    qDebug() << "another one " << msg;
    nextSelectedOption();
}

void KDSWidget::syncPrimaryScreenData(QString pName){
    if (!pName.isEmpty()){

        const KScreen::ConfigPtr &config = this->currentConfig();

        double scale = getCurrentScale();
        int x, y, w, h;

        Q_FOREACH(const KScreen::OutputPtr &output, config->connectedOutputs()) {
            if (QString::compare(output.data()->name(), pName) == 0){
                QRect rect = output.data()->geometry();

                QDBusMessage message = QDBusMessage::createMethodCall("org.ukui.SettingsDaemon",
                                                       "/org/ukui/SettingsDaemon/wayland",
                                                       "org.ukui.SettingsDaemon.wayland",
                                                       "priScreenChanged");
                x = rect.x() / scale;
                y = rect.y() / scale;
                w = rect.width() / scale;
                h = rect.height() / scale;
                message << x << y << w << h << pName;
                qDebug() << "refresh primary info:" << pName << "\n";
                qDebug() << "Pos(" << x << "," << y << ")";
                qDebug() << "QSize(" << w << "," << h << ")";
                QDBusConnection::sessionBus().send(message);
            }
        }
    }
}

QString KDSWidget::id() const
{
    if (!mConfig) {
        return QString();
    }
    return mConfig->connectedOutputsHash();
}

QString KDSWidget::configsDirPath()
{
    QString dirPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) % QStringLiteral("/kscreen/");
    return dirPath % mConfigsDirName;
}

QString KDSWidget::filePath() const
{
    if (!QDir().mkpath(configsDirPath())) {
        return QString();
    }
    return configsDirPath() % id();
}

QVariantMap metadata(const KScreen::OutputPtr &output)
{
    QVariantMap metadata;
    metadata[QStringLiteral("name")] = output->name();
    if (!output->edid() || !output->edid()->isValid()) {
        return metadata;
    }

    metadata[QStringLiteral("fullname")] = output->edid()->deviceId();
    return metadata;
}

QString KDSWidget::globalFileName(const QString &hash)
{
    Q_UNUSED(hash)
    QString s_dirPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)
                        %QStringLiteral("/kscreen/");
    QString dir = s_dirPath  % QStringLiteral("outputs/");
    if (!QDir().mkpath(dir)) {
        return QString();
    }
    return QString();
}

QVariantMap KDSWidget::getGlobalData(KScreen::OutputPtr output)
{
    QFile file(globalFileName(output->hashMd5()));
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file" << file.fileName();
        return QVariantMap();
    }
    QJsonDocument parser;
    return parser.fromJson(file.readAll()).toVariant().toMap();
}

bool KDSWidget::writeGlobalPart(const KScreen::OutputPtr &output, QVariantMap &info,
                             const KScreen::OutputPtr &fallback)
{
    info[QStringLiteral("id")] = output->hash();
    info[QStringLiteral("metadata")] = metadata(output);
    info[QStringLiteral("rotation")] = output->rotation();

    // Round scale to four digits
    info[QStringLiteral("scale")] = int(output->scale() * 10000 + 0.5) / 10000.;

    QVariantMap modeInfo;
    float refreshRate = -1.;
    QSize modeSize;
    if (output->currentMode() && output->isEnabled()) {
        refreshRate = output->currentMode()->refreshRate();
        modeSize = output->currentMode()->size();
    } else if (fallback && fallback->currentMode()) {
        refreshRate = fallback->currentMode()->refreshRate();
        modeSize = fallback->currentMode()->size();
    }

    if (refreshRate < 0 || !modeSize.isValid()) {
        return false;
    }

    modeInfo[QStringLiteral("refresh")] = refreshRate;

    QVariantMap modeSizeMap;
    modeSizeMap[QStringLiteral("width")] = modeSize.width();
    modeSizeMap[QStringLiteral("height")] = modeSize.height();
    modeInfo[QStringLiteral("size")] = modeSizeMap;

    info[QStringLiteral("mode")] = modeInfo;

    return true;
}

void KDSWidget::writeGlobal(const KScreen::OutputPtr &output)
{
    // get old values and subsequently override
    QVariantMap info = getGlobalData(output);
    if (!writeGlobalPart(output, info, nullptr)) {
        return;
    }
    QFile file(globalFileName(output->hashMd5()));
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open global output file for writing! " << file.errorString();
        return;
    }

    file.write(QJsonDocument::fromVariant(info).toJson());
    return;
}

bool KDSWidget::writeFile(const QString &filePath)
{
    if (id().isEmpty()) {
        return false;
    }

    const KScreen::OutputList outputs = mConfig->outputs();


    const auto oldConfig = mPreConfig;
    KScreen::OutputList oldOutputs;
    if (oldConfig) {
        oldOutputs = oldConfig->outputs();
    }

    qDebug() << "----------1";

    QVariantList outputList;
    for (const KScreen::OutputPtr &output : outputs) {
        QVariantMap info;

        const auto oldOutputIt = std::find_if(oldOutputs.constBegin(), oldOutputs.constEnd(),
                                              [output](const KScreen::OutputPtr &out) {
                                                  return out->hashMd5() == output->hashMd5();
                                               }
        );
        const KScreen::OutputPtr oldOutput = oldOutputIt != oldOutputs.constEnd() ? *oldOutputIt :
                                                                                    nullptr;

        if (!output->isConnected()) {
            continue;
        }

        qDebug() << "run here 1";

        writeGlobalPart(output, info, oldOutput);

        qDebug() << "run here 2";
        info[QStringLiteral("primary")] = !output->name().compare(
            getCurrentPrimaryScreenName(), Qt::CaseInsensitive);
        info[QStringLiteral("enabled")] = output->isEnabled();
        qDebug() << "run here 3";
        auto setOutputConfigInfo = [&info](const KScreen::OutputPtr &out) {
            if (!out) {
                return;
            }

            QVariantMap pos;
            pos[QStringLiteral("x")] = out->pos().x();
            pos[QStringLiteral("y")] = out->pos().y();
            info[QStringLiteral("pos")] = pos;
        };
        qDebug() << "run here 4";

        setOutputConfigInfo(output->isEnabled() ? output : oldOutput);

        if (output->isEnabled()) {
            // try to update global output data
            writeGlobal(output);
        }

        qDebug() << "run here 5";

        outputList.append(info);
    }

    qDebug() << "----------2";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
//        qWarning() << "Failed to open config file for writing! " << file.errorString();
        return false;
    }
    file.write(QJsonDocument::fromVariant(outputList).toJson());
    //qDebug() << "Config saved on: " << file.fileName();
    qDebug() << "----------3";

    return true;
}




void KDSWidget::singleOutput(KScreen::OutputList &connectedOutputs)
{
//    ASSERT_OUTPUTS(connectedOutputs);
    if (connectedOutputs.isEmpty()) {
        return;
    }

    KScreen::OutputPtr output = connectedOutputs.take(connectedOutputs.keys().first());
    if (output->modes().isEmpty()) {
        return;
    }
    output->setEnabled(true);
    output->setPrimary(true);
    output->setPos(QPoint(0, 0));
}

void KDSWidget::extendToRight(KScreen::OutputList &connectedOutputs)
{
//    if (connectedOutputs.isEmpty()) {
//        return;
//    }

//    KScreen::OutputPtr biggest = biggestOutput(connectedOutputs);
//    Q_ASSERT(biggest);

//    connectedOutputs.remove(biggest->id());

//    biggest->setEnabled(true);
//    biggest->setPrimary(true);
//    biggest->setPos(QPoint(0, 0));

//    int globalWidth = biggest->geometry().width();

//    Q_FOREACH (KScreen::OutputPtr output, connectedOutputs) {
//        output->setEnabled(true);
//        output->setPrimary(false);
//        output->setPos(QPoint(globalWidth, 0));

//        globalWidth += output->geometry().width();
//    }
}


KScreen::OutputPtr KDSWidget::embeddedOutput(const KScreen::OutputList &outputs)
{
    Q_FOREACH (const KScreen::OutputPtr &output, outputs) {
        if (output->type() != KScreen::Output::Panel) {
            continue;
        }

        return output;
    }

    return KScreen::OutputPtr();
}

KScreen::ModePtr KDSWidget::biggestMode(const KScreen::ModeList &modes)
{
    Q_ASSERT(!modes.isEmpty());

    int modeArea, biggestArea = 0;
    KScreen::ModePtr biggestMode;
    Q_FOREACH (const KScreen::ModePtr &mode, modes) {
        modeArea = mode->size().width() * mode->size().height();
        if (modeArea < biggestArea) {
            continue;
        }
        if (modeArea == biggestArea && mode->refreshRate() < biggestMode->refreshRate()) {
            continue;
        }
        if (modeArea == biggestArea && mode->refreshRate() > biggestMode->refreshRate()) {
            biggestMode = mode;
            continue;
        }

        biggestArea = modeArea;
        biggestMode = mode;
    }

    return biggestMode;
}

KScreen::ModePtr KDSWidget::bestModeForSize(const KScreen::ModeList &modes, const QSize &size)
{
    KScreen::ModePtr bestMode;
    Q_FOREACH (const KScreen::ModePtr &mode, modes) {
        if (mode->size() != size) {
            continue;
        }

        if (!bestMode) {
            bestMode = mode;
            continue;
        }

        if (mode->refreshRate() > bestMode->refreshRate()) {
            bestMode = mode;
        }
    }

    return bestMode;
}

uint qHash(const QSize &size)
{
    return size.width() * size.height();
}

void KDSWidget::cloneScreens(KScreen::OutputList &connectedOutputs)
{
    if (connectedOutputs.isEmpty()) {
        return;
    }

    QSet<QSize> commonSizes;
    QSet<QSize> modeSizes;
    const QSize maxScreenSize = mConfig->screen()->maxSize();

    Q_FOREACH (const KScreen::OutputPtr &output, connectedOutputs) {
        Q_FOREACH (const KScreen::ModePtr &mode, output->modes()) {
            const QSize size = mode->size();
            if (size.width() > maxScreenSize.width() || size.height() > maxScreenSize.height()) {
                continue;
            }
            modeSizes.insert(mode->size());
        }

        // If we have nothing to compare against
        if (commonSizes.isEmpty()) {
            commonSizes = modeSizes;
            modeSizes.clear();
            continue;
        }

        commonSizes.intersect(modeSizes);
    }

    // fallback to biggestMode if no commonSizes have been found
    if (commonSizes.isEmpty()) {
        Q_FOREACH (KScreen::OutputPtr output, connectedOutputs) {
            if (output->modes().isEmpty()) {
                continue;
            }
            output->setEnabled(true);
            output->setPos(QPoint(0, 0));
            const KScreen::ModePtr mode = biggestMode(output->modes());
            Q_ASSERT(mode);
            output->setCurrentModeId(mode->id());
        }
        return;
    }

    // At this point, we know we have common sizes, let's get the biggest on
    QList<QSize> commonSizeList = commonSizes.values();
    std::sort(commonSizeList.begin(), commonSizeList.end());
    const QSize biggestSize = commonSizeList.last();

    // Finally, look for the mode with biggestSize and biggest refreshRate and set it
    KScreen::ModePtr bestMode;
    Q_FOREACH (KScreen::OutputPtr output, connectedOutputs) {
        if (output->modes().isEmpty()) {
            continue;
        }
        bestMode = bestModeForSize(output->modes(), biggestSize);
        Q_ASSERT(bestMode); // we resolved this mode previously, so it better works
        output->setEnabled(true);
        output->setPos(QPoint(0, 0));
        output->setCurrentModeId(bestMode->id());
    }
}

void KDSWidget::initializeOutput(const KScreen::OutputPtr &output)
{
//    output->setCurrentModeId(config.modeId.value_or(bestModeForOutput(output)->id()));
//    output->setRotation(config.rotation.value_or(output->rotation()));
//    if (features & KScreen::Config::Feature::PerOutputScaling) {
//        output->setScale(config.scale.value_or(bestScaleForOutput(output)));
//    }
}

KScreen::ModePtr KDSWidget::bestModeForOutput(const KScreen::OutputPtr &output)
{
    if (KScreen::ModePtr outputMode = output->preferredMode()) {
        return outputMode;
    }

    return biggestMode(output->modes());
}

KScreen::ConfigPtr KDSWidget::displaySwitch(DisplaySwitchAction action){
    KScreen::ConfigPtr config = mConfig;
    Q_ASSERT(config);

    KScreen::OutputList connectedOutputs = config->connectedOutputs();

    for (const auto output : connectedOutputs) {
//        initializeOutput(output);
        output->setCurrentModeId(bestModeForOutput(output)->id());
        output->setRotation(output->rotation());
    }

    // There's not much else we can do with only one output
    if (connectedOutputs.count() < 2) {
        singleOutput(connectedOutputs);
        return config;
    }

    // We cannot try all possible combinations with two and more outputs
//    if (connectedOutputs.count() > 2) {
//        extendToRight(connectedOutputs);
//        return config;
//    }

    KScreen::OutputPtr embedded, external;
    embedded = embeddedOutput(connectedOutputs);
    // If we don't have an embedded output (desktop with two external screens
    // for instance), then pretend one of them is embedded
    if (!embedded) {
        embedded = connectedOutputs.value(connectedOutputs.keys().first());
    }
    // Just to be sure
    if (embedded->modes().isEmpty()) {
        return config;
    }

    if (action == DisplaySwitchAction::Clone) {
        QString pName = getCurrentPrimaryScreenName();
        //embedded->setPrimary(true);
        cloneScreens(connectedOutputs);
        syncPrimaryScreenData(pName);
        return config;
    }


    connectedOutputs.remove(embedded->id());
    external = connectedOutputs.value(connectedOutputs.keys().first());

    // Just to be sure
    if (external->modes().isEmpty()) {
        return config;
    }

    Q_ASSERT(embedded->currentMode());
    Q_ASSERT(external->currentMode());

    switch (action) {
    case TurnOffExternal: {
        embedded->setPos(QPoint(0, 0));
        embedded->setEnabled(true);
        embedded->setPrimary(true);
        syncPrimaryScreenData(embedded->name());
        qDebug()<<"embedded :" <<embedded->name();


        external->setEnabled(false);
        external->setPrimary(false);

        return config;
    }

    case ExtendToRight: {
        QString pName = getCurrentPrimaryScreenName();

        if (QString::compare(pName, embedded->name()) == 0){

            embedded->setPos(QPoint(0, 0));
            embedded->setEnabled(true);
            embedded->setPrimary(true);

            Q_ASSERT(embedded->currentMode()); // we must have a mode now
            const QSize size = embedded->geometry().size();
            external->setPos(QPoint(size.width(), 0));
            external->setEnabled(true);
            external->setPrimary(false);

            } else {
                external->setPos(QPoint(0, 0));
                external->setEnabled(true);
                external->setPrimary(true);

                Q_ASSERT(external->currentMode());
                const QSize size2 = external->geometry().size();
                embedded->setPos(QPoint(size2.width(), 0));
                embedded->setEnabled(true);
                embedded->setPrimary(false);
            }

        syncPrimaryScreenData(pName);


        return config;
    }

    case TurnOffEmbedded: {
        embedded->setEnabled(false);
        embedded->setPrimary(false);
        external->setPos(QPoint(0, 0));
        external->setEnabled(true);
        external->setPrimary(true);
        syncPrimaryScreenData(external->name());
        return config;
    }

    case None: // just return config
    case Clone: // handled above
        break;
    }

    return config;

}
