#include "qatemcontroller.h"

#include "libqatemcontrol/qatemconnection.h"

#include <QTextStream>
#include <QCoreApplication>
#include <QHostAddress>
#include <QTimer>

QAtemController::QAtemController(QObject *parent) :
    QObject(parent)
{
    m_connection = new QAtemConnection(this);
    connect(m_connection, SIGNAL(socketError(QString)),
            this, SLOT(handleError(QString)));
    connect(m_connection, SIGNAL(connected()),
            this, SLOT(handleConnect()));
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
    m_connection->changePreviewInput(input);
    m_connection->doAuto();
    QCoreApplication::exit(-1);
}

void QAtemController::switchInputNoTrans(quint8 input) {
    m_connection->changeProgramInput(input);
    QCoreApplication::exit(-1);
}

void QAtemController::handleConnect() {
    QTextStream out(stderr);
    if (m_command == "switch") {
        out << "Transitioning to input " << QString::number(m_input) << " with " << QString::number(m_delay) << "ms delay" << endl << endl;
        if (m_delay > 0) {
            QTimer::singleShot(m_delay, this, SLOT(switchInputSlot()));
        } else {
            switchInput(m_input);
        }
    } else if (m_command == "switchNoTrans") {
        out << "Changing to input " << QString::number(m_input) << " with " << QString::number(m_delay) << "ms delay" << endl << endl;
        if (m_delay > 0) {
            QTimer::singleShot(m_delay, this, SLOT(switchInputSlot()));
        } else {
            switchInputNoTrans(m_input);
        }
    } else {
        handleError("Not a valid command");
    }
}

void QAtemController::switchInputSlot() {
    switchInput(m_input);
}
void QAtemController::switchInputNoTransSlot() {
    switchInputNoTrans(m_input);
}

void QAtemController::handleError(const QString &errorString)
{
    QTextStream out(stderr);
    out << errorString << endl << endl;
    QCoreApplication::exit(-1);
}
