#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Welcome!");
    setFixedSize(250, 150);

    // Создаем основной горизонтальный макет.
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // Добавляем пустое пространство в 5 пикселей слева.
    // Делаем это для выравнивания по центру надписей и кнопок.
    mainLayout->addSpacing(5);
    QVBoxLayout* layout = new QVBoxLayout(); // Создаем вертикальный макет для виджетов.
    nameLabel = new QLabel("Hello! Enter your name:", this); // Устанавливаем текст метки.
    (*layout).addWidget(nameLabel); // Добавляем метку в вертикальный макет.
    playerNameLine = new QLineEdit(this); // Инициализируем поле для ввода имени игрока.
    playerNameLine->setFixedSize(130, 30);
    playerNameLine->setMaxLength(20); // Ограничиваем количество символов до 20.
    layout->addWidget(playerNameLine); // Добавляем поле для ввода имени в вертикальный макет.
    startButton = new QPushButton("Start", this);
    startButton->setFixedSize(130, 30); // Задаем фиксированный размер кнопки "Старт".
    startButton->setEnabled(false); // Делаем кнопку неактивной сначала.
    layout->addWidget(startButton);
    exitButton = new QPushButton("Exit", this);
    exitButton->setFixedSize(130, 30); // Задаем фиксированный размер кнопки "Выход".
    layout->addWidget(exitButton);
    mainLayout->addLayout(layout); // Добавляем вертикальный макет в горизонтальный макет.
    connect(startButton, &QPushButton::clicked, this, &WelcomeWindow::onStartClicked);
    connect(exitButton, &QPushButton::clicked, this, &WelcomeWindow::onExitClicked);
    connect(playerNameLine, &QLineEdit::textChanged, this, &WelcomeWindow::onNameChanged); // Подключаем слот для обработки изменений в поле имени.
}

void WelcomeWindow::onStartClicked()
{
    playerName = playerNameLine->text(); // Получаем введенное имя игрока.
    emit startGame(playerName); // Посылаем сигнал startGame с вложенным именем игрока.
    close(); // Закрываем приветственное окно.
}

void WelcomeWindow::onExitClicked() { QApplication::quit(); }

// Если текст в поле пустой, делаем кнопку "Start" неактивной, иначе активной.
void WelcomeWindow::onNameChanged(const QString& text) { startButton->setEnabled(!text.isEmpty()); }

void WelcomeWindow::keyPressEvent(QKeyEvent* event)
{
    if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && startButton->isEnabled()) { onStartClicked(); }
    else if (event->key() == Qt::Key_Escape) { onExitClicked(); }
    else { QWidget::keyPressEvent(event); }
}