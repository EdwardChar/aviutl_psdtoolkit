//----------------------------------------------------------------------------------
//	�ե��륿�ץ饰���� �إå��`�ե����� for AviUtl version 0.99k �Խ�
//	By �ˣţΤ���
//----------------------------------------------------------------------------------

//	YC������
typedef	struct {
	short	y;					//	����(�x��    )�ǩ`�� (     0 �� 4096 )
	short	cb;					//	����(ɫ��(��))�ǩ`�� ( -2048 �� 2048 )
	short	cr;					//	����(ɫ��(��))�ǩ`�� ( -2048 �� 2048 )
								//	���إǩ`���Ϲ�����˳��Ƥ��뤳�Ȥ�����ޤ�
								//	�ޤ������ڤ˅���ʤ��Ƥ⤫�ޤ��ޤ���
} PIXEL_YC;

//	PIXEL������
typedef	struct {
	unsigned char	b,g,r;		//	����(RGB)�ǩ`�� (0��255)
} PIXEL;

//	�ե��륿PROC�Ø�����
typedef struct {
	int			flag;			//	�ե��륿�Υե饰
								//	FILTER_PROC_INFO_FLAG_INVERT_FIELD_ORDER	: �ե��`��ɥ��`���`��˜ʤ���˒Q�� ( �˜ʤϥܥȥ�->�ȥåפˤʤäƤ��ޤ� )
								//	FILTER_PROC_INFO_FLAG_INVERT_INTERLACE		: ���������ܞ���� ( ���󥿩`��`������ե��륿�Τ� )
	PIXEL_YC	*ycp_edit;		//	����ǩ`���ؤΥݥ��� ( ycp_edit��ycp_temp������椨��ޤ� )
	PIXEL_YC	*ycp_temp;		//	�ƥ�ݥ���I��ؤΥݥ���
	int			w,h;			//	�F�ڤλ���Υ����� ( ���񥵥����ω�������ޤ� )
	int			max_w,max_h;	//	�����I��Υ�����
	int			frame;			//	�F�ڤΥե�`�෬��( ���Ť�0���� )
	int			frame_n;		//	�t�ե�`����
	int			org_w,org_h;	//	Ԫ�λ���Υ�����
	short		*audiop;		//	���`�ǥ����ǩ`���ؤΥݥ��� ( ���`�ǥ����ե��륿�Εr�Τ� )
								//	���`�ǥ�����ʽ��PCM16bit�Ǥ� ( 1����ץ�� mono = 2byte , stereo = 4byte )
	int			audio_n;		//	���`�ǥ�������ץ�ξt��
	int			audio_ch;		//	���`�ǥ��������ͥ���
	PIXEL		*pixelp;		//	�F�ڤ�ʹ�ä���Ƥ��ޤ���
	void		*editp;			//	���ǥ��åȥϥ�ɥ�
	int			yc_size;		//	�����I��λ��ؤΥХ��ȥ�����
	int			line_size;		//	�����I��η��ΥХ��ȥ�����
	int			reserve[8];		//	�����ä���s����Ƥޤ�
} FILTER_PROC_INFO;
#define	FILTER_PROC_INFO_FLAG_INVERT_FIELD_ORDER	0x00010000
#define	FILTER_PROC_INFO_FLAG_INVERT_INTERLACE		0x00020000
//	�����󥿩`��`������ե��륿�r��ycp_edit�˳��ڻ���ǩ`������äƤ��ޤ���
//	�����󥿩`��`������ե��륿�r��ycp_edit,ycp_temp,w,h�����Ǥ��ޤ���

//	�ե�`�ॹ�Ʃ`����������
typedef struct {
	int		video;			//	�g�H��ӳ��ǩ`������
	int		audio;			//	�g�H�������ǩ`������
	int		inter;			//	�ե�`��Υ��󥿩`��`��
							//	FRAME_STATUS_INTER_NORMAL	: �˜�
							//	FRAME_STATUS_INTER_REVERSE	: ��ܞ
							//	FRAME_STATUS_INTER_ODD		: ����
							//	FRAME_STATUS_INTER_EVEN		: ż��
							//	FRAME_STATUS_INTER_MIX		: ���ػ�
							//	FRAME_STATUS_INTER_AUTO		: �Ԅ�
	int		index24fps;		//	�F�ڤ�ʹ�ä���Ƥ��ޤ���
	int		config;			//	�ե�`��Υץ�ե�����h���η���
	int		vcm;			//	�ե�`��ΈR�s�O���η���
	int		edit_flag;		//	�����ե饰
							//	EDIT_FRAME_EDIT_FLAG_KEYFRAME	: ���`�ե�`��
							//	EDIT_FRAME_EDIT_FLAG_MARKFRAME	: �ީ`���ե�`��
							//	EDIT_FRAME_EDIT_FLAG_DELFRAME	: �����g�����ե�`��
							//	EDIT_FRAME_EDIT_FLAG_NULLFRAME	: ���ԩ`�ե�`��
	int		reserve[9];		//	�����ä���s����Ƥޤ�
} FRAME_STATUS;
#define	FRAME_STATUS_INTER_NORMAL		0
#define	FRAME_STATUS_INTER_REVERSE		1
#define	FRAME_STATUS_INTER_ODD			2
#define	FRAME_STATUS_INTER_EVEN			3
#define	FRAME_STATUS_INTER_MIX			4
#define	FRAME_STATUS_INTER_AUTO			5
#define	EDIT_FRAME_EDIT_FLAG_KEYFRAME		1
#define	EDIT_FRAME_EDIT_FLAG_MARKFRAME		2
#define	EDIT_FRAME_EDIT_FLAG_DELFRAME		4
#define	EDIT_FRAME_EDIT_FLAG_NULLFRAME		8

//	�ե����륤��ե���`���������
typedef struct {
	int		flag;					//	�ե�����Υե饰
									//	FILE_INFO_FLAG_VIDEO	: ӳ�񤬴��ڤ���
									//	FILE_INFO_FLAG_AUDIO	: ���������ڤ���
	LPSTR	name;					//	�ե������� ( avi_file_open()�Ǥ�NULL�ˤʤ�ޤ� )
	int		w,h;					//	Ԫ�Υ�����
	int		video_rate,video_scale;	//	�ե�`���`��
	int		audio_rate;				//	��������ץ�󥰥�`��
	int		audio_ch;				//	���������ͥ���
	int		frame_n;				//	�t�ե�`����
	DWORD	video_decode_format;	//	�ӥǥ�չ�_��ʽ
	int		video_decode_bit;		//	�ӥǥ�չ�_��ʽ�Υӥå���
	int		audio_n;				//	�����ξt����ץ��� ( avi_file_open()�Εr�Τ��O������ޤ� )
	int		reserve[4];				//	�����ä���s����Ƥޤ�
} FILE_INFO;
#define FILE_INFO_FLAG_VIDEO	1
#define FILE_INFO_FLAG_AUDIO	2

//	�����ƥ।��ե���`���������
typedef struct {
	int		flag;					//	�����ƥ�ե饰
									//	SYS_INFO_FLAG_EDIT		: ������
									//	SYS_INFO_FLAG_VFAPI		: VFAPI�����r
									//	SYS_INFO_FLAG_USE_SSE	: SSEʹ��
									//	SYS_INFO_FLAG_USE_SSE2	: SSE2ʹ��
	LPSTR	info;					//	�Щ`��������
	int		filter_n;				//	���h����Ƥ�ե��륿����
	int		min_w,min_h;			//	������������С���񥵥���
	int		max_w,max_h;			//	��������������񥵥���
	int		max_frame;				//	�������������ե�`����
	LPSTR	edit_name;				//	�����ե������� (�ե����������Q�ޤäƤ��ʤ��r�ϺΤ���äƤ��ޤ���)
	LPSTR	project_name;			//	�ץ������ȥե������� (�ե����������Q�ޤäƤ��ʤ��r�ϺΤ���äƤ��ޤ���)
	LPSTR	output_name;			//	�����ե������� (�ե����������Q�ޤäƤ��ʤ��r�ϺΤ���äƤ��ޤ���)
	int		vram_w,vram_h;			//	�����û����I��Υ�����
	int		vram_yc_size;			//	�����û����I��λ��ؤΥХ�����
	int		vram_line_size;			//	�����û����I��η��ΥХ�����
	HFONT	hfont;					//	�ե��륿�O��������ɥ���ʹ�ä��Ƥ���ե���ȤΥϥ�ɥ�
	int		build;					//	�ӥ�ɷ��� (�¤����Щ`�����ˤʤ�ۤɴ󤭤ʂ��ˤʤ�ޤ�)
	int		reserve[2];				//	�����ä���s����Ƥޤ�
} SYS_INFO;
#define SYS_INFO_FLAG_EDIT		1
#define SYS_INFO_FLAG_VFAPI		2
#define SYS_INFO_FLAG_USE_SSE	4
#define SYS_INFO_FLAG_USE_SSE2	8

