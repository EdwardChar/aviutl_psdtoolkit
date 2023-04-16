//----------------------------------------------------------------------------------
//	フィルタプラグイン ヘッダーファイル for AviUtl version 0.99k 以降
//	By ＫＥＮくん
//----------------------------------------------------------------------------------

//	YC構造体
typedef	struct {
	short	y;					//	画素(輝度    )データ (     0 ～ 4096 )
	short	cb;					//	画素(色差(青))データ ( -2048 ～ 2048 )
	short	cr;					//	画素(色差(赤))データ ( -2048 ～ 2048 )
								//	画素データは範囲外に出ていることがあります
								//	また範囲内に収めなくてもかまいません
} PIXEL_YC;

//	PIXEL構造体
typedef	struct {
	unsigned char	b,g,r;		//	画素(RGB)データ (0～255)
} PIXEL;

//	フィルタPROC用構造体
typedef struct {
	int			flag;			//	フィルタのフラグ
								//	FILTER_PROC_INFO_FLAG_INVERT_FIELD_ORDER	: フィールドオーダーを標準と逆に扱う ( 標準はボトム->トップになっています )
								//	FILTER_PROC_INFO_FLAG_INVERT_INTERLACE		: 解除方法を反転する ( インターレース解除フィルタのみ )
	PIXEL_YC	*ycp_edit;		//	画像データへのポインタ ( ycp_editとycp_tempは入れ替えれます )
	PIXEL_YC	*ycp_temp;		//	テンポラリ領域へのポインタ
	int			w,h;			//	現在の画像のサイズ ( 画像サイズは変更出来ます )
	int			max_w,max_h;	//	画像領域のサイズ
	int			frame;			//	現在のフレーム番号( 番号は0から )
	int			frame_n;		//	総フレーム数
	int			org_w,org_h;	//	元の画像のサイズ
	short		*audiop;		//	オーディオデータへのポインタ ( オーディオフィルタの時のみ )
								//	オーディオ形式はPCM16bitです ( 1サンプルは mono = 2byte , stereo = 4byte )
	int			audio_n;		//	オーディオサンプルの総数
	int			audio_ch;		//	オーディオチャンネル数
	PIXEL		*pixelp;		//	現在は使用されていません
	void		*editp;			//	エディットハンドル
	int			yc_size;		//	画像領域の画素のバイトサイズ
	int			line_size;		//	画像領域の幅のバイトサイズ
	int			reserve[8];		//	拡張用に予約されてます
} FILTER_PROC_INFO;
#define	FILTER_PROC_INFO_FLAG_INVERT_FIELD_ORDER	0x00010000
#define	FILTER_PROC_INFO_FLAG_INVERT_INTERLACE		0x00020000
//	※インターレース解除フィルタ時はycp_editに初期画像データが入っていません。
//	※インターレース解除フィルタ時はycp_edit,ycp_temp,w,hを変更できません。

