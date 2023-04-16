
typedef struct {
  short y;
  short cb;
  short cr;
} PIXEL_YC;

typedef struct {
  unsigned char b, g, r;
} PIXEL;

typedef struct {
  int flag;
  PIXEL_YC *ycp_edit;
  PIXEL_YC *ycp_temp;
  int w, h;
  int max_w, max_h;
  int frame;
  int frame_n;
  int org_w, org_h;
  short *audiop;
  int audio_n;
  int audio_ch;
  PIXEL *pixelp;
  void *editp;
  int yc_size;
  int line_size;
  int reserve[8];
} FILTER_PROC_INFO;
#define FILTER_PROC_INFO_FLAG_INVERT_FIELD_ORDER 0x00010000
#define FILTER_PROC_INFO_FLAG_INVERT_INTERLACE 0x00020000

typedef struct {
  int video;
  int audio;
  int inter;
  int index24fps;
  int config;
  int vcm;
  int edit_flag;
  int reserve[9];
} FRAME_STATUS;
#define FRAME_STATUS_INTER_NORMAL 0
#define FRAME_STATUS_INTER_REVERSE 1
#define FRAME_STATUS_INTER_ODD 2
#define FRAME_STATUS_INTER_EVEN 3
#define FRAME_STATUS_INTER_MIX 4
#define FRAME_STATUS_INTER_AUTO 5
#define EDIT_FRAME_EDIT_FLAG_KEYFRAME 1
#define EDIT_FRAME_EDIT_FLAG_MARKFRAME 2
#define EDIT_FRAME_EDIT_FLAG_DELFRAME 4
#define EDIT_FRAME_EDIT_FLAG_NULLFRAME 8

typedef struct {
  int flag;
  LPSTR name;
  int w, h;
  int video_rate, video_scale;
  int audio_rate;
  int audio_ch;
  int frame_n;
  DWORD video_decode_format;
  int video_decode_bit;
  int audio_n;
  int reserve[4];
} FILE_INFO;
#define FILE_INFO_FLAG_VIDEO 1
#define FILE_INFO_FLAG_AUDIO 2

typedef struct {
  int flag;
  LPSTR info;
  int filter_n;
  int min_w, min_h;
  int max_w, max_h;
  int max_frame;
  LPSTR edit_name;
  LPSTR project_name;
  LPSTR output_name;
  int vram_w, vram_h;
  int vram_yc_size;
  int vram_line_size;
  HFONT hfont;
  int build;
  int reserve[2];
} SYS_INFO;
#define SYS_INFO_FLAG_EDIT 1
#define SYS_INFO_FLAG_VFAPI 2
#define SYS_INFO_FLAG_USE_SSE 4
#define SYS_INFO_FLAG_USE_SSE2 8

typedef void (*MULTI_THREAD_FUNC)(int thread_id, int thread_num, void *param1, void *param2);

typedef void *AVI_FILE_HANDLE;

