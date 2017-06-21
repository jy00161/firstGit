#ifndef CW_FACE_COMMON_DEFINE_H_
#define CW_FACE_COMMON_DEFINE_H_


	// ��⿪��ѡ��
#define CW_FACE_DET					0						// (1<<0)����������⣬��������������λ��
#define CW_FACE_TRACK				2						// (1<<1)�����������٣��������������ٵ�ID
#define CW_FACE_KEYPT				4						// (1<<2)���������ؼ����⣬�����������ϵĹؼ���������Ϣ
#define CW_FACE_ALIGN				8						// (1<<3)��������ͼ����룬�����ض���������ͼ�񣨿�ֱ������������ȡ�ӿڣ����ؼ�����Ϣ
#define CW_FACE_QUALITY				16						// (1<<4)���������������֣����������������֡��ؼ�����Ϣ(�˰汾:Ҫ���������֣��벻Ҫ�򿪻��忪��)
#define CW_FACE_LIVENESS_HEAD_UP	32						// (1<<5)������: ̧ͷ
#define CW_FACE_LIVENESS_HEAD_DOWN	64						// (1<<6)������: ��ͷ
#define CW_FACE_LIVENESS_HEAD_LEFT	128						// (1<<7)������: ����תͷ
#define CW_FACE_LIVENESS_HEAD_RIGHT 256						// (1<<8)������: ����תͷ
#define CW_FACE_LIVENESS_MOUTH		512						// (1<<9)������: �첿
#define CW_FACE_LIVENESS_EYE		1024					// (1<<10)������: �۾�
#define CW_FACE_LIVENESS_ATTACK		2048					// (1<<11)�����⣺��������
#define CW_FACE_LIVENESS			4064					// �����⣺�������ֻ��忪���ۺ�(CW_FACE_LIVENESS_HEAD_UP | CW_FACE_LIVENESS_HEAD_DOWN | CW_FACE_LIVENESS_HEAD_LEFT | CW_FACE_LIVENESS_HEAD_RIGHT | CW_FACE_LIVENESS_MOUTH | CW_FACE_LIVENESS_EYE | CW_FACE_LIVENESS_ATTACK)

#define LIVE_DONOTHIN_T  0
#define	LIVE_PREPARE_T	 1 //��Ĭ
#define	LIVE_HEAD_LEFT_T		 2 //��ת
#define	LIVE_HEAD_RIGHT_T		 4 //��ת
#define	LIVE_EYE_BLINK_T	 8 //գ��
#define	LIVE_MOUTH_OPEN_T  16 //����
#define	LIVE_HEAD_UP_T	 32 //̧ͷ
#define	LIVE_HEAD_DOWN_T  64 //��ͷ



// ͨ�ô�����
typedef enum cw_face_errcode 
{ 
	CW_FACE_OK = 0,							//�ɹ� or �Ϸ�

	CW_FACE_FRAME_ERR = 20000,				// ��ͼ�񣬱����ͼ���
	CW_FACE_FORMAT_ERR,						// ͼ���ʽ��֧�֣����粻֧��
	CW_FACE_NO_FACE,                        // û������
	
	CW_FACE_ROI_ERR,						// ROI����ʧ��
	CW_FACE_MINMAX_ERR,						// ��С�����������ʧ��
	CW_FACE_RANGE_ERR,						// ���ݷ�Χ����
	CW_FACE_METHOD_UNAVAILABLE,             // ������Ч

	CW_FACE_UNAUTHORIZED_ERR,				// δ��Ȩ
	CW_FACE_UNINITIALIZED_ERR,				// ��δ��ʼ��
	CW_FACE_DETECT_MODEL_ERR,				// ���ؼ��ģ��ʧ��
	CW_FACE_KEYPT_MODEL_ERR,				// ���عؼ���ģ��ʧ��
	CW_FACE_QUALITY_MODEL_ERR,				// ������������ģ��ʧ��
	CW_FACE_LIVENESS_MODEL_ERR,				// ���ػ�����ģ��ʧ��

	CW_FACE_DET_ERR,						// ���ʧ��
	CW_FACE_KEYPT_ERR,						// ��ȡ�ؼ���ʧ��
	CW_FACE_ALIGN_ERR,						// ��������ʧ��
	CW_FACE_QUALITY_ERR,					// ��������ʧ��
	CW_FACE_LIVENESS_ERR,                   // �������
} cw_face_errcode_t; 

// �������־��
typedef enum cw_face_liveness_code
{
	CW_FACE_LIVENESS_OK = 0,				// ����������Ч
	CW_FACE_LIVENESS_NO_INFO=21000,         // ����������Ч
} cw_face_liveness_code_t;

