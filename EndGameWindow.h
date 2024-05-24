#ifndef ENDGAMEWINDOW_H
#define ENDGAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

class EndGameWindow : public QWidget
{
    Q_OBJECT

signals:

    void onExitClicked();
    void onRestartClicked();
    void onResultsClicked();

public slots:

    void showEndGameWindow(int fruitCount, int gameTimeSeconds);

    void ExitClicked();
    void RestartClicked();
    void ResultsClicked();

public:

    explicit EndGameWindow(QWidget* parent = nullptr);

private:

    QLabel* titleLabel;
    QLabel* fruitCountLabel;
    QLabel* gameTimeLabel;
    QPushButton* restartButton;
    QPushButton* viewResultsButton;
    QPushButton* exitButton;
};

#endif