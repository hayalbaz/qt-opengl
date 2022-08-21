#include "OpenGLLogHandler.h"
#include <QOpenGLDebugMessage>
#include <spdlog/spdlog.h>

OpenGLLogHandler::OpenGLLogHandler(QObject *parent)
    : QObject{parent}
{

}

void OpenGLLogHandler::onMessageLogged(const QOpenGLDebugMessage &debugMessage)
{
    spdlog::error("{}", debugMessage.message().toStdString());
}
