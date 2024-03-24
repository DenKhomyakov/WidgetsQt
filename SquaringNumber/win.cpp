#include "win.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <math.h>

Win::Win(QWidget *parent):QWidget(parent)
{
    codec = QTextCodec::codecForName("utf-8");

    setWindowTitle(codec->toUnicode("Возведение в квадрат"));

    frame = new QFrame(this);
    frame->setFrameShadow(QFrame::Raised);
    frame->setFrameShape(QFrame::Panel);

    inputLabel = new QLabel(codec->toUnicode("Введите число:"), this);
    inputEdit = new QLineEdit("", this);

    StrValidator *v=new StrValidator(inputEdit);
    inputEdit->setValidator(v);

    outputLabel = new QLabel(codec->toUnicode("Результат:"), this);
    outputEdit = new QLineEdit("", this);

    nextButton = new QPushButton(codec->toUnicode("Следующее"), this);
    exitButton = new QPushButton(codec->toUnicode("Выход"), this);

    QVBoxLayout *vLayout1 = new QVBoxLayout(frame);
    vLayout1->addWidget(inputLabel);
    vLayout1->addWidget(inputEdit);
    vLayout1->addWidget(outputLabel);
    vLayout1->addWidget(outputEdit);
    vLayout1->addStretch();

    QVBoxLayout *vLayout2 = new QVBoxLayout();
    vLayout2->addWidget(nextButton);
    vLayout2->addWidget(exitButton);
    vLayout2->addStretch();

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(frame);
    hLayout->addLayout(vLayout2);

    begin();

    connect(exitButton, &QPushButton::clicked, this, &Win::close);
    connect(nextButton, &QPushButton::clicked, this, &Win::begin);
    connect(inputEdit, &QLineEdit::returnPressed, this, &Win::calc);

}

void Win::begin()
{
    inputEdit->clear();

    nextButton->setEnabled(false);
    nextButton->setDefault(false);

    inputEdit->setEnabled(true);
    outputLabel->setVisible(false);
    outputEdit->setVisible(false);
    outputEdit->setEnabled(false);

    inputEdit->setFocus();
}

void Win::calc()
{
    bool Ok=true;
    float r;
    float a;

    QString str=inputEdit->text();
    a=str.toDouble(&Ok);

    bool bufferOverloaded = false;

    if (abs(a) >= sqrt((3.4 * pow(10,38))))
    {
        bufferOverloaded = true;
    }

    if (Ok && !bufferOverloaded)
    {
        r=a*a;

        str.setNum(r);
        outputEdit->setText(str);

        inputEdit->setEnabled(false);

        outputLabel->setVisible(true);
        outputEdit->setVisible(true);

        nextButton->setDefault(true);
        nextButton->setEnabled(true);
        nextButton->setFocus();
    }
    else
        if (!str.isEmpty() && !bufferOverloaded)
        {
            QMessageBox msgBox(QMessageBox::Information,
                           codec->toUnicode("Возведение в квадрат."),
                           codec->toUnicode("Введено неверное значение."),
                           QMessageBox::Ok);
            msgBox.exec();

            inputEdit->clear();
        }
        else
        {
            {
                QMessageBox msgBox(QMessageBox::Information,
                                   codec->toUnicode("Возведение в квадрат."),
                                   codec->toUnicode("Слишком большое значение!"),
                                   QMessageBox::Ok);
                msgBox.exec();

                inputEdit->clear();
            }
        }
}
