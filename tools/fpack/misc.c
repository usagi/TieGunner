//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  < fpack >
//   2004 ASTROLL Inc. All Rights Reserved.
//--------------------------------------------------------------
//
//	雑多な処理
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  $Id: misc.c,v 1.1.1.1 2004/02/09 08:13:36 nishi Exp $
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/********************************************/
/*           インクルードファイル           */
/********************************************/
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "default.h"
#include "misc.h"


/********************************************/
/*             定数・マクロ宣言             */
/********************************************/


/********************************************/
/*                構造体宣言                */
/********************************************/


/********************************************/
/*                 変数宣言                 */
/********************************************/


/********************************************/
/*                プログラム                */
/********************************************/

//==============================================================
void strCopyLength(char *dst, int len, const char *src)
//--------------------------------------------------------------
// 指定長の文字列コピー
// ※(指定長 - 1) に必ず '\0' を入れます
//--------------------------------------------------------------
// in:	str   = 検索する文字列
//		fname = 検索対象
//--------------------------------------------------------------
// out:	str が一致した次のポインタ(見つからなければそのまま fname を返す)
//==============================================================
{
	*(dst + len - 1) = '\0';
	strncpy(dst, src, len);
}

//==============================================================
void putvalue(unsigned char *p, int a)
//--------------------------------------------------------------
// エンディアンに依存しないで 32bit 整数を取り出す
//--------------------------------------------------------------
// in:	p = 格納先ポインタ
//		a = データ
//--------------------------------------------------------------
// out:	なし
//==============================================================
{
	*(p + 0) = a >> 24;
	*(p + 1) = a >> 16;
	*(p + 2) = a >> 8;
	*(p + 3) = a;
}

//==============================================================
int getvalue(unsigned char *p)
//--------------------------------------------------------------
// エンディアンに依存しないで 32bit 整数を格納する
//--------------------------------------------------------------
// in:	p = 格納先ポインタ
//--------------------------------------------------------------
// out:	データ
//==============================================================
{
	int a;

	a = *(p + 0) << 24;
	a |= *(p + 1) << 16;
	a |= *(p + 2) << 8;
	a |= *(p + 3);

	return a;
}

//==============================================================
int fileExist(char *file)
//--------------------------------------------------------------
// ファイルがあるかチェック
//--------------------------------------------------------------
// in:	file = ファイル名
//--------------------------------------------------------------
// out:	TRUE = ファイルあり
//==============================================================
{
	FILE *fp;
	int res = FALSE;

	fp = fopen(file, "rb");
	if(fp)
	{
		res = TRUE;
		fclose(fp);
	}

	return res;
}

//==============================================================
int getFileSize(char *file)
//--------------------------------------------------------------
// ファイルサイズを取得する
//--------------------------------------------------------------
// in:	file = ファイル名
//--------------------------------------------------------------
// out:	ファイルサイズ
//==============================================================
{
	FILE *fp;
	int l;

	fp = fopen(file, "rb");
	if(fp == NULL)
		return 0;

	fseek(fp, 0, SEEK_END);
	l = ftell(fp);
	fclose(fp);

	return l;
}

//==============================================================
int getLine(FILE *ifp, char *top, int lim)
//--------------------------------------------------------------
// ファイルからの一行入力
//--------------------------------------------------------------
// in:	ifp = ファイルハンドル
//		top = 出力ポインタ
//		lim = 最大文字長
//--------------------------------------------------------------
// out:	取り込んだ文字数(0 ファイル終端)
//==============================================================
{
	char	*ptr;
	volatile int c;

	ptr = top;
	while(--lim > 0 && (c = fgetc(ifp)) != EOF)
	{
		if(c == 0x0a)
			break;
		else
		if(c == 0x0d)
		{
			c = fgetc(ifp);
			if(c != 0x0a)
				ungetc(c, ifp);
			break;
		}
		else
		{
			*ptr++ = c;
		}
	}
	*ptr++ = '\0';
	if(c == EOF)
		return 0;
	else
		return ptr - top;
}

//==============================================================
char **separateString(char *in, char *ss, char *ns, int *cnt)
//--------------------------------------------------------------
// 指定文字で区切られたストリングを分離してリストを返す
//--------------------------------------------------------------
// in:	in = 入力文字列ポインタ
//		ss = 分離するキャラクター・キーのリスト (Ex: ",/")
//		ns = 無視するキャラクター・キーのリスト (Ex: "\t ")
//--------------------------------------------------------------
// out:	取り込んだリスト
//==============================================================
{
	int	a, b, i, j, sc, nc;
	char	*top, *p, **pp, *s;

	if(in==NULL || ss==NULL)
		return NULL;
	sc = strlen(ss);
	if(sc == 0)
		return NULL;

	if(ns)
		nc = strlen(ns);
	else
		nc = 0;

	p = top = (char *)malloc(strlen(in) + 1);
	strcpy(top, in);
	while((a = *p)!=0)
	{
		i = 0;
		while(i < nc)
		{
			// 無視するキャラクターをスキャンする
			//------------------------------------
			if(a==ns[i])
				goto SeparateNext;
			i++;
		}
		for(i=0; i<sc; ++i)
		{
			// 分離するキャラクターを統合
			//----------------------------
			if(a==ss[i])
			{
				a = ss[0];
				break;
			}
		}
		if(a >= 0) *p = a;
SeparateNext:
		p++;
	}

	// リストの数をカウント
	//----------------------
	i = 0;
	b = ss[0];									// 分離キャラクターで初期化
	p = top;
	while((a = *p)!=0)
	{
		if(a!=ss[0] && b==ss[0])
			i++;
		b = a;
		p++;
	}
	if(cnt)
		*cnt = i;

	pp = (char **)malloc(sizeof(char *) * (i + 1));

	i = 0;
	b = ss[0];
	p = top;
	while((a = *p)!=0)
	{
		if(a!=ss[0] && b==ss[0])
		{
			s = strchr(p, ss[0]);
			if(s)
				j = s - p;
			else
				j = strlen(p);

			s = (char *)malloc(j + 1);
			strncpy(s, p, j);
			s[j] = 0;
			pp[i] = s;
			i++;
		}
		b = a;
		p++;
	}
	pp[i] = NULL;
	free(top);

	return pp;
}

//==============================================================
void freeStringList(char **top)
//--------------------------------------------------------------
// 文字列リストを開放
//--------------------------------------------------------------
// in:	top = ポインタ
//--------------------------------------------------------------
// out:	なし
//==============================================================
{
	char *p, **pp;

	pp = top;
	while((p = *pp++)!=NULL)
		free(p);
	free(top);
}

//==============================================================
char *copyText(const char *text)
//--------------------------------------------------------------
// 文字列をコピー
//--------------------------------------------------------------
// in:	text = コピー元
//--------------------------------------------------------------
// out:	コピーした文字列へのポインタ
//==============================================================
{
	char *p;

	if(text == NULL)
		return NULL;

	p = (char *)malloc(strlen(text) + 1);
	strcpy(p, text);

	return p;
}

//==============================================================
void freeText(char *text)
//--------------------------------------------------------------
// CopyText() で取得したポインタの破棄
//--------------------------------------------------------------
// in:	text = 破棄するポインタ
//--------------------------------------------------------------
// out:	なし
//==============================================================
{
	if(text)
		free(text);
}

