#ifndef MYMUTEBUTTON_H
#define MYMUTEBUTTON_H

#include<QPixmap>
#include<QWidget>
#include<QPainter>

class MyMuteButton: public QWidget
{
    Q_OBJECT
public:
    explicit MyMuteButton(QWidget *parent = 0);
    void set_muted(bool b);
    bool get_muted();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPixmap* pixmap_mute;
    QPixmap* pixmap_not_mute;
    bool muted ;
    QString muted_path = ":/new/prefix1/resource/mute_2.png";
    QString not_muted_path= ":/new/prefix1/resource/sound_high.png";
    bool press;
signals:
    void pressed();
};

#endif // MYMUTEBUTTON_H
