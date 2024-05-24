#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QKeyEvent>
#include <QVBoxLayout>
#include "PlayerAchievement.h"

class ResultsWindow : public QWidget
{
	Q_OBJECT

public slots:

	void showResultWindow();
	void closeResultWindow();

public:

	ResultsWindow(QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* event) override;
};

#endif