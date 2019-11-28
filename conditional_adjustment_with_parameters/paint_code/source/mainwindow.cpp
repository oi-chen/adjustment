#include<mainwindow.h>
#include<ui_mainwindow.h>
struct point{
    double x,y;
}p[5];
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    image=QImage(1440,1080,QImage::Format_RGB32);
    QColor backColor=qRgb(255,255,255);
    image.fill(backColor);
    paint();
}
void MainWindow::paint(){
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);//反锯齿
    int ox=720,oy=540;
    painter.drawLine(720,0,720,1080);
    painter.drawLine(0,540,1440,540);
    p[0].x=-23.466,p[0].y=-24.1758;
    p[1].x=120.176,p[1].y=0.0296298;
    p[2].x=79.1834,p[2].y=79.1778;
    p[3].x=50.706,p[3].y=101.193;
    p[4].x=-0.0652179,p[4].y=119.599;
    double r=145.667;
    QPen pen;
    QFont font;
    font.setFamily("Consolas");
    font.setPointSize(18);
    font.setItalic(true);
    painter.setFont(font);
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawEllipse(QPointF(ox+3*p[0].x,oy-3*p[0].y),3*r,3*r);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(QPointF(ox,oy),3,3);
    painter.drawText(QPointF(ox+10,oy-10),"O");
    painter.drawText(QPointF(1420,oy-10),"X");
    painter.drawText(QPointF(ox+10,20),"Y");
    for(int i=0;i<=4;i++){
        string str='p'+to_string(i)+'('+to_string(p[i].x)+','+to_string(p[i].y)+')';
        painter.drawEllipse(QPointF(ox+3*p[i].x,oy-3*p[i].y),3,3);
        painter.drawText(QPointF(ox+3*p[i].x+10,oy-3*p[i].y-10),QString::fromStdString(str));
    }
}
MainWindow::~MainWindow(){
    delete ui;
}
