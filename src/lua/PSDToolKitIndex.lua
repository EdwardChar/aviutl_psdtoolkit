-- ���Υե������ AviUtl �Υƥ����ȥ��֥������Ȥ䥹����ץ������ե��륿��
-- require("PSDToolKit") �򤷤��r���i���z�ޤ��ե�����
-- ���Υե����뤬�i���z�ޤ��Ȥ������Ȥ��������ե����뤬�i���z��Ƥ��ʤ��Τǡ�
-- һ������å����o�������ѥ���ͨ�����ϤǸĤ���i���z��
package.loaded["PSDToolKit"] = nil
local origpath = package.path
local origcpath = package.cpath
package.path = obj.getinfo("script_path") .. "PSDToolKit\\?.lua"
package.cpath = obj.getinfo("script_path") .. "PSDToolKit\\?.dll"
local p = require("PSDToolKit")
require("PSDToolKitBridge")
package.path = origpath
package.cpath = origcpath
return p
