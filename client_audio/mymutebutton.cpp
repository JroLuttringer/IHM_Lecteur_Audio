#include "mymutebutton.h"
#include <QDebug>
#include <QLinearGradient>
#include <QPoint>
MyMuteButton::MyMuteButton(QWidget *parent):QWidget(parent){
    this->pixmap_mute = new QPixmap(this->muted_path);
    pixmap_mute->scaled(38,44,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->pixmap_not_mute = new QPixmap(this->not_muted_path);
     pixmap_not_mute->scaled(38,44,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    this->muted =true;
    this->resize(50,50);
    press = false;
}

void MyMuteButton::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(QRectF(0, 0, this->width(),this->height()), 2, 2);
    QLinearGradient gradient(QPoint(0,0),QPoint(0,this->height()));
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1,QColor(230,230,230,255));//Qt::lightGray);
    painter.fillRect(QRect(QPoint(0,0),QPoint(this->width(),this->height())),gradient);
    QPen pen(Qt::gray, 2);
    painter.setPen(pen);
    if(muted)
        painter.drawPixmap(7,7,this->width()-12,this->height()-14,*pixmap_mute);
    else
        painter.drawPixmap(7,7,this->width()-12,this->height()-14,*pixmap_not_mute);
    if(press){
        painter.setOpacity(0.5);
          painter.fillPath(path,Qt::lightGray);

    }
    painter.setOpacity(1);
    painter.drawPath(path);

}

void MyMuteButton::mousePressEvent(QMouseEvent *event){
//    press = true;
//    this->repaint();
    emit pressed();
    //darken background
}

void MyMuteButton::mouseReleaseEvent(QMouseEvent *event){
//    press = false;
//    this->muted = !this->muted;
//    this->repaint();
//    emit releaseMouse();
    //normalize backgrund
}

void MyMuteButton::set_muted(bool b){
    this->muted = b;
}

bool MyMuteButton::get_muted(){
    return this->muted;
}