//	�ޥ������å��v���äζ��x
typedef void (*MULTI_THREAD_FUNC)( int thread_id,int thread_num,void *param1,void *param2 );
								//	thread_id	: ����åɷ��� ( 0 �� thread_num-1 )
								//	thread_num	: ����å��� ( 1 �� )
								//	param1		: ���åѥ��`��
								//	param2		: ���åѥ��`��

//	AVI�����ե�����ϥ�ɥ�
typedef void*	AVI_FILE_HANDLE;

//	�ⲿ�v��������
typedef struct {
	void		(*get_ycp_ofs)( void *editp,int n,int ofs );
								//	�����������get_ycp_source_cache()�η���ʹ�ä���褦�ˤ��Ƥ�������
								//	ָ�������ե�`���AVI�ե������ϤǤΥ��ե��åȷ��ƄӤ���
								//	�ե�`��λ���ǩ`���Υݥ��󥿤�ȡ�ä��ޤ�
								//	�ǩ`���ϥե��륿ǰ�Τ�ΤǤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n	 	: �ե�`�෬��
								//	ofs	 	: �ե�`�फ��Υ��ե��å�
								//  ���ꂎ	: ����ǩ`���ؤΥݥ��� (NULL�ʤ�ʧ��)
								//			  ����ǩ`���ݥ��󥿤����ݤϴΤ��ⲿ�v����ʹ�����ᥤ��˄I�������ޤ��Є�
	void		*(*get_ycp)( void *editp,int n );
								//	�����������get_ycp_source_cache()�η���ʹ�ä���褦�ˤ��Ƥ�������
								//	ָ�������ե�`��λ���ǩ`���Υݥ��󥿤�ȡ�ä��ޤ�
								//	�ǩ`���ϥե��륿ǰ�Τ�ΤǤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n	 	: �ե�`�෬��
								//  ���ꂎ	: ����ǩ`���ؤΥݥ��� (NULL�ʤ�ʧ��)
								//			  ����ǩ`���ݥ��󥿤����ݤϴΤ��ⲿ�v����ʹ�����ᥤ��˄I�������ޤ��Є�
	void		*(*get_pixelp)( void *editp,int n );
								//	ָ�������ե�`���DIB��ʽ(RGB24bit)�λ���ǩ`���Υݥ��󥿤�ȡ�ä��ޤ�
								//	�ǩ`���ϥե��륿ǰ�Τ�ΤǤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n		: �ե�`�෬��
								//  ���ꂎ	: DIB��ʽ�ǩ`���ؤΥݥ��� (NULL�ʤ�ʧ��)
								//			  ����ǩ`���ݥ��󥿤����ݤϴΤ��ⲿ�v����ʹ�����ᥤ��˄I�������ޤ��Є�
	int			(*get_audio)( void *editp,int n,void *buf );
								//	ָ�������ե�`��Υ��`�ǥ����ǩ`�����i���z�ߤޤ�
								//	�ǩ`���ϥե��륿ǰ�Τ�ΤǤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n		: �ե�`�෬��
								//	buf 	: ��{����Хåե� (NULL�ʤ饵��ץ�����ȡ�äΤ�)
								//  ���ꂎ	: �i���z�������ץ���
	BOOL		(*is_editing)( void *editp );
								//	�F�ھ����Ф��{�٤ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  ���ꂎ	: TRUE�ʤ龎����
	BOOL		(*is_saving)( void *editp );
								//	�F�ڱ����Ф��{�٤ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  ���ꂎ	: TRUE�ʤ鱣����
	int			(*get_frame)( void *editp );
								//	�F�ڤα�ʾ�ե�`���ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  ���ꂎ	: �F�ڤΥե�`�෬��
	int			(*get_frame_n)( void *editp );
								//	�t�ե�`������ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  ���ꂎ	: �F�ڤξt�ե�`����
	BOOL		(*get_frame_size)( void *editp,int *w,int *h );
								//	�ե��륿ǰ�Υե�`��Υ�������ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	w,h 	: ���񥵥����θ�{�ݥ���
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	int			(*set_frame)( void *editp,int n );
								//	�F�ڤα�ʾ�ե�`��������ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  n		: �ե�`�෬��
								//  ���ꂎ	: �O�����줿�ե�`�෬��
	int			(*set_frame_n)( void *editp,int n );
								//	�t�ե�`�����������ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  n		: �ե�`����
								//  ���ꂎ	: �O�����줿�t�ե�`����
	BOOL		(*copy_frame)( void *editp,int d,int s );
								//	�ե�`������Υե�`��˥��ԩ`���ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	d	 	: ���ԩ`�ȥե�`�෬��
								//	s	 	: ���ԩ`Ԫ�ե�`�෬��
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*copy_video)( void *editp,int d,int s );
								//	�ե�`���ӳ����������Υե�`��˥��ԩ`���ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	d	 	: ���ԩ`�ȥե�`�෬��
								//	s	 	: ���ԩ`Ԫ�ե�`�෬��
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*copy_audio)( void *editp,int d,int s );
								//	�ե�`����������������Υե�`��˥��ԩ`���ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	d	 	: ���ԩ`�ȥե�`�෬��
								//	s	 	: ���ԩ`Ԫ�ե�`�෬��
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*copy_clip)( HWND hwnd,void *pixelp,int w,int h );
								//	����åץܩ`�ɤ�DIB��ʽ(RGB24bit)�λ���򥳥ԩ`���ޤ�
								//	hwnd 	: ������ɥ��ϥ�ɥ�
								//	pixelp	: DIB��ʽ�ǩ`���ؤΥݥ���
								//	w,h 	: ���񥵥���
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*paste_clip)( HWND hwnd,void *editp,int n );
								//	����åץܩ`�ɤ��黭��򏈤�Ĥ��ޤ�
								//	hwnd 	: ������ɥ��ϥ�ɥ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  n		: �ե�`�෬��
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*get_frame_status)( void *editp,int n,FRAME_STATUS *fsp );
								//	�ե�`��Υ��Ʃ`������ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  n		: �ե�`�෬��
								//  fps		: �ե�`�ॹ�Ʃ`�����ؤΥݥ���
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*set_frame_status)( void *editp,int n,FRAME_STATUS *fsp );
								//	�ե�`��Υ��Ʃ`�����������ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  n		: �ե�`�෬��
								//  fps		: �ե�`�ॹ�Ʃ`�����ؤΥݥ���
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*is_saveframe)( void *editp,int n );
								//	�g�H�˱��椵���ե�`�फ�{�٤ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  n		: �ե�`�෬��
								//  ���ꂎ	: TRUE�ʤ鱣�椵��ޤ�
	BOOL		(*is_keyframe)( void *editp,int n );
								//	���`�ե�`�फ�ɤ����{�٤ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  n		: �ե�`�෬��
								//  ���ꂎ	: TRUE�ʤ饭�`�ե�`��
	BOOL		(*is_recompress)( void *editp,int n );
								//	�وR�s����Ҫ���{�٤ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  n		: �ե�`�෬��
								//  ���ꂎ	: TRUE�ʤ��وR�s����Ҫ
	BOOL		(*filter_window_update)( void *fp );
								//	�O��������ɥ��Υȥ�å��Щ`�ȥ����å��ܥå��������軭���ޤ�
								//	fp	 	: �ե��륿������Υݥ���
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*is_filter_window_disp)( void *fp );
								//	�O��������ɥ�����ʾ����Ƥ��뤫�{�٤ޤ�
								//	fp	 	: �ե��륿������Υݥ���
								//  ���ꂎ	: TRUE�ʤ��ʾ����Ƥ���
	BOOL		(*get_file_info)( void *editp,FILE_INFO *fip );
								//	�����ե����������ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  fip		: �ե����륤��ե���`���������ؤΥݥ���
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	LPSTR		(*get_config_name)( void *editp,int n );
								//	�F�ڤΥץ�ե��������ǰ��ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  n		: �ץ�ե�����h���η���
								//  ���ꂎ	: �ץ�ե��������ǰ�ؤΥݥ��� (NULL�ʤ�ʧ��)
	BOOL		(*is_filter_active)( void *fp );
								//	�ե��륿���Є��ˤʤäƤ��뤫�{�٤ޤ�
								//	fp	 	: �ե��륿������Υݥ���
								//  ���ꂎ	: TRUE�ʤ�ե��륿�Є�
	BOOL		(*get_pixel_filtered)( void *editp,int n,void *pixelp,int *w,int *h );
								//	ָ�������ե�`���DIB��ʽ(RGB24bit)�λ���ǩ`�����i���z�ߤޤ�
								//	�ǩ`���ϥե��륿��Τ�ΤǤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n		: �ե�`�෬��
								//  pixelp	: DIB��ʽ�ǩ`�����{����ݥ��� (NULL�ʤ黭�񥵥��������򷵤��ޤ�)
								//	w,h		: ����Υ����� (NULL�ʤ�DIB��ʽ�ǩ`�������򷵤��ޤ�)
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	int			(*get_audio_filtered)( void *editp,int n,void *buf );
								//	ָ�������ե�`��Υ��`�ǥ����ǩ`�����i���z�ߤޤ�
								//	�ǩ`���ϥե��륿��Τ�ΤǤ�
								//	editp* 	: ���ǥ��åȥϥ�ɥ�
								//	n		: �ե�`�෬��
								//	buf 	: ��{����Хåե� (NULL�ʤ饵��ץ�����ȡ�äΤ�)
								//  ���ꂎ	: �i���z�������ץ���
	BOOL		(*get_select_frame)( void *editp,int *s,int *e );
								//	�x�k�_ʼ�K�˥ե�`���ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	s		: �x�k�_ʼ�ե�`��
								//	e		: �x�k�K�˥ե�`��
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*set_select_frame)( void *editp,int s,int e );
								//	�x�k�_ʼ�K�˥ե�`����O�����ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	s		: �x�k�_ʼ�ե�`��
								//	e		: �x�k�K�˥ե�`��
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*rgb2yc)( PIXEL_YC *ycp,PIXEL *pixelp,int w );
								//	PIXEL����PIXEL_YC�ˉ�Q���ޤ�
								//	ycp		: PIXEL_YC������ؤΥݥ���
								//	pixelp 	: PIXEL������ؤΥݥ���
								//	w		: ���������
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*yc2rgb)( PIXEL *pixelp,PIXEL_YC *ycp,int w );
								//	PIXEL_YC����PIXEL�ˉ�Q���ޤ�
								//	pixelp 	: PIXEL������ؤΥݥ���
								//	ycp		: PIXEL_YC������ؤΥݥ���
								//	w		: ���������
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*dlg_get_load_name)( LPSTR name,LPSTR filter,LPSTR def );
								//	�ե��������������ʹ�ä��i���z��ե���������ȡ�ä��ޤ�
								//	name	: �ե����������{����ݥ���
								//	filter	: �ե�����ե��륿
								//  def		: �ǥե���ȤΥե�������
								//  ���ꂎ	: TRUE�ʤ�ɹ� FALSE�ʤ饭��󥻥�
	BOOL		(*dlg_get_save_name)( LPSTR name,LPSTR filter,LPSTR def );
								//	�ե��������������ʹ�äƕ����z��ե���������ȡ�ä��ޤ�
								//	name	: �ե����������{����ݥ���
								//	filter	: �ե�����ե��륿
								//  def		: �ǥե���ȤΥե�������
								//  ���ꂎ	: TRUE�ʤ�ɹ� FALSE�ʤ饭��󥻥�
	int			(*ini_load_int)( void *fp,LPSTR key,int n );
								//	INI�ե����뤫���������i���z��
								//	fp	 	: �ե��륿������Υݥ���
								//	key		: ���������äΥ��`����ǰ
								//  n		: �ǥե���Ȥ�����
								//  ���ꂎ	: �i���z�������
	int			(*ini_save_int)( void *fp,LPSTR key,int n );
								//	INI�ե����������������z��
								//	fp	 	: �ե��륿������Υݥ���
								//	key		: ���������äΥ��`����ǰ
								//  n		: �����z������
								//  ���ꂎ	: �����z�������
	BOOL		(*ini_load_str)( void *fp,LPSTR key,LPSTR str,LPSTR def );
								//	INI�ե����뤫�������Ф��i���z��
								//	fp	 	: �ե��륿������Υݥ���
								//	key		: ���������äΥ��`����ǰ
								//  str		: �����Ф��i���z��Хåե�
								//  def		: �ǥե���Ȥ�������
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*ini_save_str)( void *fp,LPSTR key,LPSTR str );
								//	INI�ե�����������Ф�����z��
								//	fp	 	: �ե��륿������Υݥ���
								//	key		: ���������äΥ��`����ǰ
								//  n		: �����z��������
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*get_source_file_info)( void *editp,FILE_INFO *fip,int source_file_id );
								//	ָ�������ե�����ID�Υե����������ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  fip		: �ե����륤��ե���`���������ؤΥݥ���
								//	souce_file_id
								//			: �ե�����ID
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*get_source_video_number)( void *editp,int n,int *source_file_id,int *source_video_number );
								//	ָ�������ե�`��Υ��`���Υե�����ID�ȥե�`�෬�Ť�ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n		: �ե�`�෬��
								//	souce_file_id
								//			: �ե�����ID���{����ݥ���
								//	souce_video_number
								//			: �ե�`�෬�Ť��{����ݥ���
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*get_sys_info)( void *editp,SYS_INFO *sip );
								//	�����ƥ������ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ� (NULL�ʤ�sip�ξ����ФΥե饰�Ȥ��٤ƤΥե����������o���ˤʤ�ޤ�)
								//  sip		: �����ƥ।��ե���`���������ؤΥݥ���
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	void 		*(*get_filterp)( int filter_id );
								//	ָ���Υե��륿ID�Υե��륿������ؤΥݥ��󥿤�ȡ�ä��ޤ�
								//	filter_id
								//		 	: �ե��륿ID (0�����h����Ƥ�ե��륿����-1�ޤǤ΂�)
								//  ���ꂎ	: �ե��륿������ؤΥݥ��� (NULL�ʤ�ʧ��)
	void		*(*get_ycp_filtering)( void *fp,void *editp,int n,void *reserve );
								//	�����������get_ycp_filtering_cache_ex()�η���ʹ�ä���褦�ˤ��Ƥ�������
								//	ָ�������ե�`��λ���ǩ`���Υݥ��󥿤�ȡ�ä��ޤ�
								//	�ǩ`�����Է֤Υե��륿��ֱǰ�ޤǥե��륿������ΤǤ�
								//	fp	 	: �ե��륿������Υݥ���
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n	 	: �ե�`�෬��
								//	reserve	: NULL��ָ�����Ƥ�������
								//  ���ꂎ	: ����ǩ`���ؤΥݥ��� (NULL�ʤ�ʧ��)
								//			  ����ǩ`���ݥ��󥿤����ݤϴΤ��ⲿ�v����ʹ�����ᥤ��˄I�������ޤ��Є�
	int			(*get_audio_filtering)( void *fp,void *editp,int n,void *buf );
								//	ָ�������ե�`��Υ��`�ǥ����ǩ`�����i���z�ߤޤ�
								//	�ǩ`�����Է֤Υե��륿��ֱǰ�ޤǥե��륿������ΤǤ�
								//	fp	 	: �ե��륿������Υݥ���
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n		: �ե�`�෬��
								//	buf 	: ��{����Хåե� (NULL�ʤ饵��ץ�����ȡ�äΤ�)
								//  ���ꂎ	: �i���z�������ץ���
	BOOL		(*set_ycp_filtering_cache_size)( void *fp,int w,int h,int d,int flag );
								//	get_ycp_filtering_cache_ex()�Υ���å�����O���򤷤ޤ�
								//	�O���������ä��r�Τߥ���å����I����ٴ_�����ޤ�
								//	����å����I��ϥե��륿�������ƥ��֤Εr�Τߴ_������ޤ�
								//	fp	 	: �ե��륿������Υݥ���
								//	w	 	: ����å����I��η�
								//	h	 	: ����å����I��θߤ�
								//	d	 	: ����å��夹��ե�`����
								//	flag 	: NULL��ָ�����Ƥ�������
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	void		*(*get_ycp_filtering_cache)( void *fp,void *editp,int n );
								//	�����������get_ycp_filtering_cache_ex()�η���ʹ�ä���褦�ˤ��Ƥ�������
								//	ָ�������ե�`��λ���ǩ`���Υ���å���ݥ��󥿤�ȡ�ä��ޤ�
								//	set_ycp_filtering_cache_size()���O���ˤ������äƥ���å��夵��ޤ�
								//	�ǩ`�����Է֤Υե��륿��ֱǰ�ޤǥե��륿������ΤǤ�
								//	fp	 	: �ե��륿������Υݥ���
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n	 	: �ե�`�෬��
								//  ���ꂎ	: ����ǩ`���ؤΥ���å���ݥ��� (NULL�ʤ�ʧ��)
								//			  ����ǩ`���ݥ��󥿤����ݤϥ���å��夫���Ɨ������ޤ��Є�
	void		*(*get_ycp_source_cache)( void *editp,int n,int ofs );
								//	ָ�������ե�`��λ���ǩ`���Υݥ��󥿤�ȡ�ä��ޤ�
								//	�ǩ`���ϥե��륿ǰ�Τ�ΤǤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n	 	: �ե�`�෬��
								//	ofs	 	: Ԫ��AVI�ϤǤΥե�`��Υ��ե��å�
								//  ���ꂎ	: ����ǩ`���ؤΥݥ��� (NULL�ʤ�ʧ��)
								//			  ����ǩ`���ݥ��󥿤����ݤϥ���å��夫���Ɨ������ޤ��Є�
	void		*(*get_disp_pixelp)( void *editp,DWORD format );
								//	��ʾ����Ƥ���ե�`��λ���ǩ`���Υݥ��󥿤�ȡ�ä��ޤ�
								//	�ǩ`���ϥե��륿��Τ�ΤǤ�
								//	��ʾ�ե��륿�Τ�ʹ�ÿ��ܤǤ���
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	format	: ����ե��`�ޥå�( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 )
								//  ���ꂎ	: ����ǩ`���ؤΥݥ��� (NULL�ʤ�ʧ��)
								//			  ����ǩ`���ݥ��󥿤����ݤϴΤ��ⲿ�v����ʹ�����ᥤ��˄I�������ޤ��Є�
	BOOL		(*get_pixel_source)( void *editp,int n,void *pixelp,DWORD format );
								//	ָ�������ե�`��λ���ǩ`�����i���z�ߤޤ�
								//	�ǩ`���ϥե��륿ǰ�Τ�ΤǤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n	 	: �ե�`�෬��
								//  pixelp	: DIB��ʽ�ǩ`�����{����ݥ���
								//	format	: ����ե��`�ޥå�( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 )
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*get_pixel_filtered_ex)( void *editp,int n,void *pixelp,int *w,int *h,DWORD format );
								//	ָ�������ե�`��λ���ǩ`�����i���z�ߤޤ�
								//	�ǩ`���ϥե��륿��Τ�ΤǤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n	 	: �ե�`�෬��
								//  pixelp	: DIB��ʽ�ǩ`�����{����ݥ��� (NULL�ʤ黭�񥵥��������򷵤��ޤ�)
								//	w,h		: ����Υ����� (NULL�ʤ�DIB��ʽ�ǩ`�������򷵤��ޤ�)
								//	format	: ����ե��`�ޥå�( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 )
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	PIXEL_YC	*(*get_ycp_filtering_cache_ex)( void *fp,void *editp,int n,int *w,int *h );
								//	ָ�������ե�`��λ���ǩ`���Υ���å���ݥ��󥿤�ȡ�ä��ޤ�
								//	set_ycp_filtering_cache_size()���O���ˤ������äƥ���å��夵��ޤ�
								//	�ǩ`�����Է֤Υե��륿��ֱǰ�ޤǥե��륿������ΤǤ�
								//	fp	 	: �ե��륿������Υݥ���
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	n	 	: �ե�`�෬��
								//	w,h		: ȡ�ä�������Υ����� (NULL�ʤ�oҕ����ޤ�)
								//  ���ꂎ	: ����ǩ`���ؤΥ���å���ݥ��� (NULL�ʤ�ʧ��)
								//			  ����ǩ`���ݥ��󥿤����ݤϥ���å��夫���Ɨ������ޤ��Є�
	BOOL		(*exec_multi_thread_func)( MULTI_THREAD_FUNC func,void *param1,void *param2 );
								//	ָ�������v���򥷥��ƥ���O�����ˏꤸ������å����Ǻ��ӳ����ޤ�
								//	���ӳ����줿�v���ڤ���Win32API���ⲿ�v��(rgb2yc,yc2rgb�ϳ���)��ʹ�ä��ʤ��Ǥ�������
								//	func	: �ޥ������åɤǺ��ӳ����v��
								//	param1 	: ���ӳ����v���˶ɤ����åѥ��`��
								//	param2 	: ���ӳ����v���˶ɤ����åѥ��`��
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	PIXEL_YC	*(*create_yc)( void );
								//	�դΥե�`�໭��ǩ`���I������ɤ��ޤ�
								//	ycp_edit��ͬ�����ⲿ�v����ʹ�äǤ��ޤ���
								//	FILTER_PROC_INFO��ycp_edit,ycp_temp������椨�뤳�Ȥϳ����ޤ���
								//  ���ꂎ	: ���ɤ����ե�`�໭��ǩ`���ؤΥݥ��� (NULL�ʤ�ʧ��)
	void		(*delete_yc)( PIXEL_YC *ycp );
								//	create_yc�����ɤ����I����������ޤ�
	BOOL 		(*load_image)( PIXEL_YC *ycp,LPSTR file,int *w,int *h,int flag );
								//	�ե�`�໭��ǩ`����BMP�ե����뤫�黭����i���z�ߤޤ�
								//	ycp     : ������i���z��ե�`�໭��ؤΥݥ��� (NULL�ʤ��軭�򤻤��˥������򷵤��ޤ�)
								//	file	: �i���z��BMP�ե�������
								//	w,h		: �i���z�������Υ����� (NULL��ָ���Ǥ��ޤ�)
								//	flag 	: NULL��ָ�����Ƥ�������
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	void		(*resize_yc)( PIXEL_YC *ycp,int w,int h,PIXEL_YC *ycp_src,int sx,int sy,int sw,int sh );
								//	�ե�`�໭��ǩ`����ꥵ�������ޤ�
								//	Ԫ���������λ����I���ꥵ�������뤳�Ȥ�����ޤ�
								//	ycp     : �ꥵ������Υե�`�໭����{����ݥ���
								//	w,h     : �ꥵ�����ν����
								//	ycp_src	: Ԫ����Υե�`�໭��ؤΥݥ���(NULL�ʤ�ycp��ͬ��)
								//	sx,sy	: Ԫ����Υꥵ���������I������Ϥ�����
								//	sw,sh	: Ԫ����Υꥵ���������I��Υ�����
	void 		(*copy_yc)( PIXEL_YC *ycp,int x,int y,PIXEL_YC *ycp_src,int sx,int sy,int sw,int sh,int tr );
								//	�ե�`�໭��ǩ`����������I��򥳥ԩ`���ޤ�
								//	�軭���H������񥵥������I��˅��ޤ�褦�˥���åԥ󥰤򤷤ޤ�
								//	���ԩ`Ԫ�ȥ��ԩ`�Ȥ��I����ؤʤ�ʤ��褦�ˤ��Ƥ�������
								//	ycp     : ���ԩ`�ȤΥե�`�໭��ؤΥݥ���
								//	x,y		: ���ԩ`�Ȥ����Ϥ�����
								//	ycp_src	: ���ԩ`Ԫ�Υե�`�໭��ؤΥݥ���
								//	sx,sy	: ���ԩ`Ԫ�����Ϥ�����
								//	sw,sh	: ���ԩ`Ԫ�Υ�����
								//	tr      : ���ԩ`Ԫ��͸���� (0��4096)
	void 		(*draw_text)( PIXEL_YC *ycp,int x,int y,LPSTR text,int r,int g,int b,int tr,HFONT hfont,int *w,int *h );
								//	�ե�`�໭��ǩ`���˥ƥ����Ȥ��軭���ޤ�
								//	�軭���H������񥵥������I��˅��ޤ�褦�˥���åԥ󥰤򤷤ޤ�
								//	ycp     : �軭����ե�`�໭��ǩ`���ؤΥݥ��� (NULL�ʤ��軭�򤻤��˥������򷵤��ޤ�)
								//	x,y		: �軭�������Ϥ�����
								//	text	: �軭����ƥ����Ȥ�����
								//	r,g,b	: �軭ɫ (0��255)
								//	tr      : ͸���� (0��4096)
								//	hfont	: �軭��ʹ�ä���ե���� (NULL�ʤ�ǥե���ȤΥե����)
								//	w,h		: �軭�����ƥ������I��Υ����� (NULL��ָ���Ǥ��ޤ�)
	AVI_FILE_HANDLE (*avi_file_open)( LPSTR file,FILE_INFO *fip,int flag );
								//	AVI�ե�����򥪩`�ץ󤷤�avi_file_read_video(),avi_file_read_audio()��
								//	�ǩ`�����i���z����Υϥ�ɥ��ȡ�ä��ޤ���
								//	�������ФΥե�����ȥե��`�ޥå�(fps�䥵��ץ�󥰥�`�ȵ�)�����ʤ���Ϥ�����Τ�ע�⤷�Ƥ���������
								//	file    : �i���z��AVI�ե������� (�����ץ饰������i���z���ե������ָ���Ǥ��ޤ�)
								//  fip		: �ե����륤��ե���`���������ؤΥݥ��� (�i���z����ե������������ޤ�)
								//	flag 	: �i���z�ߥե饰
								//	AVI_FILE_OPEN_FLAG_ONLY_YUY2		: YUY2 ��չ�_����褦�ˤ��ޤ�
								//	AVI_FILE_OPEN_FLAG_ONLY_RGB24		: RGB24��չ�_����褦�ˤ��ޤ�
								//	AVI_FILE_OPEN_FLAG_ONLY_RGB32		: RGB32��չ�_����褦�ˤ��ޤ�
								//	AVI_FILE_OPEN_FLAG_VIDEO_ONLY		: �ӥǥ��Τ��i���z��褦�ˤ��ޤ�
								//	AVI_FILE_OPEN_FLAG_AUDIO_ONLY		: ���`�ǥ����Τ��i���z��褦�ˤ��ޤ�
								//  ���ꂎ	: AVI�ե�����ϥ�ɥ� (NULL�ʤ�ʧ��)
	void 		(*avi_file_close)( AVI_FILE_HANDLE afh );
								//	AVI�ե�����򥯥�`�����ޤ�
								//	afh		: AVI�ե�����ϥ�ɥ�
	BOOL 		(*avi_file_read_video)( AVI_FILE_HANDLE afh,PIXEL_YC *ycp,int n );
								//	�ե�`�໭��ǩ`����AVI�ե����뤫�黭��ǩ`�����i���z�ߤޤ�
								//	afh		: AVI�ե�����ϥ�ɥ�
								//	ycp     : ����ǩ`�����i���z��ե�`�໭��ؤΥݥ���
								//	n		: �ե�`�෬��
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	int 		(*avi_file_read_audio)( AVI_FILE_HANDLE afh,void *buf,int n );
								//	AVI�ե����뤫�������ǩ`�����i���z�ߤޤ�
								//	afh		: AVI�ե�����ϥ�ɥ�
								//	buf     : �������i���z��Хåե��ؤΥݥ���
								//	n		: �ե�`�෬��
								//  ���ꂎ	: �i���z�������ץ���
	void 		*(*avi_file_get_video_pixelp)( AVI_FILE_HANDLE afh,int n );
								//	AVI�ե����뤫���i���z���DIB��ʽ�λ���ǩ`���Υݥ��󥿤�ȡ�ä��ޤ�
								//	ȡ�äǤ��뻭��ǩ`���Υե��`�ޥåȤ�avi_file_open()��ȡ�ä���
								//	FILE_INFO�Υӥǥ�չ�_��ʽ�ˤʤ�ޤ���
								//	afh		: AVI�ե�����ϥ�ɥ�
								//	n		: �ե�`�෬��
								//  ���ꂎ	: DIB��ʽ�ǩ`���ؤΥݥ��� (NULL�ʤ�ʧ��)
								//			  ����ǩ`���ݥ��󥿤����ݤϴΤ��ⲿ�v����ʹ�����ᥤ��˄I�������ޤ��Є�
	LPSTR		(*get_avi_file_filter)( int type );
								//	avi_file_open()���i���z���ե�����Υե�����ե��륿��ȡ�ä��ޤ�
								//	type	: �ե�����ηN�
								//	GET_AVI_FILE_FILTER_TYPE_VIDEO	: �ӥǥ���
								//	GET_AVI_FILE_FILTER_TYPE_AUDIO	: ���`�ǥ���
								//  ���ꂎ	: �ե�����ե��륿�ؤΥݥ���
	int			(*avi_file_read_audio_sample)( AVI_FILE_HANDLE afh,int start,int length,void *buf );
								//	AVI�ե����뤫�������ǩ`�����i���z�ߤޤ�
								//	afh		: AVI�ե�����ϥ�ɥ�
								//	start   : �i���z���_ʼ����ץ뷬��
								//	length	: �i���z�ॵ��ץ���
								//	buf		: �ǩ`�����i���z��Хåե��ؤΥݥ���
								//  ���ꂎ	: �i���z�������ץ���
	int			(*avi_file_set_audio_sample_rate)( AVI_FILE_HANDLE afh,int audio_rate,int audio_ch );
								//	avi_file_read_audio_sample()���i���z�������Υ���ץ�󥰥�`�ȵȤ������ޤ�
								//	afh		: AVI�ե�����ϥ�ɥ�
								//	audio_rate	: ��������ץ�󥰥�`��
								//	audio_ch	: ���������ͥ���
								//  ���ꂎ	: �����������ץ�󥰥�`�ȤǤξt����ץ���
	BYTE		*(*get_frame_status_table)( void *editp,int type );
								//	�ե�`��Υ��Ʃ`��������{����Ƥ���Хåե��ؤΥݥ��󥿤�ȡ�ä��ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  type	: ���Ʃ`�����ηN�
								//	FARME_STATUS_TYPE_EDIT_FLAG	: �����ե饰
								//	FARME_STATUS_TYPE_INTER		: ���󥿩`��`��
								//  ���ꂎ	: �Хåե��ؤΥݥ���
								//			  �Хåե��ؤΥݥ��󥿤����ݤϾ����ե����뤬����`�������ޤ��Є�
	BOOL		(*set_undo)( void *editp );
								//	�F�ڤξ���״�r�򥢥�ɥ��Хåե����O�����ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL		(*add_menu_item)( void *fp,LPSTR name,HWND hwnd,int id,int def_key,int flag );
								//	�ᥤ�󥦥���ɥ����O����˥�`�Ŀ��׷�Ӥ��ޤ�
								//	��˥�`���x�k���줿�r��hwnd��ָ������������ɥ���
								//	WM_FILTER_COMMAND�Υ�å��`�����ͤ�ޤ�
								//	���ؤ�func_init()��WM_FILTER_INIT������ӳ����褦�ˤ��Ƥ���������
								//	fp	 	: �ե��륿������Υݥ���
								//	name 	: ��˥�`����ǰ
								//	hwnd 	: WM_FILTER_COMMAND���ͤ륦����ɥ��ϥ�ɥ�
								//	id	 	: WM_FILTER_COMMAND��WPARAM
								//	def_key	: �˜ʤΥ���`�ȥ��åȥ��`�΁��륭�`���`�� (NULL�ʤ�o��)
								//	flag	: �ե饰
								//	ADD_MENU_ITEM_FLAG_KEY_SHIFT	: �˜ʤΥ���`�ȥ��åȥ��`��SHIFT+���`�ˤ���
								//	ADD_MENU_ITEM_FLAG_KEY_CTRL		: �˜ʤΥ���`�ȥ��åȥ��`��CTRL+���`�ˤ���
								//	ADD_MENU_ITEM_FLAG_KEY_ALT		: �˜ʤΥ���`�ȥ��åȥ��`��ALT+���`�ˤ���
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL 		(*edit_open)( void *editp,LPSTR file,int flag );
								//	�����ե�������_���ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	file 	: �ե�������
								//	flag 	: �ե饰
								//	EDIT_OPEN_FLAG_ADD			: ׷���i���z�ߤ򤷤ޤ�
								//	EDIT_OPEN_FLAG_AUDIO		: �����i���z�ߤ򤷤ޤ�
								//	EDIT_OPEN_FLAG_PROJECT		: �ץ������ȥե�������_���ޤ�
								//	EDIT_OPEN_FLAG_DIALOG		: �i���z�ߥ����������ʾ���ޤ�
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL 		(*edit_close)( void *editp );
								//	�����ե�������]���ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL 		(*edit_output)( void *editp,LPSTR file,int flag,LPSTR type );
								//	�����ǩ`����AVI�������ޤ�
								//	WAV������ץ饰�������������ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//	file 	: �����ե�������
								//	flag	: �ե饰
								//	EDIT_OUTPUT_FLAG_NO_DIALOG	: ���������������ʾ���ޤ���
								//	EDIT_OUTPUT_FLAG_WAV		: WAV�����򤷤ޤ�
								//	type	: �����ץ饰�������ǰ (NULL�ʤ�AVI/WAV����)
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	BOOL 		(*set_config)( void *editp,int n,LPSTR name );
								//	�ץ�ե�������O�����ޤ�
								//	editp 	: ���ǥ��åȥϥ�ɥ�
								//  n		: �ץ�ե�����h���η���
								//  name	: �ץ�ե��������ǰ
								//  ���ꂎ	: TRUE�ʤ�ɹ�
	int			reserve[7];
} EXFUNC;
#define	AVI_FILE_OPEN_FLAG_VIDEO_ONLY		16
#define	AVI_FILE_OPEN_FLAG_AUDIO_ONLY		32
#define	AVI_FILE_OPEN_FLAG_ONLY_YUY2		0x10000
#define	AVI_FILE_OPEN_FLAG_ONLY_RGB24		0x20000
#define	AVI_FILE_OPEN_FLAG_ONLY_RGB32		0x40000
#define	GET_AVI_FILE_FILTER_TYPE_VIDEO		0
#define	GET_AVI_FILE_FILTER_TYPE_AUDIO		1
#define FARME_STATUS_TYPE_EDIT_FLAG			0
#define FARME_STATUS_TYPE_INTER				1
#define ADD_MENU_ITEM_FLAG_KEY_SHIFT		1
#define ADD_MENU_ITEM_FLAG_KEY_CTRL			2
#define ADD_MENU_ITEM_FLAG_KEY_ALT			4
#define	EDIT_OPEN_FLAG_ADD					2
#define	EDIT_OPEN_FLAG_AUDIO				16
#define	EDIT_OPEN_FLAG_PROJECT				512
#define	EDIT_OPEN_FLAG_DIALOG				65536
#define	EDIT_OUTPUT_FLAG_NO_DIALOG			2
#define	EDIT_OUTPUT_FLAG_WAV				4

