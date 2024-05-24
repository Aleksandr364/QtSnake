#include "EndGameWindow.h"

EndGameWindow::EndGameWindow(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Game results"); // Установка заголовка окна.
    setFixedSize(250, 200);

    // Создаем основной горизонтальный макет.
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // Добавляем пустое пространство в 5 пикселей слева.
    // Делаем это для выравнивания по центру надписей и кнопок.
    mainLayout->addSpacing(5);
    QVBoxLayout* layout = new QVBoxLayout(); // Создаем вертикальный макет для виджетов.
    titleLabel = new QLabel("YOUR RESULT", this);
    layout->addWidget(titleLabel);
    fruitCountLabel = new QLabel(this);
    layout->addWidget(fruitCountLabel);
    gameTimeLabel = new QLabel(this);
    layout->addWidget(gameTimeLabel);
    restartButton = new QPushButton("Restart", this);
    restartButton->setFixedSize(130, 30);
    layout->addWidget(restartButton);
    viewResultsButton = new QPushButton("Results", this);
    viewResultsButton->setFixedSize(130, 30);
    layout->addWidget(viewResultsButton);
    exitButton = new QPushButton("Exit", this);
    exitButton->setFixedSize(130, 30);
    layout->addWidget(exitButton);
    mainLayout->addLayout(layout); // Добавляем вертикальный макет в горизонтальный макет.
    
    // Подключаем слоты для кнопок.
    connect(restartButton, &QPushButton::clicked, this, &EndGameWindow::RestartClicked);
    connect(viewResultsButton, &QPushButton::clicked, this, &EndGameWindow::ResultsClicked);
    connect(exitButton, &QPushButton::clicked, this, &EndGameWindow::ExitClicked);
}

void EndGameWindow::showEndGameWindow(int fruitCount, int gameTimeSeconds)
{
    fruitCountLabel->setText("Fruits: " + QString::number(fruitCount));
    gameTimeLabel->setText("Time: " + QString::number(gameTimeSeconds) + " seconds");
    show();
}

void EndGameWindow::ExitClicked() { emit onExitClicked(); }
void EndGameWindow::ResultsClicked() { emit onResultsClicked(); }
void EndGameWindow::RestartClicked()
{
    emit onRestartClicked();
    close();
}