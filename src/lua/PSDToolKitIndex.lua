-- このファイルは AviUtl のテキストオブジェクトやスクリプト崙囮フィルタで
-- require("PSDToolKit") をした�rに�iみ�zまれるファイル
-- このファイルが�iみ�zまれるということは屎しいファイルが�iみ�zめていないので、
-- 匯稀キャッシュを�o�浸�しパスを宥した貧で個めて�iみ�zむ
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