// ѡͼ��־��
typedef enum cw_face_liveness_select_code
{
	CW_FACE_LIVENESS_SELECT_OK = 0,				  // ѡͼ�ɹ�
	CW_FACE_LIVENESS_SELECT_RUNNING = 21050,      // δ��ѡͼ��ԭ������ѡͼ��
	CW_FACE_LIVENESS_SELECT_NONE,                 // δ��ѡͼ��ԭ��ѡͼ��δ��ʼ
	CW_FACE_LIVENESS_SELECT_TIMEOUT,              // δ��ѡͼ��ԭ�򣺳�ʱ
	CW_FACE_LIVENESS_SELECT_UNKNOWN,              // δ��ѡͼ��ԭ��δ֪
}cw_face_liveness_select_code_t;

// ģ��ѡ��ʽ
typedef enum cw_model_mode
{
	CW_MODEL_FILE=0,                        // �ļ���ʽ
	CW_MODEL_MEMORY,                        // �ڴ淽ʽ
	CW_MODEL_FILE_MEMORY                    // �ļ����ڴ淽ʽ������Ч��
}cw_model_mode_t;

// �ӿڲ�����ע�⣺���в���û���ر���������£����Խ�磬�㷨���Զ���������ֵ��

typedef struct cw_face_param
{
	int roiX;								// ���ROI, Ĭ����֡ͼ��0, 0, 0, 0
	int roiY;
	int roiWidth;
	int roiHeight;
	
	int maxFaceNumPerImg;					// ÿ֡�������������С1��Ĭ��5.

	int minSize;							// �����ߴ緶Χ��Ĭ��[100,400],�������÷�Χ[30,1500].��С��������96ʱ��perfmonLevel���������6
	int maxSize;

	int globleDetFreq;						// ȫ�ּ��Ƶ�ʣ���С1��Ĭ��25

	float minTrackedKeyptScore;				// ���ٹؼ���ʱ����С���Ŷ�,��Χ{0.30-1.0f,1.01f},Ĭ��0.5f;���
	                                        // Ҫ��ʹ�ã������ô�ֵ����1.0��

	int   imageMode;                         // 0-����ͷ��1-��Ƶ��2-ͼ��Ĭ��0.

	int   nMissAllowed;                     // ������������������֡������Χ��0~10����ֵԽ��Խ�ù������������ܹ�����
											// Ĭ��Ϊ0-�������֡.

	int   perfmonLevel;                     // �������ˮƽ����Χ(1~6).����Խ���ٶ�Խ������Ч���������ֺͻ��壩Խ��,��֮��Ȼ.Ĭ��
											// ֵ1����⾲̬ͼ����6

	unsigned int nCpuCores;                 // CPU����������Ӧ�ò㴫�룬Ĭ�ϵ���2. �ڲ������û����õ���ֵ���Զ�������������1~2��
											// ����Ϊ2��3~5����Ϊ3��6�����ϵ���Ϊ4�������ʵ��ϵͳ���øò����������������Ӱ�����ܡ�

	float minLivingBrightness;              // ����������͹��������֣���Χ(0.0f~1.0f),Ĭ��0.280f������
											// �����û����Ǹ����ض�ƽ̨���ж໷������ȷ����

	int  bCollectFrmsLiving;                // �Ƿ��ͼ��0-�������ǡ�Ĭ��0.

	char  imgSavePath[1024];                // ��������ͼƬ���·����Ĭ��Ϊ��ǰ·��.
	int   bSaveImg;                         // �Ƿ񱣴��������:0-�����棬1����, Ĭ��0.
} cw_face_param_t;

// ͼ����ת�Ƕȣ���ʱ�룩
typedef enum cw_image_angle
{ 
	CW_IMG_ANGLE_0 = 0,       
	CW_IMG_ANGLE_90,       
	CW_IMG_ANGLE_180,       
	CW_IMG_ANGLE_270       
} cw_image_angle_t; 

// ͼ����
typedef enum cw_image_mirror
{ 
	CW_IMG_MIRROR_NONE = 0,        // ������  
	CW_IMG_MIRROR_HOR,             // ˮƽ����
	CW_IMG_MIRROR_VER,             // ��ֱ����
	CW_IMG_MIRROR_HV               // ��ֱ��ˮƽ����
} cw_image_mirror_t; 

// ͼ���ʽ
typedef enum cw_image_form 
{ 
	CW_IMG_GRAY8 = 0,
	CW_IMG_BGR888,
	CW_IMG_BGRA8888,
	CW_IMG_YUV420P,
	CW_IMG_NV12, 
	CW_IMG_NV21,
	CW_IMG_BINARY,
} cw_image_form_t; 

