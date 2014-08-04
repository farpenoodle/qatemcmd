#ifndef QATEMCONTROLLER_H
#define QATEMCONTROLLER_H

#include <QObject>

class QAtemConnection;

class QAtemController : public QObject
{
    Q_OBJECT
public:

    explicit QAtemController(QObject *parent = 0);

//    void setMediaPlayer(qint8 id) { m_mediaplayer = id; }
//    void upload(const QString &filename, const QString &address, quint8 position);
      void connectAtem(const QString &address, const QString &command, quint8 input);
      void switchInput(quint8 input);
      void switchInputNoTrans(quint8 input);

      void setDelay(int delay) { m_delay = delay; }

protected slots:
    void handleError(const QString &errorString);
    void handleConnect();
    void switchInputSlot();
    void switchInputNoTransSlot();

private:
    QAtemConnection *m_connection;
    QString m_command;
    quint8 m_input;
    int m_delay;
};

#endif // QATEMCONTROLLER_H
