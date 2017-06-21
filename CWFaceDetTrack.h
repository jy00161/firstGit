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
	 * 根据传入的授权码及模型文件创建人脸活体检测器.
	 * 输入：
	 *		pLicence               - 授权码.
	 *      modelMode              - 加载模型方式.
	 *		pFaceDetectFile        - 人脸检测模型文件.
	 *		pFaceKeyPtDetFile      - 关键点检测模型文件.
	 *		pFaceKeyPtTrackFile    - 关键点跟踪模型文件.
	 *		pFaceQualityFile       - 人脸质量评估模型文件.
	 *		pFaceLivenessFile      - 活体模型文件.
	 * 输出：
	 *      errCode - 成功返回CW_FACE_OK，失败返回其他.
	 * 返回值：
	 *		检测器句柄 - 成功返回句柄，失败返回0.
	 * 
	 * 注意事项：如果是仅从内存加载模型，只需设置前errCode三个参数，
	 *           否则所有参数都要设置.
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
	 * 释放检测器
	 * 输入： 
	 *		pDetector - 检测器句柄
	 * 输出：
	 *      无
	 * 返回值：
	 *		无
	 */
CW_DET_TRACK_C_API 
void cwReleaseDetector(void* pDetector);

	/**
	 * 获取检测器参数
	 * 输入：
	 *		pDetector - 检测器句柄
	 * 输出：
	 *      param - 检测器参数
	 * 返回值：
	 *		cw_face_errcode_t - 成功返回CW_FACE_OK，失败返回其他
	 */
CW_DET_TRACK_C_API
cw_face_errcode_t cwGetParam(void* pDetector, cw_face_param_t* param);


	/**
	 * 设置检测器参数（必须先调用cwGetParam(pDet,&params)再使用此函数）
	 * 输入：
	 *      pDetector - 检测器句柄
	 *		param - 参数
	 * 输出：
	 *      无
	 * 返回值：
	 *		cw_face_errcode_t - 成功返回CW_FACE_OK，失败返回其他	
	 */
CW_DET_TRACK_C_API
cw_face_errcode_t cwSetParam(void* pDetector, const cw_face_param_t* param);


	/**
	 * 人脸检测跟踪接口
	 * 输入：
	 *      pDetector - 检测器句柄
	 *		frameImg - 被检测图像
	 *		buffLen - 存放检测结果pFaceBuffer数组的元素个数
	 *		op - 操作码
	 *      to_next_stage 1:通过；-1;失败；0:等待
	 * 输出：
	 *		pFaceBuffer - 存放检测结果的数组
	 *		nFace - 实际被检测和跟踪到的人脸数
	 * 返回值：
	 *		cw_face_errcode_t - 成功返回CW_FACE_OK，失败返回其他	
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
	 * 检测状态重置接口
	 * 输入：
	 *		pDetector - 检测器句柄
	 * 输出：
	 *      无
	 * 返回值：
	 *		cw_face_errcode_t - 成功返回CW_FACE_OK，失败返回其他
	 */
CW_DET_TRACK_C_API 
cw_face_errcode_t cwResetLiving(void* pDetector);
    
//CW_DET_TRACK_C_API
//cw_face_errcode_t cwResetLianYou(void* pDetector);


	/**
	 * 开始选图接口，一般在启动某一活体动作检测时候调用一次
	 * 输入：
	 *		pDetector - 检测器句柄
	 *      op        - 选图标记，即选什么活体动作下的图，跟跟活体操作码一致，其中32,64,128,256,512,
	 *                  1024依次表示抬头、点头、左转头、右转头、张嘴、眨眼，其他数字无效
	 * 输出：
	 *      无
	 * 返回值：
	 *		cw_face_errcode_t - 成功返回CW_FACE_OK，失败返回其他
	 */
CW_DET_TRACK_C_API 
cw_face_errcode_t cwStartFaceSelect(void* pDetector,
									int op=0);


	/**
	 * 结束选图接口，并返回选图结果，一般在结束某一活体动作检测时候调用一次
	 * 输入：
	 *		pDetector  - 检测器句柄
	 * 输出：
	 *      pFaceLiving - 选图结果(彩色对齐人脸图)
	 * 返回值：
	 *		cw_face_errcode_t - 成功返回CW_FACE_OK，失败返回其他
	 */
CW_DET_TRACK_C_API 
cw_face_errcode_t cwFinishFaceSelect(void* pDetector,
									 cw_face_living_t *pFaceLiving);

	/**
	 * 获取剩余存图信息(每次调用cwResetLiving(void* pDetector)之前调用此函数)
	 * 输入：
	 *      pDetector - 检测器句柄
	 *		nBuffer_in - reportImgBuffers数组的元素预设个数(可预设50左右).
	 * 输出：
	 *		reportImgBuffers - 获取到的剩余存图信息数组(可预设50左右).
	 *		nBuffer_out - 实际获取到的剩余存图的个数.
	 * 返回值：
	 *		cw_face_errcode_t - 成功返回CW_FACE_OK，失败返回其他	
	 */
CW_DET_TRACK_C_API 
cw_face_errcode_t cwGetReportImageRemain(void* pDetector,				
									cw_face_report_image_t* reportImgBuffers,					
									int nBuffer_in,					
									int* nBuffer_out);		


/**
	* 获取最佳人脸图像和关键点信息
	* return：
	*		存储人脸图像和关键点的结构体，长度为4帧，传给后端的可以用两帧
	*
	*/

CW_DET_TRACK_C_API
cw_face_errcode_t cwGetLivingImageSample(void* pDetector
										 , cw_living_image_frame_t* livingImageBuffer);
//	/**
//	 * 版本信息函数
//	 * 输入：
//	 *		无
//	 * 输出：
//	 *      无
//	 * 返回值：
//	 *		版本信息
//	 */
CW_DET_TRACK_C_API
const char* cwGetVersionInfo(void* pDetector); 

//	/**
//	 * 释放存图内存
//	 * 输入：
//	 *		无
//	 * 输出：
//	 *      无
//	 * 返回值：
//	 *		版本信息
//	 */
CW_DET_TRACK_C_API
void releaseReportImageMem(void* pDetector); 

#if defined (__cplusplus)
}
#endif

#endif   // CW_FACEDETTRACK_H_
