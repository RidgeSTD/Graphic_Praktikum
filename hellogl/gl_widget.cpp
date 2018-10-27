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

    const unsigned int num_verts = 4;
    const unsigned int num_tris = 2;
    const GLfloat vertex_position[3 * num_verts] =
        {
            1.0, 1.0, 0.0,
            -1.0, 1.0, 0.0,
            -1.0, -1.0, 0.0,
            1.0, -1.0, 0.0};

    const GLuint vertex_index[3 * num_tris] =
        {
            0, 1, 2,
            0, 2, 3};
    vao = new GLuint[3 * num_verts];
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);
    vbo = new GLuint[3 * num_verts];
    glGenVertexArrays(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);

    glBufferData(GL_ARRAY_BUFFER, 3 * num_verts * sizeof(GLfloat), vertex_position, GL_STATIC_DRAW);

    ibo = new GLuint[3 * num_tris];
    glGenBuffers(1, ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * num_tris * sizeof(GLuint), vertex_index, GL_STATIC_DRAW);

    initShaders();
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
    if (l_attr > 0)
    {
        program->setAttributeBuffer(l_attr, GL_FLOAT, 0, 3, 0);
        glEnableVertexAttribArray(l_attr);
    }

    l_attr = program->attributeLocation("frag");
    if (l_attr > 0)
    {
        program->setUniformValue(l_attr, 1.0, 2.0, 3.0);
        glEnableVertexAttribArray(l_attr);
    }

    if (!program->bind())
    {
        close();
    }
}

void GLWidget::paintGL()
{
    glClearColor(0, 0, 0, 1);

//    glDrawElements()
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
