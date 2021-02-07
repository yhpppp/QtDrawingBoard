#include "mainwindow.h"

#include <QColorDialog>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    drawWidget = new DrawWidget;
    setCentralWidget(drawWidget);
    createToolBar();
    setMinimumSize(600,400);
    ShowStyle();
    drawWidget->setWidth(widthSpinBox->value());
    drawWidget->setColor(Qt::black);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar("Tool");
    styleLabel = new QLabel(tr("线性风格"));
    styleComboBox = new QComboBox;
    styleComboBox->addItem(tr("SolidLine"),static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem(tr("DashLine"),static_cast<int>(Qt::DashLine));
        styleComboBox->addItem(tr("DotLine"),static_cast<int>(Qt::DotLine));
            styleComboBox->addItem(tr("DashDotLine"),static_cast<int>(Qt::DashDotLine));
                styleComboBox->addItem(tr("DashDotDotLine"),static_cast<int>(Qt::DashDotDotLine));
    connect(styleComboBox,SIGNAL(activated(int)),this,SLOT(ShowStyle()));

    widthLabel = new QLabel(tr("线宽: "));
    widthSpinBox = new QSpinBox;
    connect(widthSpinBox,SIGNAL(valueChanged(int)),drawWidget,SLOT(setWidth(int)));
    colorBtn = new QToolButton;
    QPixmap pixmap(20,20);
    pixmap.fill(Qt::black);
    colorBtn->setIcon(QIcon(pixmap));
    connect(colorBtn,SIGNAL(clicked(bool)),this,SLOT(ShowColor()));

    clearBtn = new QToolButton;
    clearBtn->setText(tr("清除"));
    connect(clearBtn,SIGNAL(clicked(bool)),drawWidget,SLOT(clear()));

    toolBar->addWidget(styleLabel);
    toolBar->addWidget(styleComboBox);
    toolBar->addWidget(widthLabel);
    toolBar->addWidget(widthSpinBox);
    toolBar->addWidget(colorBtn);
    toolBar->addWidget(clearBtn);
}

void MainWindow::ShowStyle()
{
    drawWidget->setStyle(styleComboBox->itemData(styleComboBox->currentIndex(),Qt::UserRole).toInt());
}

void MainWindow::ShowColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black),this);
    if(color.isValid()){
        drawWidget->setColor(color);
        QPixmap p(20,20);
        p.fill(color);
        colorBtn->setIcon(QIcon(p));
    }
}




