typedef struct {
  void (*get_ycp_ofs)(void *editp, int n, int ofs);
  void *(*get_ycp)(void *editp, int n);
  void *(*get_pixelp)(void *editp, int n);
  int (*get_audio)(void *editp, int n, void *buf);
  BOOL (*is_editing)(void *editp);
  BOOL (*is_saving)(void *editp);
  int (*get_frame)(void *editp);
  int (*get_frame_n)(void *editp);
  BOOL (*get_frame_size)(void *editp, int *w, int *h);
  int (*set_frame)(void *editp, int n);
  int (*set_frame_n)(void *editp, int n);
  BOOL (*copy_frame)(void *editp, int d, int s);
  BOOL (*copy_video)(void *editp, int d, int s);
  BOOL (*copy_audio)(void *editp, int d, int s);
  BOOL (*copy_clip)(HWND hwnd, void *pixelp, int w, int h);
  BOOL (*paste_clip)(HWND hwnd, void *editp, int n);
  BOOL (*get_frame_status)(void *editp, int n, FRAME_STATUS *fsp);
  BOOL (*set_frame_status)(void *editp, int n, FRAME_STATUS *fsp);
  BOOL (*is_saveframe)(void *editp, int n);
  BOOL (*is_keyframe)(void *editp, int n);
  BOOL (*is_recompress)(void *editp, int n);
  BOOL (*filter_window_update)(void *fp);
  BOOL (*is_filter_window_disp)(void *fp);
  BOOL (*get_file_info)(void *editp, FILE_INFO *fip);
  LPSTR (*get_config_name)(void *editp, int n);
  BOOL (*is_filter_active)(void *fp);
  BOOL (*get_pixel_filtered)(void *editp, int n, void *pixelp, int *w, int *h);
  int (*get_audio_filtered)(void *editp, int n, void *buf);
  BOOL (*get_select_frame)(void *editp, int *s, int *e);
  BOOL (*set_select_frame)(void *editp, int s, int e);
  BOOL (*rgb2yc)(PIXEL_YC *ycp, PIXEL *pixelp, int w);
  BOOL (*yc2rgb)(PIXEL *pixelp, PIXEL_YC *ycp, int w);
  BOOL (*dlg_get_load_name)(LPSTR name, LPSTR filter, LPSTR def);
  BOOL (*dlg_get_save_name)(LPSTR name, LPSTR filter, LPSTR def);
  int (*ini_load_int)(void *fp, LPSTR key, int n);
  int (*ini_save_int)(void *fp, LPSTR key, int n);
  BOOL (*ini_load_str)(void *fp, LPSTR key, LPSTR str, LPSTR def);
  BOOL (*ini_save_str)(void *fp, LPSTR key, LPSTR str);
  BOOL (*get_source_file_info)(void *editp, FILE_INFO *fip, int source_file_id);
  BOOL (*get_source_video_number)(void *editp, int n, int *source_file_id, int *source_video_number);
  BOOL (*get_sys_info)(void *editp, SYS_INFO *sip);
  void *(*get_filterp)(int filter_id);
  void *(*get_ycp_filtering)(void *fp, void *editp, int n, void *reserve);
  int (*get_audio_filtering)(void *fp, void *editp, int n, void *buf);
  BOOL (*set_ycp_filtering_cache_size)(void *fp, int w, int h, int d, int flag);
  void *(*get_ycp_filtering_cache)(void *fp, void *editp, int n);
  void *(*get_ycp_source_cache)(void *editp, int n, int ofs);
  void *(*get_disp_pixelp)(void *editp, DWORD format);
  BOOL (*get_pixel_source)(void *editp, int n, void *pixelp, DWORD format);
  BOOL (*get_pixel_filtered_ex)(void *editp, int n, void *pixelp, int *w, int *h, DWORD format);
  PIXEL_YC *(*get_ycp_filtering_cache_ex)(void *fp, void *editp, int n, int *w, int *h);
  BOOL (*exec_multi_thread_func)(MULTI_THREAD_FUNC func, void *param1, void *param2);
  PIXEL_YC *(*create_yc)(void);
  void (*delete_yc)(PIXEL_YC *ycp);
  BOOL (*load_image)(PIXEL_YC *ycp, LPSTR file, int *w, int *h, int flag);
  void (*resize_yc)(PIXEL_YC *ycp, int w, int h, PIXEL_YC *ycp_src, int sx, int sy, int sw, int sh);
  void (*copy_yc)(PIXEL_YC *ycp, int x, int y, PIXEL_YC *ycp_src, int sx, int sy, int sw, int sh, int tr);
  void (*draw_text)(PIXEL_YC *ycp, int x, int y, LPSTR text, int r, int g, int b, int tr, HFONT hfont, int *w, int *h);
  AVI_FILE_HANDLE (*avi_file_open)(LPSTR file, FILE_INFO *fip, int flag);
  void (*avi_file_close)(AVI_FILE_HANDLE afh);
  BOOL (*avi_file_read_video)(AVI_FILE_HANDLE afh, PIXEL_YC *ycp, int n);
  int (*avi_file_read_audio)(AVI_FILE_HANDLE afh, void *buf, int n);
  void *(*avi_file_get_video_pixelp)(AVI_FILE_HANDLE afh, int n);
  LPSTR (*get_avi_file_filter)(int type);
  int (*avi_file_read_audio_sample)(AVI_FILE_HANDLE afh, int start, int length, void *buf);
  int (*avi_file_set_audio_sample_rate)(AVI_FILE_HANDLE afh, int audio_rate, int audio_ch);
  BYTE *(*get_frame_status_table)(void *editp, int type);
  BOOL (*set_undo)(void *editp);
  BOOL (*add_menu_item)(void *fp, LPSTR name, HWND hwnd, int id, int def_key, int flag);
  BOOL (*edit_open)(void *editp, LPSTR file, int flag);
  BOOL (*edit_close)(void *editp);
  BOOL (*edit_output)(void *editp, LPSTR file, int flag, LPSTR type);
  BOOL (*set_config)(void *editp, int n, LPSTR name);
  int reserve[7];
} EXFUNC;
#define AVI_FILE_OPEN_FLAG_VIDEO_ONLY 16
#define AVI_FILE_OPEN_FLAG_AUDIO_ONLY 32
#define AVI_FILE_OPEN_FLAG_ONLY_YUY2 0x10000
#define AVI_FILE_OPEN_FLAG_ONLY_RGB24 0x20000
#define AVI_FILE_OPEN_FLAG_ONLY_RGB32 0x40000
#define GET_AVI_FILE_FILTER_TYPE_VIDEO 0
#define GET_AVI_FILE_FILTER_TYPE_AUDIO 1
#define FARME_STATUS_TYPE_EDIT_FLAG 0
#define FARME_STATUS_TYPE_INTER 1
#define ADD_MENU_ITEM_FLAG_KEY_SHIFT 1
#define ADD_MENU_ITEM_FLAG_KEY_CTRL 2
#define ADD_MENU_ITEM_FLAG_KEY_ALT 4
#define EDIT_OPEN_FLAG_ADD 2
#define EDIT_OPEN_FLAG_AUDIO 16
#define EDIT_OPEN_FLAG_PROJECT 512
#define EDIT_OPEN_FLAG_DIALOG 65536
#define EDIT_OUTPUT_FLAG_NO_DIALOG 2
#define EDIT_OUTPUT_FLAG_WAV 4

