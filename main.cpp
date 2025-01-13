// QApplication — это класс из библиотеки Qt,
// который управляет основным циклом обработки событий и основными настройками приложения.
// Это основной класс, который требуется для создания любого приложения на основе виджетов Qt.
// Он отвечает за:
// 1 Инициализацию основных ресурсов приложения.
// 2 Управление циклами событий.
// 3 Обработку аргументов командной строки.
// 4 Установку и управление параметрами, такими как стиль и конфигурация приложения.
// Инициализация: QApplication инициализирует внутренние структуры и настройки Qt, необходимые для работы графического интерфейса.
// Цикл событий : Основной цикл событий приложения(app.exec()) запускается с помощью QApplication.
// Это цикл, в котором обрабатываются все события(например, нажатия клавиш, движения мыши и т.д.).
// Аргументы командной строки : QApplication может принимать аргументы командной строки и использовать их для настройки приложения.
#include "GameWindow.h"
#include "WelcomeWindow.h"
#include "EndGameWindow.h"
#include "ResultsWindow.h"

// int argC (argument count) — это целое число,
// которое представляет количество аргументов командной строки,
// переданных программе при ее запуске.
// Всегда как минимум равно 1,
// так как первый аргумент всегда является именем самой программы.
// char* argV[] (argument vector) — это массив строк (массив указателей на символы),
// содержащий сами аргументы командной строки.
// Каждый элемент массива argV представляет собой отдельный аргумент.
// В контексте приложения на Qt argC и argV передаются в конструктор объекта QApplication,
// чтобы Qt мог обрабатывать аргументы командной строки,
// которые могут включать различные опции и параметры, 
// используемые для настройки поведения приложения.
int main(int argc, char* argv[]) // Стандартная сигнатура функции main в C и C++, которая принимает аргументы командной строки.
{
	// Создание объекта QApplication, который управляет жизненным циклом приложения.
	// Ему передаются аргументы командной строки, чтобы он мог их обрабатывать.
	QApplication app(argc, argv);
	WelcomeWindow welcomeWindow; // Создание объекта приветственного окна.
	welcomeWindow.show(); // Показывает окно на экране.
	GameWindow gameWindow; // Создание объекта окна, в котором будет происходить основное действие игры.
	EndGameWindow endGameWindow;
	ResultsWindow resultsWindow;

	// Показать игровое окно по сигналу, испускаемому приветственным окном.
	QObject::connect(&welcomeWindow, &WelcomeWindow::startGame, &gameWindow, &GameWindow::showGameWindow);
	QObject::connect(&welcomeWindow, &WelcomeWindow::startGame, &gameWindow, &GameWindow::gameTimeTimerStart);
	QObject::connect(&welcomeWindow, &WelcomeWindow::startGame, &gameWindow, &GameWindow::fruitTimerStart);
	QObject::connect(&welcomeWindow, &WelcomeWindow::startGame, &gameWindow, &GameWindow::playerNameEntered);

	// Подключаем сигнал конца игры к слоту показа окна окончания игры.
	QObject::connect(&gameWindow, &GameWindow::gameEnd, &endGameWindow, &EndGameWindow::showEndGameWindow);
	QObject::connect(&gameWindow, &QWidget::destroyed, &app, &QApplication::quit);

	// Подключаем сигналы окна окончания игры к слотам приветственного окна.
	QObject::connect(&endGameWindow, &EndGameWindow::onExitClicked, &welcomeWindow, &WelcomeWindow::onExitClicked);
	QObject::connect(&endGameWindow, &EndGameWindow::onRestartClicked, &welcomeWindow, &WelcomeWindow::onStartClicked);

	// Сигналы для слотов окна результатов.
	QObject::connect(&endGameWindow, &EndGameWindow::onResultsClicked, &resultsWindow, &ResultsWindow::showResultWindow);
	QObject::connect(&welcomeWindow, &WelcomeWindow::startGame, &resultsWindow, &ResultsWindow::closeResultWindow);

	// Запускает главный цикл обработки событий приложения.
	// Эта функция будет выполняться до тех пор, пока не будет вызвано app.quit(),
	// что означает завершение работы приложения.
	return app.exec();
}