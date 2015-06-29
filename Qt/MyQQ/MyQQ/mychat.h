#ifndef MYCHAT_H
#define MYCHAT_H

#include <QWidget>
#include <QTextBrowser>
#include <QFontComboBox>
#include <QComboBox>
#include <QToolButton>
#include <QTextEdit>
#include <QPushButton>

class MyChat : public QWidget
{
    Q_OBJECT
public:
    explicit MyChat(QWidget *parent = 0);

signals:

public slots:
    void sendMsg();
    void closeClicked();
private:
    QTextBrowser* showText;
    QTextEdit* inputText;

    QFontComboBox* fontHomeBox;
    QComboBox* fontSizeBox;
    QToolButton* boldToolBtn;
    QToolButton* italicToolBtn;
    QToolButton* underlineToolBtn;
    QToolButton* colorToolBtn;
    QToolButton* sendToolBtn;
    QToolButton* saveToolBtn;
    QToolButton* clearToolBtn;

    QPushButton* closeBtn;
    QPushButton* sendBtn;
};

#endif // MYCHAT_H
