#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QPushButton>
#include <QDockWidget>
#include <QSignalMapper>
#include <QApplication>
#include <map>
#include <QtCharts/QBarSet>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QGridLayout>
#include <iostream>
#include <algorithm>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void add_one(int i);
signals:
    void call_graph();
public slots:

    void digitClicked(int i){
        //QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

        //int digitValue = clickedButton->text().toInt();

        add_one(i);
    }

    int printgraph();

private:
    void createLayout();
    Ui::MainWindow *ui;
    std::map<int,int> nbs;
    std::vector<QPushButton*> buttonsvect;
};



#endif // MAINWINDOW_H
