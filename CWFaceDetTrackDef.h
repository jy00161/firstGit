#ifndef CW_FACE_COMMON_DEFINE_H_
#define CW_FACE_COMMON_DEFINE_H_


	// 检测开关选项
#define CW_FACE_DET					0						// (1<<0)进行人脸检测，并返回人脸矩形位置
#define CW_FACE_TRACK				2						// (1<<1)进行人脸跟踪，并返回人脸跟踪的ID
#define CW_FACE_KEYPT				4						// (1<<2)进行人脸关键点检测，并返回人脸上的关键点坐标信息
#define CW_FACE_ALIGN				8						// (1<<3)进行人脸图像对齐，并返回对齐后的人脸图像（可直接送入特征提取接口）、关键点信息
#define CW_FACE_QUALITY				16						// (1<<4)进行人脸质量评分，并返回人脸质量分、关键点信息(此版本:要返回质量分，请不要打开活体开关)
#define CW_FACE_LIVENESS_HEAD_UP	32						// (1<<5)活体检测: 抬头
#define CW_FACE_LIVENESS_HEAD_DOWN	64						// (1<<6)活体检测: 点头
#define CW_FACE_LIVENESS_HEAD_LEFT	128						// (1<<7)活体检测: 向左转头
#define CW_FACE_LIVENESS_HEAD_RIGHT 256						// (1<<8)活体检测: 向右转头
#define CW_FACE_LIVENESS_MOUTH		512						// (1<<9)活体检测: 嘴部
#define CW_FACE_LIVENESS_EYE		1024					// (1<<10)活体检测: 眼睛
#define CW_FACE_LIVENESS_ATTACK		2048					// (1<<11)活体检测：攻击类型
#define CW_FACE_LIVENESS			4064					// 活体检测：上面七种活体开关综合(CW_FACE_LIVENESS_HEAD_UP | CW_FACE_LIVENESS_HEAD_DOWN | CW_FACE_LIVENESS_HEAD_LEFT | CW_FACE_LIVENESS_HEAD_RIGHT | CW_FACE_LIVENESS_MOUTH | CW_FACE_LIVENESS_EYE | CW_FACE_LIVENESS_ATTACK)

#define LIVE_DONOTHIN_T  0
#define	LIVE_PREPARE_T	 1 //静默
#define	LIVE_HEAD_LEFT_T		 2 //左转
#define	LIVE_HEAD_RIGHT_T		 4 //右转
#define	LIVE_EYE_BLINK_T	 8 //眨眼
#define	LIVE_MOUTH_OPEN_T  16 //张嘴
#define	LIVE_HEAD_UP_T	 32 //抬头
#define	LIVE_HEAD_DOWN_T  64 //低头



// 通用错误码
typedef enum cw_face_errcode 
{ 
	CW_FACE_OK = 0,							//成功 or 合法

	CW_FACE_FRAME_ERR = 20000,				// 空图像，比如空图像等
	CW_FACE_FORMAT_ERR,						// 图像格式不支持，比如不支持
	CW_FACE_NO_FACE,                        // 没有人脸
	
	CW_FACE_ROI_ERR,						// ROI设置失败
	CW_FACE_MINMAX_ERR,						// 最小最大人脸设置失败
	CW_FACE_RANGE_ERR,						// 数据范围错误
	CW_FACE_METHOD_UNAVAILABLE,             // 方法无效

	CW_FACE_UNAUTHORIZED_ERR,				// 未授权
	CW_FACE_UNINITIALIZED_ERR,				// 尚未初始化
	CW_FACE_DETECT_MODEL_ERR,				// 加载检测模型失败
	CW_FACE_KEYPT_MODEL_ERR,				// 加载关键点模型失败
	CW_FACE_QUALITY_MODEL_ERR,				// 加载质量评估模型失败
	CW_FACE_LIVENESS_MODEL_ERR,				// 加载活体检测模型失败

	CW_FACE_DET_ERR,						// 检测失败
	CW_FACE_KEYPT_ERR,						// 提取关键点失败
	CW_FACE_ALIGN_ERR,						// 对齐人脸失败
	CW_FACE_QUALITY_ERR,					// 质量评估失败
	CW_FACE_LIVENESS_ERR,                   // 活体检测错
} cw_face_errcode_t; 

