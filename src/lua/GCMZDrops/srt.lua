local P = {}

P.name = "����SRT�ļ�"

P.priority = 0

local wavP = require("psdtoolkit_wav")

function P.ondragenter(files, state)
  for i, v in ipairs(files) do
    if v.filepath:match("[^.]+$"):lower() == "srt" then
      -- �ե�����Β����Ӥ� srt �Υե����뤬���ä���I��Ǥ������ʤΤ� true
      return true
    end
  end
  return false
end

function P.ondragover(files, state)
  -- ondragenter �ǄI��Ǥ������ʤ�Τ� ondragover �Ǥ�I��Ǥ������ʤΤ��{�٤� true
  return true
end

function P.ondragleave()
end

function P.parse(filepath)
  local setting = wavP.loadsetting()
  local f, err = io.open(filepath, "rb")
  if f == nil then
    error(err)
  end
  local srt = f:read("*all")
  f:close()
  if setting.srt_encoding ~= "utf8" then
    srt = GCMZDrops.convertencoding(srt, setting.srt_encoding, "utf8")
  end
  if srt:sub(-1) ~= "\n" then
    srt = srt .. "\r\n"
  end

  local r = {}
  local id = nil
  local subtitle = ""
  local startf = nil
  local endf = nil
  local maxendf = 0
  for line in srt:gmatch("(.-)\r?\n") do
    if line ~= "" then
      local yet = true
      if yet and (id == nil) then
        local s = line:match("^%d+$")
        if s ~= nil then
          id = tonumber(s)
          yet = false
        end
      end
      if yet and (startf == nil)and(endf == nil) then
        local sh, sm, ss, sms, eh, em, es, ems = line:match("^(%d+):(%d%d):(%d%d),(%d%d%d) %-%-> (%d+):(%d%d):(%d%d),(%d%d%d)$")
        if sh ~= nil then
          startf = tonumber(sh)*60*60 + tonumber(sm)*60 + tonumber(ss) + tonumber(sms)/1000
          endf = tonumber(eh)*60*60 + tonumber(em)*60 + tonumber(es) + tonumber(ems)/1000
          yet = false
        end
      end
      if yet then
        subtitle = subtitle .. line .. "\r\n"
        yet = false
      end
    else
      if (id ~= nil)and(subtitle ~= "")and(startf ~= nil)and(endf ~= nil) then
        endf = endf + setting.srt_margin
        table.insert(r, {id=id, s=startf, e=endf, subtitle=subtitle})
        if maxendf < endf then
          maxendf = endf
        end
      end
      id = nil
      subtitle = ""
      startf = nil
      endf = nil
    end
  end
  -- ��ֱ�Ҫ�ʤ����ɡ��r�g�S��oҕ�������ä�Ǥ���Τ�һ�ꌝ��
  table.sort(r, function(a, b)
    return a.s < b.s
  end)
  return r, maxendf
end

function P.ondrop(files, state)
  local setting = wavP.loadsetting()
  for i, v in ipairs(files) do
    -- �ե�����Β����Ӥ� srt �ʤ�
    if v.filepath:match("[^.]+$"):lower() == "srt" then
      -- �ץ������Ȥ�����ȡ�ä���
      local proj = GCMZDrops.getexeditfileinfo()
      -- SRT �ե���������
      local srt, len = P.parse(v.filepath)

      local oini = GCMZDrops.inistring("")
      oini:set("exedit", "width", proj.width)
      oini:set("exedit", "height", proj.height)
      oini:set("exedit", "rate", proj.rate)
      oini:set("exedit", "scale", proj.scale)
      oini:set("exedit", "length", math.floor(len * proj.rate / proj.scale))
      oini:set("exedit", "audio_rate", proj.audio_rate)
      oini:set("exedit", "audio_ch", proj.audio_ch)
      
      -- SRT �����ݤˏ��äƥƥ����ȥ��֥������Ȥ��뤷�Ƥ���
      -- �⤷��ʾ��������Ϥϱ�ʾ�ȤΥ쥤��`��䤨��
      -- �����������`��1���ȽY���������Q���ʤ��ΤǤ��ޤ���ζ�Ϥʤ�����
      local textbase = tostring(wavP.exaread(wavP.resolvepath(v.filepath, setting.srt_exafinder, setting), "srt"))
      local values = {
        START = 0,
        END = 0,
        SUBTITLE = ""
      }
      local modifiers = {
        ENCODE_TEXT = function(v)
          return GCMZDrops.encodeexotextutf8(v)
        end
      }
      local layers = {}
      local n = 0
      for i, t in ipairs(srt) do
        local subtitle = t.subtitle
        -- �ÓQ�ÄI�����ӳ���
        subtitle = setting:wav_subtitle_replacer(subtitle)
        -- �����`�ɤ� 1 �Εr�ϥƥ����Ȥ򥹥���ץȤȤ������Τ���
        if setting.srt_insertmode == 1 then
          subtitle = setting:srt_subtitle_scripter(subtitle)
        end
        values.SUBTITLE = subtitle
        values.START = math.floor(t.s * proj.rate / proj.scale)
        values.END = math.floor(t.e * proj.rate / proj.scale)
        local found = nil
        for li, le in ipairs(layers) do
          if le < values.START then
            found = li
            break
          end
        end
        if found ~= nil then
          layers[found] = values.END
        else
          table.insert(layers, values.END)
          found = #layers
        end

        local aini = GCMZDrops.inistring(textbase)
        setting:srt_examodifler(aini, values, modifiers)
        wavP.insertexa(oini, aini, n, found)
        n = n + 1
      end

      local filepath = GCMZDrops.createtempfile("srt", ".exo")
      local exo, err = io.open(filepath, "wb")
      if exo == nil then
        error(err)
      end
      exo:write(tostring(oini))
      exo:close()
      debug_print("["..P.name.."] ��exo�ļ��滻�� " .. v.filepath .. " ��ԭ�ļ�����ͨ��orgfilepath��ȡ��")
      files[i] = {filepath=filepath, orgfilepath=v.filepath}
    end
  end
  -- ���Υ��٥�ȥϥ�ɥ�`�ˤ�I��򤵤������ΤǤ����ϳ��� false
  return false
end

return P
