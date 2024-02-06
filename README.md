# Level1 : get_next_line

## 課題指定事項
- Prototype : char *get_next_line(int fd);
- Turn in files : get_next_line.c, get_next_line_utils.c, get_next_line.h
- External functs : read, malloc, free
- Parameters fd : The file descriptor to read from

## 概要
-  **`get_next_line`** 関数は、指定されたファイルディスクリプタから1行ずつ読み込む関数です。この関数はループを使用して複数回呼び出すことができ、ファイル内のテキストを一行ずつ読み取ります。
- 関数は、読み取った行を返します。もし読み取るものがないか、エラーが発生した場合は **`NULL`** を返します。
- 読み取った行には、改行文字 **`\n`** が含まれます。ただし、ファイルの末尾に達した場合、かつその行が改行文字で終わっていない場合は、改行文字を含まないで返します。