// ͼ��
typedef struct cw_image
{
	char* data;								// ͼ������
	int	  dataLen;							// ���ݳ��ȣ��Ƕ�����ͼ�ɲ���
	int   width;							// ��, JPG�ȶ�����ͼ�ɲ���
	int   height;							// ��, JPG�ȶ�����ͼ�ɲ���
	cw_image_form_t format;					// ͼ���ʽ
	cw_image_angle_t angle;					// ��ת�Ƕ�
	cw_image_mirror_t  mirror;              // ����
	int   coordMap;							// �������ϵ��־, 0��������������+����ͼ��Ϊ׼����0:������ǰͼ��Ϊ׼
	int   stageflag;						// ����ͼ�������Ľ׶α�־��ȡֵ��ΧΪ������֤�׶ο���
	long   timestamp;                        // ����ͼ��Ľ���ʱ���
} cw_image_t;

// ������
typedef struct cw_face_rect
{
	int    x;
	int    y;
	int    width;
	int    height;
} cw_face_rect_t;

// ��������
#define CW_ALIGNED_IMAGE_WH 128
#define CW_ALIGNED_IMAGE_CHNS 3
typedef struct cw_face_aligned
{
	char   data[CW_ALIGNED_IMAGE_WH * CW_ALIGNED_IMAGE_WH * CW_ALIGNED_IMAGE_CHNS];		// ͼ�����ݣ�ʵ����Ч������ͨ����nChannels��������1ͨ��ͼ����Ч����Ϊ
																						// ǰ(CW_ALIGNED_IMAGE_WH*CW_ALIGNED_IMAGE_WH)������,2ͨ����3ͨ����������.
	int    width;																		// ͼ���.
	int    height;																		// ͼ���.
	int    nChannels;																	// ͼ��ͨ��,��֧��1��3ͨ��.
} cw_face_aligned_t;

// �ؼ���
#define CW_MAX_FACE_KEYPT_NUM 68
typedef struct cw_face_point
{
 	float x;				
	float y;
} cw_face_point_t;

typedef struct cw_face_keypt
{
	cw_face_point_t	points[CW_MAX_FACE_KEYPT_NUM];					// �ؼ���
	int				nkeypt;											// �ؼ������
	float			keyptScore;										// �ؼ���÷�
} cw_face_keypt_t;


// ͷ����̬
typedef struct cw_face_head_pose
{
	float pitch;		// ̧ͷ����ͷ,��Χ-90��90��Խ���ʾԽ̧ͷ
	float yaw;			// ����תͷ,��Χ-90��90��Խ���ʾԽ��������תͷ
	float roll;			// ƽ����ƫͷ,��Χ-90��90��Խ���ʾԽ��������ƫͷ
} cw_face_head_pose_t;

// ��������
typedef struct cw_face_quality
{
    float qualityScore; // ���������ܷ֣��Ƽ���Χ0.65-1.0
    float clarity; // �����ȣ�Խ���ʾԽ�������Ƽ���Χ0.65-1.0
    float brightness; // ���ȣ�Խ���ʾԽ�����Ƽ���Χ0.2-0.8
    float yaw;       // �����Ƕȣ���תΪ������תΪ��
    float pitch;    // �����Ƕȣ�̧ͷΪ������ͷΪ��
    float roll;     // �����Ƕȣ�˳ʱ��Ϊ������ʱ��Ϊ��
    float yawScore; // ����ת�̶ȣ�Խ���ʾ�Ƕ�Խ���Ƽ���Χ0.0-0.5
    float pitchScore; // ̧��ͷ�̶ȣ�Խ���ʾ�Ƕ�Խ��,�Ƽ���Χ0.0-0.5
    float skinScore; // ��ɫ�ӽ����˷�ɫ�̶ȣ�Խ���ʾԽ��ʵ���Ƽ���Χ0.5-1.0

    float mouthOpening; // ��������� Խ���ʾԽ�������죬�Ƽ���Χ0.0-0.5
    float leftEyeOpening; // �������۷����� Խ���ʾ����Խ���������ۣ��Ƽ���Χ0.5-1.0
    float rightEyeOpening; // �������۷����� Խ���ʾ����Խ���������ۣ��Ƽ���Χ0.5-1.0
    float blackframeglassProb; // ���ڿ��۾����Ŷȣ�Խ���ʾ���ڿ��۾��Ŀ�����Խ���Ƽ���Χ0.0-0.5
    float sunglassProb; // ��ī�������ŷ֣�Խ���ʾ��ī���Ŀ�����Խ���Ƽ���Χ0.0-0.5
    float rightEyeOcclusionProb; // �۾����ڵ������Ŷȣ�Խ���ʾ�۾�Խ���ܱ��ڵ����Ƽ���Χ0.0-0.5
	float leftEyeOcclusionProb; // �۾����ڵ������Ŷȣ�Խ���ʾ�۾�Խ���ܱ��ڵ����Ƽ���Χ0.0-0.5
} cw_face_quality_t;


	// ����������Ϣ�ṹ
