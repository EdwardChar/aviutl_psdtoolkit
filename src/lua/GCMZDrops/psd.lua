local P = {}

P.name = "PSD�ļ�תexo"

P.priority = 0

function P.ondragenter(files, state)
  for i, v in ipairs(files) do
    local ext = v.filepath:match("[^.]+$"):lower()
    if ext == "psd" or ext == "psb" then
      -- �ե�����Β����Ӥ� psd �� psb �Υե����뤬���ä���I���Ǥ������ʤΤ� true
      return true
    end
  end
  return false
end

function P.ondragover(files, state)
  -- ondragenter �ǄI���Ǥ������ʤ�Τ� ondragover �Ǥ�I���Ǥ������ʤΤ��{�٤� true
  return true
end

function P.ondragleave()
end

function P.encodelua(s)
  s = GCMZDrops.convertencoding(s, "gbk", "utf8")
  s = GCMZDrops.encodeluastring(s)
  s = GCMZDrops.convertencoding(s, "utf8", "gbk")
  return s
end

function P.ondrop(files, state)
  for i, v in ipairs(files) do
    -- �ե�����Β����Ӥ� psd �� psb ���ä���
    local ext = v.filepath:match("[^.]+$"):lower()
    if ext == "psd" or ext == "psb" then
      local filepath = v.filepath
      local filename = filepath:match("[^/\\]+$")

      -- һ�w�� pfv �ե���������Ǥ��ʤ����{�٤�
      local psddir = filepath:sub(1, #filepath-#filename)
      for i2, v2 in ipairs(files) do
        if v2.filepath:match("[^.]+$"):lower() == "pfv" then
          local pfv = v2.filepath:match("[^/\\]+$")
          local pfvdir = v2.filepath:sub(1, #v2.filepath-#pfv)
          if psddir == pfvdir then
            -- ͬ���ե�����`�ڤ� pfv �ե������һ�w��Ͷ���z��Ǥ����Τ��B�Y
            filepath = filepath .. "|" .. pfv
            -- ���� pfv �ե�����ϥɥ��åפ����ե����뤫���ȡ������Ƥ���
            table.remove(files, i2)
            break
          end
        end
      end

      -- �ե������ֱ���i���z������� exo �ե������M�����Ƥ�
      math.randomseed(os.time())
      local tag = math.floor(math.random()*0x7fffffff + 1)
      local proj = GCMZDrops.getexeditfileinfo()
      local jp = not GCMZDrops.englishpatched()
      local exo = [[
[exedit]
width=]] .. proj.width .. "\r\n" .. [[
height=]] .. proj.height .. "\r\n" .. [[
rate=]] .. proj.rate .. "\r\n" .. [[
scale=]] .. proj.scale .. "\r\n" .. [[
length=64
audio_rate=]] .. proj.audio_rate .. "\r\n" .. [[
audio_ch=]] .. proj.audio_ch .. "\r\n" .. [[
[0]
start=1
end=64
layer=1
overlay=1
camera=0
[0.0]
_name=]] .. (jp and [[�ı�]] or [[Text]]) .. "\r\n" .. [[
]] .. (jp and [[��С]] or [[Size]]) .. [[=1
]] .. (jp and [[��ʾ�ٶ�]] or [[vDisplay]]) .. [[=0.0
]] .. (jp and [[���ֵ�һ����]] or [[1char1obj]]) .. [[=0
]] .. (jp and [[��·������]] or [[Show on motion coordinate]]) .. [[=0
]] .. (jp and [[�Զ�����]] or [[Automatic scrolling]]) .. [[=0
B=0
I=0
type=0
autoadjust=0
soft=0
monospace=0
align=4
spacing_x=0
spacing_y=0
precision=0
color=ffffff
color2=000000
font=]] .. (jp and [[����]] or [[����]]) .. "\r\n" .. [[
text=]] .. GCMZDrops.encodeexotext("<?-- " .. filename .. " \r\n\r\no={ -- ѡ���趨\r\nlipsync = 0    ,-- �Կ���Ԥ��ͼ���\r\nmpslider = 0    ,-- �۲��������ͼ���\r\nscene = 0    ,-- �κϳ����\r\ntag = " .. tag .. "    ,-- ʶ���ñ��\r\n\r\n-- �Կ���Ԥ��Ĭ���趨\r\nls_locut = 100    ,-- ����\r\nls_hicut = 1000    ,-- ����\r\nls_threshold = 20    ,-- ��ֵ\r\nls_sensitivity = 1    ,-- ������\r\n\r\n-- �벻Ҫ��д��������\r\nptkf=" .. P.encodelua(filepath) .. ",ptkl=\"\"}PSD,subobj=require(\"PSDToolKit\").PSDState.init(obj,o)?>") .. "\r\n" .. [[
[0.1]
_name=]] .. (jp and [[����Ч��]] or [[Animation effect]]) .. "\r\n" .. [[
track0=-1.00
track1=100.00
track2=0.00
track3=0.00
check0=100
type=0
filter=2
name=�軭@PSD
param=
[0.2]
_name=]] .. (jp and [[��׼����]] or [[Standard drawing]]) .. "\r\n" .. [[
X=0.0
Y=0.0
Z=0.0
]] .. (jp and [[������]] or [[Zoom%]]) .. [[=100.00
]] .. (jp and [[͸����]] or [[Clearness]]) .. [[=0.0
]] .. (jp and [[��ת\]] or [[Rotation]]) .. [[=0.00
blend=0
]]

      -- PSDToolKit ������ɥ��˥ɥ��åפ��줿�ե������׷�Ӥ���
      -- һ�r�Ĥ� package.cpath ������Q�� PSDToolKitBridge.dll ���i���z��� addfile �����
      local origcpath = package.cpath
      package.cpath = GCMZDrops.scriptdir() .. "..\\script\\PSDToolKit\\?.dll"
      require('PSDToolKitBridge').addfile(GCMZDrops.convertencoding(filepath, "gbk", "utf8"), tag)
      package.cpath = origcpath

      local filepath = GCMZDrops.createtempfile("psd", ".exo")
      f, err = io.open(filepath, "wb")
      if f == nil then
        error(err)
      end
      f:write(exo)
      f:close()
      debug_print("["..P.name.."] ��exo�ļ��滻�� " .. v.filepath .. " ��ԭ�ļ�����ͨ��orgfilepath��ȡ��")
      files[i] = {filepath=filepath, orgfilepath=v.filepath}
    end
  end
  -- ���Υ��٥�ȥϥ�ɥ�`�ˤ�I���򤵤������ΤǤ����ϳ��� false
  return false
end

return P
