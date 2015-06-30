#ifndef MYCHAT_H
#define MYCHAT_H

#include <QWidget>
#include <QTextBrowser>
#include <QFontComboBox>
#include <QComboBox>
#include <QToolButton>
#include <QTextEdit>
#include <QPushButton>
#include <QFont>
#include <QColor>
#include <QTextCharFormat>
#include <QCloseEvent>

class MyChat : public QWidget
{
    Q_OBJECT
public:
    explicit MyChat(QWidget *parent = 0);

protected:
//    void closeEvent(QCloseEvent * e);
//    bool eventFilter(QObject *o, QEvent *e);
private slots:
    void sendMsg();
    void closeClicked();
    void fontHomeChange();
    void fontSizeChange();
    void fontBoldChange();
    void fontItalicChange();
    void fontUnderlineChange();
    void colorBtnClicked();
    void saveBtnClicked();
    void clearBtnClicked();
    void fontFormatChanged(const QTextCharFormat& format);
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

    QColor color;

    void showMsg();
    bool saveFile(QString& fileName);
};

#endif // MYCHAT_H