// 活体检测标志码
typedef enum cw_face_liveness_code
{
	CW_FACE_LIVENESS_OK = 0,				// 活体数据有效
	CW_FACE_LIVENESS_NO_INFO=21000,         // 活体数据无效
} cw_face_liveness_code_t;

// 选图标志码
typedef enum cw_face_liveness_select_code
{
	CW_FACE_LIVENESS_SELECT_OK = 0,				  // 选图成功
	CW_FACE_LIVENESS_SELECT_RUNNING = 21050,      // 未能选图，原因：正在选图中
	CW_FACE_LIVENESS_SELECT_NONE,                 // 未能选图，原因：选图还未开始
	CW_FACE_LIVENESS_SELECT_TIMEOUT,              // 未能选图，原因：超时
	CW_FACE_LIVENESS_SELECT_UNKNOWN,              // 未能选图，原因：未知
}cw_face_liveness_select_code_t;

// 模型选择方式
typedef enum cw_model_mode
{
	CW_MODEL_FILE=0,                        // 文件方式
	CW_MODEL_MEMORY,                        // 内存方式
	CW_MODEL_FILE_MEMORY                    // 文件和内存方式（暂无效）
}cw_model_mode_t;

// 接口参数（注意：所有参数没有特别声明情况下，如果越界，算法会自动调整参数值）

typedef struct cw_face_param
{
	int roiX;								// 检测ROI, 默认整帧图像0, 0, 0, 0
	int roiY;
	int roiWidth;
	int roiHeight;
	
	int maxFaceNumPerImg;					// 每帧最大人脸数，最小1，默认5.

	int minSize;							// 人脸尺寸范围，默认[100,400],最大可设置范围[30,1500].最小人脸低于96时，perfmonLevel参数最好是6
	int maxSize;

	int globleDetFreq;						// 全局检测频率，最小1，默认25

	float minTrackedKeyptScore;				// 跟踪关键点时的最小置信度,范围{0.30-1.0f,1.01f},默认0.5f;如果
	                                        // 要不使用，请设置此值大于1.0。

	int   imageMode;                         // 0-摄像头；1-视频；2-图像，默认0.

	int   nMissAllowed;                     // 活体最多允许的连续断帧数，范围（0~10），值越大越好过，但更容易受攻击，
											// 默认为0-不允许断帧.

	int   perfmonLevel;                     // 检测性能水平，范围(1~6).数字越大速度越慢，但效果（质量分和活体）越好,反之亦然.默认
											// 值1。检测静态图像建议6

	unsigned int nCpuCores;                 // CPU核心数，由应用层传入，默认当做2. 内部根据用户设置的数值做自动调整，具体是1~2会
											// 调整为2；3~5调整为3；6或以上调整为4。须根据实际系统设置该参数，否则可能严重影响性能。

	float minLivingBrightness;              // 活体启动最低光线质量分，范围(0.0f~1.0f),默认0.280f。另外
											// 建议用户还是根据特定平台进行多环境测试确定。

	int  bCollectFrmsLiving;                // 是否存图：0-否；其他是。默认0.

	char  imgSavePath[1024];                // 活体人脸图片存放路径，默认为当前路径.
	int   bSaveImg;                         // 是否保存活体人脸:0-不保存，1保存, 默认0.
} cw_face_param_t;

// 图像旋转角度（逆时针）
typedef enum cw_image_angle
{ 
	CW_IMG_ANGLE_0 = 0,       
	CW_IMG_ANGLE_90,       
	CW_IMG_ANGLE_180,       
	CW_IMG_ANGLE_270       
} cw_image_angle_t; 

// 图像镜像
typedef enum cw_image_mirror
{ 
	CW_IMG_MIRROR_NONE = 0,        // 不镜像  
	CW_IMG_MIRROR_HOR,             // 水平镜像
	CW_IMG_MIRROR_VER,             // 垂直镜像
	CW_IMG_MIRROR_HV               // 垂直和水平镜像
} cw_image_mirror_t; 

