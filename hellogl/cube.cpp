#include "cube.h"

Cube::Cube()
    : m_count(0)
{
    m_data.resize(2500 * 6);

    const GLfloat x1= 1.0f;
    const GLfloat y1= 1.0f;
    const GLfloat z1= 1.0f;

    const GLfloat x2=-1.0f;
    const GLfloat y2= 1.0f;
    const GLfloat z2= 1.0f;

    const GLfloat x3= -1.0f;
    const GLfloat y3= -1.0f;
    const GLfloat z3= 1.0f;

    const GLfloat x4= 1.0f;
    const GLfloat y4= -1.0f;
    const GLfloat z4= 1.0f;

    const GLfloat x5 = 1.0f;
    const GLfloat y5 = 1.0f;
    const GLfloat z5 = -1.0f;

    const GLfloat x6 =-1.0f;
    const GLfloat y6 = 1.0f;
    const GLfloat z6 = -1.0f;

    const GLfloat x7 = -1.0f;
    const GLfloat y7 = -1.0f;
    const GLfloat z7 = -1.0f;

    const GLfloat x8 = 1.0f;
    const GLfloat y8 = -1.0f;
    const GLfloat z8 = -1.0f;

    quad(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    quad(x1, y1, z1, x4, y4, z4, x8, y8, z8, x5, y5, z5);
    quad(x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8);
    quad(x2, y2, z2, x3, y3, z3, x7, y7, z7, x6, y6, z6);
    quad(x1, y1, z1, x2, y2, z2, x6, y6, z6, x5, y5, z5);
    quad(x3, y3, z3, x4, y4, z4, x8, y8, z8, x7, y7, z7);

}

void Cube::add(const QVector3D &v, const QVector3D &n)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    m_count += 6;
}

void Cube::quad(GLfloat x1, GLfloat y1, GLfloat z1,  GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, z4 - z1), QVector3D(x2 - x1, y2 - y1, z2 - z1));

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x2, y2, z2), n);

    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x4, y4, z4), n);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, z1 - z4), QVector3D(x2 - x4, y2 - y4, z2 - z4));

    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x2, y2, z2), n);

    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x4, y4, z4), n);
}
