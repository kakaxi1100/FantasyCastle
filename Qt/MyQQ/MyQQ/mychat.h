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
private:
    QTextBrowser* showText;
    QTextEdit* inputText;

    QPushButton* closeBtn;
    QPushButton* sendBtn;
};

#endif // MYCHAT_H