// 图像格式
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

// 图像
typedef struct cw_image
{
	char* data;								// 图像数据
	int	  dataLen;							// 数据长度，非二进制图可不设
	int   width;							// 宽, JPG等二进制图可不设
	int   height;							// 高, JPG等二进制图可不设
	cw_image_form_t format;					// 图像格式
	cw_image_angle_t angle;					// 旋转角度
	cw_image_mirror_t  mirror;              // 镜像
	int   coordMap;							// 输出坐标系标志, 0：以旋正（旋正+镜像）图像为准，非0:以旋正前图像为准
	int   stageflag;						// 输入图像所处的阶段标志，取值范围为活体验证阶段开关
	long   timestamp;                        // 输入图像的进入时间戳
} cw_image_t;

// 人脸框
typedef struct cw_face_rect
{
	int    x;
	int    y;
	int    width;
	int    height;
} cw_face_rect_t;

// 对齐人脸
#define CW_ALIGNED_IMAGE_WH 128
#define CW_ALIGNED_IMAGE_CHNS 3
typedef struct cw_face_aligned
{
	char   data[CW_ALIGNED_IMAGE_WH * CW_ALIGNED_IMAGE_WH * CW_ALIGNED_IMAGE_CHNS];		// 图像数据，实际有效部分由通道数nChannels决定，即1通道图的有效数据为
																						// 前(CW_ALIGNED_IMAGE_WH*CW_ALIGNED_IMAGE_WH)个数据,2通道、3通道依次类推.
	int    width;																		// 图像宽.
	int    height;																		// 图像高.
	int    nChannels;																	// 图像通道,仅支持1到3通道.
} cw_face_aligned_t;

// 关键点
#define CW_MAX_FACE_KEYPT_NUM 68
typedef struct cw_face_point
{
 	float x;				
	float y;
} cw_face_point_t;

typedef struct cw_face_keypt
{
	cw_face_point_t	points[CW_MAX_FACE_KEYPT_NUM];					// 关键点
	int				nkeypt;											// 关键点个数
	float			keyptScore;										// 关键点得分
} cw_face_keypt_t;


// 头部姿态
typedef struct cw_face_head_pose
{
	float pitch;		// 抬头、低头,范围-90到90，越大表示越抬头
	float yaw;			// 左右转头,范围-90到90，越大表示越可能向左转头
	float roll;			// 平面内偏头,范围-90到90，越大表示越可能向左偏头
} cw_face_head_pose_t;

// 人脸质量
typedef struct cw_face_quality
{
    float qualityScore; // 人脸质量总分，推荐范围0.65-1.0
    float clarity; // 清晰度，越大表示越清晰，推荐范围0.65-1.0
    float brightness; // 亮度，越大表示越亮，推荐范围0.2-0.8
    float yaw;       // 人脸角度，左转为正，右转为负
    float pitch;    // 人脸角度，抬头为正，低头为负
    float roll;     // 人脸角度，顺时针为正，逆时针为负
    float yawScore; // 左右转程度，越大表示角度越大，推荐范围0.0-0.5
    float pitchScore; // 抬低头程度，越大表示角度越大,推荐范围0.0-0.5
    float skinScore; // 肤色接近真人肤色程度，越大表示越真实，推荐范围0.5-1.0

    float mouthOpening; // 张嘴分数， 越大表示越可能张嘴，推荐范围0.0-0.5
    float leftEyeOpening; // 左眼睁眼分数， 越大表示左眼越可能是睁眼，推荐范围0.5-1.0
    float rightEyeOpening; // 右眼睁眼分数， 越大表示右眼越可能是睁眼，推荐范围0.5-1.0
    float blackframeglassProb; // 戴黑框眼镜置信度，越大表示戴黑框眼镜的可能性越大，推荐范围0.0-0.5
    float sunglassProb; // 戴墨镜的置信分，越大表示戴墨镜的可能性越大，推荐范围0.0-0.5
    float rightEyeOcclusionProb; // 眼睛被遮挡的置信度，越大表示眼睛越可能被遮挡，推荐范围0.0-0.5
	float leftEyeOcclusionProb; // 眼睛被遮挡的置信度，越大表示眼睛越可能被遮挡，推荐范围0.0-0.5
} cw_face_quality_t;


	// 人脸活体信息结构
