#include "error_ptk.h"

NODISCARD static error get_ptk_message(int const code, struct NATIVE_STR *const message) {
  switch (code) {
  case err_ptk_arch_is_not_64bit:
    return scpy(message, NSTR("需要在64位Windows系统下运行。"));
  case err_ptk_unsupported_aviutl_version:
    return scpy(message, NSTR("AviUtl版本超出范围。"));
  case err_ptk_exedit_not_found:
    return scpy(message, NSTR("找不到扩展编辑插件。"));
  case err_ptk_exedit_not_found_in_same_dir:
    return scpy(message, NSTR("无法在同一目录中找到扩展编辑插件。"));
  case err_ptk_lua51_cannot_load:
    return scpy(message, NSTR("lua51.dll读取失败。"));
  case err_ptk_bridge_cannot_load:
    return scpy(message, NSTR("PSDToolKitBridge.dll读取失败。"));
  case err_ptk_unsupported_exedit_version:
    return scpy(message, NSTR("扩展编辑插件版本超出范围。"));
  case err_ptk_project_is_not_open:
    return scpy(message, NSTR("AviUtl工程文件(*.aup)尚未打开。"));
  case err_ptk_project_has_not_yet_been_saved:
    return scpy(message, NSTR("AviUtl工程文件(*.aup)尚未保存。"));
  case err_ptk_target_psd_file_object_not_found:
    return scpy(message, NSTR("未找到设定传送目标 - 文本输入栏。"));
  case err_ptk_target_variable_not_found:
    return scpy(message, NSTR("未找到需改写的变量。"));

  case err_ptk_ipc_target_not_found:
    return scpy(message, NSTR("未找到需启动的程序。"));
  case err_ptk_ipc_target_access_denied:
    return scpy(message, NSTR("程序执行被拒绝。"));

  case err_ptk_lua:
    return scpy(message, NSTR("Lua脚本运行时出错。"));
  }
  return scpy(message, NSTR("未知的错误。"));
}

error error_ptk_init(void) {
  error err = error_register_message_mapper(err_type_ptk, get_ptk_message);
  if (efailed(err)) {
    return err;
  }
  return eok();
}
