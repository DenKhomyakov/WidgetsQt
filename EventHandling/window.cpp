#include "window.h"

#include <QVBoxLayout>

Window::Window()
{
codec = QTextCodec::codecForName("utf-8");

this->setWindowTitle(codec->toUnicode("Обработка событий"));

area = new Area( this );

btn = new QPushButton(codec->toUnicode("Завершить"), this );

QVBoxLayout *layout = new QVBoxLayout(this);
layout->addWidget(area);
layout->addWidget(btn);

connect(btn, &QPushButton::clicked, this, &Window::close);
};
