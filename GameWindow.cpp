// Этот файл задаёт тело конструктора класса GameWindow и тело метода этого класса void paintEvent() после чего рисует игровое окно.

#include "GameWindow.h"

// Тело конструктора класса GameWindow.
// GameWindow:: — Обозначает, что это метод (конструктор) класса GameWindow.
// GameWindow(QWidget *parent) — Конструктор класса, который принимает указатель на родительский виджет.
// : QWidget(parent) — Список инициализации конструктора, который вызывает конструктор базового класса QWidget с аргументом parent.
// setFixedSize — Метод QWidget, устанавливающий фиксированный размер для виджета.
// (400, 400) — Устанавливает ширину и высоту виджета в пикселях.
GameWindow::GameWindow(QWidget* parent) : QWidget(parent)
{
    setFixedSize(400, 400); // Устанавливаем фиксированный размер окна 400x400.
    snake.initialize(); // Инициализируем змейку.
    spawnFruit(snake); // Создаём первый Фрукт на старте игры.
    
    // connect:
    // Это функция Qt, которая используется для подключения сигналов и слотов.
    // Сигналы и слоты — это механизм, который позволяет объектам взаимодействовать друг с другом в ответ на определенные события.
    // timer:
    // Это объект, сигнал которого мы хотим подключить. В данном случае это указатель на объект типа QTimer.
    // &QTimer::timeout:
    // Это адрес сигнала timeout класса QTimer.
    // Сигнал timeout испускается каждый раз, когда таймер срабатывает, то есть по истечении заданного интервала времени
    // (например, каждые 100 миллисекунд).
    // this:
    // Указатель на текущий объект, который содержит слот, к которому мы подключаем сигнал. В данном случае это объект класса GameWindow.
    // &GameWindow::updateGame:
    // Это адрес слота updateGame в классе GameWindow.
    // Слот updateGame — это метод, который будет вызван каждый раз, когда сигнал timeout будет испущен объектом timer.
    connect(timer, &QTimer::timeout, this, &GameWindow::updateGame);
    timer->start(100); // Запускаем таймер с интервалом 100 миллисекунд.
    connect(directionChangeTimer, &QTimer::timeout, this, &GameWindow::resetDirectionChangeFlag);
    connect(pauseChangeTimer, &QTimer::timeout, this, &GameWindow::resetPauseChangeFlag);
    connect(fruitTimer, &QTimer::timeout, this, &GameWindow::spawnFruitSlot);
    connect(gameTimeTimer, &QTimer::timeout, this, &GameWindow::updateGameTime);
}

