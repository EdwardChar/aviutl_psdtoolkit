package prop

import "testing"

var testdata = [][2]string{
	{"无法显示的源字符串", ".%xQ法显示%xP的%xB原字符串"},
	{"无法显示", ".%xQ法显示%xP"},
	{"酱汁脸", ".%xB酱汁脸"},
	{"👍好字", ".%vTfQB字"},
	{"好👍字", ".好%vTfQB字"},
	{"好字👍", ".好字%vTfQB"},
}

func TestEncode(t *testing.T) {
	for idx, data := range testdata {
		if got := Encode(data[0]); data[1] != got {
			t.Errorf("[%d] want %q, got %q", idx, data[1], got)
		}
	}
}

func TestDecode(t *testing.T) {
	for idx, data := range testdata {
		got, err := Decode(data[1])
		if err != nil {
			t.Fatal(err)
		}
		if data[0] != got {
			t.Errorf("[%d] want %q, got %q", idx, data[0], got)
		}
	}
}
