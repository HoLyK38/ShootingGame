#include "Ball.h"

Ball::Ball(GLuint id,float x,float y)
{
	this->m_textureID = id;
	this->m_imageH = 256;
	this->m_imageW = 256;
	this->SetPoint(x,y,m_imageW,m_imageH,0);
	this->SetVertex();
	this->m_right = this->m_down = 1.0f;
	this->m_left = this->m_top = 0.0f;
	this->luaState = luaL_newstate();
}
Ball::Ball(GLuint id, float x,float y,float w,float h)
{
	this->m_textureID = id;
	this->m_imageH = 256;
	this->m_imageW = 256;
	this->SetPoint(x,y,w,h,0);
	this->SetVertex();
	this->m_right = this->m_down = 1.0f;
	this->m_left = this->m_top = 0.0f;
	this->luaState = luaL_newstate();
}
Ball::Ball(GLuint id,float x,float y,float angle)
{
	this->m_textureID = id;
	this->m_imageH = 256;
	this->m_imageW = 256;
	this->SetPoint(x,y,m_imageW,m_imageH,angle);
	this->SetVertex();
	this->m_right = this->m_down = 1.0f;
	this->m_left = this->m_top = 0.0f;
	this->luaState = luaL_newstate();
}
Ball::Ball(GLuint id,float x,float y,float w,float h,float angle)
{
	this->m_textureID = id;
	this->m_imageH = 256;
	this->m_imageW = 256;
	this->SetPoint(x,y,w,h,angle);
	this->SetVertex();
	this->m_right = this->m_down = 1.0f;
	this->m_left = this->m_top = 0.0f;
	this->luaState = luaL_newstate();
}
void Ball::SetVertex()
{
	float x_left,x_right;
	float y_top,y_down;

	x_left = 0 - (this->m_width / 2);
	x_right = (this->m_width / 2);
	y_top = (this->m_height / 2);
	y_down = 0 - (this->m_height / 2);
	
	this->m_vertex[0] = Vector2(x_left,y_down);
	this->m_vertex[1] = Vector2(x_right,y_down);
	this->m_vertex[2] = Vector2(x_right,y_top);
	this->m_vertex[3] = Vector2(x_left,y_top);
}
void Ball::SetImageWH(int w,int h)
{
	this->m_imageW = w;
	this->m_imageH = h;
}
void Ball::SetPoint(float x,float y)
{
	this->SetPoint(x,y,this->m_width,this->m_height,this->m_angle);
}
void Ball::SetPoint(float x,float y,float angle)
{
	this->SetPoint(x,y,this->m_width,this->m_height,angle);
}
void Ball::SetPoint(float x,float y,float w,float h,float angle)
{
	this->m_pos.x = x;
	this->m_pos.y = y;
	this->m_width = w;
	this->m_height = h;
	this->m_angle = angle;
	this->SetVertex();
}
void Ball::SetTexCoord(float left,float right,float top,float down)
{
	this->m_top = top/this->m_imageH;
	this->m_down = down/this->m_imageH;
	this->m_left = left/this->m_imageW;
	this->m_right = right/this->m_imageW;
}
void Ball::SetTexCoord(float left,float right)
{
	this->m_left = left/this->m_imageW;
	this->m_right = right/this->m_imageW;
}
void Ball::Render(void)
{
	if(this){
		glPushMatrix();
		glTranslated(this->m_pos.x,this->m_pos.y,0);
		glRotated(m_angle,0,0,1);
		glBindTexture(GL_TEXTURE_2D,this->m_textureID);//選擇你要用的材質
		glEnable(GL_BLEND);//啟動混和功能
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
			glTexCoord2f(m_left,m_down);glVertex3f(this->m_vertex[0].x, this->m_vertex[0].y, Z);
			glTexCoord2f(m_right,m_down);glVertex3f(this->m_vertex[1].x, this->m_vertex[1].y, Z);
			glTexCoord2f(m_right,m_top);glVertex3f(this->m_vertex[2].x, this->m_vertex[2].y, Z);
			glTexCoord2f(m_left,m_top);glVertex3f(this->m_vertex[3].x, this->m_vertex[3].y, Z);
		glEnd();
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}
float Ball::GetWidth(){return this->m_width;};
float Ball::GetHeight(){return this->m_height;};
Vector2 Ball::GetPos(){return this->m_pos;};