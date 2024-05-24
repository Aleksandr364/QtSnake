#include "ResultsWindow.h"

ResultsWindow::ResultsWindow(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Results");
    setFixedSize(400, 200);
}

void ResultsWindow::showResultWindow()
{   
    this->update();
    this->show();
}

void ResultsWindow::closeResultWindow() { this->close(); }
void ResultsWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this); // Создаем объект для рисования.

    // painter.setBrush — Метод QPainter, устанавливающий кисть, которая будет использоваться для заливки форм.
    // Qt::black — Предопределенный цвет в Qt, чёрный цвет.
    painter.setBrush(Qt::black); // Устанавливаем черный цвет кисти.

    // painter.drawRect — Метод QPainter, рисующий прямоугольник.
    // (0, 0, width(), height()) — Координаты верхнего левого угла(0, 0) и ширина и высота прямоугольника, равные ширине и высоте виджета.
    painter.drawRect(0, 0, width(), height());
    QColor orange(255, 165, 0); // Создаем оранжевый цвет.
    painter.setPen(orange); // Устанавливаем оранжевый цвет для пера.
    painter.setFont(QFont("Arial", 12));
    std::vector<PlayerAchievement> achievements = PlayerAchievement::readAchievements();
    int yOffset = 30;
    for (const auto& achievement : achievements)
    {
        QString achievementText = QString("  Player: %1  \nFruits: %2  \nTime: %3 seconds").arg(achievement.getName()).arg(achievement.getFruits()).arg(achievement.getTime());
        painter.drawText(10, yOffset, achievementText);
        yOffset += 50;
    }
}