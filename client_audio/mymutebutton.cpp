/*
 * Copyright Cyrille MULLER Jean-Romain LUTTRINGER
 * UFR de Mathématiques et d'Informatique
 * Université de Strasbourg
 * © 2017
 */

#include "mymutebutton.h"

MyMuteButton::MyMuteButton(QWidget *parent):QWidget(parent){
    this->pixmap_mute = new QPixmap(this->muted_path);
    this->pixmap_not_mute = new QPixmap(this->not_muted_path);
    this->muted = false;
    press = false;
}

void MyMuteButton::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(QRectF(0, 0, this->width(),this->height()), 4, 4);
    QLinearGradient gradient(QPoint(0,0),QPoint(0,this->height()));
    gradient.setColorAt(0, QColor(142,120,98,255));
    gradient.setColorAt(1,QColor(142,120,98,255));//Qt::lightGray);
//    painter.fillRect(QRect(QPoint(0,0),QPoint(this->width(),this->height())),gradient);
    painter.fillPath(path, gradient);
    QPen pen(Qt::gray, 2);
    painter.setPen(pen);
    if(muted)
        painter.drawPixmap(7,5,this->width()-10,this->height()-8,*pixmap_mute);
    else
        painter.drawPixmap(7,5,this->width()-10,this->height()-8,*pixmap_not_mute);
    if(press){
        painter.setOpacity(0.5);
          painter.fillPath(path,Qt::black);

    }
    painter.setOpacity(1);
    painter.drawPath(path);
}

void MyMuteButton::mousePressEvent(QMouseEvent *event){
    press = true;
    this->repaint();
    //darken background
}

void MyMuteButton::mouseReleaseEvent(QMouseEvent *event){
    press = false;
//    this->muted = !this->muted;
    this->repaint();
    emit mute();
//    emit releaseMouse();
    //normalize backgrund
}

void MyMuteButton::set_muted(bool b){
    this->muted = b;
}

bool MyMuteButton::get_muted(){
    return this->muted;
}


