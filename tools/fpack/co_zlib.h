//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  < TEST >
//
//--------------------------------------------------------------
//
//	zlib �������܂�
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  $Id: co_hash.h,v 1.1 2004/02/09 10:01:26 nishi Exp $
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/*

	zlib �𗘗p�����f�[�^�̈��k/�W�J���s���܂��B

	���k���ꂽ�f�[�^�̐擪�S�o�C�g�ɁA���k�O�ƈ��k��̃f�[�^�T�C�Y��
	�L�^����Ă��܂��B

*/

//==============================================================
#ifndef _CO_ZLIB_H_
#define _CO_ZLIB_H_
//==============================================================
#ifdef __cplusplus
extern              "C"
{
#endif

/********************************************/
/*             �萔�E�}�N���錾             */
/********************************************/


/********************************************/
/*                �\���̐錾                */
/********************************************/


/********************************************/
/*              �O���[�o���ϐ�              */
/********************************************/


/********************************************/
/*              �O���[�o���֐�              */
/********************************************/
extern void *ZlibEncode(void *ptr, int size);
extern void *ZlibDecode(void *ptr, int size);

extern int ZlibEncodeSize(void *ptr);
extern int ZlibDecodeSize(void *ptr);


#ifdef __cplusplus
}
#endif
//==============================================================
#endif				// #ifndef _CO_ZLIB_H_
//==============================================================
