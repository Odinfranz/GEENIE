#include "loggerwidget.h"
#include "ui_loggerwidget.h"
#include <QDateTime>
#include <QDebug>

LoggerWidget::LoggerWidget(QWidget *parent) :
    QWidget(parent),
    _debugChecked(true),
    _errorChecked(true),
    _warningChecked(true),
    _infoChecked(true),
    ui(new Ui::LoggerWidget)
{
    ui->setupUi(this);
    ui->logViewer->setReadOnly(true);
    QPalette p = ui->logViewer->palette();
    p.setColor(QPalette::Base,QColor(0,0,0));
    ui->logViewer->setPalette(p);
    ui->debugCheckBox->setChecked(true);
    ui->errorCheckBox->setChecked(true);
    ui->warningCheckBox->setChecked(true);
    ui->infoCheckBox->setChecked(true);
}

LoggerWidget::~LoggerWidget()
{
    delete ui;
}

void LoggerWidget::newMessage(const QString &msg, logger::MessageType type) const
{
    ui->logViewer->moveCursor(QTextCursor::End);
    QString color = QString();
    QString stringType = QString();
    switch(type)
    {
    case logger::MessageType::DEBUG:
    {
        stringType = QString("DEBUG");
        color = QString("#459A06");
        break;
    }
    case logger::MessageType::ERROR:
    {
        stringType = QString("ERROR");
        color = QString("#CC0000");
        break;
    }
    case logger::MessageType::WARNING:
    {
        stringType = QString("WARNING");
        color = QString("#AAA000");
        break;
    }
    case logger::MessageType::INFO:
    {
        stringType = QString("INFO");
        color = QString("White");
        break;
    }
    default:
    {

    }
    }
    QString htmlMessage = QString("<font color=#459A06>%1</font>"
                                  "<font color=\"White\"> - </font>"
                                  "<font color=%2>[%3] %4</font>"
                                  "<br>")
            .arg(QDateTime::currentDateTime().toString(QString("yyyy-MM-dd hh:mm:ss")))
            .arg(color)
            .arg(stringType)
            .arg(msg);
    ui->logViewer->insertHtml(htmlMessage);
    ui->logViewer->moveCursor(QTextCursor::End);

}

void LoggerWidget::on_debugCheckBox_toggled(bool checked)
{
    _debugChecked = checked;
}

void LoggerWidget::on_errorCheckBox_toggled(bool checked)
{
    _errorChecked = checked;
}

void LoggerWidget::on_warningCheckBox_toggled(bool checked)
{
    _warningChecked = checked;
}

void LoggerWidget::on_infoCheckBox_toggled(bool checked)
{
    _infoChecked = checked;
}
