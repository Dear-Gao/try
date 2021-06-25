/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *titleFrame;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *outputPrimaryTip;
    QLabel *outputName;
    QLabel *outputDisplayName;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *btnsVerLayout;
    QFrame *splitFrame;
    QFrame *bottomFrame;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(400, 460);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        titleFrame = new QFrame(Widget);
        titleFrame->setObjectName(QString::fromUtf8("titleFrame"));
        titleFrame->setMinimumSize(QSize(0, 98));
        titleFrame->setMaximumSize(QSize(16777215, 98));
        titleFrame->setFrameShape(QFrame::StyledPanel);
        titleFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(titleFrame);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        titleLabel = new QLabel(titleFrame);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

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

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addWidget(titleFrame);

        btnsVerLayout = new QVBoxLayout();
        btnsVerLayout->setSpacing(0);
        btnsVerLayout->setObjectName(QString::fromUtf8("btnsVerLayout"));

        verticalLayout_2->addLayout(btnsVerLayout);

        splitFrame = new QFrame(Widget);
        splitFrame->setObjectName(QString::fromUtf8("splitFrame"));
        splitFrame->setMinimumSize(QSize(0, 1));
        splitFrame->setMaximumSize(QSize(16777215, 1));
        splitFrame->setFrameShape(QFrame::StyledPanel);
        splitFrame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(splitFrame);

        bottomFrame = new QFrame(Widget);
        bottomFrame->setObjectName(QString::fromUtf8("bottomFrame"));
        bottomFrame->setFrameShape(QFrame::StyledPanel);
        bottomFrame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(bottomFrame);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "KDS", nullptr));
        titleLabel->setText(QApplication::translate("Widget", "System Screen Projection", nullptr));
        outputPrimaryTip->setText(QApplication::translate("Widget", "FirstOutput:", nullptr));
        outputName->setText(QString());
        outputDisplayName->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