typedef struct {
  int flag;
  int x, y;
  TCHAR *name;
  int track_n;
  TCHAR **track_name;
  int *track_default;
  int *track_s, *track_e;
  int check_n;
  TCHAR **check_name;
  int *check_default;
  BOOL (*func_proc)(void *fp, FILTER_PROC_INFO *fpip);
  BOOL (*func_init)(void *fp);
  BOOL (*func_exit)(void *fp);
  BOOL (*func_update)(void *fp, int status);
  BOOL (*func_WndProc)(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, void *fp);
  int *track;
  int *check;
  void *ex_data_ptr;
  int ex_data_size;
  TCHAR *information;
  BOOL (*func_save_start)(void *fp, int s, int e, void *editp);
  BOOL (*func_save_end)(void *fp, void *editp);
  EXFUNC *exfunc;
  HWND hwnd;
  HINSTANCE dll_hinst;
  void *ex_data_def;
  BOOL (*func_is_saveframe)(void *fp, void *editp, int saveno, int frame, int fps, int edit_flag, int inter);
  BOOL (*func_project_load)(void *fp, void *editp, void *data, int size);
  BOOL (*func_project_save)(void *fp, void *editp, void *data, int *size);
  BOOL (*func_modify_title)(void *fp, void *editp, int frame, LPSTR title, int max_title);
  TCHAR *dll_path;
  int reserve[2];
} FILTER;
#define FILTER_FLAG_ACTIVE 1
#define FILTER_FLAG_ALWAYS_ACTIVE 4
#define FILTER_FLAG_CONFIG_POPUP 8
#define FILTER_FLAG_CONFIG_CHECK 16
#define FILTER_FLAG_CONFIG_RADIO 32
#define FILTER_FLAG_EX_DATA 1024
#define FILTER_FLAG_PRIORITY_HIGHEST 2048
#define FILTER_FLAG_PRIORITY_LOWEST 4096
#define FILTER_FLAG_WINDOW_THICKFRAME 8192
#define FILTER_FLAG_WINDOW_SIZE 16384
#define FILTER_FLAG_DISP_FILTER 32768
#define FILTER_FLAG_REDRAW 0x20000
#define FILTER_FLAG_EX_INFORMATION 0x40000
#define FILTER_FLAG_INFORMATION 0x80000
#define FILTER_FLAG_NO_CONFIG 0x100000
#define FILTER_FLAG_AUDIO_FILTER 0x200000
#define FILTER_FLAG_RADIO_BUTTON 0x400000
#define FILTER_FLAG_WINDOW_HSCROLL 0x800000
#define FILTER_FLAG_WINDOW_VSCROLL 0x1000000
#define FILTER_FLAG_INTERLACE_FILTER 0x4000000
#define FILTER_FLAG_NO_INIT_DATA 0x8000000
#define FILTER_FLAG_IMPORT 0x10000000
#define FILTER_FLAG_EXPORT 0x20000000
#define FILTER_FLAG_MAIN_MESSAGE 0x40000000
#define WM_FILTER_UPDATE (WM_USER + 100)
#define WM_FILTER_FILE_OPEN (WM_USER + 101)
#define WM_FILTER_FILE_CLOSE (WM_USER + 102)
#define WM_FILTER_INIT (WM_USER + 103)
#define WM_FILTER_EXIT (WM_USER + 104)
#define WM_FILTER_SAVE_START (WM_USER + 105)
#define WM_FILTER_SAVE_END (WM_USER + 106)
#define WM_FILTER_IMPORT (WM_USER + 107)
#define WM_FILTER_EXPORT (WM_USER + 108)
#define WM_FILTER_CHANGE_ACTIVE (WM_USER + 109)
#define WM_FILTER_CHANGE_WINDOW (WM_USER + 110)
#define WM_FILTER_CHANGE_PARAM (WM_USER + 111)
#define WM_FILTER_CHANGE_EDIT (WM_USER + 112)
#define WM_FILTER_COMMAND (WM_USER + 113)
#define WM_FILTER_FILE_UPDATE (WM_USER + 114)
#define WM_FILTER_MAIN_MOUSE_DOWN (WM_USER + 120)
#define WM_FILTER_MAIN_MOUSE_UP (WM_USER + 121)
#define WM_FILTER_MAIN_MOUSE_MOVE (WM_USER + 122)
#define WM_FILTER_MAIN_KEY_DOWN (WM_USER + 123)
#define WM_FILTER_MAIN_KEY_UP (WM_USER + 124)
#define WM_FILTER_MAIN_MOVESIZE (WM_USER + 125)
#define WM_FILTER_MAIN_MOUSE_DBLCLK (WM_USER + 126)
#define WM_FILTER_MAIN_MOUSE_R_DOWN (WM_USER + 127)
#define WM_FILTER_MAIN_MOUSE_R_UP (WM_USER + 128)
#define WM_FILTER_MAIN_MOUSE_WHEEL (WM_USER + 129)
#define WM_FILTER_MAIN_CONTEXTMENU (WM_USER + 130)
#define FILTER_UPDATE_STATUS_ALL 0
#define FILTER_UPDATE_STATUS_TRACK 0x10000
#define FILTER_UPDATE_STATUS_CHECK 0x20000
#define FILTER_WINDOW_SIZE_CLIENT 0x10000000
#define FILTER_WINDOW_SIZE_ADD 0x30000000

