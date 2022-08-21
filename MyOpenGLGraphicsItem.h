#ifndef MYOPENGLGRAPHICSITEM_H
#define MYOPENGLGRAPHICSITEM_H

#include <vector>
#include <QMatrix4x4>
#include <QVector2D>

class MyOpenGLWidget;
class QOpenGLShaderProgram;
class MyOpenGLGraphicsItem
{
public:
    MyOpenGLGraphicsItem(MyOpenGLGraphicsItem *parent = nullptr);
    virtual ~MyOpenGLGraphicsItem();

    /**
     * @brief initializeGL ilk önce bu objeyi daha sonrada child objelerin OpenGL kaynaklarını initialize eder.
     */
    virtual void initializeGL();
    /**
     * @brief paintGL ilk önce bu objeyi daha sonrada child objeleri OpenGL kullanarak çizer.
     * @param program bu obje çizilirken kullanılacak OpenGL programı
     */
    virtual void paintGL(QOpenGLShaderProgram *program);

    /**
     * @brief setX bu objenin x koordinatını set eder.
     * @param x
     */
    void setX(const float x);
    /**
     * @brief setY bu objenin y koordinatını set eder.
     * @param y
     */
    void setY(const float y);

    /**
     * @brief getX bu objenin x koordinatına bir referans döner.
     * @return
     */
    float& getX();
    /**
     * @brief getY bu objenin y koordinatına bir referans döner.
     * @return
     */
    float& getY();

    /**
     * @brief setPos bu objenin x ve y koordinatını set eder.
     * @param x
     * @param y
     */
    void setPos(const float x, const float y);
    /**
     * @brief setPos bu objenin x ve y koordinatını set eder.
     * @param x
     * @param y
     */
    void setPos(const QPointF &pos);

    /**
     * @brief move bu objeyi dx ve dy kadar oynatır.
     * @param dx
     * @param dy
     */
    void move(const float dx, const float dy);
    /**
     * @brief move bu objeyi dx ve dy kadar oynatır.
     * @param dx
     * @param dy
     */
    void move(const QVector2D &dp);

    /**
     * @brief setWidget sets the OpenGL widget this object is being show on
     * @param widget
     */
    void setWidget(MyOpenGLWidget *widget);
    /**
     * @brief getWidget returns the OpenGL widget this object is being show on, nullptr if none.
     * @return
     */
    MyOpenGLWidget* getWidget();

protected:
    /**
     * @brief initialize bu objeye ait OpenGL kaynaklarının initialize edilmesi için kullanılan fonksiyon.
     */
    virtual void initialize()=0;
    /**
     * @brief paint bu objeyi OpenGL kullanarak çizmek için kullanılan fonksiyon.
     * @param program
     */
    virtual void paint(QOpenGLShaderProgram *program)=0;

protected:
    MyOpenGLGraphicsItem *parent;
    std::vector<MyOpenGLGraphicsItem*> items;

private:
    QMatrix4x4 modelMatrix;
    MyOpenGLWidget *widget;
};

#endif // MYOPENGLGRAPHICSITEM_H
