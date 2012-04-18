void LoadTexture(char *fileName,char *alphaFileName,GLuint& id,float a);
void LoadTexture(char *fileName,char *alphaFileName,GLuint& id);
void LoadTexture(char *fileName,GLuint& id);
unsigned char *LoadBitmapFile(char *fileName, BITMAPINFO *bitmapInfo);
unsigned char *TransIntoRGBA(char *fileName,char *alphaFileName, BITMAPINFO *bitmapInfo);
unsigned char *TransIntoRGBA(char *fileName,char *alphaFileName, BITMAPINFO *bitmapInfo,float a);
void LoadTexture(char *fileName,GLuint& id)
{
	unsigned char *image;         //�o��ϮסA�w�g���OBMP�ϤF�A�O�ઽ����OpenGL�ϥΪ���ƤF
	BITMAPINFO bmpinfo;            //�ΨӦs��HEADER��T
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id);

	image = LoadBitmapFile(fileName, &bmpinfo);

	//glTexImage2D(GL_TEXTURE_2D,0,4,bmpinfo.bmiHeader.biWidth,bmpinfo.bmiHeader.biHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,image);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,bmpinfo.bmiHeader.biWidth,bmpinfo.bmiHeader.biHeight,GL_RGBA,GL_UNSIGNED_BYTE,image);
	//							 4					RGBA
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
}
void LoadTexture(char *fileName,char *alphaFileName,GLuint& id)
{
	unsigned char *image;         //�o��ϮסA�w�g���OBMP�ϤF�A�O�ઽ����OpenGL�ϥΪ���ƤF
	BITMAPINFO bmpinfo;            //�ΨӦs��HEADER��T
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id);

	image = TransIntoRGBA(fileName,alphaFileName, &bmpinfo);

	//glTexImage2D(GL_TEXTURE_2D,0,4,bmpinfo.bmiHeader.biWidth,bmpinfo.bmiHeader.biHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,image);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,bmpinfo.bmiHeader.biWidth,bmpinfo.bmiHeader.biHeight,GL_RGBA,GL_UNSIGNED_BYTE,image);
	//							 4					RGBA
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
}
void LoadTexture(char *fileName,char *alphaFileName,GLuint& id,float a)
{
	unsigned char *image;         //�o��ϮסA�w�g���OBMP�ϤF�A�O�ઽ����OpenGL�ϥΪ���ƤF
	BITMAPINFO bmpinfo;            //�ΨӦs��HEADER��T
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id);

	image = TransIntoRGBA(fileName,alphaFileName, &bmpinfo,a);

	//glTexImage2D(GL_TEXTURE_2D,0,4,bmpinfo.bmiHeader.biWidth,bmpinfo.bmiHeader.biHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,image);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,bmpinfo.bmiHeader.biWidth,bmpinfo.bmiHeader.biHeight,GL_RGBA,GL_UNSIGNED_BYTE,image);
	//							 4					RGBA
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
}
unsigned char *LoadBitmapFile(char *fileName, BITMAPINFO *bitmapInfo)
{
	FILE				*fp;
	BITMAPFILEHEADER	bitmapFileHeader;	// Bitmap file header
	unsigned char 		*bitmapImage;		// Bitmap image data
	unsigned int		lInfoSize;			// Size of information
	unsigned int		lBitSize;			// Size of bitmap
	unsigned char change;
	int pixel;
	int p=0;
	fp = fopen(fileName, "rb");
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);			//Ū�� bitmap header

	lInfoSize = bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);	//Info��size
	fread(bitmapInfo, lInfoSize, 1, fp);


	lBitSize = bitmapInfo->bmiHeader.biSizeImage*3;						//�t�m�O����
	bitmapImage = new BYTE[lBitSize];
	fread(bitmapImage, 1, lBitSize, fp);								//Ū���v����

	fclose(fp);

	//���ɶǦ^bitmapImage���ܡA�C��|�OBGR���ǡA�U���j��|�ﶶ�Ǭ�RGB 
	pixel = (bitmapInfo->bmiHeader.biWidth)*(bitmapInfo->bmiHeader.biHeight);

	for( int i=0 ; i<pixel ; i++, p+=3 )
	{
		//�洫bitmapImage[p]�MbitmapImage[p+2]����
		change = bitmapImage[p];
		bitmapImage[p] = bitmapImage[p+2];
		bitmapImage[p+2]  = change;
	}

	return bitmapImage;
}
unsigned char *TransIntoRGBA(char *fileName,char *alphaFileName, BITMAPINFO *bitmapInfo)
{
	unsigned char *rgb;         //�x�s��qbmp���Ӫ�RGB��
	unsigned char *rgba;      //�x�s�̫᧹����RGBA�Ϩæ^��
	unsigned char *alpha;
	int x,y,p;

	unsigned char *rgb_ptr;
	unsigned char *rgba_ptr;

	rgb = LoadBitmapFile(fileName, bitmapInfo);
	alpha = LoadBitmapFile(alphaFileName,bitmapInfo);
	rgba= (unsigned char *)malloc(bitmapInfo->bmiHeader.biWidth*bitmapInfo->bmiHeader.biHeight*4*sizeof(unsigned char));

	for( y=0,p=0 ; y<bitmapInfo->bmiHeader.biHeight ; y++ )
	{
		rgb_ptr = rgb+y*bitmapInfo->bmiHeader.biWidth*3;
		rgba_ptr= rgba+y*bitmapInfo->bmiHeader.biWidth*4;


		for( x=0 ; x<bitmapInfo->bmiHeader.biWidth ; x++, rgb_ptr+=3, rgba_ptr+=4,p+=3 )
		{
			rgba_ptr[0]=rgb_ptr[0];
			rgba_ptr[1]=rgb_ptr[1];
			rgba_ptr[2]=rgb_ptr[2];
			rgba_ptr[3]=alpha[p]*0.85;
			/*
			if ( rgba_ptr[0]==255 && rgba_ptr[1]==255 && rgba_ptr[2]==255)
				rgba_ptr[3]=0;//�z���� 0���z��100%
			else
				rgba_ptr[3]=255;//�z����
			*/
		}
	}
	free(rgb);
	return rgba;
}
unsigned char *TransIntoRGBA(char *fileName,char *alphaFileName, BITMAPINFO *bitmapInfo,float a)
{
	unsigned char *rgb;         //�x�s��qbmp���Ӫ�RGB��
	unsigned char *rgba;      //�x�s�̫᧹����RGBA�Ϩæ^��
	unsigned char *alpha;
	int x,y,p;

	unsigned char *rgb_ptr;
	unsigned char *rgba_ptr;

	rgb = LoadBitmapFile(fileName, bitmapInfo);
	alpha = LoadBitmapFile(alphaFileName,bitmapInfo);
	rgba= (unsigned char *)malloc(bitmapInfo->bmiHeader.biWidth*bitmapInfo->bmiHeader.biHeight*4*sizeof(unsigned char));

	for( y=0,p=0 ; y<bitmapInfo->bmiHeader.biHeight ; y++ )
	{
		rgb_ptr = rgb+y*bitmapInfo->bmiHeader.biWidth*3;
		rgba_ptr= rgba+y*bitmapInfo->bmiHeader.biWidth*4;


		for( x=0 ; x<bitmapInfo->bmiHeader.biWidth ; x++, rgb_ptr+=3, rgba_ptr+=4,p+=3 )
		{
			rgba_ptr[0]=rgb_ptr[0];
			rgba_ptr[1]=rgb_ptr[1];
			rgba_ptr[2]=rgb_ptr[2];
			rgba_ptr[3]=alpha[p]*a;
			/*
			if ( rgba_ptr[0]==255 && rgba_ptr[1]==255 && rgba_ptr[2]==255)
				rgba_ptr[3]=0;//�z���� 0���z��100%
			else
				rgba_ptr[3]=255;//�z����
			*/
		}
	}
	free(rgb);
	return rgba;
}