//	�ե��륿������
typedef struct {
	int		flag;				//	�ե��륿�Υե饰
								//	FILTER_FLAG_ALWAYS_ACTIVE		: �ե��륿�򳣤˥����ƥ��֤ˤ��ޤ�
								//	FILTER_FLAG_CONFIG_POPUP		: �O����ݥåץ��åץ�˥�`�ˤ��ޤ�
								//	FILTER_FLAG_CONFIG_CHECK		: �O��������å��ܥå�����˥�`�ˤ��ޤ�
								//	FILTER_FLAG_CONFIG_RADIO		: �O����饸���ܥ����˥�`�ˤ��ޤ�
								//	FILTER_FLAG_EX_DATA				: �����ǩ`���򱣴������褦�ˤ��ޤ�
								//	FILTER_FLAG_PRIORITY_HIGHEST	: �ե��륿�Υץ饤����ƥ��򳣤�����λ�ˤ��ޤ�
								//	FILTER_FLAG_PRIORITY_LOWEST		: �ե��륿�Υץ饤����ƥ��򳣤�����λ�ˤ��ޤ�
								//	FILTER_FLAG_WINDOW_THICKFRAME	: ������������ܤʥ�����ɥ�������ޤ�
								//	FILTER_FLAG_WINDOW_SIZE			: �O��������ɥ��Υ�������ָ��������褦�ˤ��ޤ�
								//	FILTER_FLAG_DISP_FILTER			: ��ʾ�ե��륿�ˤ��ޤ�
								//	FILTER_FLAG_REDRAW				: ���軭��plugin�ȤǄI����褦�ˤ��ޤ�
								//	FILTER_FLAG_EX_INFORMATION		: �ե��륿�Β��������O���Ǥ���褦�ˤ��ޤ�
								//	FILTER_FLAG_INFORMATION			: FILTER_FLAG_EX_INFORMATION ��ʹ���褦�ˤ����¤���
								//	FILTER_FLAG_NO_CONFIG			: �O��������ɥ����ʾ���ʤ��褦�ˤ��ޤ�
								//	FILTER_FLAG_AUDIO_FILTER		: ���`�ǥ����ե��륿�ˤ��ޤ�
								//	FILTER_FLAG_RADIO_BUTTON		: �����å��ܥå�����饸���ܥ���ˤ��ޤ�
								//	FILTER_FLAG_WINDOW_HSCROLL		: ˮƽ������`��Щ`��֤ĥ�����ɥ�������ޤ�
								//	FILTER_FLAG_WINDOW_VSCROLL		: ��ֱ������`��Щ`��֤ĥ�����ɥ�������ޤ�
								//	FILTER_FLAG_INTERLACE_FILTER	: ���󥿩`��`������ե��륿�ˤ��ޤ�
								//	FILTER_FLAG_NO_INIT_DATA		: func_proc()�λ���γ��ڥǩ`�������ɤ��ʤ��褦�ˤ��ޤ�
								//	FILTER_FLAG_IMPORT				: ����ݩ`�ȥ�˥�`������ޤ�
								//	FILTER_FLAG_EXPORT				: �������ݩ`�ȥ�˥�`������ޤ�
								//	FILTER_FLAG_MAIN_MESSAGE		: func_WndProc()��WM_FILTER_MAIN_???�Υ�å��`�����ͤ�褦�ˤ��ޤ�
	int		x,y;				//	�O��������ɥ��Υ����� (FILTER_FLAG_WINDOW_SIZE�����äƤ���r���Є�)
								//	�O������ FILTER_WINDOW_SIZE_CLIENT ��OR�����O������ȥ��饤������I��ǤΥ�����ָ���ˤʤ�ޤ���
								//	�O������ FILTER_WINDOW_SIZE_ADD ��OR�����O������Ș˜ʤΥ����������׷�ӷ֤�ָ���ˤʤ�ޤ���
	TCHAR	*name;				//	�ե��륿����ǰ
	int		track_n;			//	�ȥ�å��Щ`����
	TCHAR	**track_name;		//	�ȥ�å��Щ`����ǰ���ؤΥݥ���(�ȥ�å��Щ`����0�ʤ�NULL�Ǥ褤)
	int		*track_default;		//	�ȥ�å��Щ`�γ��ڂ����ؤΥݥ���(�ȥ�å��Щ`����0�ʤ�NULL�Ǥ褤)
	int		*track_s,*track_e;	//	�ȥ�å��Щ`���������������� (NULL�ʤ�ȫ��0��256)
	int		check_n;			//	�����å��ܥå�������
	TCHAR	**check_name;		//	�����å��ܥå�������ǰ���ؤΥݥ���(�����å��ܥå�������0�ʤ�NULL�Ǥ褤)
	int		*check_default;		//	�����å��ܥå����γ��ڂ����ؤΥݥ���(�����å��ܥå�������0�ʤ�NULL�Ǥ褤)
								//	���ڂ����ޥ��ʥ����Έ��Ϥϥܥ���ˤʤ�ޤ����ܥ����Ѻ�����Ȥ���WM_COMMAND( WPARAM = MID_FILTER_BUTTON + n )�Υ�����ɥ���å��`�����ͤ��ޤ�
	BOOL	(*func_proc)( void *fp,FILTER_PROC_INFO *fpip );
								//	�ե��륿�I���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
	BOOL	(*func_init)( void *fp );
								//	�_ʼ�r�˺��Ф���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
	BOOL	(*func_exit)( void *fp );
								//	�K�˕r�˺��Ф���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
	BOOL	(*func_update)( void *fp,int status );
								//	�Է֤��O����������줿�Ȥ��˺��Ф���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
								//	FILTER_UPDATE_STATUS_ALL		: ȫ�Ŀ��������줿
								//	FILTER_UPDATE_STATUS_TRACK + n	: n��Ŀ�Υȥ�å��Щ`��������줿
								//	FILTER_UPDATE_STATUS_CHECK + n	: n��Ŀ�Υ����å��ܥå�����������줿
	BOOL 	(*func_WndProc)( HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam,void *editp,void *fp );
								//	�O��������ɥ��˥�����ɥ���å��`���������r�˺��Ф���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
								//	VFAPI�����r�ˤϺ��Ф�ޤ���
								//	ͨ���Υ�å��`����������¤Β�����å��`�����ͤ��ޤ�
								//	WM_FILTER_UPDATE		: ���ե��륿�O���侎�����ݤ�������줿ֱ����ͤ��ޤ�
								//	WM_FILTER_FILE_OPEN		: �����ե����뤬���`�ץ󤵤줿ֱ����ͤ��ޤ�
								//	WM_FILTER_FILE_UPDATE	: �����ե�����θ���(׷�Ӥ������i���z�ߵ�)�����ä�ֱ����ͤ��ޤ�
								//	WM_FILTER_FILE_CLOSE	: �����ե����뤬����`�������ֱǰ���ͤ��ޤ�
								//	WM_FILTER_INIT			: �_ʼֱ����ͤ��ޤ�
								//	WM_FILTER_EXIT			: �K��ֱǰ���ͤ��ޤ�
								//	WM_FILTER_SAVE_START	: ���`�֤��_ʼ�����ֱǰ���ͤ��ޤ�
								//	WM_FILTER_SAVE_END		: ���`�֤��K�ˤ��줿ֱ����ͤ��ޤ�
								//	WM_FILTER_IMPORT		: ����ݩ`�Ȥ��x�k���줿ֱ����ͤ��ޤ�
								//	WM_FILTER_EXPORT		: �������ݩ`�Ȥ��x�k���줿ֱ����ͤ��ޤ�
								//	WM_FILTER_CHANGE_ACTIVE	: �ե��륿���Є�/�o����������줿ֱ����ͤ��ޤ�
								//	WM_FILTER_CHANGE_WINDOW	: �ե��륿������ɥ��α�ʾ/�Ǳ�ʾ��������줿ֱ����ͤ��ޤ�
								//	WM_FILTER_CHANGE_PARAM	: �Է֤Υե��륿���O����������줿ֱ����ͤ��ޤ�
								//	WM_FILTER_CHANGE_EDIT	: ������/�Ǿ����Ф�������줿ֱ����ͤ��ޤ�
								//	�����Խ��Υ�å��`����FILTER_FLAG_MAIN_MESSAGE�O���r�Τ��ͤ��ޤ�
								//	WM_FILTER_MAIN_MOUSE_DOWN	: �ᥤ�󥦥���ɥ��ǥޥ�������ܥ���Ѻ���줿�r���ͤ��ޤ�
								//	WM_FILTER_MAIN_MOUSE_UP		: �ᥤ�󥦥���ɥ��ǥޥ������ƄӤ����r���ͤ��ޤ�
								//	WM_FILTER_MAIN_MOUSE_MOVE	: �ᥤ�󥦥���ɥ��ǥޥ�������ܥ����x���줿�r���ͤ��ޤ�
								//	WM_FILTER_MAIN_MOUSE_DBLCLK	: �ᥤ�󥦥���ɥ��ǥޥ�������ܥ��󤬥��֥륯��å����줿�r���ͤ��ޤ�
								//	WM_FILTER_MAIN_MOUSE_R_DOWN	: �ᥤ�󥦥���ɥ��ǥޥ������ҥܥ���Ѻ���줿�r���ͤ��ޤ�
								//	WM_FILTER_MAIN_MOUSE_R_UP	: �ᥤ�󥦥���ɥ��ǥޥ������ҥܥ����x���줿�r���ͤ��ޤ�
								//	WM_FILTER_MAIN_MOUSE_WHEEL	: �ᥤ�󥦥���ɥ��ǥޥ����Υۥ��`�뤬��ܞ�����r���ͤ��ޤ�
								//	WM_FILTER_MAIN_KEY_DOWN		: �ᥤ�󥦥���ɥ��ǥ��`��Ѻ���줿�r���ͤ��ޤ�
								//	WM_FILTER_MAIN_KEY_UP		: �ᥤ�󥦥���ɥ��ǥ��`���x���줿�r���ͤ��ޤ�
								//	WM_FILTER_MAIN_MOVESIZE		: �ᥤ�󥦥���ɥ���λ�ä䥵������������줿�r���ͤ��ޤ�
								//	WM_FILTER_MAIN_CONTEXTMENU	: �ᥤ�󥦥���ɥ��ǥ���ƥ����ȥ�˥�`����ʾ�����r���ͤ��ޤ�
								//	WM_FILTER_MAIN_MOUSE_???��lparam�ˤϾ��������ϤǤ����ˤ����ޤ�(�����������0�ˤʤ�ޤ�)
								//	WM_FILTER_MAIN_MOUSE_WHEEL��wparam����λ��`�ɤ˥ۥ��`��λ�ܞ�������ޤ�
								//	WM_FILTER_MAIN_KEY_???��wparam�ˤρ��륭�`���`�ɤ����ޤ�
								//	WM_FILTER_MAIN_MOVESIZE��lparam�ˤϥᥤ�󥦥���ɥ��Υ�����ɥ��ϥ�ɥ뤬���ޤ�
								//	WM_FILTER_MAIN_CONTEXTMENU��lparam�ˤϥ�����`�����ˤ����ޤ�
								//	WM_FILTER_MAIN_CONTEXTMENU�ǥ�˥�`���ʾ�����r�ϑ��ꂎ��TRUE�ˤ��Ƥ�������(���軭�Ϥ���ޤ���)
								//	���ꂎ��TRUE�ˤ���Ⱦ������ݤ����¤��줿�Ȥ���ȫ�夬���軭����ޤ�
	int		*track;				//	�ȥ�å��Щ`���O�������ؤΥݥ��� (AviUtl�Ȥ��O������ޤ�)
	int		*check;				//	�����å��ܥå������O�������ؤΥݥ��� (AviUtl�Ȥ��O������ޤ�)
	void	*ex_data_ptr;		//	�����ǩ`���I��ؤΥݥ��� (FILTER_FLAG_EX_DATA�����äƤ���r���Є�)
	int		ex_data_size;		//	�����ǩ`�������� (FILTER_FLAG_EX_DATA�����äƤ���r���Є�)
	TCHAR	*information;		//	�ե��륿���ؤΥݥ��� (FILTER_FLAG_EX_INFORMATION�����äƤ���r���Є�)
	BOOL	(*func_save_start)( void *fp,int s,int e,void *editp );
								//	���`�֤��_ʼ�����ֱǰ�˺��Ф���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
								//	s	 	: ���`�֤������^�ե�`��
								//	e 		: ���`�֤�����K�ե�`��
								//  ���ꂎ	: �ɹ��ʤ�TRUE
	BOOL	(*func_save_end)( void *fp,void *editp );
								//	���`�֤��K�ˤ���ֱǰ�˺��Ф���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
	EXFUNC	*exfunc;			//	�ⲿ�v���Ʃ`�֥�ؤΥݥ��� (AviUtl�Ȥ��O������ޤ�)
	HWND	hwnd;				//	������ɥ��ϥ�ɥ� (AviUtl�Ȥ��O������ޤ�)
	HINSTANCE	dll_hinst;		//	DLL�Υ��󥹥��󥹥ϥ�ɥ� (AviUtl�Ȥ��O������ޤ�)
	void	*ex_data_def;		//	�����ǩ`���γ��ڂ��ǩ`���I��ؤΥݥ��� (NULL�ʤ���ڻ�����ޤ���)
	BOOL	(*func_is_saveframe)( void *fp,void *editp,int saveno,int frame,int fps,int edit_flag,int inter );
								//	���󥿩`��`������ե��륿�Ǳ��椹��ե�`���Q���r�˺��Ф���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
								//	saveno		: ���`�֤��빠������^����Υե�`�෬��
								//	frame		: �����ե�`�෬��
								//	fps			: �ե�`���`�ȤΉ�����O���� (30,24,20,15,10)
								//	edit_flag	: �����ե饰
								//	inter		: �ե�`��Υ��󥿩`��`��
								//	���ꂎ		: TRUE�򷵤��ȱ���ե�`�ࡢFALSE�򷵤����g�����ե�`��ˤʤ�ޤ���
	BOOL	(*func_project_load)( void *fp,void *editp,void *data,int size );
								//	�ץ������ȥե����뤫��ǩ`�����i���z����r�˺��Ф���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
								//	�ץ������ȥե�����˱��椷���ǩ`�����o�����ϤϺ��Ф�ޤ���
								//	data 	: �ץ������Ȥ����i���z����ǩ`���ؤΥݥ���
								//	size 	: �ץ������Ȥ����i���z����ǩ`���ΥХ�����
								//  ���ꂎ	: �ɹ��ʤ�TRUE
	BOOL	(*func_project_save)( void *fp,void *editp,void *data,int *size );
								//	�ץ������ȥե�����򥻩`�֤��Ƥ���r�˺��Ф���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
								//	�ץ������ȥե�����˥ե��륿�Υǩ`���򱣴椷�ޤ�
								//	��AviUtl�����ʼ��˱��極����ȡ�äΞ��data��NULL�Ǻ��ӳ����졢�A���ƌg�H�Υǩ`����ȡ�ä����˺��ӳ�����ޤ���
								//	data 	: �ץ������Ȥ˕����z��ǩ`�����{����Хåե��ؤΥݥ��� (NULL�Έ��Ϥϥǩ`���ΥХ������Τ߷���)
								//	size 	: �ץ������Ȥ˕����z��ǩ`���ΥХ������򷵤��ݥ���
								//  ���ꂎ	: ���椹��ǩ`��������ʤ�TRUE
	BOOL	(*func_modify_title)( void *fp,void *editp,int frame,LPSTR title,int max_title );
								//	�ᥤ�󥦥���ɥ��Υ����ȥ�Щ`���ʾ����r�˺��Ф���v���ؤΥݥ��� (NULL�ʤ���Ф�ޤ���)
								//	�����ȥ�Щ`�������Ф����Ǥ��ޤ� (δ�����r�������r�Ϻ��Ф�ޤ���)
								//	frame		: �����ե�`�෬��
								//	title 		: ��ʾ���륿���ȥ�Щ`��������
								//	max_title 	: title�ΥХåե�������
								//  ���ꂎ	: �ɹ��ʤ�TRUE
	TCHAR	*dll_path;			//	Plugins�ǥ��쥯�ȥ�Υ��֥ǥ��쥯�ȥ��DLL������r�Τߡ����֥ǥ��쥯�ȥ��������ޤ���
	int		reserve[2];			//	�����ä���s����Ƥޤ���NULL�ˤ��Ƥ���������

} FILTER;
#define	FILTER_FLAG_ACTIVE				1
#define	FILTER_FLAG_ALWAYS_ACTIVE		4
#define	FILTER_FLAG_CONFIG_POPUP		8
#define	FILTER_FLAG_CONFIG_CHECK		16
#define	FILTER_FLAG_CONFIG_RADIO		32
#define	FILTER_FLAG_EX_DATA				1024
#define	FILTER_FLAG_PRIORITY_HIGHEST	2048
#define	FILTER_FLAG_PRIORITY_LOWEST		4096
#define	FILTER_FLAG_WINDOW_THICKFRAME	8192
#define	FILTER_FLAG_WINDOW_SIZE			16384
#define	FILTER_FLAG_DISP_FILTER			32768
#define	FILTER_FLAG_REDRAW				0x20000
#define	FILTER_FLAG_EX_INFORMATION		0x40000
#define	FILTER_FLAG_INFORMATION			0x80000
#define	FILTER_FLAG_NO_CONFIG			0x100000
#define	FILTER_FLAG_AUDIO_FILTER		0x200000
#define	FILTER_FLAG_RADIO_BUTTON		0x400000
#define	FILTER_FLAG_WINDOW_HSCROLL		0x800000
#define	FILTER_FLAG_WINDOW_VSCROLL		0x1000000
#define	FILTER_FLAG_INTERLACE_FILTER	0x4000000
#define	FILTER_FLAG_NO_INIT_DATA		0x8000000
#define	FILTER_FLAG_IMPORT				0x10000000
#define	FILTER_FLAG_EXPORT				0x20000000
#define	FILTER_FLAG_MAIN_MESSAGE		0x40000000
#define WM_FILTER_UPDATE				(WM_USER+100)
#define WM_FILTER_FILE_OPEN				(WM_USER+101)
#define WM_FILTER_FILE_CLOSE			(WM_USER+102)
#define WM_FILTER_INIT					(WM_USER+103)
#define WM_FILTER_EXIT					(WM_USER+104)
#define WM_FILTER_SAVE_START			(WM_USER+105)
#define WM_FILTER_SAVE_END				(WM_USER+106)
#define WM_FILTER_IMPORT				(WM_USER+107)
#define WM_FILTER_EXPORT				(WM_USER+108)
#define WM_FILTER_CHANGE_ACTIVE			(WM_USER+109)
#define WM_FILTER_CHANGE_WINDOW			(WM_USER+110)
#define WM_FILTER_CHANGE_PARAM			(WM_USER+111)
#define WM_FILTER_CHANGE_EDIT			(WM_USER+112)
#define WM_FILTER_COMMAND				(WM_USER+113)
#define	WM_FILTER_FILE_UPDATE			(WM_USER+114)
#define	WM_FILTER_MAIN_MOUSE_DOWN		(WM_USER+120)
#define	WM_FILTER_MAIN_MOUSE_UP			(WM_USER+121)
#define	WM_FILTER_MAIN_MOUSE_MOVE		(WM_USER+122)
#define	WM_FILTER_MAIN_KEY_DOWN			(WM_USER+123)
#define	WM_FILTER_MAIN_KEY_UP			(WM_USER+124)
#define	WM_FILTER_MAIN_MOVESIZE			(WM_USER+125)
#define	WM_FILTER_MAIN_MOUSE_DBLCLK		(WM_USER+126)
#define	WM_FILTER_MAIN_MOUSE_R_DOWN		(WM_USER+127)
#define	WM_FILTER_MAIN_MOUSE_R_UP		(WM_USER+128)
#define	WM_FILTER_MAIN_MOUSE_WHEEL		(WM_USER+129)
#define	WM_FILTER_MAIN_CONTEXTMENU		(WM_USER+130)
#define FILTER_UPDATE_STATUS_ALL		0
#define FILTER_UPDATE_STATUS_TRACK		0x10000
#define FILTER_UPDATE_STATUS_CHECK		0x20000
#define	FILTER_WINDOW_SIZE_CLIENT		0x10000000
#define	FILTER_WINDOW_SIZE_ADD			0x30000000

