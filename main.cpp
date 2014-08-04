#include <QCoreApplication>
#include <QCommandLineParser>

#include "qatemcontroller.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("qatemcmd");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Send commands to a Blackmagic ATEM switcher via commandline.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("address", QCoreApplication::translate("main", "Address of the Blackmagic ATEM switcher"));
    parser.addPositionalArgument("command", QCoreApplication::translate("main", "Command to send: switch, switchNoTrans"));
    parser.addPositionalArgument("input", QCoreApplication::translate("main", "Input number"));

    QCommandLineOption delay (QStringList() << "d" << "delay", QCoreApplication::translate("main", "Delay by x milliseconds"), "0");
    parser.addOption(delay);

    parser.process(a);

    QStringList arguments = parser.positionalArguments();

    if (arguments.count() != 3)
    {
        parser.showHelp(-1);
    }

    QAtemController controller;

    controller.setDelay(parser.value(delay).toInt());

    //qDebug() << "delay: " + QString::number(parser.value(delay).toInt());

    controller.connectAtem(arguments.at(0),arguments.at(1),arguments.at(2).toInt());

    //qDebug() << arguments.at(0) + " " + arguments.at(1) + " " + arguments.at(2);

    return a.exec();
}
