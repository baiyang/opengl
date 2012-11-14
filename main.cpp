

#include <iostream>
#include <GL/glut.h>
#include <vector>
using namespace std;

#include "math3d.h"
#include "Selection.h"


Selection selection;

M3DVector2f left_bottom, right_top;
bool bool_select_area = false;



int viewport[4];

static M3DVector3f corners[] = {
	-25, 25, 25, 
	25, 25, 25, 
	25, -25, 25, 
	-25, -25, 25,
	-25, 25, -25, 
	25, 25, -25, 
	25, -25, -25,
	-25, -25, -25
};


void init(void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
}

void display(void)
{
   M3DMatrix44f mat_proj, mat_modelview;

   int width = glutGet( GLUT_WINDOW_WIDTH ), height = glutGet( GLUT_WINDOW_HEIGHT );
   

   glViewport (0, 0, (GLsizei) width, (GLsizei) height); 

   glGetIntegerv(GL_VIEWPORT, viewport);

   glClear (GL_COLOR_BUFFER_BIT);

   glPushAttrib(GL_POLYGON_BIT);
   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 300);

   // 获取投影矩阵
   glGetFloatv(GL_PROJECTION_MATRIX, mat_proj);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0, 0, 70, 0, 0, 0, 0, 1, 0);
   glColor4f(0.1, 0.4, 0.6, 0.7);
   glPushMatrix();

		// 获取模型视图矩阵
		glGetFloatv(GL_MODELVIEW_MATRIX, mat_modelview);

		glBegin( GL_QUADS );
		glVertex3fv(corners[0]);
		glVertex3fv(corners[1]);
		glVertex3fv(corners[5]);
		glVertex3fv(corners[4]);

		glVertex3fv(corners[4]);
		glVertex3fv(corners[7]);
		glVertex3fv(corners[3]);
		glVertex3fv(corners[0]);

		glVertex3fv(corners[3]);
		glVertex3fv(corners[2]);
		glVertex3fv(corners[6]);
		glVertex3fv(corners[7]);

		glVertex3fv(corners[7]);
		glVertex3fv(corners[6]);
		glVertex3fv(corners[5]);
		glVertex3fv(corners[4]);

		glVertex3fv(corners[5]);
		glVertex3fv(corners[1]);
		glVertex3fv(corners[2]);
		glVertex3fv(corners[6]);

		glVertex3fv(corners[1]);
		glVertex3fv(corners[2]);
		glVertex3fv(corners[3]);
		glVertex3fv(corners[0]);
		glEnd();

   glPopMatrix();
   glPopAttrib();
   
   // 配置

   selection.set_config( corners, 8, left_bottom, right_top, mat_modelview, mat_proj, viewport);

   /************************************************************************/
   /* 构造一个新的环境                                                                     */
   /************************************************************************/
   
   if( bool_select_area ){
	   
	   selection.draw_area();
	   selection.highlight_selected_pts();

   }
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
}

void mouse(int button, int state, int x, int y)
{
	int width = glutGet( GLUT_WINDOW_WIDTH ), height = glutGet( GLUT_WINDOW_HEIGHT );

	if( button == GLUT_LEFT_BUTTON ){

		if(state == GLUT_DOWN){
			bool_select_area = true;
		}else if ( state == GLUT_UP)
		{
			bool_select_area = false;
		}

		m3dLoadVector2(left_bottom, x, height - y);
		m3dLoadVector2(right_top, x, height - y);
	}

	glutPostRedisplay();
}

void motion(int x, int y)
{
	int width = glutGet( GLUT_WINDOW_WIDTH ), height = glutGet( GLUT_WINDOW_HEIGHT );

	if( bool_select_area ){
		m3dLoadVector2(right_top, x, height - y);
	}

	glutPostRedisplay();

}

/* ARGSUSED1 */
void keyboard (unsigned char key, int x, int y)
{

}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);

   glutMainLoop();
   return 0;
}