// Тело метода void paintEvent() класса GameWindow.
// GameWindow::— Обозначает, что это метод(переопределение) класса GameWindow.
// paintEvent(QPaintEvent *event) — Метод, принимающий указатель на объект QPaintEvent.
// Этот метод вызывается всякий раз, когда нужно перерисовать виджет.
void GameWindow::paintEvent(QPaintEvent* event)
{
    // QPainter — Класс, используемый для рисования графики.
    // painter(this) — Создаем объект QPainter, который будет рисовать на текущем виджете(this).
    QPainter painter(this); // Создаем объект для рисования.

    // painter.setBrush — Метод QPainter, устанавливающий кисть, которая будет использоваться для заливки форм.
    // Qt::black — Предопределенный цвет в Qt, чёрный цвет.
    painter.setBrush(Qt::black); // Устанавливаем черный цвет кисти.

    // painter.drawRect — Метод QPainter, рисующий прямоугольник.
    // (0, 0, width(), height()) — Координаты верхнего левого угла(0, 0) и ширина и высота прямоугольника, равные ширине и высоте виджета.
    painter.drawRect(0, 0, width(), height()); // Рисуем прямоугольник, заполняющий все окно.
    snake.draw(painter); // Отрисовываем Змейку.
    fruit.draw(painter); // Отрисовываем Фрукт.

    // Рисуем счетчик съеденных Фруктов.
    QColor orange(255, 165, 0); // Создаем оранжевый цвет.
    painter.setPen(orange); // Устанавливаем оранжевый цвет для пера.
    painter.setFont(QFont("Arial", 14));
    painter.drawText(10, 50, QString("Fruits: %1").arg(fruitCount));

    // Рисуем счетчик времени.
    int minutes = gameTimeSeconds / 60;
    int seconds = gameTimeSeconds % 60;
    QString timeText = QString("Time: %1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    painter.drawText(10, 30, timeText);

    if (paused)
    {
        painter.setPen(orange); // Устанавливаем оранжевый цвет для пера.
        painter.setFont(QFont("Arial", 24, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "PAUSE");
    }
}

// Тело метода keyPressEvent(QKeyEvent* event) для управления Змейкой с помощью нажатия клавиш.
void GameWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) { return; } // Пропускаем повторное нажатие клавиши, если оно является автоматическим.
    else if (event->key() == Qt::Key_Space)
    {
        if (!spacePressed) 
        {
            spacePressed = true;
            if (!pauseChangedRecently)
            {
                pauseChangedRecently = true;
                pauseChangeTimer->start(100);
                paused = !paused;
                if (paused)
                {
                    timer->stop();
                    gameTimeTimerRemaining = gameTimeTimer->remainingTime();
                    gameTimeTimer->stop();
                    fruitTimeRemaining = fruitTimer->remainingTime();
                    fruitTimer->stop();
                }
                else
                {
                    timer->start();
                    gameTimeTimer->start(gameTimeTimerRemaining);
                    fruitTimer->start(fruitTimeRemaining);
                }
                update();
            }
        }
    }
    else
    {
        // Получаем код нажатой клавиши.
        int key = event->key();

        // Обрабатываем нажатие клавиш для управления Змейкой.
        if (!directionChangedRecently)
        {
            directionChangedRecently = true;
            directionChangeTimer->start(100);
            switch (key)
            {
            case Qt::Key_Up:
                if (snake.direction == Snake::Direction::Left || snake.direction == Snake::Direction::Right) { snake.setDirection(Snake::Direction::Up); }
                break;
            case Qt::Key_Down:
                if (snake.direction == Snake::Direction::Left || snake.direction == Snake::Direction::Right) { snake.setDirection(Snake::Direction::Down); }
                break;
            case Qt::Key_Left:
                if (snake.direction == Snake::Direction::Up || snake.direction == Snake::Direction::Down) { snake.setDirection(Snake::Direction::Left); }
                break;
            case Qt::Key_Right:
                if (snake.direction == Snake::Direction::Up || snake.direction == Snake::Direction::Down) { snake.setDirection(Snake::Direction::Right); }
                break;
            default:
                break;
            }
        }
    }
}

// Тело метода updateGame().
void GameWindow::updateGame()
{
    if (!paused)
    {
        snake.move(); // Перемещаем Змейку.
        int newX = snake.getHeadX();
        int newY = snake.getHeadY();

        // Проверяем на столкновение с телом Змейки.
        for (const auto& bodySegment : snake.getBodySegments())
        {
            if (bodySegment.x == newX && bodySegment.y == newY)
            {
                // Отправляем сигнал об окончании игры.
                endGame();
                return;
            }
        }

        // Проверяем, съела ли Змейка Фрукт.
        if (snake.contains(fruit.getX(), fruit.getY()))
        {
            snake.grow(); // Змейка растет.
            ++fruitCount;
            spawnFruit(snake); // Обновляем Фрукт.
        }
        update(); // Перерисовываем окно. Стандартный метод Qt.
    }
}

// Тело метода resetDirectionChangeFlag().
void GameWindow::resetDirectionChangeFlag() { directionChangedRecently = false; }
void GameWindow::resetPauseChangeFlag() { pauseChangedRecently = false; }
bool GameWindow::directionContains(int x, int y) const
{
    // Получение координат головы змейки.
    int headX = snake.getHeadX();
    int headY = snake.getHeadY();
    if ((snake.direction == Snake::Direction::Left || snake.direction == Snake::Direction::Right) && y == headY) { return true; }
    else if ((snake.direction == Snake::Direction::Up || snake.direction == Snake::Direction::Down) && x == headX) { return true; }
    else { return false; }
}

// Тело метода spawnFruit(int width, int height, const Snake& snake) для генерации случайных координат Фрукта.
void GameWindow::spawnFruit(const Snake& snake)
{
    // Генерируем новые координаты, пока они не будут вне тела Змейки и вне траектории движения Змейки (чтобы не появляться у неё на пути).
    do
    {
        fruit.x = getRandomNumber(0, 19);
        fruit.y = getRandomNumber(0, 19);
    }
    while (snake.contains(fruit.x, fruit.y) || directionContains(fruit.x, fruit.y));
    fruitTimer->start(5000); // Перезапускаем таймер жизни Фрукта сразу после "спавна" очередного Фрукта (для случаев, когда Змейка его съест).
}
void GameWindow::spawnFruitSlot() { spawnFruit(snake); }
void GameWindow::updateGameTime()
{
    ++gameTimeSeconds; // Увеличиваем время игры на одну секунду.
    update(); // Перерисовываем окно для обновления времени.
    gameTimeTimer->start(1000); // Обновляем таймер.
}

