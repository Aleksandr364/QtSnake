// Файл задаёт тело конструктора класса Snake и его методов initialize(), move(), draw(QPainter& painter), setDirection(Direction newDirection).

#include "Snake.h"

// Объявление конструктора класса Snake, который принимает один аргумент parent типа QObject* (указатель на объект-родитель).
// Конструктор используется для создания объекта Snake.
// : QObject(parent): Список инициализации конструктора. Он вызывает конструктор базового класса QObject и передает ему указатель parent.
Snake::Snake(QObject* parent) : QObject(parent) {}

// Метод инициализации тела Змейки.
void Snake::initialize()
{
    segments.clear(); // Очищаем вектор сегментов, чтобы начать с чистого листа.
    direction = Direction::Up;
    directionChangedRecently = false;

    // Добавляем несколько сегментов змейки для начальной отрисовки.
    segments.push_back({ 10, 10 }); // Голова Змейки.
    segments.push_back({ 10, 11 }); // Тело Змейки #1.
    segments.push_back({ 10, 12 }); // Тело Змейки #2.
}

// Метод задания направления движения Змейки.
void Snake::setDirection(Direction newDirection) { direction = newDirection; }

// Метод, отвечающий за обработку движения Змейки.
void Snake::move()
{
    // Перемещаем каждый сегмент кроме головы на место следующего сегмента.
    // Перечисление начинается с конца Змейки. Движение от последнего сегмента к голове.
    for (size_t i = segments.size() - 1; i > 0; --i)
    {
        segments[i].x = segments[i - 1].x;
        segments[i].y = segments[i - 1].y;
    }

    // Перемещаем голову в соответствии с текущим направлением.
    switch (direction)
    {
    case Direction::Up:
        segments[0].y--;
        break;
    case Direction::Down:
        segments[0].y++;
        break;
    case Direction::Left:
        segments[0].x--;
        break;
    case Direction::Right:
        segments[0].x++;
        break;
    }

    // Проверка границ игрового поля и перемещение головы Змейки на противоположную сторону поля, если она вышла за границу поля.
    int width = 400 / 20;  // Ширина игрового поля в сегментах.
    int height = 400 / 20; // Высота игрового поля в сегментах.
    if (segments[0].x < 0) { segments[0].x = width - 1; }
    else if (segments[0].x >= width) { segments[0].x = 0; }
    if (segments[0].y < 0) { segments[0].y = height - 1; }
    else if (segments[0].y >= height) { segments[0].y = 0; }
}

// Объявление метода draw(), который принимает ссылку на объект QPainter.
void Snake::draw(QPainter& painter)
{
    painter.setPen(Qt::NoPen); // Устанавливаем отсутствие пера, чтобы избежать границ вокруг сегментов.
    
    // Рисуем голову Змейки другим цветом.
    painter.setBrush(Qt::red); // Устанавливаем красный цвет для головы Змейки.

    // Координаты сегмента умножаются на 20, чтобы получить пиксельные координаты (каждая ячейка имеет размер 20x20 пикселей).
    painter.drawRect(segments[0].x * 20, segments[0].y * 20, 20, 20); // Рисуем голову Змейки.
    painter.setBrush(Qt::white); // Устанавливаем цвет кисти для тела Змейки.

    // Рисуем сегменты Змейки.
    // Цикл for, который проходит по всем сегментам змейки в векторе segments.
    // const auto &segment: Использует auto для автоматического определения типа элемента (в данном случае SnakeSegment)
    // и создает константную ссылку на элемент.
    for (size_t i = 1; i < segments.size(); ++i)
    {
        // Рисует каждый сегмент змейки как квадрат размером 20x20 пикселей.
        // Координаты сегмента умножаются на 20, чтобы получить пиксельные координаты (каждая ячейка имеет размер 20x20 пикселей).
        painter.drawRect(segments[i].x * 20, segments[i].y * 20, 20, 20);
    }
}

// Тело метода contains(int x, int y) const.
bool Snake::contains(int x, int y) const
{
    for (const auto& segment : segments) { if (segment.x == x && segment.y == y) { return true; } }
    return false;
}

// Добавляем новый сегмент в конец Змейки.
void Snake::grow() { segments.push_back(segments.back()); }
int Snake::getHeadX() const { return segments.front().x; }
int Snake::getHeadY() const { return segments.front().y; }
std::vector<Snake::SnakeSegment> Snake::getBodySegments() const
{
    std::vector<SnakeSegment> bodySegments(segments.begin() + 1, segments.end());
    return bodySegments;
}