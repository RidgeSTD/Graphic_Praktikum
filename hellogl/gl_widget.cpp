#include "gl_widget.h"
#include <QMouseEvent>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    program = new QOpenGLShaderProgram(this);

    initShaders();

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
//    on mac it's opengl 2.1, it's not a must to use vao, and it's also not
//    supported. Here is just in case
    vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&vao);

    vbo.create();
    vbo.bind();
    vbo.allocate(vertex_position, 3 * num_verts * sizeof(GLfloat));
    vbo.bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vbo.release();

    ibo.create();
    ibo.bind();
    ibo.allocate(vertex_index, 3 * num_tris * sizeof(GLuint));


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    program->release();
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
    program->bindAttributeLocation("pos", 0);

    if (!program->link())
    {
        close();
    }

    if (!program->bind())
    {
        close();
    }

    mvpUniformLoc = program->uniformLocation("mvp_matrix");
    colorUniformLoc = program->uniformLocation("color");
}

void GLWidget::paintGL()
{
//    QMatrix4x4 view;
//    view.lookAt(QVector3D(2, 3, 3), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

//    // no need to use model matrix for it's identical
//    program->setUniformValue(1, projectionM * view);

////    glDrawElements(GL_TRIANGLES, 3 * num_tris, GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_TRIANGLES, 0, 3 * num_verts);
//    program->release();
//    glClearColor(0, 200, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 清除屏幕及深度缓存
    glLoadIdentity();
    glBegin(GL_TRIANGLES); // 绘制三角形
            glVertex3f(0.0f, 1.0f, 0.0f); // 上顶点
            glVertex3f(-1.0f,-1.0f, 0.0f); // 左下
            glVertex3f( 1.0f,-1.0f, 0.0f); // 右下
        glEnd(); // 三角形绘制结束
}

void GLWidget::resizeGL(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }
    glViewport(0, 0, width, height);

    // reset projection matrix
    glMatrixMode(GL_PROJECTION);

    qreal aspect = (qreal)width / height;
    projectionM.setToIdentity();
    projectionM.perspective(45.0f, aspect, 0.1f, 10.0f);
}

//void GLWidget::mousePressEvent(QMouseEvent *event)
//{
//    m_lastPos = event->pos();
//}

//void GLWidget::mouseMoveEvent(QMouseEvent *event)
//{
//}

//void GLWidget::wheelEvent(QWheelEvent *event)
//{
//}
