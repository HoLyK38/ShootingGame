#include <cv.h>
#include <highgui.h> 
void LoadTexture(char *fileName,char *alphaFileName,GLuint& id);
void LoadTexture(char *fileName,char *alphaFileName,GLuint& id,float a);
IplImage alpha(char *alphaFileName, char *fileName, int n1, int n2);
IplImage alpha(char *alphaFileName, char *fileName, int n1, int n2,float a);

IplImage alpha(char *alphaFileName, char *fileName, int n1, int n2)
{

	IplImage *Image1 = cvLoadImage(alphaFileName,CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	IplImage *Image2 = cvLoadImage(fileName,CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

	IplImage *Image3 = cvCreateImage(cvSize(n1,n2),IPL_DEPTH_8U, 4 ); 

	CvScalar s;
	CvScalar alpha;

	for(int i=0;i<Image1->height;i++){
		for(int j=0;j<Image1->width;j++){
			alpha=cvGet2D(Image1,i,j);
			s=cvGet2D(Image2,i,j);
			uchar* value_ptr = &CV_IMAGE_ELEM( Image3, uchar, i, j*4 );
			value_ptr[0] = s.val[2];
			value_ptr[1] = s.val[1];
			value_ptr[2] = s.val[0];
			value_ptr[3] = alpha.val[2]*0.85;
		}
	}

	return *Image3;
}
IplImage alpha(char *alphaFileName, char *fileName, int n1, int n2,float a)
{

	IplImage *Image1 = cvLoadImage(alphaFileName,CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	IplImage *Image2 = cvLoadImage(fileName,CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

	IplImage *Image3 = cvCreateImage(cvSize(n1,n2),IPL_DEPTH_8U, 4 ); 

	CvScalar s;
	CvScalar alpha;

	for(int i=0;i<Image1->height;i++){
		for(int j=0;j<Image1->width;j++){
			alpha=cvGet2D(Image1,i,j);
			s=cvGet2D(Image2,i,j);
			uchar* value_ptr = &CV_IMAGE_ELEM( Image3, uchar, i, j*4 );
			value_ptr[0] = s.val[2];
			value_ptr[1] = s.val[1];
			value_ptr[2] = s.val[0];
			value_ptr[3] = alpha.val[2]*a;
		}
	}

	return *Image3;
}
void LoadTexture(char *fileName,char *alphaFileName,GLuint& id)
{
	int w, h;
	IplImage *Image1 = cvLoadImage(fileName,CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	w=Image1->width;
	h=Image1->height;
	IplImage *AlphaImage = cvCreateImage(cvSize(w,h),IPL_DEPTH_8U, 4 );
	AlphaImage = &alpha(alphaFileName,fileName,w,h);


	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,w,h,GL_RGBA,GL_UNSIGNED_BYTE,AlphaImage->imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
}
void LoadTexture(char *fileName,char *alphaFileName,GLuint& id,float a)
{
	int w, h;
	IplImage *Image1 = cvLoadImage(fileName,CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	w=Image1->width;
	h=Image1->height;
	IplImage *AlphaImage = cvCreateImage(cvSize(w,h),IPL_DEPTH_8U, 4 );
	AlphaImage = &alpha(alphaFileName,fileName,w,h,a);


	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,w,h,GL_RGBA,GL_UNSIGNED_BYTE,AlphaImage->imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
}