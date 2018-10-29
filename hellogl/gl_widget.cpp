#include "gl_widget.h"
#include <QMouseEvent>
#include <iostream>
#include <GL/glu.h>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

GLWidget::~GLWidget()
{
    cleanup();
}

void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    std::cout<<"OpenGL Version: "<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"GLSL Version: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    program = new QOpenGLShaderProgram;
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    initShaders();

//    on mac it's opengl 2.1, it's not a must to use vao, and it's also not
//    supported. Here is just in case
    vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&vao);

    vbo.create();
    vbo.bind();
    vbo.allocate(mCube.constData(), mCube.count() * sizeof(GLfloat));

    setupVertexAttribs();

    ibo.create();
    ibo.bind();
    ibo.allocate(vertex_index, 3 * num_tris * sizeof(GLuint));
    ibo.bind();

//    this->cameraM.setToIdentity();

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    program->release();
}

void GLWidget::setupVertexAttribs() {
    vbo.bind();
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glEnableVertexAttribArray(0);
        f->glEnableVertexAttribArray(1);
        f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
        f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
        vbo.release();
}

void GLWidget::initShaders()
{
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");

    program->bindAttributeLocation("pos", 0);
    program->bindAttributeLocation("normal", 1);

    program->link();
    program->bind();

    mvMatrixLoc = program->uniformLocation("mvMatrix");
    mProjMatrixLoc = program->uniformLocation("projMatrix");
    mNomalMatrixLoc = program->uniformLocation("normalMatrix");
    colorUniformLoc = program->uniformLocation("color");
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_world.setToIdentity();
    m_world.rotate(180.0f - (xRot / 16.0f), 1, 0, 0);
    m_world.rotate(yRot / 16.0f, 0, 1, 0);
    m_world.rotate(zRot / 16.0f, 0, 0, 1);

    QOpenGLVertexArrayObject::Binder vaoBinder(&vao);
    program->bind();
    program->setUniformValue(mProjMatrixLoc, m_proj);
    program->setUniformValue(mvMatrixLoc, m_camera * m_world);
    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    program->setUniformValue(mNomalMatrixLoc, normalMatrix);

    glDrawArrays(GL_TRIANGLES, 0, mCube.vertexCount());

    program->release();
}

void GLWidget::resizeGL(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }
    glViewport(0, 0, width, height);

    m_proj.setToIdentity();
    qreal aspect = GLfloat(width) / GLfloat(height);
    m_proj.perspective(45.0f, aspect, 0.1f, 10.0f);
}


void GLWidget::cleanup()
{
    if (program == nullptr)
        return;
    makeCurrent();
    delete program;
    program = 0;
    doneCurrent();
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
            angle += 360;
        while (angle > 360)
            angle -= 360;
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    m_lastPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
}


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}
