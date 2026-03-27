#include "../include/ClickBox.hpp"
#include <QPainter>
#include <QTimer>
#include <QApplication>
#include <QMouseEvent>
#include <QEnterEvent>
#include <QEvent>

ClickBox::ClickBox(QWidget *const parent) : QWidget{parent} {
    setMinimumWidth(100);
    setMinimumHeight(60);

    timer = new QTimer{this};
    timer->setInterval(10'000);
    connect(timer, &QTimer::timeout, this, &ClickBox::increase_multiplier);
    timer->start();
}

void ClickBox::mousePressEvent(QMouseEvent *const e) {
    pressed = true;
    update();

    e->accept();
}

void ClickBox::mouseReleaseEvent(QMouseEvent *const e) {
    if (hover) {
        if (double_clicked) {
            counter = 0;
            double_clicked = false;
        } else counter += multiplier;
        emit clicked(counter);
    }

    pressed = false;
    update();

    e->accept();
}

void ClickBox::mouseDoubleClickEvent(QMouseEvent *const e) {
    pressed = double_clicked = true;
    update();

    e->accept();
}

void ClickBox::enterEvent(QEnterEvent *const e) {
    hover = true;
    update();

    e->accept();
}

void ClickBox::leaveEvent(QEvent *const e) {
    hover = false;
    update();

    e->accept();
}

void ClickBox::paintEvent(QPaintEvent *const e) {
    QPainter painter{this};

    if (pressed) painter.setBrush(Qt::darkBlue);
    else if (hover) painter.setBrush(Qt::blue);
    else painter.setBrush(Qt::white);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    painter.setPen(Qt::red);
    painter.setFont(QFont{"Calibri", 32, 1000, false});
    painter.drawText(rect(), Qt::AlignCenter, QString::number(counter));

    e->accept();
}

[[nodiscard]] QSize ClickBox::sizeHint() const {
    return QSize{150, 80};
}

[[nodiscard]] int ClickBox::value() const {
    return counter;
}

void ClickBox::reset() {
    counter = 0;
    emit clicked(counter);
    update();
}

void ClickBox::increase_multiplier() {
    ++multiplier;
    qDebug("multiplier has been increased!");
}
