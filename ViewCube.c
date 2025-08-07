#include <GL/glut.h>
#include <math.h>

float view_rot_x = 20, view_rot_y = -30; // 主視圖旋轉
float cube_rot_x = 20, cube_rot_y = -30; // ViewCube 旋轉
int dragging = 0, last_x, last_y;

void drawCube(float size) {
    glutSolidCube(size);
}

void drawViewCube() {
    glPushMatrix();
    glRotatef(cube_rot_x, 1, 0, 0);
    glRotatef(cube_rot_y, 0, 1, 0);

    // 不同面上色
    glBegin(GL_QUADS);
    // +Z 藍
    glColor3f(0,0,1); glVertex3f(-0.5, -0.5, 0.5); glVertex3f(0.5, -0.5, 0.5); glVertex3f(0.5, 0.5, 0.5); glVertex3f(-0.5, 0.5, 0.5);
    // -Z 綠
    glColor3f(0,1,0); glVertex3f(-0.5, -0.5, -0.5); glVertex3f(0.5, -0.5, -0.5); glVertex3f(0.5, 0.5, -0.5); glVertex3f(-0.5, 0.5, -0.5);
    // +Y 紅
    glColor3f(1,0,0); glVertex3f(-0.5, 0.5, -0.5); glVertex3f(0.5, 0.5, -0.5); glVertex3f(0.5, 0.5, 0.5); glVertex3f(-0.5, 0.5, 0.5);
    // -Y 黃
    glColor3f(1,1,0); glVertex3f(-0.5, -0.5, -0.5); glVertex3f(0.5, -0.5, -0.5); glVertex3f(0.5, -0.5, 0.5); glVertex3f(-0.5, -0.5, 0.5);
    // +X 青
    glColor3f(0,1,1); glVertex3f(0.5, -0.5, -0.5); glVertex3f(0.5, 0.5, -0.5); glVertex3f(0.5, 0.5, 0.5); glVertex3f(0.5, -0.5, 0.5);
    // -X 紫
    glColor3f(1,0,1); glVertex3f(-0.5, -0.5, -0.5); glVertex3f(-0.5, 0.5, -0.5); glVertex3f(-0.5, 0.5, 0.5); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 主視圖
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)glutGet(GLUT_WINDOW_WIDTH)/glutGet(GLUT_WINDOW_HEIGHT), 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,8, 0,0,0, 0,1,0);

    glPushMatrix();
    glRotatef(view_rot_x, 1, 0, 0);
    glRotatef(view_rot_y, 0, 1, 0);
    glColor3f(1,1,1);
    drawCube(2.0);
    glPopMatrix();

    // ViewCube 視窗右上角
    int size = 100;
    glViewport(glutGet(GLUT_WINDOW_WIDTH)-size-10, glutGet(GLUT_WINDOW_HEIGHT)-size-10, size, size);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);

    drawViewCube();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    int win_w = glutGet(GLUT_WINDOW_WIDTH);
    int win_h = glutGet(GLUT_WINDOW_HEIGHT);
    int size = 100;
    // 檢查是否點擊 ViewCube
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x > win_w-size-10 && y < size+10) {
            dragging = 1;
            last_x = x;
            last_y = y;
        }
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        dragging = 0;
        // 同步主視圖旋轉
        view_rot_x = cube_rot_x;
        view_rot_y = cube_rot_y;
    }
}

void motion(int x, int y) {
    if (dragging) {
        cube_rot_y += (x - last_x);
        cube_rot_x += (y - last_y);
        last_x = x;
        last_y = y;
        glutPostRedisplay();
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D View with ViewCube");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();
    return 0;
}