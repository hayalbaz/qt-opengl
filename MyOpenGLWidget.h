#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>

class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QOpenGLDebugLogger;
class QOpenGLShader;
class QOpenGLFunctions;
class OpenGLLogHandler;
class MyOpenGLGraphicsItem;
class MyOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = nullptr);
    QOpenGLShaderProgram* getProgram();
    void addItem(MyOpenGLGraphicsItem *item);

signals:
    void advance();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
    std::vector<QOpenGLShader*> createShaders();

protected:
    QOpenGLShaderProgram *program;

    std::vector<QOpenGLShader*> shaders;
#ifdef DEBUG_OPENGL
    QOpenGLDebugLogger *logger;
    OpenGLLogHandler *logHandler;
#endif
    std::vector<MyOpenGLGraphicsItem*> items;
    QMatrix4x4 projectionMatrix;
};

#endif // MYOPENGLWIDGET_H
