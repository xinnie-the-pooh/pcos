# pcos
mcu uart parallel comunacate system

单片机并发串口通信系统

2024-6 准备合并到scpi模式 用于gpib通信

*IDN?
标识查询。返回仪器的标识字符串。

参数	一般返回
(无)	Agilent Technologies,33522B,XXXXXXXXXX,0.179-1.19-8.88-52-00
返回仪器的标识字符串：
#  *IDN?
标识字符串包含四个用逗号分隔的字段：
制造商名称
型号
序列号
修订版代码
33500 系列仪器的标识字符串采用以下格式：

Agilent Technologies,[型号],[长度为 10 个字符的序列号],A.aaa-B.bb-C.cc-DD-EE

A.aaa

= 固件版本

B.bb

= 前面板固件版本

C.cc

= 电源控制器固件修订版

DD

= FPGA 版本

EE

= PCBA 版本
# *RST
将仪器重置为典型或安全的预定义值。 在重置状态中介绍此类设置。

参数	典型返回
（无）	（无）
重置仪器：*RST
*RST 强制执行 ABORt 命令。该命令将取消当前正在执行的测量或瞬变。这将在“操作状态”寄存器中重置 WTG-meas、MEAS-active、WTG-tran 和 TRAN-active 位。
