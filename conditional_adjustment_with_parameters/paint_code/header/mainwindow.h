#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<all.h>
namespace Ui{
class MainWindow;
}
class MainWindow:public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent*){
        QPainter painter(this);
        painter.drawImage(0,0,image);
    }
private:
    void paint();
    QImage image;
    Ui::MainWindow *ui;
};
#endif//MAINWINDOW_H
