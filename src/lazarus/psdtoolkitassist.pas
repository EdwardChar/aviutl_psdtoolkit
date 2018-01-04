unit PSDToolKitAssist;

{$mode objfpc}{$H+}
{$CODEPAGE UTF-8}

interface

uses
  Windows, AviUtl;

type
  { TPSDToolKitAssist }

  TPSDToolKitAssist = class
  private
    FEntry: TFilterDLL;
    FWindow: THandle;
    function GetEntry: PFilterDLL;
  public
    constructor Create();
    destructor Destroy(); override;
    function InitProc(fp: PFilter): boolean;
    function ExitProc({%H-}fp: PFilter): boolean;
    property Entry: PFilterDLL read GetEntry;
  end;

implementation

uses
  lua, SysUtils, Ver;

var
  MainDLLInstance: THandle;

function LuaAllocator({%H-}ud, ptr: Pointer; {%H-}osize, nsize: size_t): Pointer; cdecl;
begin
  if nsize = 0 then
  begin
    if ptr <> nil then
      FreeMem(ptr);
    Result := nil;
    Exit;
  end;
  if ptr <> nil then
    Result := ReallocMem({%H-}ptr, nsize)
  else
    Result := GetMem(nsize);
end;

function FindExEditWindow(): THandle;
var
  h: THandle;
  pid, mypid: DWORD;
begin
  Result := 0;
  mypid := GetCurrentProcessId();
  h := 0;
  while Result = 0 do
  begin
    h := FindWindowExA(0, h, 'ExtendedFilterClass', nil);
    if h = 0 then
      Exit;
    GetWindowThreadProcessId(h, @pid);
    if pid = mypid then
       Result := h;
  end;
end;

procedure ShowGUI();
var
  h: THandle;
  s: WideString;
  L: Plua_state;
  Proc: lua_CFunction;
  n: integer;
begin
  if MainDLLInstance = 0 then
    Exit;
  Proc := lua_CFunction(GetProcAddress(MainDLLInstance, 'luaopen_PSDToolKit'));
  if Proc = nil then
    Exit;
  L := lua_newstate(@LuaAllocator, nil);
  if L = nil then
    Exit;
  try
    lua_pushstring(L, 'PSDToolKit');
    n := Proc(L);
    if n <> 1 then
      Exit;
    lua_getfield(L, 2, 'showgui');
    if not lua_iscfunction(L, 3) then
      Exit;
    lua_call(L, 0, 2);
    if not lua_toboolean(L, -2) then begin
      h := FindExEditWindow();
      s := 'ウィンドウの表示中にエラーが発生しました。'#13#10#13#10+WideString(string(lua_tostring(L, -1)));
      MessageBoxW(h, PWideChar(s), 'PSDToolKit', MB_ICONERROR);
    end;
  finally
    lua_close(L);
  end;
end;

function WndProc(hwnd: HWND; Msg: UINT; WP: WPARAM; LP: LPARAM): LRESULT; stdcall;
begin
  if (Msg = WM_FILTER_COMMAND) and (WP = 1) then
    ShowGUI();
  Result := DefWindowProc(hwnd, Msg, WP, LP);
end;

{ TPSDToolKitAssist }

function TPSDToolKitAssist.GetEntry: PFilterDLL;
begin
  Result := @FEntry;
end;

constructor TPSDToolKitAssist.Create;
const
  PluginName = 'PSDToolKit';
  PluginInfo = 'PSDToolKitAssist '+Version;
begin
  inherited Create();
  FillChar(FEntry, SizeOf(FEntry), 0);
  FEntry.Flag := FILTER_FLAG_ALWAYS_ACTIVE or FILTER_FLAG_EX_INFORMATION or FILTER_FLAG_NO_CONFIG;
  FEntry.Name := PluginName;
  FEntry.Information := PluginInfo;
end;

destructor TPSDToolKitAssist.Destroy;
begin
  inherited Destroy();
end;

function TPSDToolKitAssist.InitProc(fp: PFilter): boolean;
type
  ShiftJISString = type ansistring(932);
