#include "gl_widget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    initializeGL();
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

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
}

void GLWidget::paintGL()
{
}

void GLWidget::resizeGL(int width, int height)
{
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
