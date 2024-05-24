// Файл задаёт тело конструктора класса Fruit и его методов.

#include "Fruit.h"

Fruit::Fruit(QObject* parent) : QObject(parent) {} 

void Fruit::draw(QPainter& painter)
{
    painter.setPen(Qt::NoPen); // Устанавливаем отсутствие пера, чтобы избежать границ вокруг сегментов.
    painter.setBrush(Qt::green); // Устанавливаем цвет кисти для фрукта.
    painter.drawRect(x * 20, y * 20, 20, 20); // Рисуем фрукт.
}

int Fruit::getX() const { return x; }
int Fruit::getY() const { return y; }