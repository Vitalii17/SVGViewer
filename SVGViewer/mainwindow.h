#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSettings>
#include <QColor>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDropEvent>

#include "svgview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow() override;

public slots:
    void openFile(const QString &path);

private slots:
    void on_actionExit_triggered();
    void on_actionOpen_triggered();

    void on_actionChangeBackgroundColor_triggered();
    void on_actionReset_to_default_BackgroundColor_triggered();
    void on_actionDraw_background_triggered(bool checked);

    void on_actionAbout_SVGViewer_triggered();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void setBackgroundColor(QWidget *targetWidget, QColor color);
    QColor getBackgroundColor(QWidget *targetWidget);

private:
    Ui::MainWindow *ui;
    QSettings      *m_pSettings;
    SvgView        *m_pSvgView;
};

#endif // MAINWINDOW_H
