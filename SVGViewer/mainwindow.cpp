#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QColorDialog>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pSettings(new QSettings("Vitalii Shunkov", "SVGViewer", parent))
{
    ui->setupUi(this);
    setAcceptDrops(true);

    m_pSvgView = new SvgView(this);
    m_pSvgView->setAcceptDrops(true);
    m_pSvgView->viewport()->setAcceptDrops(true);

    ui->centralWidget->layout()->addWidget(m_pSvgView);

    if(m_pSettings->contains("Geometry/WindowGeometry"))
    {
        if(m_pSettings->value("Geometry/ShowMaximized", false).toBool())
        {
            showMaximized();
        }
        else
        {
            setGeometry(m_pSettings->value("Geometry/WindowGeometry").value<QRect>());
        }
    }

//    QColor scrollAreaBackgroundColor = m_pSettings->value("Colors/BackgroundColor",
//                                                          getBackgroundColor(this)
//                                                          ).value<QColor>();
//    setBackgroundColor(ui->scrollArea, scrollAreaBackgroundColor);
}

MainWindow::~MainWindow()
{
    if(!isMaximized())
    {
        m_pSettings->setValue("Geometry/WindowGeometry", this->geometry());
    }
    m_pSettings->setValue("Geometry/ShowMaximized", this->isMaximized());
//    m_pSettings->setValue("Colors/BackgroundColor", getBackgroundColor(ui->scrollArea));

    delete ui;
}

void MainWindow::openFile(const QString &path)
{
    m_pSvgView->openFile(path);
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionOpen_triggered()
{
    QString lastPath = m_pSettings->value("FileDialog/LastPath", "/home").toString();

    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                lastPath,
                                                tr("Images (*.svg)"));

    if(!path.isEmpty())
    {
        openFile(path);

        QFileInfo fileInfo(path);
        lastPath = fileInfo.path();
        m_pSettings->setValue("FileDialog/LastPath", lastPath);
    }
}


void MainWindow::on_actionChangeBackgroundColor_triggered()
{
//    QColor lastColor = m_pSettings->value("Colors/BackgroundColor",
//                                          ui->scrollArea->palette().color(QPalette::Background)
//                                          ).value<QColor>();

//    QColor color = QColorDialog::getColor(lastColor, this, tr("Set Color"));

//    setBackgroundColor(ui->scrollArea, color);
}

void MainWindow::setBackgroundColor(QWidget *targetWidget, QColor color)
{
    QPalette palette;

    if(color.isValid())
    {
        palette.setColor(QPalette::Background, color);
        targetWidget->setPalette(palette);
    }
}

QColor MainWindow::getBackgroundColor(QWidget *targetWidget)
{
    return targetWidget->palette().color(QPalette::Background);
}

void MainWindow::on_actionReset_to_default_BackgroundColor_triggered()
{
//    setBackgroundColor(ui->scrollArea, getBackgroundColor(this));
}

void MainWindow::on_actionDraw_background_triggered(bool checked)
{
    m_pSvgView->setViewBackground(checked);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Space:
        m_pSvgView->fitInView(m_pSvgView->sceneRect(), Qt::KeepAspectRatio);
        event->accept();
        break;
    case Qt::Key_Backspace:
        m_pSvgView->resetMatrix();
        event->accept();
        break;

        // Also 1061(0x425) and 1066(0x430) in Russian
    case Qt::Key_BracketLeft:
        qDebug() << "Left bracket pressed";
        event->accept();
        break;
    case Qt::Key_BracketRight:
        qDebug() << "Right bracket pressed";
        event->accept();
        break;
    case Qt::Key_F11:
        static bool isWindowMaximizedPreviously = false;
        if(isFullScreen())
        {
            if(isWindowMaximizedPreviously)
            {
                showMaximized();
            }
            else
            {
                showNormal();
            }
        }
        else
        {
            isWindowMaximizedPreviously = isMaximized();
            showFullScreen();
        }
        event->accept();
        break;
    default:
        break;
    }
}







