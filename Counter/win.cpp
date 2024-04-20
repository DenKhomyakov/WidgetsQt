#include "win.h"

#include <QHBoxLayout>

Win::Win(QWidget *parent):QWidget(parent)
{
    codec = QTextCodec::codecForName("utf-8");

    setWindowTitle("Счётчик");

    label1 = new QLabel("Счёт по 1",this);
    //label2 = new QLabel("Счёт по 5",this);
    label2 = nullptr;

    //edit1 = new Counter("0",this);
    edit1 = nullptr;
    //edit2 = new Counter("0",this);
    edit2 = nullptr;

    calcbutton = new QPushButton("+1" , this);
    //exitbutton = new QPushButton("Выход",this);
    exitbutton = nullptr;

    if(!label1 || !label2 || !edit1 || !edit2 || !calcbutton || !exitbutton)
    {
        std::cerr << "Memory allocation error!";
    }

    QHBoxLayout *layout1 = new QHBoxLayout();
    QHBoxLayout *layout2 = new QHBoxLayout();
    QHBoxLayout *layout3 = new QHBoxLayout();
    QVBoxLayout *layout4 = new QVBoxLayout(this);

    if(layout1 && layout2 && layout3 && layout4)
    {
        layout1->addWidget(label1);
        layout1->addWidget(label2);

        layout2->addWidget(edit1);
        layout2->addWidget(edit2);

        layout3->addWidget(calcbutton);
        layout3->addWidget(exitbutton);

        layout4->addLayout(layout1);
        layout4->addLayout(layout2);
        layout4->addLayout(layout3);

    }
    else
    {
        std::cerr << "Memory allocation error!";
    }

    edit1->setEnabled(false);
    edit2->setEnabled(false);

    connect(exitbutton, &QPushButton::clicked, this, &Win::close);
    connect(calcbutton, &QPushButton::clicked, edit1, &Counter::add_one);
    connect(edit1, &Counter::tick_signal, edit2, &Counter::add_one);
}
