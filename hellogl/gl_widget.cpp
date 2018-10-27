#include "gl_widget.h"
#include <QCoreApplication>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      program(new QOpenGLShaderProgram)
{
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 200, 0, 1);

    //    glGenVertexArrays(1, &vao);
    //    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_position), vertex_position, GL_STATIC_DRAW);

    //    glGenBuffers(1, &ibo);
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_index), vertex_index, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // initShaders();

    glEnable(GL_CULL_FACE);
}

void GLWidget::initShaders()
{
    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert"))
    {
        close();
    }
    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag"))
    {
        close();
    }

    if (!program->link())
    {
        close();
    }

    int l_attr = program->attributeLocation("pos");
    if (l_attr >= 0)
    {
        program->setAttributeBuffer(l_attr, GL_FLOAT, 0, 3, 0);
    }

    program->setUniformValue("color", 0.0, 200.0, 0.0);
    program->enableAttributeArray(0);

    if (!program->bind())
    {
        close();
    }
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    glDrawElements(GL_TRIANGLES, 3 * NUM_TRIS, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 9);
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
}