const
  ShowGUICaption: WideString = 'ウィンドウを表示';
  ExEditNameANSI = #$8a#$67#$92#$a3#$95#$d2#$8f#$57; // '拡張編集'
  ExEditVersion = ' version 0.92 ';
  HWND_MESSAGE = HWND(-3);
  PROCESSOR_ARCHITECTURE_AMD64 = 9;
var
  i: Integer;
  wc: WNDCLASS;
  si: SYSTEM_INFO;
  asi: TSysInfo;
  exedit: PFilter;
begin
  Result := True;
  FWindow := 0;

  try
    GetNativeSystemInfo(@si);
    if si.wProcessorArchitecture <> PROCESSOR_ARCHITECTURE_AMD64 then
      raise Exception.Create('PSDToolKit を使用するには64bit 版の Windows が必要です。');
    if MainDLLInstance = 0 then
      raise Exception.Create('script\PSDToolKit\PSDToolKit.dll の読み込みに失敗しました。');
    if not LuaLoaded() then
      raise Exception.Create('lua51.dll の読み込みに失敗しました。');
    if fp^.ExFunc^.GetSysInfo(nil, @asi) = AVIUTL_FALSE then
      raise Exception.Create('AviUtl のバージョン情報取得に失敗しました。');
    if asi.Build < 10000 then
      raise Exception.Create('PSDToolKit を使うには AviUtl version 1.00 以降が必要です。');
    for i := 0 to asi.FilterN - 1 do
    begin
      exedit := fp^.ExFunc^.GetFilterP(i);
      if (exedit = nil) or (exedit^.Name <> ExEditNameANSI) then
        continue;
      if StrPos(exedit^.Information, ExEditVersion) = nil then
        raise Exception.Create('PSDToolKit を使うには拡張編集'+ExEditVersion+'が必要です。');
      break;
    end;
  except
    on E: Exception do begin
      MessageBoxW(0, PWideChar('PSDToolKit の初期化に失敗しました。'#13#10#13#10 + WideString(E.Message)), 'PSDToolKit', MB_ICONERROR);
      Exit;
    end;
  end;

  wc.style := 0;
  wc.lpfnWndProc := @WndProc;
  wc.cbClsExtra := 0;
  wc.cbWndExtra := 0;
  wc.hInstance := fp^.DLLHInst;
  wc.hIcon := 0;
  wc.hCursor := 0;
  wc.hbrBackground := 0;
  wc.lpszMenuName := nil;
  wc.lpszClassName := 'PSDToolKitAssist';
  RegisterClass(wc);
  FWindow := CreateWindow('PSDToolKitAssist', nil, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_MESSAGE,
    0, fp^.DLLHInst, nil);
  fp^.ExFunc^.AddMenuItem(fp, PChar(ShiftJISString(ShowGUICaption)),
    FWindow, 1, VK_W, ADD_MENU_ITEM_FLAG_KEY_CTRL);
end;

function TPSDToolKitAssist.ExitProc(fp: PFilter): boolean;
begin
  Result := True;
  if MainDLLInstance = 0 then
    Exit;
  if FWindow <> 0 then
    DestroyWindow(FWindow);
end;

function GetMainDLLName(): WideString;
begin
  SetLength(Result, MAX_PATH);
  GetModuleFileNameW(hInstance, @Result[1], MAX_PATH);
  Result := ExtractFileDir(PWideChar(Result)) + '\script\PSDToolKit\PSDToolKit.dll';
end;

function GetLuaDLLName(): WideString;
begin
  SetLength(Result, MAX_PATH);
  GetModuleFileNameW(hInstance, @Result[1], MAX_PATH);
  Result := ExtractFileDir(PWideChar(Result)) + '\lua51.dll';
end;

initialization
  MainDLLInstance := LoadLibraryW(PWideChar(GetMainDLLName()));
  LoadLua(GetLuaDLLName());

finalization
  if MainDLLInstance <> 0 then
    FreeLibrary(MainDLLInstance);
  if LuaLoaded() then
    FreeLua();

end.
