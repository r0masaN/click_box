#ifndef CLICKBOX_HPP
#define CLICKBOX_HPP

#include <QWidget>

class ClickBox final : public QWidget {
    Q_OBJECT

    bool hover{false}, pressed{false}, double_clicked{false};
    int counter{0}, multiplier{1};
    QTimer *timer;

public:
    explicit ClickBox(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void mouseDoubleClickEvent(QMouseEvent *e);

    void enterEvent(QEnterEvent *e);

    void leaveEvent(QEvent *e);

    void paintEvent(QPaintEvent *e);

    [[nodiscard]] QSize sizeHint() const;

    [[nodiscard]] int value() const;

signals:
    void clicked(int new_value);

public slots:
    void reset();

private slots:
    void increase_multiplier();
};

#endif