typedef struct cw_face_liveness
{
	cw_face_liveness_code_t errcode;		                        // �����������(Ĭ�ϳ�ʼ��ΪCW_FACE_LIVENESS_NO_FACE)

	int                        headPitch;							// ��̧ͷ������1��̧ͷ��0:ͷδ��,-1����ͷ��
	int                        headYaw;							    // ͷת������1����ͼ�����תͷ��0��ͷδ����-1��ͼ���Ҳ�תͷ��
	int                        mouthAct;							// �첿������1�����죬0��δ���죩
	int                        eyeAct;								// �۾�������1��գ�ۣ�0��δգ�ۣ�
	int                        attack;								/* �������ͣ�0: �ȴ���� -2:�챻��ȡ -3:�۱���ȡ
											                        -4:�ڰ�ͼƬ���� -5:�߿򹥻� -6:ֽ�Ź��� -7:������Ƶ������*/
	long                      timeStamp;                           // ���巢��ʱ�������λ��tick��
} cw_face_liveness_t;

	// ������ͼ
typedef struct cw_face_report_image
{
	int    opType;												// ������������ͣ��������嶯������|���幥������)һ�£�����2080,2112,2176,2304,2560,3072���α�ʾ
																// (̧ͷ|����)��(��ͷ|����)��(��תͷ|����)��(��תͷ|����)��(����|����)��(գ��|����)������������Ч.       
	cw_face_rect_t          faceRect;                           // ������
	long                    timeStamp;                          // ֡ʱ�������λ��ms��                  
	char				   *data;                               // ͼ�����ݣ��������û���ǰ�����㹻��ռ䣬���Ҫ��640*480*3�ֽڡ�
	int						width;								// ͼ���
	int						height;								// ͼ���
	int						nChannels;							// ͼ��ͨ��
	cw_face_keypt_t			keyPts;								// ��Ӧ��ǰ�����Ĺؼ���.
	cw_face_head_pose_t     headPose;                           // ��Ӧ��ǰ�����ĽǶ�.
} cw_face_report_image_t;

	// �����ۺϽṹ
typedef struct cw_face
{
	int						detected;			// 1: ��⵽������,.0�����ٵ�������. 
												// ע�� ���ٵ��Ľ�ID��������������Ч
	int						faceId;             // ����id
	cw_face_rect_t			faceRect;			// ������
	cw_face_keypt_t			keypt;              // �����ؼ���
	cw_face_head_pose_t		headPose;			// ͷ����̬
	cw_face_aligned_t		faceAligned;		// ��������
	cw_face_quality_t		quality;			// ��������
	cw_face_liveness_t		liveness;           // ������Ϣ
	cw_face_report_image_t  reportImage;        // ԭʼ���ͼ
} cw_face_t;

	// ��ѡ������Ϣ�ṹ�����ڻ��壩
typedef struct cw_face_living{
	cw_face_liveness_select_code_t      code;              // ѡͼ��־
	int									iAction;           // ���嶯�����ͣ������������һ�£�����32,64,128,256,512,1024
	                                                       // ���α�ʾ̧ͷ����ͷ����תͷ����תͷ�����졢գ�ۣ�����������Ч.
	cw_face_aligned_t					faceAligned;       // ��ѡ�Ķ�������
	cw_face_keypt_t						keypt;             // �����ؼ�����Ϣ
	cw_face_head_pose_t					angle;             // �����Ƕ���Ϣ
}cw_face_living_t;

# define CW_LIVING_IMAGE_WH 680
# define CW_LIVING_IMAGE_CHNS 3
typedef struct living_image_frame{
	//unsigned char   data[CW_LIVING_IMAGE_WH * CW_LIVING_IMAGE_WH * CW_LIVING_IMAGE_CHNS];  
	unsigned char   *data;
	int    width;																		// ͼ���.
	int    height;																		// ͼ���.
	int    nChannels;
	cw_face_point_t keypoints[CW_MAX_FACE_KEYPT_NUM];
	long timestamp; 
	float pitch;
	float yaw;
	float roll;
	int nkeypt;
	float keypoint_score;
} living_image_frame_t;

typedef struct cw_living_image_frame{
	living_image_frame_t living_frame_image_1;
	living_image_frame_t living_frame_image_2;
	living_image_frame_t living_frame_image_3;
	living_image_frame_t living_frame_image_4;
} cw_living_image_frame_t;
#endif
