#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <iostream>
#include <time.h>
#include "opengl_func.h"
#include "vec_field.h"

#define MAX_STEPS 1000
#define STEP 1e-2
#define XLEFT -2.
#define XRIGHT 2.
#define YBOTTOM -2.
#define YTOP 2.
#define ZNEAR -2.
#define ZFAR 2.

#define IS_INTO_SCENE(v) ((v).x >= XLEFT && (v).x <= XRIGHT && (v).y >= YBOTTOM && (v).y <= YTOP && (v).z >= ZNEAR && (v).z <= ZFAR)

int WidthScreen, HeightScreen;
double ratio;

void Init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Vector field");

    glutDisplayFunc(Display);
    glutMainLoop();
}

auto x = -X * Y;
auto y = -Y * Z;
auto z = -Z * X;

auto vf = rot(CreateVecField(x, y, z));

void Display(void)
{
    static int timer = clock();
    static const glm::vec3 arr[] = { glm::vec3(XLEFT, YBOTTOM, ZNEAR), glm::vec3(XLEFT, YBOTTOM, ZFAR), 
        glm::vec3(XLEFT, YTOP, ZNEAR), glm::vec3(XLEFT, YTOP, ZFAR),
        glm::vec3(XRIGHT, YBOTTOM, ZNEAR), glm::vec3(XRIGHT, YBOTTOM, ZFAR),
        glm::vec3(XRIGHT, YTOP, ZNEAR), glm::vec3(XRIGHT, YTOP, ZFAR), 

        glm::vec3(XRIGHT, YBOTTOM, 0), glm::vec3(XLEFT, YBOTTOM, 0),
        glm::vec3(XRIGHT, YTOP, 0), glm::vec3(XLEFT, YTOP, 0),
        glm::vec3(0, YBOTTOM, ZNEAR), glm::vec3(0, YBOTTOM, ZFAR),
        glm::vec3(0, YTOP, ZNEAR), glm::vec3(0, YTOP, ZFAR), 
        glm::vec3(XLEFT, 0, ZNEAR), glm::vec3(XLEFT, 0, ZFAR),
        glm::vec3(XRIGHT, 0, ZNEAR), glm::vec3(XRIGHT, 0, ZFAR),
        glm::vec3(0, 0, ZNEAR), glm::vec3(0, 0, ZFAR),
        glm::vec3(0, YTOP, 0), glm::vec3(XLEFT, 0, 0),
        glm::vec3(0, YBOTTOM, 0), glm::vec3(XRIGHT, 0, 0), 

        glm::vec3(XLEFT / 2, YBOTTOM, ZNEAR / 2), glm::vec3(XLEFT / 2, YBOTTOM / 2, ZFAR),
        glm::vec3(XLEFT / 2, YTOP / 2, ZNEAR), glm::vec3(XLEFT / 2, YTOP, ZFAR / 2),
        glm::vec3(XRIGHT / 2, YBOTTOM, ZNEAR / 2), glm::vec3(XRIGHT / 2, YBOTTOM / 2, ZFAR),
        glm::vec3(XRIGHT / 2, YTOP / 2, ZNEAR), glm::vec3(XRIGHT / 2, YTOP, ZFAR / 2),
        glm::vec3(XLEFT / 2, YBOTTOM / 2, ZNEAR), glm::vec3(XLEFT / 2, YBOTTOM, ZFAR / 2),
        glm::vec3(XLEFT / 2, YTOP, ZNEAR / 2), glm::vec3(XLEFT / 2, YTOP / 2, ZFAR),
        glm::vec3(XRIGHT / 2, YBOTTOM / 2, ZNEAR), glm::vec3(XRIGHT / 2, YBOTTOM, ZFAR / 2),
        glm::vec3(XRIGHT / 2, YTOP, ZNEAR / 2), glm::vec3(XRIGHT / 2, YTOP / 2, ZFAR),
        glm::vec3(XLEFT, YBOTTOM / 2, ZNEAR / 2), glm::vec3(XLEFT, YBOTTOM / 2, ZFAR / 2),
        glm::vec3(XLEFT, YTOP / 2, ZNEAR / 2), glm::vec3(XLEFT, YTOP / 2, ZFAR / 2), 
        glm::vec3(XRIGHT, YBOTTOM / 2, ZNEAR / 2), glm::vec3(XRIGHT, YBOTTOM / 2, ZFAR / 2),
        glm::vec3(XRIGHT, YTOP / 2, ZNEAR / 2), glm::vec3(XRIGHT, YTOP / 2, ZFAR / 2), 
        
        glm::vec3(XLEFT / 2, YBOTTOM, ZNEAR), glm::vec3(XLEFT / 2, YBOTTOM, ZFAR),
        glm::vec3(XLEFT / 2, YTOP, ZNEAR), glm::vec3(XLEFT / 2, YTOP, ZFAR),
        glm::vec3(XRIGHT / 2, YBOTTOM, ZNEAR), glm::vec3(XRIGHT / 2, YBOTTOM, ZFAR),
        glm::vec3(XRIGHT / 2, YTOP, ZNEAR), glm::vec3(XRIGHT / 2, YTOP, ZFAR),
        glm::vec3(XLEFT, YBOTTOM / 2, ZNEAR), glm::vec3(XLEFT, YBOTTOM / 2, ZFAR),
        glm::vec3(XLEFT, YTOP / 2, ZNEAR), glm::vec3(XLEFT, YTOP / 2, ZFAR / 2),
        glm::vec3(XRIGHT, YBOTTOM / 2, ZNEAR), glm::vec3(XRIGHT, YBOTTOM / 2, ZFAR),
        glm::vec3(XRIGHT, YTOP / 2, ZNEAR), glm::vec3(XRIGHT, YTOP / 2, ZFAR), 

        glm::vec3(XLEFT, YBOTTOM / 2, ZNEAR), glm::vec3(XLEFT, YBOTTOM, ZFAR / 2),
        glm::vec3(XLEFT, YTOP, ZNEAR / 2), glm::vec3(XLEFT, YTOP / 2, ZFAR),
        glm::vec3(XRIGHT, YBOTTOM / 2, ZNEAR), glm::vec3(XRIGHT, YBOTTOM, ZFAR / 2),
        glm::vec3(XRIGHT, YTOP, ZNEAR / 2), glm::vec3(XRIGHT, YTOP / 2, ZFAR),
        glm::vec3(XLEFT, YBOTTOM, ZNEAR / 2), glm::vec3(XLEFT, YBOTTOM, ZFAR / 2),
        glm::vec3(XLEFT, YTOP, ZNEAR / 2), glm::vec3(XLEFT, YTOP, ZFAR / 2),
        glm::vec3(XRIGHT, YBOTTOM, ZNEAR / 2), glm::vec3(XRIGHT, YBOTTOM, ZFAR / 2),
        glm::vec3(XRIGHT, YTOP, ZNEAR / 2), glm::vec3(XRIGHT, YTOP, ZFAR / 2)
    };
    static const size_t len_arr = sizeof(arr) / sizeof(glm::vec3);
    glClearColor(0.05, 0., 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glOrtho(XLEFT * 2, XRIGHT * 2, YBOTTOM * 2, YTOP * 2, ZNEAR * 2, ZFAR * 2);
    glRotated(timer / 30, 0, 0.3, 0.5);

    glColor3d(1,1,1);

    for (int i = 0; i < len_arr; i++) {
        glm::vec3 v = arr[i], dir;
        int steps_count = 0;

        glColor3d(1, 1, 1);
        while (IS_INTO_SCENE(v) && steps_count++ < MAX_STEPS) {
            dir = vf(v);
            dir *= STEP / dir.length();
            glBegin(GL_LINES);
            glVertex3d(v.x, v.y, v.z);
            glVertex3d(v.x + dir.x, v.y + dir.y, v.z + dir.z);
            glEnd();
            v += dir;
        }
        glColor3d(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex3d(v.x, v.y, v.z);
        glEnd();
    }
    timer = clock();
    glutSwapBuffers();
    glutPostRedisplay();
}
