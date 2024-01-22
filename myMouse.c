#include<math.h>
#include "./config.h"

// マウスイベントのコールバック関数間でやりとりするための変数
// ファイルに関する静的変数なので、このファイルの中だけで有効
static int startx = 0;
static int starty = 0;
static int endx = 0;
static int endy = 0;
static int pressedButton = -1;

int drag_mouse_r_s = 0;

void
myMouse(int button, int state, int x, int y)
{
#ifdef MOUSE_FUNCTION
	switch(state) {
		case  GLUT_DOWN: {  // マウスボタンが押された
			pressedButton = button;
			startx = x;
			starty = y;
			switch(button) {
				case GLUT_LEFT_BUTTON: {
				    // myCameraRotateY(1.0/M_PI);
				    break;
				}	
				case GLUT_MIDDLE_BUTTON: {
				    //myCameraRotateX(1.0/M_PI);
				    break;
				}	
				case GLUT_RIGHT_BUTTON: {
				    // シフトを押したときにはフラグを立てる
				    if(glutGetModifiers()&GLUT_ACTIVE_SHIFT){
				        drag_mouse_r_s = 1;
					break;
				    }	
				    break;
				}	
			}
			break;
		}
		case GLUT_UP: { // マウスボタンが離された
			endx = x;
			endy = y;
			pressedButton = -1;
			switch(button) {
				case GLUT_LEFT_BUTTON: {
					break;
				}	
				case GLUT_MIDDLE_BUTTON: {
					break;
				}	
				case GLUT_RIGHT_BUTTON: {
				    drag_mouse_r_s = 0;
				    break;
				}	
			}
			break;
		}
	}	
#endif	
	// 再描画イベント
	glutPostRedisplay();
}


void
myMouseMotion(int x, int y)
{
#ifdef MOTION_FUNCTION
	int delx, dely;

	delx = x - startx;
	dely = y - starty; // デバイス座標系のy軸の関係

	switch(pressedButton) {
	        // 分子の回転
	        case GLUT_LEFT_BUTTON: {		
		    myCameraRotateY(delx/M_PI/20);
		    myCameraRotateX(dely/M_PI/20);
		    startx =  x;
		    starty =  y;
		    break;
		}
		// 分子のズーム
	        case GLUT_MIDDLE_BUTTON: {		
		    myCameraTranslateZ(delx/20.0);
		    myCameraTranslateZ(dely/20.0);
		    startx =  x;
		    starty =  y;
		    break;
		}
	        // 移動
		case GLUT_RIGHT_BUTTON: {
		    // SHIFTを押している場合にはZ軸回転
		    if(drag_mouse_r_s){
			myCameraRotateZ(delx/M_PI/20);
			starty = y;
			break;
		    }	
		    myCameraTranslateX(delx/20.0);
		    myCameraTranslateY(dely/20.0);	
		    startx =  x;
		    starty =  y;
		    break;
		}
	}
#endif
	// 再描画イベント
	glutPostRedisplay();
}


void
myMousePassiveMotion(int x, int y)
{
#ifdef PASSIVEMOTION_FUNCTION
#endif
	// 再描画イベント
	glutPostRedisplay();
}


