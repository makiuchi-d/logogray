#include <stdio.h>
#include "logo.h"
#include <windows.h>


int main(int argc, char *argv[])
{
	FILE *fp,*fpw;
	char output[MAX_PATH];
	int i;

	LOGO_FILE_HEADER lfh;
	LOGO_HEADER lh;
	LOGO_PIXEL lp;

	if(argc<2){
		puts("USEAGE: LOGOGRAY <LogoDataFile(*.lgd)>");
		return 0;
	}

	sprintf(output,"%s_gray.lgd",argv[1]);

	if((fp=fopen(argv[1],"rb"))==NULL){
		puts("�ǂݍ��݃t�@�C�����J���܂���");
		return 0;
	}
	if((fpw=fopen(output,"wb"))==NULL){
		puts("�o�̓t�@�C�����J���܂���");
		fclose(fp);
		return 0;
	}

	if(fread(&lfh,sizeof(lfh),1,fp)!=1){
		puts("LOGO_FILE_HEADER�̓ǂݍ��݂Ɏ��s���܂���");
		fclose(fp);
		fclose(fpw);
		remove(output);
		return 0;
	}

	printf("DataFileVersion: %s\n",lfh.str);

	if(fwrite(&lfh,sizeof(lfh),1,fpw)!=1){
		puts("�������݂Ɏ��s���܂���");
		fclose(fp);
		fclose(fpw);
		remove(output);
		return 0;
	}

	if(fread(&lh,sizeof(lh),1,fp)!=1){
		puts("LOGO_HEADER�̓ǂݍ��݂Ɏ��s���܂���");
		fclose(fp);
		fclose(fpw);
		remove(output);
		return 0;
	}
	printf("LogoName: %s\n\tx,y = %d,%d\th,w = %d,%d\n",lh.name,lh.x,lh.y,lh.h,lh.w);

	if(fwrite(&lh,sizeof(lh),1,fpw)!=1){
		puts("LOGO_HEADER�̏������݂Ɏ��s���܂���");
		fclose(fp);
		fclose(fpw);
		remove(output);
		return 0;
	}

	for( i=lh.h*lh.w; i; --i){
		if(fread(&lp,sizeof(lp),1,fp)!=1){
			puts("LOGO_PIXEL�̓ǂݍ��݂Ɏ��s���܂����B");
			fclose(fp);
			fclose(fpw);
			remove(output);
			return 0;
		}
		// �P���ɐF�������O�ɂ���
		lp.cb = 0;
		lp.cr = 0;
		if(fwrite(&lp,sizeof(lp),1,fpw)!=1){
			puts("LOGO_PIXEL�̏������݂Ɏ��s���܂����B");
			fclose(fp);
			fclose(fpw);
			remove(output);
			return 0;
		}
	}

	puts("�������܂���");

	return 0;
}

