#ifndef MYADDFRIEND_H
#define MYADDFRIEND_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

class MyAddFriend : public QWidget
{
    Q_OBJECT
public:
    explicit MyAddFriend(QWidget *parent = 0);

private slots:

private:
    QPushButton* findBtn;
    QPushButton* addBtn;
    QLineEdit* numberLE;
    QTextEdit* infoTE;
};

#endif // MYADDFRIEND_H
