# postfixConversion

這是一個用C語言編寫的中綴表達式計算器程序，支援從檔案讀取中綴表達式和互動式輸入。

## 編譯和運行

確保已安裝合適的編譯器，如GCC。 在終端機中執行以下命令：

```bash
gcc -o calculator main.c -lm
./calculator expressions.dat'
```

或者，如果要從標準輸入獲取中綴表達式：

```bash
./calculator
```
程式將提示輸入中綴表達式，輸入 結束輸入。stop

## 檔案格式

程式支援從檔中讀取中綴表達式。 檔中每行包含一個獨立的中綴表達式。

範例檔 ：[expressions.dat](https://github.com/BAGLE102/postfixConversion/blob/main/Homework%2003/expressions.dat)

## 互動式輸入
如果沒有提供檔名作為參數，程式將等待使用者輸入中綴表達式。

```bash
Infix : 3+5*2
Postfix : 3 5 2* +
Value : 13.000000
==========================
Infix : (4+6)*2
Postfix : 4 6 + 2* 
Value : 20.000000
==========================
Infix : stop
```
## 注意事項
- 如果檔名作為參數提供，程式將按順序處理檔中的每個中綴表達式。
- 對於每個處理的表達式，程式將輸出其中綴運算式、後綴表達式和計算結果。
- 如果沒有提供檔名作為參數，程式將等待使用者輸入中綴表達式，輸入 `stop` 結束輸入。


