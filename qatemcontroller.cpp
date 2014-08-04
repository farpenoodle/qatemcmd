#include "qatemcontroller.h"

#include "libqatemcontrol/qatemconnection.h"

#include <QTextStream>
#include <QCoreApplication>
#include <QHostAddress>
#include <QImage>
#include <QFileInfo>

QAtemController::QAtemController(QObject *parent) :
    QObject(parent)
{
    m_connection = new QAtemConnection(this);
    connect(m_connection, SIGNAL(socketError(QString)),
            this, SLOT(handleError(QString)));
    connect(m_connection, SIGNAL(connected()),
            this, SLOT(handleConnect()));
/*    connect(m_connection, SIGNAL(mediaLockStateChanged(quint8,bool)),
            this, SLOT(handleMediaLockState(quint8,bool)));
    connect(m_connection, SIGNAL(dataTransferFinished(quint16)),
            this, SLOT(handleDataTransferFinished(quint16)));*/
}

void QAtemController::connectAtem(const QString &address, const QString &command, quint8 input) {
    QHostAddress host(address);

    if(host.isNull())
    {
        handleError(tr("Invalid switcher address"));
        return;
    }

    m_connection->connectToSwitcher(host);

    m_command = command;
    m_input = input;
}

void QAtemController::switchInput(quint8 input) {
    QTextStream out(stderr);
    out << "Transitioning to input " << QString::number(input) << endl << endl;
    m_connection->changePreviewInput(input);
    m_connection->doAuto();
    QCoreApplication::exit(-1);
}

void QAtemController::switchInputNoTrans(quint8 input) {
    QTextStream out(stderr);
    out << "Changing to input " << QString::number(input) << endl << endl;
    m_connection->changeProgramInput(input);
    QCoreApplication::exit(-1);
}

void QAtemController::handleConnect() {
    if (m_command == "switch") {
        switchInput(m_input);
    } else if (m_command == "switchNoTrans") {
        switchInputNoTrans(m_input);
    } else {
        handleError("Not a valid command");
    }
}

void QAtemController::handleError(const QString &errorString)
{
    QTextStream out(stderr);
    out << errorString << endl << endl;
    QCoreApplication::exit(-1);
}