typedef struct cw_face_liveness
{
	cw_face_liveness_code_t errcode;		                        // 活体检测错误码(默认初始化为CW_FACE_LIVENESS_NO_FACE)

	int                        headPitch;							// 低抬头动作（1：抬头，0:头未动,-1：低头）
	int                        headYaw;							    // 头转动作（1：往图像左侧转头，0：头未动，-1往图像右侧转头）
	int                        mouthAct;							// 嘴部动作（1：张嘴，0：未张嘴）
	int                        eyeAct;								// 眼睛动作（1：眨眼，0：未眨眼）
	int                        attack;								/* 攻击类型（0: 等待结果 -2:嘴被扣取 -3:眼被扣取
											                        -4:黑白图片攻击 -5:边框攻击 -6:纸张攻击 -7:脸优视频攻击）*/
	long                      timeStamp;                           // 活体发生时间戳（单位：tick）
} cw_face_liveness_t;

	// 活体检测图
typedef struct cw_face_report_image
{
	int    opType;												// 活体操作码类型，跟（活体动作开关|活体攻击开关)一致，其中2080,2112,2176,2304,2560,3072依次表示
																// (抬头|攻击)、(点头|攻击)、(左转头|攻击)、(右转头|攻击)、(张嘴|攻击)、(眨眼|攻击)，其他数字无效.       
	cw_face_rect_t          faceRect;                           // 人脸框
	long                    timeStamp;                          // 帧时间戳（单位：ms）                  
	char				   *data;                               // 图像数据，必须由用户提前分配足够大空间，最低要求：640*480*3字节。
	int						width;								// 图像宽
	int						height;								// 图像高
	int						nChannels;							// 图像通道
	cw_face_keypt_t			keyPts;								// 对应当前人脸的关键点.
	cw_face_head_pose_t     headPose;                           // 对应当前人脸的角度.
} cw_face_report_image_t;

	// 人脸综合结构
typedef struct cw_face
{
	int						detected;			// 1: 检测到的人脸,.0：跟踪到的人脸. 
												// 注： 跟踪到的仅ID和人脸框数据有效
	int						faceId;             // 人脸id
	cw_face_rect_t			faceRect;			// 人脸框
	cw_face_keypt_t			keypt;              // 人脸关键点
	cw_face_head_pose_t		headPose;			// 头部姿态
	cw_face_aligned_t		faceAligned;		// 对齐人脸
	cw_face_quality_t		quality;			// 人脸质量
	cw_face_liveness_t		liveness;           // 活体信息
	cw_face_report_image_t  reportImage;        // 原始检测图
} cw_face_t;

	// 优选人脸信息结构（用于活体）
typedef struct cw_face_living{
	cw_face_liveness_select_code_t      code;              // 选图标志
	int									iAction;           // 活体动作类型，跟活体操作码一致，其中32,64,128,256,512,1024
	                                                       // 依次表示抬头、点头、左转头、右转头、张嘴、眨眼，其他数字无效.
	cw_face_aligned_t					faceAligned;       // 优选的对齐人脸
	cw_face_keypt_t						keypt;             // 人脸关键点信息
	cw_face_head_pose_t					angle;             // 人脸角度信息
}cw_face_living_t;

# define CW_LIVING_IMAGE_WH 680
# define CW_LIVING_IMAGE_CHNS 3
typedef struct living_image_frame{
	//unsigned char   data[CW_LIVING_IMAGE_WH * CW_LIVING_IMAGE_WH * CW_LIVING_IMAGE_CHNS];  
	unsigned char   *data;
	int    width;																		// 图像宽.
	int    height;																		// 图像高.
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
