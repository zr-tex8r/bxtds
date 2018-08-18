bxtds
=====

LaTeX: TeXies' Data Structure on expl3  
（TeX者のデータ構造 on expl3）

![SUSHI](https://raw.githubusercontent.com/googlei18n/noto-emoji/master/png/128/emoji_u1f363.png)

bxtds ― 本体
-------------

  * `\bxtds_exp:n {x:int式}` ★：
    2のx乗。有効範囲は 0≤x≤30。
  * `\bxtds_ilog:n {x:int式}` ★：
    xの二進対数の整数部分。有効範囲は 1≤x。
  * `\bxtds_get_isqrt:n {x:int式} \RET_int`：
    xの非負平方根の整数部分の値を`\RET_int`に返す。有効範囲は 0≤x<2^20。

※引数が有効範囲外の場合はゼロを返す。

--------------------
Takayuki YATO (aka. "ZR") 
http://zrbabbler.sp.land.to/
