#include "mainwindow.h"


QT_CHARTS_USE_NAMESPACE

using namespace std;
bool compare(pair<int,int>p, pair<int,int> q)
{
    return p.second < q.second;
}

void MainWindow::createLayout()
    {
        QWidget *list_button = new QWidget(this);
        QGridLayout *layout = new QGridLayout(list_button);
        layout->setMargin(6);
        layout->setSpacing(6);

        for (int i = 0; i < 11; ++i)
            layout->addWidget(buttonsvect[i], i / 6, i % 6);

        QDockWidget *posButton = new QDockWidget(tr("add numbers"), this);
        posButton->setAllowedAreas(Qt::BottomDockWidgetArea);
        addDockWidget(Qt::BottomDockWidgetArea,posButton);
        posButton->setWidget(list_button);
    }



MainWindow::~MainWindow(){}

void MainWindow::add_one(int i) {
    nbs[i]++;
    emit call_graph();
}

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow (parent)
{
    this->setFixedSize(600,400);

    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(digitClicked(int)));

    for (int i = 0; i < 11; ++i) {
        QString text = QString::number(i+2);
        buttonsvect.push_back(new QPushButton(text, this));
        signalMapper->setMapping(buttonsvect[i], i+2);
        connect(buttonsvect[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
    }
    connect(this, SIGNAL(call_graph()), this, SLOT(printgraph()));
    createLayout();
}

int MainWindow::printgraph(){
    QBarSet *set0 = new QBarSet("Numbers");

    for (int i = 2; i<13; i++)
        *set0 << nbs[i];

//![2]
    QBarSeries *series = new QBarSeries();
    series->append(set0);
//![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Jets de dés");
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![4]
    QStringList categories;
    categories << "2" << "3" << "4" << "5" << "6" << "7"
               << "8" << "9" << "10" << "11" << "12";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    int max = (*max_element(nbs.begin(),nbs.end(),compare)).second;
    int maxAxis = (max%2==0)? max:max+1;
    axisY->setRange(0,maxAxis);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    axisY->setTickCount(((maxAxis/2)>=2)?maxAxis%2 : 2);
    axisY->applyNiceNumbers();
    chart->legend()->setVisible(false);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);




    setCentralWidget(chartView);

    show();

    return EXIT_SUCCESS;
}


int main(int argc, char *argv[])
{

    map<int,int> nbs;
    QApplication a(argc, argv);

    MainWindow window;
    window.resize(600, 400);

    window.printgraph();



    return a.exec();
}

