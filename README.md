# multi_motor_control

Arduinoでモーターを複数個(ここでは16台を想定)独立に操作します。Arduinoは親機と子機（master/slave）の関係で、PCからシリアル通信で親機に送り、親機から子機に送っている。

## 回路図

![circuit](/etc/cirkit.svg)