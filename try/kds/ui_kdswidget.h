/********************************************************************************
** Form generated from reading UI file 'kdswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KDSWIDGET_H
#define UI_KDSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KDSWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *titleFrame;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *outputPrimaryTip;
    QLabel *outputName;
    QLabel *outputDisplayName;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *btnsVerLayout;
    QFrame *splitFrame;
    QFrame *bottomFrame;

    void setupUi(QWidget *KDSWidget)
    {
        if (KDSWidget->objectName().isEmpty())
            KDSWidget->setObjectName(QString::fromUtf8("KDSWidget"));
        KDSWidget->resize(535, 512);
        KDSWidget->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout_2 = new QVBoxLayout(KDSWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        titleFrame = new QFrame(KDSWidget);
        titleFrame->setObjectName(QString::fromUtf8("titleFrame"));
        titleFrame->setMinimumSize(QSize(0, 98));
        titleFrame->setMaximumSize(QSize(16777215, 98));
        titleFrame->setFrameShape(QFrame::StyledPanel);
        titleFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(titleFrame);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        titleLabel = new QLabel(titleFrame);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(titleLabel, 0, Qt::AlignHCenter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        outputPrimaryTip = new QLabel(titleFrame);
        outputPrimaryTip->setObjectName(QString::fromUtf8("outputPrimaryTip"));
        sizePolicy.setHeightForWidth(outputPrimaryTip->sizePolicy().hasHeightForWidth());
        outputPrimaryTip->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(outputPrimaryTip);

        outputName = new QLabel(titleFrame);
        outputName->setObjectName(QString::fromUtf8("outputName"));
        sizePolicy.setHeightForWidth(outputName->sizePolicy().hasHeightForWidth());
        outputName->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(outputName);

        outputDisplayName = new QLabel(titleFrame);
        outputDisplayName->setObjectName(QString::fromUtf8("outputDisplayName"));
        sizePolicy.setHeightForWidth(outputDisplayName->sizePolicy().hasHeightForWidth());
        outputDisplayName->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(outputDisplayName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        verticalLayout_2->addWidget(titleFrame);

        btnsVerLayout = new QVBoxLayout();
        btnsVerLayout->setSpacing(0);
        btnsVerLayout->setObjectName(QString::fromUtf8("btnsVerLayout"));

        verticalLayout_2->addLayout(btnsVerLayout);

        splitFrame = new QFrame(KDSWidget);
        splitFrame->setObjectName(QString::fromUtf8("splitFrame"));
        splitFrame->setMinimumSize(QSize(0, 1));
        splitFrame->setMaximumSize(QSize(16777215, 1));
        splitFrame->setFrameShape(QFrame::StyledPanel);
        splitFrame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(splitFrame);

        bottomFrame = new QFrame(KDSWidget);
        bottomFrame->setObjectName(QString::fromUtf8("bottomFrame"));
        bottomFrame->setMinimumSize(QSize(0, 30));
        bottomFrame->setFrameShape(QFrame::StyledPanel);
        bottomFrame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(bottomFrame);


        retranslateUi(KDSWidget);

        QMetaObject::connectSlotsByName(KDSWidget);
    } // setupUi

    void retranslateUi(QWidget *KDSWidget)
    {
        titleLabel->setText(QApplication::translate("KDSWidget", "System Screen Projection", nullptr));
        outputPrimaryTip->setText(QApplication::translate("KDSWidget", "FirstOutput:", nullptr));
        outputName->setText(QString());
        outputDisplayName->setText(QString());
        Q_UNUSED(KDSWidget);
    } // retranslateUi

};

namespace Ui {
    class KDSWidget: public Ui_KDSWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KDSWIDGET_H
