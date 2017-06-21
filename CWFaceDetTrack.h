#ifndef CW_FACEDETTRACK_H_
#define CW_FACEDETTRACK_H_
#include "CWFaceDetTrackDef.h"

#ifdef CW_FACE_DET_TRACK_EXPORTS_C
#define CW_DET_TRACK_C_API  __declspec(dllexport)
#else
#define CW_DET_TRACK_C_API
#endif

#if defined (__cplusplus)
extern "C" {
#endif	

	/**
	 *
	 * ���ݴ������Ȩ�뼰ģ���ļ�����������������.
	 * ���룺
	 *		pLicence               - ��Ȩ��.
	 *      modelMode              - ����ģ�ͷ�ʽ.
	 *		pFaceDetectFile        - �������ģ���ļ�.
	 *		pFaceKeyPtDetFile      - �ؼ�����ģ���ļ�.
	 *		pFaceKeyPtTrackFile    - �ؼ������ģ���ļ�.
	 *		pFaceQualityFile       - ������������ģ���ļ�.
	 *		pFaceLivenessFile      - ����ģ���ļ�.
	 * �����
	 *      errCode - �ɹ�����CW_FACE_OK��ʧ�ܷ�������.
	 * ����ֵ��
	 *		�������� - �ɹ����ؾ����ʧ�ܷ���0.
	 * 
	 * ע���������ǽ����ڴ����ģ�ͣ�ֻ������ǰerrCode����������
	 *           �������в�����Ҫ����.
	 *      
	 */
CW_DET_TRACK_C_API 
void* cwCreateDetector(cw_face_errcode_t* errCode, 
					 cw_model_mode_t modelMode,
					 const char* pLicence,
					 const char* pFaceDetectFile = 0,		
					 const char* pFaceKeyPtDetFile = 0,	
					 const char* pFaceKeyPtTrackFile = 0,
					 const char* pFaceQualityFile = 0,	
					 const char* pFaceLivenessFile = 0);		

	/**
	 * �ͷż����
	 * ���룺 
	 *		pDetector - ��������
	 * �����
	 *      ��
	 * ����ֵ��
	 *		��
	 */
CW_DET_TRACK_C_API 
void cwReleaseDetector(void* pDetector);

	/**
	 * ��ȡ���������
	 * ���룺
	 *		pDetector - ��������
	 * �����
	 *      param - ���������
	 * ����ֵ��
	 *		cw_face_errcode_t - �ɹ�����CW_FACE_OK��ʧ�ܷ�������
	 */
CW_DET_TRACK_C_API
cw_face_errcode_t cwGetParam(void* pDetector, cw_face_param_t* param);


	/**
	 * ���ü���������������ȵ���cwGetParam(pDet,&params)��ʹ�ô˺�����
	 * ���룺
	 *      pDetector - ��������
	 *		param - ����
	 * �����
	 *      ��
	 * ����ֵ��
	 *		cw_face_errcode_t - �ɹ�����CW_FACE_OK��ʧ�ܷ�������	
	 */
CW_DET_TRACK_C_API
cw_face_errcode_t cwSetParam(void* pDetector, const cw_face_param_t* param);


	/**
	 * ���������ٽӿ�
	 * ���룺
	 *      pDetector - ��������
	 *		frameImg - �����ͼ��
	 *		buffLen - ��ż����pFaceBuffer�����Ԫ�ظ���
	 *		op - ������
	 *      to_next_stage 1:ͨ����-1;ʧ�ܣ�0:�ȴ�
	 * �����
	 *		pFaceBuffer - ��ż����������
	 *		nFace - ʵ�ʱ����͸��ٵ���������
	 * ����ֵ��
	 *		cw_face_errcode_t - �ɹ�����CW_FACE_OK��ʧ�ܷ�������	
	 */
CW_DET_TRACK_C_API 
cw_face_errcode_t cwFaceDetectTrack(void* pDetector,				
									cw_image_t* frameImg,			
									cw_face_t* pFaceBuffer,			
									int buffLen,					
									int* nFace,	
									int* to_next_stage,
									int op = CW_FACE_DET);
	

	/**
	 * ���״̬���ýӿ�
	 * ���룺
	 *		pDetector - ��������
	 * �����
	 *      ��
	 * ����ֵ��
	 *		cw_face_errcode_t - �ɹ�����CW_FACE_OK��ʧ�ܷ�������
	 */
CW_DET_TRACK_C_API 
cw_face_errcode_t cwResetLiving(void* pDetector);
    
//CW_DET_TRACK_C_API
//cw_face_errcode_t cwResetLianYou(void* pDetector);


	/**
	 * ��ʼѡͼ�ӿڣ�һ��������ĳһ���嶯�����ʱ�����һ��
	 * ���룺
	 *		pDetector - ��������
	 *      op        - ѡͼ��ǣ���ѡʲô���嶯���µ�ͼ���������������һ�£�����32,64,128,256,512,
	 *                  1024���α�ʾ̧ͷ����ͷ����תͷ����תͷ�����졢գ�ۣ�����������Ч
	 * �����
	 *      ��
	 * ����ֵ��
	 *		cw_face_errcode_t - �ɹ�����CW_FACE_OK��ʧ�ܷ�������
	 */
CW_DET_TRACK_C_API 
cw_face_errcode_t cwStartFaceSelect(void* pDetector,
									int op=0);


	/**
	 * ����ѡͼ�ӿڣ�������ѡͼ�����һ���ڽ���ĳһ���嶯�����ʱ�����һ��
	 * ���룺
	 *		pDetector  - ��������
	 * �����
	 *      pFaceLiving - ѡͼ���(��ɫ��������ͼ)
	 * ����ֵ��
	 *		cw_face_errcode_t - �ɹ�����CW_FACE_OK��ʧ�ܷ�������
	 */
CW_DET_TRACK_C_API 
cw_face_errcode_t cwFinishFaceSelect(void* pDetector,
									 cw_face_living_t *pFaceLiving);

	/**
	 * ��ȡʣ���ͼ��Ϣ(ÿ�ε���cwResetLiving(void* pDetector)֮ǰ���ô˺���)
	 * ���룺
	 *      pDetector - ��������
	 *		nBuffer_in - reportImgBuffers�����Ԫ��Ԥ�����(��Ԥ��50����).
	 * �����
	 *		reportImgBuffers - ��ȡ����ʣ���ͼ��Ϣ����(��Ԥ��50����).
	 *		nBuffer_out - ʵ�ʻ�ȡ����ʣ���ͼ�ĸ���.
	 * ����ֵ��
	 *		cw_face_errcode_t - �ɹ�����CW_FACE_OK��ʧ�ܷ�������	
	 */
CW_DET_TRACK_C_API 
cw_face_errcode_t cwGetReportImageRemain(void* pDetector,				
									cw_face_report_image_t* reportImgBuffers,					
									int nBuffer_in,					
									int* nBuffer_out);		


/**
	* ��ȡ�������ͼ��͹ؼ�����Ϣ
	* return��
	*		�洢����ͼ��͹ؼ���Ľṹ�壬����Ϊ4֡��������˵Ŀ�������֡
	*
	*/

CW_DET_TRACK_C_API
cw_face_errcode_t cwGetLivingImageSample(void* pDetector
										 , cw_living_image_frame_t* livingImageBuffer);
//	/**
//	 * �汾��Ϣ����
//	 * ���룺
//	 *		��
//	 * �����
//	 *      ��
//	 * ����ֵ��
//	 *		�汾��Ϣ
//	 */
CW_DET_TRACK_C_API
const char* cwGetVersionInfo(void* pDetector); 

//	/**
//	 * �ͷŴ�ͼ�ڴ�
//	 * ���룺
//	 *		��
//	 * �����
//	 *      ��
//	 * ����ֵ��
//	 *		�汾��Ϣ
//	 */
CW_DET_TRACK_C_API
void releaseReportImageMem(void* pDetector); 

#if defined (__cplusplus)
}
#endif

#endif   // CW_FACEDETTRACK_H_
