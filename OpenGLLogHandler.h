#ifndef OPENGLLOGHANDLER_H
#define OPENGLLOGHANDLER_H

#include <QObject>

class QOpenGLDebugMessage;
class OpenGLLogHandler : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLLogHandler(QObject *parent = nullptr);

public slots:
    void onMessageLogged(const QOpenGLDebugMessage &debugMessage);
};

#endif // OPENGLLOGHANDLER_H
