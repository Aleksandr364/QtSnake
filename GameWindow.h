// Этот заголовочный файл объявляет класс GameWindow, который наследует от QWidget и предназначен для создания пользовательского окна.
// Макрос Q_OBJECT добавляет метаобъектные возможности, а функция paintEvent переопределяется для кастомного рисования в окне.

// #ifndef, #define, #endif
// #ifndef GAMEWINDOW_H — Начинает условный блок, который будет включен, только если GAMEWINDOW_H еще не определен.
// #define GAMEWINDOW_H — Определяет GAMEWINDOW_H, чтобы предотвратить повторное включение этого файла.
// #endif — Закрывает условный блок.
// #pragma once
// #pragma once — Директива препроцессора, которая гарантирует, что файл включается только один раз в пределах одной компиляции.
// Это более краткая и часто более надежная альтернатива условным директивам, так как не требует уникальных имен для макросов.
// #pragma once проще в использовании, так как требует всего одной строки.
// #ifndef, #define, #endif требуют трех строк и уникального имени макроса.
// #pragma once поддерживается большинством современных компиляторов (GCC, Clang, MSVC), но не является частью стандарта C/C++.
// Условные директивы(#ifndef, #define, #endif) являются частью стандарта C / C++ и поддерживаются всеми компиляторами.
// В некоторых случаях #pragma once может приводить к более быстрой компиляции,
// так как компилятор не должен проверять макросы при каждом включении файла.

// #ifndef — директива препроцессора, означающая "если не определено".
// GAMEWINDOW_H — макрос, который используется в качестве условного флага.
// Если этот макрос еще не определен, код между #ifndef и #endif будет включен.
#ifndef GAMEWINDOW_H

// #define — директива препроцессора для определения макроса.
// GAMEWINDOW_H — имя макроса.Эта строка определяет макрос GAMEWINDOW_H,
// чтобы предотвратить многократное включение содержимого этого заголовочного файла.
// Таким образом, если файл будет включен снова, #ifndef GAMEWINDOW_H вернет ложь, и код не будет включен повторно.
#define GAMEWINDOW_H

// QWidget — заголовочный файл, содержащий объявление класса QWidget.
// Этот класс представляет базовый виджет, который используется для создания пользовательских элементов графического интерфейса.
#include <QWidget>
#include <QPainter> // Заголовочный файл, предоставляющий класс QPainter, который используется для рисования на виджетах.
#include "Snake.h"
#include "Fruit.h"
#include <QKeyEvent> // Подключаем класс QKeyEvent для обработки событий клавиатуры.
#include <QTimer> // Таймер для периодического вызова метода, который будет перемещать Змейку и обновлять окно.
#include <random> // Для генерации случайных чисел.
#include <QTime>
#include <QLabel>
#include "PlayerAchievement.h"

class GameWindow : public QWidget // Наследуем от WelcomeWindow для создания игрового окна взамен приветственного.
{
	// Макрос Qt, который добавляет метаобъектные возможности классу, такие как сигналы и слоты.
	// Этот макрос необходим для работы системы сигналов и слотов, а также других возможностей, предоставляемых метаобъектной системой Qt.
	Q_OBJECT

signals:

	void gameEnd(int fruitCount, int gameTimeSeconds);

private slots:

	void updateGame(); // Слот(Qt) для обновления игры.
	void resetDirectionChangeFlag(); // Слот(Qt) для обновления "флага" изменения направления.
	void spawnFruitSlot(); // Слот(Qt) для создания нового Фрукта через определённое время.
	void updateGameTime(); // Слот(Qt) для обновления счётчика времени игры.
	void resetPauseChangeFlag(); // Слот(Qt) для обновления "флага" смены паузы.

public slots:

	void endGame();
	void showGameWindow(); // Новый слот для показа игрового окна.
	void gameTimeTimerStart();
	void fruitTimerStart();
	void playerNameEntered(const QString& playerName);

private:

	Snake snake; // Объект класса Змейка.
	Fruit fruit; // Объект класса Fruit.
	QTimer* timer = new QTimer(this); // Таймер для обновления игры.
	QTimer* fruitTimer = new QTimer(this); // Таймер для появления Фрукта.
	bool directionChangedRecently = false; // Флаг смены направления.
	QTimer* directionChangeTimer = new QTimer(this); // Таймер для задержки нажатия клавиш.
	bool paused = false; // Флаг для паузы.
	int fruitTimeRemaining = 0; // Оставшееся время жизни Фрукта.
	int gameTimeTimerRemaining = 0; // Оставшееся время таймера отсчета секунд времени игры.
	bool pauseChangedRecently = false; // Флаг смены паузы.
	QTimer* pauseChangeTimer = new QTimer(this);
	bool spacePressed = false;
	QTimer* gameTimeTimer = new QTimer(this); // Таймер для счётчика времени игры.
	int fruitCount = 0; // Переменная для хранения количества съеденных Фруктов.
	int gameTimeSeconds = 0; // Переменная - счётчик времени игры.

protected:

	// paintEvent — имя виртуальной функции QWidget, которая будет переопределена.
	// QPaintEvent* event — параметр функции, указатель на объект QPaintEvent, который содержит информацию о событии рисования.
	// override — ключевое слово, указывающее, что эта функция переопределяет виртуальную функцию базового класса.
	// Это помогает компилятору проверять правильность переопределения.
	void paintEvent(QPaintEvent* event) override;

	// Метод для управления Змейкой в игровом окне с помощью нажатия клавиш.
	void keyPressEvent(QKeyEvent* event) override; // Переопределение обработчика событий нажатия клавиши.
	void keyReleaseEvent(QKeyEvent* event) override;
	void hideEvent(QHideEvent* event) override;
	void showEvent(QShowEvent* event) override;

public:

	void writeAchievementLogic(); // Метод для логики записи результатов в файл.
	QString currentPlayerName;

	// GameWindow — это конструктор класса GameWindow.
	// QWidget* parent — указатель на родительский виджет.
	// Если виджет передается в качестве родителя, новый виджет будет дочерним элементом этого родительского виджета.
	// = nullptr — значение по умолчанию для параметра parent.
	// Если родитель не указан, будет использоваться nullptr, что означает отсутствие родителя.
	GameWindow(QWidget* parent = nullptr);

	void spawnFruit(const Snake& snake); // Метод для создания фрукта в случайном месте.
	bool directionContains(int x, int y) const; // Метод проверяющий попадают ли данные координаты на траекторию движения Змейки.

	QLabel* fruitCountLabel;
	QLabel* gameTimeLabel;
};

int getRandomNumber(int min, int max);

// #endif — директива препроцессора, завершающая условный блок, начатый директивой #ifndef.
#endif
