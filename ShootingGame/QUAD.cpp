#include "QUAD.h"

QUAD::QUAD(GLuint id,float x,float y)
{
	this->m_textureID = id;
	this->m_imageH = 256;
	this->m_imageW = 256;
	this->SetPoint(x,y,m_imageW,m_imageH,0);
	this->SetVertex();
	this->m_right = this->m_down = 1.0f;
	this->m_left = this->m_top = 0.0f;
	
}
QUAD::QUAD(GLuint id, float x,float y,float w,float h)
{
	this->m_textureID = id;
	this->m_imageH = 256;
	this->m_imageW = 256;
	this->SetPoint(x,y,w,h,0);
	this->SetVertex();
	this->m_right = this->m_down = 1.0f;
	this->m_left = this->m_top = 0.0f;
}
QUAD::QUAD(GLuint id,float x,float y,float angle)
{
	this->m_textureID = id;
	this->m_imageH = 256;
	this->m_imageW = 256;
	this->SetPoint(x,y,m_imageW,m_imageH,angle);
	this->SetVertex();
	this->m_right = this->m_down = 1.0f;
	this->m_left = this->m_top = 0.0f;
}
QUAD::QUAD(GLuint id,float x,float y,float w,float h,float angle)
{
	this->m_textureID = id;
	this->m_imageH = 256;
	this->m_imageW = 256;
	this->SetPoint(x,y,w,h,angle);
	this->SetVertex();
	this->m_right = this->m_down = 1.0f;
	this->m_left = this->m_top = 0.0f;
}
void QUAD::SetVertex()
{
	this->m_vertexX[0] = 0 - (this->m_w / 2);
	this->m_vertexX[1] = (this->m_w / 2);
	this->m_vertexY[0] = 0 - (this->m_h / 2);
	this->m_vertexY[1] = (this->m_h / 2);
}
void QUAD::SetImageWH(int w,int h)
{
	this->m_imageW = w;
	this->m_imageH = h;
}
void QUAD::SetPoint(float x,float y)
{
	this->SetPoint(x,y,this->m_w,this->m_h,this->m_angle);
}
void QUAD::SetPoint(float x,float y,float angle)
{
	this->SetPoint(x,y,this->m_w,this->m_h,angle);
}
void QUAD::SetPoint(float x,float y,float w,float h,float angle)
{
	this->m_x = x;
	this->m_y = y;
	this->m_w = w;
	this->m_h = h;
	this->m_angle = angle;
	this->SetVertex();
}
void QUAD::SetTexCoord(float left,float right,float top,float down)
{
	this->m_top = top/this->m_imageH;
	this->m_down = down/this->m_imageH;
	this->m_left = left/this->m_imageW;
	this->m_right = right/this->m_imageW;
}
void QUAD::SetTexCoord(float left,float right)
{
	this->m_left = left/this->m_imageW;
	this->m_right = right/this->m_imageW;
}
void QUAD::Draw(void)
{
	if(this){
		glPushMatrix();
			glTranslated(m_x,m_y,0);
			glRotated(m_angle,0,0,1);
			glBindTexture(GL_TEXTURE_2D,this->m_textureID);//選擇你要用的材質
			glEnable(GL_BLEND);//啟動混和功能
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
				glTexCoord2f(m_left,m_down);glVertex3f(this->m_vertexX[0], this->m_vertexY[0], Z);
				glTexCoord2f(m_right,m_down);glVertex3f(this->m_vertexX[1], this->m_vertexY[0], Z);
				glTexCoord2f(m_right,m_top);glVertex3f(this->m_vertexX[1], this->m_vertexY[1], Z);
				glTexCoord2f(m_left,m_top);glVertex3f(this->m_vertexX[0], this->m_vertexY[1], Z);
			glEnd();
			glDisable(GL_BLEND);
		glPopMatrix();
	}
}