//	フレームステータス構造体
typedef struct {
	int		video;			//	実際の映像データ番号
	int		audio;			//	実際の音声データ番号
	int		inter;			//	フレームのインターレース
							//	FRAME_STATUS_INTER_NORMAL	: 標準
							//	FRAME_STATUS_INTER_REVERSE	: 反転
							//	FRAME_STATUS_INTER_ODD		: 奇数
							//	FRAME_STATUS_INTER_EVEN		: 偶数
							//	FRAME_STATUS_INTER_MIX		: 二重化
							//	FRAME_STATUS_INTER_AUTO		: 自動
	int		index24fps;		//	現在は使用されていません
	int		config;			//	フレームのプロファイル環境の番号
	int		vcm;			//	フレームの圧縮設定の番号
	int		edit_flag;		//	編集フラグ
							//	EDIT_FRAME_EDIT_FLAG_KEYFRAME	: キーフレーム
							//	EDIT_FRAME_EDIT_FLAG_MARKFRAME	: マークフレーム
							//	EDIT_FRAME_EDIT_FLAG_DELFRAME	: 優先間引きフレーム
							//	EDIT_FRAME_EDIT_FLAG_NULLFRAME	: コピーフレーム
	int		reserve[9];		//	拡張用に予約されてます
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

//	ファイルインフォメーション構造体
typedef struct {
	int		flag;					//	ファイルのフラグ
									//	FILE_INFO_FLAG_VIDEO	: 映像が存在する
									//	FILE_INFO_FLAG_AUDIO	: 音声が存在する
	LPSTR	name;					//	ファイル名 ( avi_file_open()ではNULLになります )
	int		w,h;					//	元のサイズ
	int		video_rate,video_scale;	//	フレームレート
	int		audio_rate;				//	音声サンプリングレート
	int		audio_ch;				//	音声チャンネル数
	int		frame_n;				//	総フレーム数
	DWORD	video_decode_format;	//	ビデオ展開形式
	int		video_decode_bit;		//	ビデオ展開形式のビット数
	int		audio_n;				//	音声の総サンプル数 ( avi_file_open()の時のみ設定されます )
	int		reserve[4];				//	拡張用に予約されてます
} FILE_INFO;
#define FILE_INFO_FLAG_VIDEO	1
#define FILE_INFO_FLAG_AUDIO	2

//	システムインフォメーション構造体
typedef struct {
	int		flag;					//	システムフラグ
									//	SYS_INFO_FLAG_EDIT		: 編集中
									//	SYS_INFO_FLAG_VFAPI		: VFAPI動作時
									//	SYS_INFO_FLAG_USE_SSE	: SSE使用
									//	SYS_INFO_FLAG_USE_SSE2	: SSE2使用
	LPSTR	info;					//	バージョン情報
	int		filter_n;				//	登録されてるフィルタの数
	int		min_w,min_h;			//	編集出来る最小画像サイズ
	int		max_w,max_h;			//	編集出来る最大画像サイズ
	int		max_frame;				//	編集出来る最大フレーム数
	LPSTR	edit_name;				//	編集ファイル名 (ファイル名が決まっていない時は何も入っていません)
	LPSTR	project_name;			//	プロジェクトファイル名 (ファイル名が決まっていない時は何も入っていません)
	LPSTR	output_name;			//	出力ファイル名 (ファイル名が決まっていない時は何も入っていません)
	int		vram_w,vram_h;			//	編集用画像領域のサイズ
	int		vram_yc_size;			//	編集用画像領域の画素のバイト数
	int		vram_line_size;			//	編集用画像領域の幅のバイト数
	HFONT	hfont;					//	フィルタ設定ウィンドウで使用しているフォントのハンドル
	int		build;					//	ビルド番号 (新しいバージョンになるほど大きな値になります)
	int		reserve[2];				//	拡張用に予約されてます
} SYS_INFO;
#define SYS_INFO_FLAG_EDIT		1
#define SYS_INFO_FLAG_VFAPI		2
#define SYS_INFO_FLAG_USE_SSE	4
#define SYS_INFO_FLAG_USE_SSE2	8

//	マルチスレッド関数用の定義
typedef void (*MULTI_THREAD_FUNC)( int thread_id,int thread_num,void *param1,void *param2 );
								//	thread_id	: スレッド番号 ( 0 ～ thread_num-1 )
								//	thread_num	: スレッド数 ( 1 ～ )
								//	param1		: 汎用パラメータ
								//	param2		: 汎用パラメータ

//	AVI入力ファイルハンドル
typedef void*	AVI_FILE_HANDLE;

//	外部関数構造体
typedef struct {
	void		(*get_ycp_ofs)( void *editp,int n,int ofs );
								//	※出来るだけget_ycp_source_cache()の方を使用するようにしてください
								//	指定したフレームのAVIファイル上でのオフセット分移動した
								//	フレームの画像データのポインタを取得します
								//	データはフィルタ前のものです
								//	editp 	: エディットハンドル
								//	n	 	: フレーム番号
								//	ofs	 	: フレームからのオフセット
								//  戻り値	: 画像データへのポインタ (NULLなら失敗)
								//			  画像データポインタの内容は次に外部関数を使うかメインに処理を戻すまで有効
	void		*(*get_ycp)( void *editp,int n );
								//	※出来るだけget_ycp_source_cache()の方を使用するようにしてください
								//	指定したフレームの画像データのポインタを取得します
								//	データはフィルタ前のものです
								//	editp 	: エディットハンドル
								//	n	 	: フレーム番号
								//  戻り値	: 画像データへのポインタ (NULLなら失敗)
								//			  画像データポインタの内容は次に外部関数を使うかメインに処理を戻すまで有効
	void		*(*get_pixelp)( void *editp,int n );
								//	指定したフレームのDIB形式(RGB24bit)の画像データのポインタを取得します
								//	データはフィルタ前のものです
								//	editp 	: エディットハンドル
								//	n		: フレーム番号
								//  戻り値	: DIB形式データへのポインタ (NULLなら失敗)
								//			  画像データポインタの内容は次に外部関数を使うかメインに処理を戻すまで有効
	int			(*get_audio)( void *editp,int n,void *buf );
								//	指定したフレームのオーディオデータを読み込みます
								//	データはフィルタ前のものです
								//	editp 	: エディットハンドル
								//	n		: フレーム番号
								//	buf 	: 格納するバッファ (NULLならサンプル数の取得のみ)
								//  戻り値	: 読み込んだサンプル数
	BOOL		(*is_editing)( void *editp );
								//	現在編集中か調べます
								//	editp 	: エディットハンドル
								//  戻り値	: TRUEなら編集中
	BOOL		(*is_saving)( void *editp );
								//	現在保存中か調べます
								//	editp 	: エディットハンドル
								//  戻り値	: TRUEなら保存中
	int			(*get_frame)( void *editp );
								//	現在の表示フレームを取得します
								//	editp 	: エディットハンドル
								//  戻り値	: 現在のフレーム番号
	int			(*get_frame_n)( void *editp );
								//	総フレーム数を取得します
								//	editp 	: エディットハンドル
								//  戻り値	: 現在の総フレーム数
	BOOL		(*get_frame_size)( void *editp,int *w,int *h );
								//	フィルタ前のフレームのサイズを取得します
								//	editp 	: エディットハンドル
								//	w,h 	: 画像サイズの格納ポインタ
								//  戻り値	: TRUEなら成功
	int			(*set_frame)( void *editp,int n );
								//	現在の表示フレームを変更します
								//	editp 	: エディットハンドル
								//  n		: フレーム番号
								//  戻り値	: 設定されたフレーム番号
	int			(*set_frame_n)( void *editp,int n );
								//	総フレーム数を変更します
								//	editp 	: エディットハンドル
								//  n		: フレーム数
								//  戻り値	: 設定された総フレーム数
	BOOL		(*copy_frame)( void *editp,int d,int s );
								//	フレームを他のフレームにコピーします
								//	editp 	: エディットハンドル
								//	d	 	: コピー先フレーム番号
								//	s	 	: コピー元フレーム番号
								//  戻り値	: TRUEなら成功
	BOOL		(*copy_video)( void *editp,int d,int s );
								//	フレームの映像だけを他のフレームにコピーします
								//	editp 	: エディットハンドル
								//	d	 	: コピー先フレーム番号
								//	s	 	: コピー元フレーム番号
								//  戻り値	: TRUEなら成功
	BOOL		(*copy_audio)( void *editp,int d,int s );
								//	フレームの音声だけを他のフレームにコピーします
								//	editp 	: エディットハンドル
								//	d	 	: コピー先フレーム番号
								//	s	 	: コピー元フレーム番号
								//  戻り値	: TRUEなら成功
	BOOL		(*copy_clip)( HWND hwnd,void *pixelp,int w,int h );
								//	クリップボードにDIB形式(RGB24bit)の画像をコピーします
								//	hwnd 	: ウィンドウハンドル
								//	pixelp	: DIB形式データへのポインタ
								//	w,h 	: 画像サイズ
								//  戻り値	: TRUEなら成功
	BOOL		(*paste_clip)( HWND hwnd,void *editp,int n );
								//	クリップボードから画像を張りつけます
								//	hwnd 	: ウィンドウハンドル
								//	editp 	: エディットハンドル
								//  n		: フレーム番号
								//  戻り値	: TRUEなら成功
	BOOL		(*get_frame_status)( void *editp,int n,FRAME_STATUS *fsp );
								//	フレームのステータスを取得します
								//	editp 	: エディットハンドル
								//  n		: フレーム番号
								//  fps		: フレームステータスへのポインタ
								//  戻り値	: TRUEなら成功
	BOOL		(*set_frame_status)( void *editp,int n,FRAME_STATUS *fsp );
								//	フレームのステータスを変更します
								//	editp 	: エディットハンドル
								//  n		: フレーム番号
								//  fps		: フレームステータスへのポインタ
								//  戻り値	: TRUEなら成功
	BOOL		(*is_saveframe)( void *editp,int n );
								//	実際に保存されるフレームか調べます
								//	editp 	: エディットハンドル
								//  n		: フレーム番号
								//  戻り値	: TRUEなら保存されます
	BOOL		(*is_keyframe)( void *editp,int n );
								//	キーフレームかどうか調べます
								//	editp 	: エディットハンドル
								//  n		: フレーム番号
								//  戻り値	: TRUEならキーフレーム
	BOOL		(*is_recompress)( void *editp,int n );
								//	再圧縮が必要か調べます
								//	editp 	: エディットハンドル
								//  n		: フレーム番号
								//  戻り値	: TRUEなら再圧縮が必要
	BOOL		(*filter_window_update)( void *fp );
								//	設定ウィンドウのトラックバーとチェックボックスを再描画します
								//	fp	 	: フィルタ構造体のポインタ
								//  戻り値	: TRUEなら成功
	BOOL		(*is_filter_window_disp)( void *fp );
								//	設定ウィンドウが表示されているか調べます
								//	fp	 	: フィルタ構造体のポインタ
								//  戻り値	: TRUEなら表示されている
	BOOL		(*get_file_info)( void *editp,FILE_INFO *fip );
								//	編集ファイルの情報を取得します
								//	editp 	: エディットハンドル
								//  fip		: ファイルインフォメーション構造体へのポインタ
								//  戻り値	: TRUEなら成功
	LPSTR		(*get_config_name)( void *editp,int n );
								//	現在のプロファイルの名前を取得します
								//	editp 	: エディットハンドル
								//  n		: プロファイル環境の番号
								//  戻り値	: プロファイルの名前へのポインタ (NULLなら失敗)
	BOOL		(*is_filter_active)( void *fp );
								//	フィルタが有効になっているか調べます
								//	fp	 	: フィルタ構造体のポインタ
								//  戻り値	: TRUEならフィルタ有効
	BOOL		(*get_pixel_filtered)( void *editp,int n,void *pixelp,int *w,int *h );
								//	指定したフレームのDIB形式(RGB24bit)の画像データを読み込みます
								//	データはフィルタ後のものです
								//	editp 	: エディットハンドル
								//	n		: フレーム番号
								//  pixelp	: DIB形式データを格納するポインタ (NULLなら画像サイズだけを返します)
								//	w,h		: 画像のサイズ (NULLならDIB形式データだけを返します)
								//  戻り値	: TRUEなら成功
	int			(*get_audio_filtered)( void *editp,int n,void *buf );
								//	指定したフレームのオーディオデータを読み込みます
								//	データはフィルタ後のものです
								//	editp* 	: エディットハンドル
								//	n		: フレーム番号
								//	buf 	: 格納するバッファ (NULLならサンプル数の取得のみ)
								//  戻り値	: 読み込んだサンプル数
	BOOL		(*get_select_frame)( void *editp,int *s,int *e );
								//	選択開始終了フレームを取得します
								//	editp 	: エディットハンドル
								//	s		: 選択開始フレーム
								//	e		: 選択終了フレーム
								//  戻り値	: TRUEなら成功
	BOOL		(*set_select_frame)( void *editp,int s,int e );
								//	選択開始終了フレームを設定します
								//	editp 	: エディットハンドル
								//	s		: 選択開始フレーム
								//	e		: 選択終了フレーム
								//  戻り値	: TRUEなら成功
	BOOL		(*rgb2yc)( PIXEL_YC *ycp,PIXEL *pixelp,int w );
								//	PIXELからPIXEL_YCに変換します
								//	ycp		: PIXEL_YC構造体へのポインタ
								//	pixelp 	: PIXEL構造体へのポインタ
								//	w		: 構造体の数
								//  戻り値	: TRUEなら成功
	BOOL		(*yc2rgb)( PIXEL *pixelp,PIXEL_YC *ycp,int w );
								//	PIXEL_YCからPIXELに変換します
								//	pixelp 	: PIXEL構造体へのポインタ
								//	ycp		: PIXEL_YC構造体へのポインタ
								//	w		: 構造体の数
								//  戻り値	: TRUEなら成功
	BOOL		(*dlg_get_load_name)( LPSTR name,LPSTR filter,LPSTR def );
								//	ファイルダイアログを使って読み込むファイル名を取得します
								//	name	: ファイル名を格納するポインタ
								//	filter	: ファイルフィルタ
								//  def		: デフォルトのファイル名
								//  戻り値	: TRUEなら成功 FALSEならキャンセル
	BOOL		(*dlg_get_save_name)( LPSTR name,LPSTR filter,LPSTR def );
								//	ファイルダイアログを使って書き込むファイル名を取得します
								//	name	: ファイル名を格納するポインタ
								//	filter	: ファイルフィルタ
								//  def		: デフォルトのファイル名
								//  戻り値	: TRUEなら成功 FALSEならキャンセル
	int			(*ini_load_int)( void *fp,LPSTR key,int n );
								//	INIファイルから数値を読み込む
								//	fp	 	: フィルタ構造体のポインタ
								//	key		: アクセス用のキーの名前
								//  n		: デフォルトの数値
								//  戻り値	: 読み込んだ数値
	int			(*ini_save_int)( void *fp,LPSTR key,int n );
								//	INIファイルに数値を書き込む
								//	fp	 	: フィルタ構造体のポインタ
								//	key		: アクセス用のキーの名前
								//  n		: 書き込む数値
								//  戻り値	: 書き込んだ数値
	BOOL		(*ini_load_str)( void *fp,LPSTR key,LPSTR str,LPSTR def );
								//	INIファイルから文字列を読み込む
								//	fp	 	: フィルタ構造体のポインタ
								//	key		: アクセス用のキーの名前
								//  str		: 文字列を読み込むバッファ
								//  def		: デフォルトの文字列
								//  戻り値	: TRUEなら成功
	BOOL		(*ini_save_str)( void *fp,LPSTR key,LPSTR str );
								//	INIファイルに文字列を書き込む
								//	fp	 	: フィルタ構造体のポインタ
								//	key		: アクセス用のキーの名前
								//  n		: 書き込む文字列
								//  戻り値	: TRUEなら成功
	BOOL		(*get_source_file_info)( void *editp,FILE_INFO *fip,int source_file_id );
								//	指定したファイルIDのファイルの情報を取得します
								//	editp 	: エディットハンドル
								//  fip		: ファイルインフォメーション構造体へのポインタ
								//	souce_file_id
								//			: ファイルID
								//  戻り値	: TRUEなら成功
	BOOL		(*get_source_video_number)( void *editp,int n,int *source_file_id,int *source_video_number );
								//	指定したフレームのソースのファイルIDとフレーム番号を取得します
								//	editp 	: エディットハンドル
								//	n		: フレーム番号
								//	souce_file_id
								//			: ファイルIDを格納するポインタ
								//	souce_video_number
								//			: フレーム番号を格納するポインタ
								//  戻り値	: TRUEなら成功
	BOOL		(*get_sys_info)( void *editp,SYS_INFO *sip );
								//	システムの情報を取得します
								//	editp 	: エディットハンドル (NULLならsipの編集中のフラグとすべてのファイル名が無効になります)
								//  sip		: システムインフォメーション構造体へのポインタ
								//  戻り値	: TRUEなら成功
	void 		*(*get_filterp)( int filter_id );
								//	指定のフィルタIDのフィルタ構造体へのポインタを取得します
								//	filter_id
								//		 	: フィルタID (0～登録されてるフィルタの数-1までの値)
								//  戻り値	: フィルタ構造体へのポインタ (NULLなら失敗)
	void		*(*get_ycp_filtering)( void *fp,void *editp,int n,void *reserve );
								//	※出来るだけget_ycp_filtering_cache_ex()の方を使用するようにしてください
								//	指定したフレームの画像データのポインタを取得します
								//	データは自分のフィルタの直前までフィルタしたものです
								//	fp	 	: フィルタ構造体のポインタ
								//	editp 	: エディットハンドル
								//	n	 	: フレーム番号
								//	reserve	: NULLを指定してください
								//  戻り値	: 画像データへのポインタ (NULLなら失敗)
								//			  画像データポインタの内容は次に外部関数を使うかメインに処理を戻すまで有効
	int			(*get_audio_filtering)( void *fp,void *editp,int n,void *buf );
								//	指定したフレームのオーディオデータを読み込みます
								//	データは自分のフィルタの直前までフィルタしたものです
								//	fp	 	: フィルタ構造体のポインタ
								//	editp 	: エディットハンドル
								//	n		: フレーム番号
								//	buf 	: 格納するバッファ (NULLならサンプル数の取得のみ)
								//  戻り値	: 読み込んだサンプル数
	BOOL		(*set_ycp_filtering_cache_size)( void *fp,int w,int h,int d,int flag );
								//	get_ycp_filtering_cache_ex()のキャッシュの設定をします
								//	設定値が変わった時のみキャッシュ領域を再確保します
								//	キャッシュ領域はフィルタがアクティブの時のみ確保されます
								//	fp	 	: フィルタ構造体のポインタ
								//	w	 	: キャッシュ領域の幅
								//	h	 	: キャッシュ領域の高さ
								//	d	 	: キャッシュするフレーム数
								//	flag 	: NULLを指定してください
								//  戻り値	: TRUEなら成功
	void		*(*get_ycp_filtering_cache)( void *fp,void *editp,int n );
								//	※出来るだけget_ycp_filtering_cache_ex()の方を使用するようにしてください
								//	指定したフレームの画像データのキャッシュポインタを取得します
								//	set_ycp_filtering_cache_size()の設定にしたがってキャッシュされます
								//	データは自分のフィルタの直前までフィルタしたものです
								//	fp	 	: フィルタ構造体のポインタ
								//	editp 	: エディットハンドル
								//	n	 	: フレーム番号
								//  戻り値	: 画像データへのキャッシュポインタ (NULLなら失敗)
								//			  画像データポインタの内容はキャッシュから破棄されるまで有効
	void		*(*get_ycp_source_cache)( void *editp,int n,int ofs );
								//	指定したフレームの画像データのポインタを取得します
								//	データはフィルタ前のものです
								//	editp 	: エディットハンドル
								//	n	 	: フレーム番号
								//	ofs	 	: 元のAVI上でのフレームのオフセット
								//  戻り値	: 画像データへのポインタ (NULLなら失敗)
								//			  画像データポインタの内容はキャッシュから破棄されるまで有効
	void		*(*get_disp_pixelp)( void *editp,DWORD format );
								//	表示されているフレームの画像データのポインタを取得します
								//	データはフィルタ後のものです
								//	表示フィルタのみ使用可能です。
								//	editp 	: エディットハンドル
								//	format	: 画像フォーマット( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 )
								//  戻り値	: 画像データへのポインタ (NULLなら失敗)
								//			  画像データポインタの内容は次に外部関数を使うかメインに処理を戻すまで有効
	BOOL		(*get_pixel_source)( void *editp,int n,void *pixelp,DWORD format );
								//	指定したフレームの画像データを読み込みます
								//	データはフィルタ前のものです
								//	editp 	: エディットハンドル
								//	n	 	: フレーム番号
								//  pixelp	: DIB形式データを格納するポインタ
								//	format	: 画像フォーマット( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 )
								//  戻り値	: TRUEなら成功
	BOOL		(*get_pixel_filtered_ex)( void *editp,int n,void *pixelp,int *w,int *h,DWORD format );
								//	指定したフレームの画像データを読み込みます
								//	データはフィルタ後のものです
								//	editp 	: エディットハンドル
								//	n	 	: フレーム番号
								//  pixelp	: DIB形式データを格納するポインタ (NULLなら画像サイズだけを返します)
								//	w,h		: 画像のサイズ (NULLならDIB形式データだけを返します)
								//	format	: 画像フォーマット( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 )
								//  戻り値	: TRUEなら成功
	PIXEL_YC	*(*get_ycp_filtering_cache_ex)( void *fp,void *editp,int n,int *w,int *h );
								//	指定したフレームの画像データのキャッシュポインタを取得します
								//	set_ycp_filtering_cache_size()の設定にしたがってキャッシュされます
								//	データは自分のフィルタの直前までフィルタしたものです
								//	fp	 	: フィルタ構造体のポインタ
								//	editp 	: エディットハンドル
								//	n	 	: フレーム番号
								//	w,h		: 取得した画像のサイズ (NULLなら無視されます)
								//  戻り値	: 画像データへのキャッシュポインタ (NULLなら失敗)
								//			  画像データポインタの内容はキャッシュから破棄されるまで有効
	BOOL		(*exec_multi_thread_func)( MULTI_THREAD_FUNC func,void *param1,void *param2 );
								//	指定した関数をシステムの設定値に応じたスレッド数で呼び出します
								//	呼び出された関数内からWin32APIや外部関数(rgb2yc,yc2rgbは除く)を使用しないでください
								//	func	: マルチスレッドで呼び出す関数
								//	param1 	: 呼び出す関数に渡す汎用パラメータ
								//	param2 	: 呼び出す関数に渡す汎用パラメータ
								//  戻り値	: TRUEなら成功
	PIXEL_YC	*(*create_yc)( void );
								//	空のフレーム画像データ領域を作成します
								//	ycp_editと同様に外部関数で使用できますが
								//	FILTER_PROC_INFOのycp_edit,ycp_tempと入れ替えることは出来ません
								//  戻り値	: 作成したフレーム画像データへのポインタ (NULLなら失敗)
	void		(*delete_yc)( PIXEL_YC *ycp );
								//	create_ycで作成した領域を削除します
	BOOL 		(*load_image)( PIXEL_YC *ycp,LPSTR file,int *w,int *h,int flag );
								//	フレーム画像データにBMPファイルから画像を読み込みます
								//	ycp     : 画像を読み込むフレーム画像へのポインタ (NULLなら描画をせずにサイズを返します)
								//	file	: 読み込むBMPファイル名
								//	w,h		: 読み込んだ画像のサイズ (NULLを指定できます)
								//	flag 	: NULLを指定してください
								//  戻り値	: TRUEなら成功
	void		(*resize_yc)( PIXEL_YC *ycp,int w,int h,PIXEL_YC *ycp_src,int sx,int sy,int sw,int sh );
								//	フレーム画像データをリサイズします
								//	元画像の任意の画像領域をリサイズすることも出来ます
								//	ycp     : リサイズ後のフレーム画像を格納するポインタ
								//	w,h     : リサイズの解像度
								//	ycp_src	: 元画像のフレーム画像へのポインタ(NULLならycpと同じ)
								//	sx,sy	: 元画像のリサイズ対象領域の左上の座標
								//	sw,sh	: 元画像のリサイズ対象領域のサイズ
	void 		(*copy_yc)( PIXEL_YC *ycp,int x,int y,PIXEL_YC *ycp_src,int sx,int sy,int sw,int sh,int tr );
								//	フレーム画像データの任意の領域をコピーします
								//	描画の際は最大画像サイズの領域に収まるようにクリッピングをします
								//	コピー元とコピー先の領域は重ならないようにしてください
								//	ycp     : コピー先のフレーム画像へのポインタ
								//	x,y		: コピー先の左上の座標
								//	ycp_src	: コピー元のフレーム画像へのポインタ
								//	sx,sy	: コピー元の左上の座標
								//	sw,sh	: コピー元のサイズ
								//	tr      : コピー元の透明度 (0～4096)
	void 		(*draw_text)( PIXEL_YC *ycp,int x,int y,LPSTR text,int r,int g,int b,int tr,HFONT hfont,int *w,int *h );
								//	フレーム画像データにテキストを描画します
								//	描画の際は最大画像サイズの領域に収まるようにクリッピングをします
								//	ycp     : 描画するフレーム画像データへのポインタ (NULLなら描画をせずにサイズを返します)
								//	x,y		: 描画する左上の座標
								//	text	: 描画するテキストの内容
								//	r,g,b	: 描画色 (0～255)
								//	tr      : 透明度 (0～4096)
								//	hfont	: 描画で使用するフォント (NULLならデフォルトのフォント)
								//	w,h		: 描画したテキスト領域のサイズ (NULLを指定できます)
	AVI_FILE_HANDLE (*avi_file_open)( LPSTR file,FILE_INFO *fip,int flag );
								//	AVIファイルをオープンしてavi_file_read_video(),avi_file_read_audio()で
								//	データを読み込む為のハンドルを取得します。
								//	※編集中のファイルとフォーマット(fpsやサンプリングレート等)が異なる場合があるので注意してください。
								//	file    : 読み込むAVIファイル名 (入力プラグインで読み込めるファイルも指定できます)
								//  fip		: ファイルインフォメーション構造体へのポインタ (読み込んだファイルの情報が入ります)
								//	flag 	: 読み込みフラグ
								//	AVI_FILE_OPEN_FLAG_ONLY_YUY2		: YUY2 で展開するようにします
								//	AVI_FILE_OPEN_FLAG_ONLY_RGB24		: RGB24で展開するようにします
								//	AVI_FILE_OPEN_FLAG_ONLY_RGB32		: RGB32で展開するようにします
								//	AVI_FILE_OPEN_FLAG_VIDEO_ONLY		: ビデオのみ読み込むようにします
								//	AVI_FILE_OPEN_FLAG_AUDIO_ONLY		: オーディオのみ読み込むようにします
								//  戻り値	: AVIファイルハンドル (NULLなら失敗)
	void 		(*avi_file_close)( AVI_FILE_HANDLE afh );
								//	AVIファイルをクローズします
								//	afh		: AVIファイルハンドル
	BOOL 		(*avi_file_read_video)( AVI_FILE_HANDLE afh,PIXEL_YC *ycp,int n );
								//	フレーム画像データにAVIファイルから画像データを読み込みます
								//	afh		: AVIファイルハンドル
								//	ycp     : 画像データを読み込むフレーム画像へのポインタ
								//	n		: フレーム番号
								//  戻り値	: TRUEなら成功
	int 		(*avi_file_read_audio)( AVI_FILE_HANDLE afh,void *buf,int n );
								//	AVIファイルから音声データを読み込みます
								//	afh		: AVIファイルハンドル
								//	buf     : 音声を読み込むバッファへのポインタ
								//	n		: フレーム番号
								//  戻り値	: 読み込んだサンプル数
	void 		*(*avi_file_get_video_pixelp)( AVI_FILE_HANDLE afh,int n );
								//	AVIファイルから読み込んだDIB形式の画像データのポインタを取得します
								//	取得できる画像データのフォーマットはavi_file_open()で取得した
								//	FILE_INFOのビデオ展開形式になります。
								//	afh		: AVIファイルハンドル
								//	n		: フレーム番号
								//  戻り値	: DIB形式データへのポインタ (NULLなら失敗)
								//			  画像データポインタの内容は次に外部関数を使うかメインに処理を戻すまで有効
	LPSTR		(*get_avi_file_filter)( int type );
								//	avi_file_open()で読み込めるファイルのファイルフィルタを取得します
								//	type	: ファイルの種類
								//	GET_AVI_FILE_FILTER_TYPE_VIDEO	: ビデオル
								//	GET_AVI_FILE_FILTER_TYPE_AUDIO	: オーディオ
								//  戻り値	: ファイルフィルタへのポインタ
	int			(*avi_file_read_audio_sample)( AVI_FILE_HANDLE afh,int start,int length,void *buf );
								//	AVIファイルから音声データを読み込みます
								//	afh		: AVIファイルハンドル
								//	start   : 読み込み開始サンプル番号
								//	length	: 読み込むサンプル数
								//	buf		: データを読み込むバッファへのポインタ
								//  戻り値	: 読み込んだサンプル数
	int			(*avi_file_set_audio_sample_rate)( AVI_FILE_HANDLE afh,int audio_rate,int audio_ch );
								//	avi_file_read_audio_sample()で読み込む音声のサンプリングレート等を変更します
								//	afh		: AVIファイルハンドル
								//	audio_rate	: 音声サンプリングレート
								//	audio_ch	: 音声チャンネル数
								//  戻り値	: 変更したサンプリングレートでの総サンプル数
	BYTE		*(*get_frame_status_table)( void *editp,int type );
								//	フレームのステータスが格納されているバッファへのポインタを取得します
								//	editp 	: エディットハンドル
								//  type	: ステータスの種類
								//	FARME_STATUS_TYPE_EDIT_FLAG	: 編集フラグ
								//	FARME_STATUS_TYPE_INTER		: インターレース
								//  戻り値	: バッファへのポインタ
								//			  バッファへのポインタの内容は編集ファイルがクローズされるまで有効
	BOOL		(*set_undo)( void *editp );
								//	現在の編集状況をアンドゥバッファに設定します
								//	editp 	: エディットハンドル
								//  戻り値	: TRUEなら成功
	BOOL		(*add_menu_item)( void *fp,LPSTR name,HWND hwnd,int id,int def_key,int flag );
								//	メインウィンドウの設定メニュー項目を追加します
								//	メニューが選択された時にhwndで指定したウィンドウに
								//	WM_FILTER_COMMANDのメッセージを送ります
								//	※必ずfunc_init()かWM_FILTER_INITから呼び出すようにしてください。
								//	fp	 	: フィルタ構造体のポインタ
								//	name 	: メニューの名前
								//	hwnd 	: WM_FILTER_COMMANDを送るウィンドウハンドル
								//	id	 	: WM_FILTER_COMMANDのWPARAM
								//	def_key	: 標準のショートカットキーの仮想キーコード (NULLなら無し)
								//	flag	: フラグ
								//	ADD_MENU_ITEM_FLAG_KEY_SHIFT	: 標準のショートカットキーをSHIFT+キーにする
								//	ADD_MENU_ITEM_FLAG_KEY_CTRL		: 標準のショートカットキーをCTRL+キーにする
								//	ADD_MENU_ITEM_FLAG_KEY_ALT		: 標準のショートカットキーをALT+キーにする
								//  戻り値	: TRUEなら成功
	BOOL 		(*edit_open)( void *editp,LPSTR file,int flag );
								//	編集ファイルを開きます
								//	editp 	: エディットハンドル
								//	file 	: ファイル名
								//	flag 	: フラグ
								//	EDIT_OPEN_FLAG_ADD			: 追加読み込みをします
								//	EDIT_OPEN_FLAG_AUDIO		: 音声読み込みをします
								//	EDIT_OPEN_FLAG_PROJECT		: プロジェクトファイルを開きます
								//	EDIT_OPEN_FLAG_DIALOG		: 読み込みダイアログを表示します
								//  戻り値	: TRUEなら成功
	BOOL 		(*edit_close)( void *editp );
								//	編集ファイルを閉じます
								//	editp 	: エディットハンドル
								//  戻り値	: TRUEなら成功
	BOOL 		(*edit_output)( void *editp,LPSTR file,int flag,LPSTR type );
								//	編集データをAVI出力します
								//	WAV出力やプラグイン出力も出来ます
								//	editp 	: エディットハンドル
								//	file 	: 出力ファイル名
								//	flag	: フラグ
								//	EDIT_OUTPUT_FLAG_NO_DIALOG	: 出力ダイアログを表示しません
								//	EDIT_OUTPUT_FLAG_WAV		: WAV出力をします
								//	type	: 出力プラグインの名前 (NULLならAVI/WAV出力)
								//  戻り値	: TRUEなら成功
	BOOL 		(*set_config)( void *editp,int n,LPSTR name );
								//	プロファイルを設定します
								//	editp 	: エディットハンドル
								//  n		: プロファイル環境の番号
								//  name	: プロファイルの名前
								//  戻り値	: TRUEなら成功
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

//	フィルタ構造体
typedef struct {
	int		flag;				//	フィルタのフラグ
								//	FILTER_FLAG_ALWAYS_ACTIVE		: フィルタを常にアクティブにします
								//	FILTER_FLAG_CONFIG_POPUP		: 設定をポップアップメニューにします
								//	FILTER_FLAG_CONFIG_CHECK		: 設定をチェックボックスメニューにします
								//	FILTER_FLAG_CONFIG_RADIO		: 設定をラジオボタンメニューにします
								//	FILTER_FLAG_EX_DATA				: 拡張データを保存出来るようにします
								//	FILTER_FLAG_PRIORITY_HIGHEST	: フィルタのプライオリティを常に最上位にします
								//	FILTER_FLAG_PRIORITY_LOWEST		: フィルタのプライオリティを常に最下位にします
								//	FILTER_FLAG_WINDOW_THICKFRAME	: サイズ変更可能なウィンドウを作ります
								//	FILTER_FLAG_WINDOW_SIZE			: 設定ウィンドウのサイズを指定出来るようにします
								//	FILTER_FLAG_DISP_FILTER			: 表示フィルタにします
								//	FILTER_FLAG_REDRAW				: 再描画をplugin側で処理するようにします
								//	FILTER_FLAG_EX_INFORMATION		: フィルタの拡張情報を設定できるようにします
								//	FILTER_FLAG_INFORMATION			: FILTER_FLAG_EX_INFORMATION を使うようにして下さい
								//	FILTER_FLAG_NO_CONFIG			: 設定ウィンドウを表示しないようにします
								//	FILTER_FLAG_AUDIO_FILTER		: オーディオフィルタにします
								//	FILTER_FLAG_RADIO_BUTTON		: チェックボックスをラジオボタンにします
								//	FILTER_FLAG_WINDOW_HSCROLL		: 水平スクロールバーを持つウィンドウを作ります
								//	FILTER_FLAG_WINDOW_VSCROLL		: 垂直スクロールバーを持つウィンドウを作ります
								//	FILTER_FLAG_INTERLACE_FILTER	: インターレース解除フィルタにします
								//	FILTER_FLAG_NO_INIT_DATA		: func_proc()の画像の初期データを作成しないようにします
								//	FILTER_FLAG_IMPORT				: インポートメニューを作ります
								//	FILTER_FLAG_EXPORT				: エクスポートメニューを作ります
								//	FILTER_FLAG_MAIN_MESSAGE		: func_WndProc()にWM_FILTER_MAIN_???のメッセージを送るようにします
	int		x,y;				//	設定ウインドウのサイズ (FILTER_FLAG_WINDOW_SIZEが立っている時に有効)
								//	設定値に FILTER_WINDOW_SIZE_CLIENT をORして設定するとクライアント領域でのサイズ指定になります。
								//	設定値に FILTER_WINDOW_SIZE_ADD をORして設定すると標準のサイズからの追加分の指定になります。
	TCHAR	*name;				//	フィルタの名前
	int		track_n;			//	トラックバーの数
	TCHAR	**track_name;		//	トラックバーの名前郡へのポインタ(トラックバー数が0ならNULLでよい)
	int		*track_default;		//	トラックバーの初期値郡へのポインタ(トラックバー数が0ならNULLでよい)
	int		*track_s,*track_e;	//	トラックバーの数値の下限上限 (NULLなら全て0～256)
	int		check_n;			//	チェックボックスの数
	TCHAR	**check_name;		//	チェックボックスの名前郡へのポインタ(チェックボックス数が0ならNULLでよい)
	int		*check_default;		//	チェックボックスの初期値郡へのポインタ(チェックボックス数が0ならNULLでよい)
								//	初期値がマイナス値の場合はボタンになります。ボタンを押したときにWM_COMMAND( WPARAM = MID_FILTER_BUTTON + n )のウィンドウメッセージが送られます
	BOOL	(*func_proc)( void *fp,FILTER_PROC_INFO *fpip );
								//	フィルタ処理関数へのポインタ (NULLなら呼ばれません)
	BOOL	(*func_init)( void *fp );
								//	開始時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
	BOOL	(*func_exit)( void *fp );
								//	終了時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
	BOOL	(*func_update)( void *fp,int status );
								//	自分の設定が変更されたときに呼ばれる関数へのポインタ (NULLなら呼ばれません)
								//	FILTER_UPDATE_STATUS_ALL		: 全項目が変更された
								//	FILTER_UPDATE_STATUS_TRACK + n	: n番目のトラックバーが変更された
								//	FILTER_UPDATE_STATUS_CHECK + n	: n番目のチェックボックスが変更された
	BOOL 	(*func_WndProc)( HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam,void *editp,void *fp );
								//	設定ウィンドウにウィンドウメッセージが来た時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
								//	VFAPI動作時には呼ばれません
								//	通常のメッセージ以外に以下の拡張メッセージが送られます
								//	WM_FILTER_UPDATE		: 各フィルタ設定や編集内容が変更された直後に送られます
								//	WM_FILTER_FILE_OPEN		: 編集ファイルがオープンされた直後に送られます
								//	WM_FILTER_FILE_UPDATE	: 編集ファイルの更新(追加や音声読み込み等)があった直後に送られます
								//	WM_FILTER_FILE_CLOSE	: 編集ファイルがクローズされる直前に送られます
								//	WM_FILTER_INIT			: 開始直後に送られます
								//	WM_FILTER_EXIT			: 終了直前に送られます
								//	WM_FILTER_SAVE_START	: セーブが開始される直前に送られます
								//	WM_FILTER_SAVE_END		: セーブが終了された直後に送られます
								//	WM_FILTER_IMPORT		: インポートが選択された直後に送られます
								//	WM_FILTER_EXPORT		: エクスポートが選択された直後に送られます
								//	WM_FILTER_CHANGE_ACTIVE	: フィルタの有効/無効が変更された直後に送られます
								//	WM_FILTER_CHANGE_WINDOW	: フィルタウィンドウの表示/非表示が変更された直後に送られます
								//	WM_FILTER_CHANGE_PARAM	: 自分のフィルタの設定が変更された直後に送られます
								//	WM_FILTER_CHANGE_EDIT	: 編集中/非編集中が変更された直後に送られます
								//	これ以降のメッセージはFILTER_FLAG_MAIN_MESSAGE設定時のみ送られます
								//	WM_FILTER_MAIN_MOUSE_DOWN	: メインウィンドウでマウスの左ボタンが押された時に送られます
								//	WM_FILTER_MAIN_MOUSE_UP		: メインウィンドウでマウスが移動した時に送られます
								//	WM_FILTER_MAIN_MOUSE_MOVE	: メインウィンドウでマウスの左ボタンが離された時に送られます
								//	WM_FILTER_MAIN_MOUSE_DBLCLK	: メインウィンドウでマウスの左ボタンがダブルクリックされた時に送られます
								//	WM_FILTER_MAIN_MOUSE_R_DOWN	: メインウィンドウでマウスの右ボタンが押された時に送られます
								//	WM_FILTER_MAIN_MOUSE_R_UP	: メインウィンドウでマウスの右ボタンが離された時に送られます
								//	WM_FILTER_MAIN_MOUSE_WHEEL	: メインウィンドウでマウスのホイールが回転した時に送られます
								//	WM_FILTER_MAIN_KEY_DOWN		: メインウィンドウでキーが押された時に送られます
								//	WM_FILTER_MAIN_KEY_UP		: メインウィンドウでキーが離された時に送られます
								//	WM_FILTER_MAIN_MOVESIZE		: メインウィンドウの位置やサイズが変更された時に送られます
								//	WM_FILTER_MAIN_CONTEXTMENU	: メインウィンドウでコンテキストメニューが表示される時に送られます
								//	WM_FILTER_MAIN_MOUSE_???のlparamには編集画像上での座標が入ります(編集中以外は0になります)
								//	WM_FILTER_MAIN_MOUSE_WHEELのwparamの上位ワードにホイールの回転量が入ります
								//	WM_FILTER_MAIN_KEY_???のwparamには仮想キーコードが入ります
								//	WM_FILTER_MAIN_MOVESIZEのlparamにはメインウィンドウのウィンドウハンドルが入ります
								//	WM_FILTER_MAIN_CONTEXTMENUのlparamにはスクリーン座標が入ります
								//	WM_FILTER_MAIN_CONTEXTMENUでメニューを表示した時は戻り値をTRUEにしてください(再描画はされません)
								//	戻り値をTRUEにすると編集内容が更新されたとして全体が再描画されます
	int		*track;				//	トラックバーの設定値郡へのポインタ (AviUtl側で設定されます)
	int		*check;				//	チェックボックスの設定値郡へのポインタ (AviUtl側で設定されます)
	void	*ex_data_ptr;		//	拡張データ領域へのポインタ (FILTER_FLAG_EX_DATAが立っている時に有効)
	int		ex_data_size;		//	拡張データサイズ (FILTER_FLAG_EX_DATAが立っている時に有効)
	TCHAR	*information;		//	フィルタ情報へのポインタ (FILTER_FLAG_EX_INFORMATIONが立っている時に有効)
	BOOL	(*func_save_start)( void *fp,int s,int e,void *editp );
								//	セーブが開始される直前に呼ばれる関数へのポインタ (NULLなら呼ばれません)
								//	s	 	: セーブする先頭フレーム
								//	e 		: セーブする最終フレーム
								//  戻り値	: 成功ならTRUE
	BOOL	(*func_save_end)( void *fp,void *editp );
								//	セーブが終了した直前に呼ばれる関数へのポインタ (NULLなら呼ばれません)
	EXFUNC	*exfunc;			//	外部関数テーブルへのポインタ (AviUtl側で設定されます)
	HWND	hwnd;				//	ウィンドウハンドル (AviUtl側で設定されます)
	HINSTANCE	dll_hinst;		//	DLLのインスタンスハンドル (AviUtl側で設定されます)
	void	*ex_data_def;		//	拡張データの初期値データ領域へのポインタ (NULLなら初期化されません)
	BOOL	(*func_is_saveframe)( void *fp,void *editp,int saveno,int frame,int fps,int edit_flag,int inter );
								//	インターレース解除フィルタで保存するフレームを決める時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
								//	saveno		: セーブする範囲の先頭からのフレーム番号
								//	frame		: 編集フレーム番号
								//	fps			: フレームレートの変更の設定値 (30,24,20,15,10)
								//	edit_flag	: 編集フラグ
								//	inter		: フレームのインターレース
								//	戻り値		: TRUEを返すと保存フレーム、FALSEを返すと間引きフレームになります。
	BOOL	(*func_project_load)( void *fp,void *editp,void *data,int size );
								//	プロジェクトファイルからデータを読み込んだ時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
								//	プロジェクトファイルに保存したデータが無い場合は呼ばれません
								//	data 	: プロジェクトから読み込んだデータへのポインタ
								//	size 	: プロジェクトから読み込んだデータのバイト数
								//  戻り値	: 成功ならTRUE
	BOOL	(*func_project_save)( void *fp,void *editp,void *data,int *size );
								//	プロジェクトファイルをセーブしている時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
								//	プロジェクトファイルにフィルタのデータを保存します
								//	※AviUtlからは始めに保存サイズ取得の為にdataがNULLで呼び出され、続けて実際のデータを取得する為に呼び出されます。
								//	data 	: プロジェクトに書き込むデータを格納するバッファへのポインタ (NULLの場合はデータのバイト数のみ返す)
								//	size 	: プロジェクトに書き込むデータのバイト数を返すポインタ
								//  戻り値	: 保存するデータがあるならTRUE
	BOOL	(*func_modify_title)( void *fp,void *editp,int frame,LPSTR title,int max_title );
								//	メインウィンドウのタイトルバーを表示する時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
								//	タイトルバーの文字列を変更できます (未編集時、出力時は呼ばれません)
								//	frame		: 編集フレーム番号
								//	title 		: 表示するタイトルバーの文字列
								//	max_title 	: titleのバッファサイズ
								//  戻り値	: 成功ならTRUE
	TCHAR	*dll_path;			//	PluginsディレクトリのサブディレクトリにDLLがある時のみ、サブディレクトリ名が入ります。
	int		reserve[2];			//	拡張用に予約されてます。NULLにしてください。

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

//	フィルタDLL用構造体
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
