// Заголовочный файл объявляет класс, отвечающий за создание и отрисовку Фрукта.

#ifndef FRUIT_H
#define FRUIT_H
#include <QObject>
#include <QPainter>

class Fruit : public QObject
{
    Q_OBJECT

public:

    int x = 0, y = 0; // Координаты фрукта.
    explicit Fruit(QObject* parent = nullptr);
    void draw(QPainter& painter); // Метод для отрисовки фрукта.
    int getX() const; // Метод для получения координаты X фрукта.
    int getY() const; // Метод для получения координаты Y фрукта.
};

#endif