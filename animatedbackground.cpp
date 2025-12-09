#include "animatedbackground.h"
#include <QPainter>
#include <QGraphicsBlurEffect>
#include <QLinearGradient>


// --- AnimatedShape class remains mostly the same ---
AnimatedShape::AnimatedShape(QWidget *parent, QColor startColor)
    : QWidget(parent), m_color(startColor)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);

    // Floating animation
    auto animation = new QPropertyAnimation(this, "offset");
    animation->setDuration(6000 + (rand() % 3000));
    animation->setStartValue(-10);
    animation->setEndValue(10);
    animation->setLoopCount(-1);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();

    // Blur effect
    auto blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(50);
    setGraphicsEffect(blur);
}

void AnimatedShape::setOffset(int value) {
    m_offset = value;
    move(x(), y() + m_offset);
    update();
}

void AnimatedShape::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setBrush(m_color);
    p.setPen(Qt::NoPen);
    p.drawEllipse(rect());
}

// --- AnimatedBackground with radial gradient ---
AnimatedBackground::AnimatedBackground(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);

    // Add your floating shapes
    shapes << new AnimatedShape(this, QColor(111, 66, 193, 40)); // violet
    shapes << new AnimatedShape(this, QColor(255, 80, 120, 40)); // rose
    shapes << new AnimatedShape(this, QColor(120, 180, 255, 40)); // indigo
    shapes << new AnimatedShape(this, QColor(255, 200, 100, 40)); // amber
    shapes << new AnimatedShape(this, QColor(80, 255, 255, 40));  // cyan
}

void AnimatedBackground::resizeEvent(QResizeEvent *) {
    int w = width();
    int h = height();

    if (shapes.size() >= 5) {
        shapes[0]->setGeometry(w * 0.05, h * 0.20, 220, 80);
        shapes[1]->setGeometry(w * 0.75, h * 0.65, 200, 70);
        shapes[2]->setGeometry(w * 0.15, h * 0.80, 160, 60);
        shapes[3]->setGeometry(w * 0.70, h * 0.10, 140, 50);
        shapes[4]->setGeometry(w * 0.30, h * 0.05, 120, 40);
    }
}

// Draw radial gradient like React version
void AnimatedBackground::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    QRadialGradient gradient(width() * 0.5, height() * 0.1, width() * 1.25, width() * 0.5, height() * 0.1);
    gradient.setColorAt(0.0, QColor("#ffffff"));       // center white
    gradient.setColorAt(0.4, QColor("#ffffff"));       // soft inner
    gradient.setColorAt(1.0, QColor(99, 102, 241));   // #6366f1 (indigo)
    p.fillRect(rect(), gradient);
}

