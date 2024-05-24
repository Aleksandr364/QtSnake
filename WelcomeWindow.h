#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H
#include <QApplication>
#include <QWidget>
#include <QPushButton> // Заголовочный файл для кнопок.
#include <QVBoxLayout> // Заголовочный файл для размещения кнопок.
#include <QLineEdit> // Заголовочный файл для размещения текстового поля в окне.
#include <QLabel> // Заголовочный файл для добавления метки, отображающей текст.
#include <QKeyEvent>

class WelcomeWindow : public QWidget
{
    Q_OBJECT

signals:

    void startGame(const QString& playerName); // const QString& playerName - для передачи имени игрока;

public slots:

    void onStartClicked();
    void onExitClicked();
    void onNameChanged(const QString& text); // Новый слот для обработки изменений в поле имени.

private:

    QLabel* nameLabel; // Метка для отображения текста.
    QLineEdit* playerNameLine; // Поле для ввода имени игрока.
    QPushButton* startButton;
    QPushButton* exitButton;
    QString playerName; // Контейнер для имени игрока.

    // Метод для управления Окном с помощью нажатия клавиш.
    void keyPressEvent(QKeyEvent* event) override; // Переопределение обработчика событий нажатия клавиши.

public:

    explicit WelcomeWindow(QWidget* parent = nullptr);
};

#endif