typedef struct {
  int flag;
  int x, y;
  TCHAR *name;
  int track_n;
  TCHAR **track_name;
  int *track_default;
  int *track_s, *track_e;
  int check_n;
  TCHAR **check_name;
  int *check_default;
  BOOL (*func_proc)(FILTER *fp, FILTER_PROC_INFO *fpip);
  BOOL (*func_init)(FILTER *fp);
  BOOL (*func_exit)(FILTER *fp);
  BOOL (*func_update)(FILTER *fp, int status);
  BOOL (*func_WndProc)(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, FILTER *fp);
  int *track, *check;
  void *ex_data_ptr;
  int ex_data_size;
  TCHAR *information;
  BOOL (*func_save_start)(FILTER *fp, int s, int e, void *editp);
  BOOL (*func_save_end)(FILTER *fp, void *editp);
  EXFUNC *exfunc;
  HWND hwnd;
  HINSTANCE dll_hinst;
  void *ex_data_def;
  BOOL (*func_is_saveframe)(FILTER *fp, void *editp, int saveno, int frame, int fps, int edit_flag, int inter);
  BOOL (*func_project_load)(FILTER *fp, void *editp, void *data, int size);
  BOOL (*func_project_save)(FILTER *fp, void *editp, void *data, int *size);
  BOOL (*func_modify_title)(FILTER *fp, void *editp, int frame, LPSTR title, int max_title);
  TCHAR *dll_path;
  int reserve[2];
} FILTER_DLL;

#define MID_FILTER_BUTTON 12004

BOOL func_proc(FILTER *fp, FILTER_PROC_INFO *fpip);
BOOL func_init(FILTER *fp);
BOOL func_exit(FILTER *fp);
BOOL func_update(FILTER *fp, int status);
BOOL func_WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, FILTER *fp);
BOOL func_save_start(FILTER *fp, int s, int e, void *editp);
BOOL func_save_end(FILTER *fp, void *editp);
BOOL func_is_saveframe(FILTER *fp, void *editp, int saveno, int frame, int fps, int edit_flag, int inter);
BOOL func_project_load(FILTER *fp, void *editp, void *data, int size);
BOOL func_project_save(FILTER *fp, void *editp, void *data, int *size);
BOOL func_modify_title(FILTER *fp, void *editp, int frame, LPSTR title, int max_title);