//	�ե��륿DLL�Ø�����
typedef struct {
	int			flag;
	int			x,y;
	TCHAR		*name;
	int			track_n;
	TCHAR		**track_name;
	int			*track_default;
	int			*track_s,*track_e;
	int			check_n;
	TCHAR		**check_name;
	int			*check_default;
	BOOL		(*func_proc)( FILTER *fp,FILTER_PROC_INFO *fpip );
	BOOL		(*func_init)( FILTER *fp );
	BOOL		(*func_exit)( FILTER *fp );
	BOOL		(*func_update)( FILTER *fp,int status );
	BOOL 		(*func_WndProc)( HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam,void *editp,FILTER *fp );
	int			*track,*check;
	void		*ex_data_ptr;
	int			ex_data_size;
	TCHAR		*information;
	BOOL		(*func_save_start)( FILTER *fp,int s,int e,void *editp );
	BOOL		(*func_save_end)( FILTER *fp,void *editp );
	EXFUNC		*exfunc;
	HWND		hwnd;
	HINSTANCE	dll_hinst;
	void		*ex_data_def;
	BOOL		(*func_is_saveframe)( FILTER *fp,void *editp,int saveno,int frame,int fps,int edit_flag,int inter );
	BOOL		(*func_project_load)( FILTER *fp,void *editp,void *data,int size );
	BOOL		(*func_project_save)( FILTER *fp,void *editp,void *data,int *size );
	BOOL		(*func_modify_title)( FILTER *fp,void *editp,int frame,LPSTR title,int max_title );
	TCHAR		*dll_path;
	int			reserve[2];
} FILTER_DLL;

#define	MID_FILTER_BUTTON			12004

BOOL func_proc( FILTER *fp,FILTER_PROC_INFO *fpip );
BOOL func_init( FILTER *fp );
BOOL func_exit( FILTER *fp );
BOOL func_update( FILTER *fp,int status );
BOOL func_WndProc( HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam,void *editp,FILTER *fp );
BOOL func_save_start( FILTER *fp,int s,int e,void *editp );
BOOL func_save_end( FILTER *fp,void *editp );
BOOL func_is_saveframe( FILTER *fp,void *editp,int saveno,int frame,int fps,int edit_flag,int inter );
BOOL func_project_load( FILTER *fp,void *editp,void *data,int size );
BOOL func_project_save( FILTER *fp,void *editp,void *data,int *size );
BOOL func_modify_title( FILTER *fp,void *editp,int frame,LPSTR title,int max_title );
