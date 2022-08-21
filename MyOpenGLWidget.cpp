#include "MyOpenGLWidget.h"
#include "OpenGLLogHandler.h"
#include "MyOpenGLGraphicsItem.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLDebugLogger>
#include <QThread>

QMatrix4x4 createOrthographicsProjectionMatrix(const float left, const float right, const float top, const float bottom)
{
    static constexpr float near = -1.0f;
    static constexpr float far = 1.0f;

    auto rml = right - left;
    auto rpl = right + left;
    auto tmb = top - bottom;
    auto tpb = top + bottom;
    auto fmn = far - near;
    auto fpn = far + near;

    auto m11 =  2 / rml;
    auto m14 = -1 * rpl / rml;
    auto m22 =  2 / tmb;
    auto m24 = -1 * tpb / tmb;
    auto m33 = -2 * fmn;
    auto m34 = -1 * fpn / fmn;
    auto m44 =  1.0f;

    QMatrix4x4 projectionMatrix(m11, 0,  0,   m14,
                                0,  m22, 0,   m24,
                                0,   0,  m33, m34,
                                0,   0,  0,   m44);
    return projectionMatrix;
}

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      program(new QOpenGLShaderProgram(this))
{
    connect(this, &QOpenGLWidget::frameSwapped, this, [this] {
        emit advance();
        update();
    });
}

std::vector<QOpenGLShader*> MyOpenGLWidget::createShaders()
{
    std::vector<QOpenGLShader*> shaders;

    QOpenGLShader *vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    vertexShader->compileSourceFile("/home/xray/workspace/learnopengl/MyVertexShader.vert");
    assert(vertexShader->isCompiled());

    QOpenGLShader *fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    fragmentShader->compileSourceFile("/home/xray/workspace/learnopengl/MyFragmentShader.frag");
    assert(fragmentShader->isCompiled());

    shaders.push_back(vertexShader);
    shaders.push_back(fragmentShader);

    return shaders;
}

void MyOpenGLWidget::initializeGL()
{
#ifdef DEBUG_OPENGL
    logger = new QOpenGLDebugLogger(this);
    logHandler = new OpenGLLogHandler(this);
    QObject::connect(logger, &QOpenGLDebugLogger::messageLogged, logHandler, &OpenGLLogHandler::onMessageLogged);
    logger->initialize();
    logger->startLogging();
#endif

    shaders = createShaders();
    for (auto *shader : shaders) {
        program->addShader(shader);
    }
    assert(program->link());
    assert(program->bind());
}

void MyOpenGLWidget::paintGL()
{
    program->setUniformValue("u_projection", projectionMatrix);
    for (auto *item : items) {
        item->paintGL(program);
    }
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    projectionMatrix = createOrthographicsProjectionMatrix(0, w, 0, h);
}

QOpenGLShaderProgram* MyOpenGLWidget::getProgram()
{
    return program;
}

void MyOpenGLWidget::addItem(MyOpenGLGraphicsItem *item)
{
    if (thread() != QThread::currentThread()) {
        return;
    }
    if (item == nullptr) {
        return;
    }

    item->setWidget(this);
    makeCurrent();
    assert(QOpenGLContext::currentContext() != nullptr);
    item->initializeGL();
    doneCurrent();
    items.push_back(item);
}
