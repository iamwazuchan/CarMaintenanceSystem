#ifndef ANIMATEDBACKGROUND_H
#define ANIMATEDBACKGROUND_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QTimer>

class AnimatedShape : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset)

public:
    AnimatedShape(QWidget *parent = nullptr, QColor startColor = QColor(255,255,255,30));

    int offset() const { return m_offset; }
    void setOffset(int value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_offset = 0;
    QColor m_color;
};

class AnimatedBackground : public QWidget {
    Q_OBJECT
public:
    explicit AnimatedBackground(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QList<AnimatedShape*> shapes;
};

#endif // ANIMATEDBACKGROUND_H
