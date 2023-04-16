-- このファイルは AviUtl のテキストオブジェクトやスクリプト制御フィルタで
-- require("PSDToolKit") をした時に読み込まれるファイル
-- このファイルが読み込まれるということは正しいファイルが読み込めていないので、
-- 一旦キャッシュを無効化しパスを通した上で改めて読み込む
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
