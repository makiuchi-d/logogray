/*====================================================================
*	ロゴパターン			logo.h
* 
* 
* 
* [ロゴデータファイル構造]
* 
* 	"logo file x.xx\n"	// ファイルヘッダ文字列：バージョン情報とか(31byte)
* 	+----
* 	|	ファイルに含まれるロゴデータの数(1byte)
* 	+----
* 	|	LOGO_HEADER		// データヘッダ
* 	+----
* 	|
* 	:	LOGO_PIXEL[h*w]	// ピクセル情報：サイズはLOGO_HEADERのw,hから算出
* 	:
* 	+----
* 	|	LOGO_HEADER
* 	+----
* 	|
* 	:	LOGO_PIXEL[h*w]
* 	:
* 
*===================================================================*/
#ifndef ___LOGO_H
#define ___LOGO_H

/* ロゴファイルヘッダ
* 	31BYTEの文字列
* 	データ数 1BYTE
*/
#define LOGO_FILE_HEADER_STR "<logo data file ver0.1>\0\0\0\0\0\0\0\0\0\0\0"
#define LOGO_FILE_HEADER_STR_SIZE  31

typedef struct {
	char          str[LOGO_FILE_HEADER_STR_SIZE];
	unsigned char logonum;
} LOGO_FILE_HEADER;


/* ロゴデータ最大サイズ：
* 		ロゴデータをプロファイルに保存しないようにしたため、
* 		サイズ制限は実質なくなった
*/
#define LOGO_MAXPIXEL (21840)
#define LOGO_MAXSIZE  (0x40000)

/* 不透明度最大値 */
#define LOGO_MAX_DP   1000

/* ロゴ名最大文字数（終端\0含む） */
#define LOGO_MAX_NAME 32

/*--------------------------------------------------------------------
*	LOGO_HEADER 構造体
*		ロゴの基本的な情報を記録
*-------------------------------------------------------------------*/
typedef struct {
	char     name[LOGO_MAX_NAME]; 	/* 名称         */
	short    x, y;      			/* 基本位置     */
	short    h, w;      			/* ロゴ高さ・幅 */
	int      reserve[2];			/* 拡張用に予約 */
} LOGO_HEADER;

/*--------------------------------------------------------------------
*	LOGO_PIXEL 構造体
*		ロゴの各ピクセルごとの情報を記録
*-------------------------------------------------------------------*/
typedef struct {
	short dp_y;		/* 不透明度（輝度）            */
	short y;		/* 輝度              0〜4096   */
	short dp_cb;	/* 不透明度（青）              */
	short cb;		/* 色差（青）    -2048〜2048   */
	short dp_cr;	/* 不透明度（赤）              */
	short cr;		/* 色差（赤）    -2048〜2048   */
} LOGO_PIXEL;


/*--------------------------------------------------------------------
*	ロゴデータ全体のサイズ
*-------------------------------------------------------------------*/
#define LOGO_DATASIZE(ptr)  \
	(sizeof(LOGO_HEADER)+((LOGO_HEADER *)ptr)->h*((LOGO_HEADER *)ptr)->w*sizeof(LOGO_PIXEL))

/*--------------------------------------------------------------------
*	ロゴデータのサイズ（ヘッダ無し）
*-------------------------------------------------------------------*/
#define LOGO_PIXELSIZE(ptr)  \
	(((LOGO_HEADER *)ptr)->h*((LOGO_HEADER *)ptr)->w*sizeof(LOGO_PIXEL))


#endif