// Тело функции для генерации случайных целых чисел в заданном диапазоне.
int getRandomNumber(int min, int max)
{
    std::random_device rd; // Источник случайности.
    std::mt19937 gen(rd()); // Генератор случайных чисел с инициализацией от random_device.
    std::uniform_int_distribution<> distrib(min, max); // Диапазон распределения.
    return distrib(gen); // Генерация случайного числа.
}
void GameWindow::showGameWindow() { this->show(); }
void GameWindow::gameTimeTimerStart() { gameTimeTimer->start(1000); }
void GameWindow::fruitTimerStart() { fruitTimer->start(5000); }
void GameWindow::keyReleaseEvent(QKeyEvent* event) { if (event->key() == Qt::Key_Space) { spacePressed = false; } }

void GameWindow::endGame()
{
    emit gameEnd(fruitCount, gameTimeSeconds);
    writeAchievementLogic();
    close(); // Закрываем текущее окно игры.
    snake.initialize(); // Инициализируем Змейку заново.
    spawnFruit(snake); // Создаём новый Фрукт.
    gameTimeTimer->stop();
    fruitTimer->stop();
    gameTimeSeconds = 0;
    fruitCount = 0;
    directionChangedRecently = false;
    paused = false;
    fruitTimeRemaining = 0;
    gameTimeTimerRemaining = 0;
    pauseChangedRecently = false;
    spacePressed = false;
}

// Окно сворачивается, но таймеры продолжают работать.
void GameWindow::hideEvent(QHideEvent* event)
{
    if (!paused)
    {
        timer->start(100);
        gameTimeTimerRemaining = gameTimeTimer->remainingTime();
        gameTimeTimer->start(gameTimeTimerRemaining);
        fruitTimeRemaining = fruitTimer->remainingTime();
        fruitTimer->start(fruitTimeRemaining);
    }
    QWidget::hideEvent(event);
}

// Окно разворачивается, таймеры продолжают работать.
void GameWindow::showEvent(QShowEvent* event)
{
    if (!paused)
    {
        timer->start(100);
        gameTimeTimerRemaining = gameTimeTimer->remainingTime();
        gameTimeTimer->start(gameTimeTimerRemaining);
        fruitTimeRemaining = fruitTimer->remainingTime();
        fruitTimer->start(fruitTimeRemaining);
    }
    QWidget::showEvent(event);
}

void GameWindow::playerNameEntered(const QString& playerName) { currentPlayerName = playerName; }

void GameWindow::writeAchievementLogic()
{
    PlayerAchievement newPlayerAchievement(currentPlayerName, fruitCount, gameTimeSeconds);
    std::vector<PlayerAchievement> currentAchievements = PlayerAchievement::readAchievements();
    if (currentAchievements.empty())
    {
        currentAchievements.push_back(newPlayerAchievement);
        PlayerAchievement::writeAchievements(currentAchievements);
        return;
    }
    else
    {
        auto it = currentAchievements.begin();
        for (; it != currentAchievements.end(); ++it)
        {
            if (newPlayerAchievement > *it)
            {
                currentAchievements.insert(it, newPlayerAchievement);
                if (currentAchievements.size() > 3) currentAchievements.pop_back();
                PlayerAchievement::writeAchievements(currentAchievements);
                return;
            }
            else if (newPlayerAchievement == *it)
            {
                // Если новое достижение равно текущему, вставляем его ПОСЛЕ текущего, а остальные сдвигаем вправо.
                ++it;
                currentAchievements.insert(it, newPlayerAchievement);
                if (currentAchievements.size() > 3) currentAchievements.pop_back();
                PlayerAchievement::writeAchievements(currentAchievements);
                return;
            }
        }

        // Если новое достижение меньше всех текущих, добавляем его в конец.
        if (currentAchievements.size() < 3)
        {
            currentAchievements.push_back(newPlayerAchievement);
            PlayerAchievement::writeAchievements(currentAchievements);
        }
    }
}