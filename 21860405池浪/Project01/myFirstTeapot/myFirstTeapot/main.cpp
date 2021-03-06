//
//  main.cpp
//  myFirstTeapot
//
//  Created by mac on 2018/12/16.
//  Copyright © 2018年 mac. All rights reserved.
//

//仅用于测试，代码直接往上拷贝，只修改了个头文件
//绘制茶壶

#include <GLUT/GLUT.h>
#include <math.h>
#include <iostream>

float teapot_size = 0.5;
float tx=0,ty=0,tz=0;
int viewx,viewy=0;


//自定义初始化opengl函数
void init(void)
{
    
    
    //材质反光性设置
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //镜面反射参数
    GLfloat mat_shininess[] = { 50.0 };               //高光指数
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };   //灯位置(1,1,1), 最后1-开关
    GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //环境光参数
    
    glClearColor(0.0, 0.0, 0.0, 0.0);  //背景色
    glShadeModel(GL_SMOOTH);           //多变性填充模式
    
    //材质属性
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    //灯光设置
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数
    
    glEnable(GL_LIGHTING);   //开关:使用光
    glEnable(GL_LIGHT0);     //打开0#灯
    glEnable(GL_DEPTH_TEST); //打开深度测试
     
     
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(1, 0, 1, 0);
    glTranslated(tx,ty,tz);
    //gluLookAt(0.0,0.0,5.0,  0.0,0.0,0.0,  0.0,1.0,0.0);
    //gluLookAt(9.0,5.0,5.0,0.0,0.0,-10.0,0.0,1.0,0.0);
    glutSolidTeapot(teapot_size);
    
    
    /*
     glBegin(GL_QUADS);
     glVertex3f(0, 0, 10);
     glVertex3f(0, 0, 10);
     glVertex3f(20, 5, 10);
     glVertex3f(30, 40, -10);
     glEnd();
    */
    
    glFlush();
    //glutSwapBuffers();
}

void reshape(int w, int h)
{
    //glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glViewport(viewx, viewy, (GLsizei)w, (GLsizei)h);
    
    //设置投影参数
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    
    //正交投影
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5*(GLfloat)w / (GLfloat)h, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    
    //设置模型参数--几何体参数
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0.0,0.0,5.0,  0.0,0.0,0.0,  0.0,1.0,0.0);
}

void mouseCB(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON){
        if(teapot_size<0.8){
            viewx=x;
            viewy=y;
            teapot_size += 0.1;
        }
    }
    else if(button==GLUT_RIGHT_BUTTON){
        if(teapot_size>0.2){
            viewx=x;
            viewy=y;
            teapot_size -= 0.1;
        }
    }
}

void SpecialKey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            tx=0.01;
            break;
        case GLUT_KEY_RIGHT:
            tx=-0.01;
            break;
        case GLUT_KEY_UP:
            ty=0.01;
            break;
        case GLUT_KEY_DOWN:
            ty=-0.01;
            break;
    }
}

void CommonKey(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 'a':
            tx=0.01;
            break;
        case 'd':
            tx=-0.01;
            break;
        case 'w':
            ty=0.01;
            break;
        case 's':
            ty=-0.01;
            break;
        case 'z':
            tz=0.01;
            break;
        case 'x':
            tz=-0.01;
            break;
        case 'q':
            tx=ty=tz=0;
            break;
    }
}

void mouseMotionCB(int x,int y)
{
    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("茶壶");
    
    init();
    
    glutDisplayFunc(display);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);
    glutSpecialFunc(SpecialKey);
    glutKeyboardFunc(CommonKey);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}
