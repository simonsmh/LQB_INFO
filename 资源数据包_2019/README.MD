## 官方提供的资源包
比赛官方只提供这些资源，应当多多参考

```
.
└── 资源数据包_2019
    ├── 赛点资源数据包_单片机_2019
    │   ├── 1-STC-ISP软件
    │   │   ├── stc-isp-15xx-v6.85I.exe
    │   │   ├── stc-isp-15xx-v6.85N.exe
    │   │   └── stc-isp-15xx-v6.86r.exe
    │   ├── 2-USB驱动程序
    │   │   ├── 驱动程序安装说明.txt
    │   │   ├── X64
    │   │   │   └── CH341SER_x64.EXE
    │   │   └── X86
    │   │       └── CH341SER.EXE
    │   ├── 3-底层驱动代码参考
    │   │   ├── 驱动代码说明.TXT
    │   │   ├── ds1302.c
    │   │   ├── ds1302.h
    │   │   ├── iic.c
    │   │   ├── iic.h
    │   │   ├── onewire.c
    │   │   └── onewire.h
    │   ├── 4-工具软件
    │   │   ├── 串口调试助手
    │   │   ├── 代码编辑器-Notepad++
    │   │   └── PDF阅读器.exe
    │   ├── 5-竞赛板芯片资料
    │   │   ├── 74HC138.pdf
    │   │   ├── 74HC_HCT02.pdf
    │   │   ├── 74HC_HCT04.pdf
    │   │   ├── 74HC_HCT573.pdf
    │   │   ├── 红外一体化接收头8.pdf
    │   │   ├── AT24C02.pdf
    │   │   ├── CH340DS1.PDF
    │   │   ├── DS1302.pdf
    │   │   ├── DS18B20.pdf
    │   │   ├── LM324.pdf
    │   │   ├── LM386.pdf
    │   │   ├── LM555.pdf
    │   │   ├── PCF8591.pdf
    │   │   ├── STC12C5A60S2.pdf
    │   │   ├── STC89C51RC-RD+_GUIDE-CHINESE.pdf
    │   │   ├── ULN2003.pdf
    │   │   └── USBCH341.pdf
    │   ├── 6-IAP15F2K61S2单片机转接板技术资料
    │   │   ├── 转接板PCB.pdf
    │   │   └── IAP15F2K61S2-89C52转换板说明文件.pdf
    │   ├── 7-竞赛板资料
    │   │   ├── 原理图
    │   │   │   ├── 说明.txt
    │   │   │   ├── CT107D单片机竞赛板V10原理图+IAP15转接板原理图
    │   │   │   │   ├── CT107D单片机竞赛板V10原理图.pdf
    │   │   │   │   └── IAP15转接板原理图.pdf
    │   │   │   └── CT107D单片机竞赛板V20原理图
    │   │   │       └── CT107D单片机竞赛板V20原理图.pdf
    │   │   └── CT107D单片机竞赛板使用说明书.pdf
    │   ├── 程序下载说明.txt
    │   ├── 共阳极数码管段码表.txt
    │   ├── IAP15F2K61S2单片机仿真使用说明.pdf
    │   └── STC15系列单片机用户手册.pdf
    ├── 赛点资源数据包_嵌入式_2019
    │   ├── 1-USB驱动程序（FT2232）
    │   │   └── FT2232驱动
    │   │       ├── amd64
    │   │       │   ├── ftbusui.dll
    │   │       │   ├── ftcserco.dll
    │   │       │   ├── ftd2xx64.dll
    │   │       │   ├── ftd2xx.lib
    │   │       │   ├── ftdibus.sys
    │   │       │   ├── ftlang.dll
    │   │       │   ├── ftser2k.sys
    │   │       │   └── ftserui2.dll
    │   │       ├── ftd2xx.h
    │   │       ├── ftdibus.cat
    │   │       ├── ftdibus.inf
    │   │       ├── ftdiport.cat
    │   │       ├── ftdiport.inf
    │   │       ├── i386
    │   │       │   ├── ftbusui.dll
    │   │       │   ├── ftcserco.dll
    │   │       │   ├── ftd2xx.dll
    │   │       │   ├── ftd2xx.lib
    │   │       │   ├── ftdibus.sys
    │   │       │   ├── ftlang.dll
    │   │       │   ├── ftser2k.sys
    │   │       │   └── ftserui2.dll
    │   │       ├── LogoVerificationReport.pdf
    │   │       └── Static
    │   │           ├── amd64
    │   │           │   └── ftd2xx.lib
    │   │           └── i386
    │   │               └── ftd2xx.lib
    │   ├── 2-Colink for MDK插件
    │   │   └── CoMDKPlugin-1.3.1.exe
    │   ├── 3-底层驱动代码参考
    │   │   ├── 说明.txt
    │   │   ├── i2c.c
    │   │   └── i2c.h
    │   ├── 4-工具软件
    │   │   ├── 串口调试助手
    │   │   ├── 代码编辑器-Notepad++
    │   │   └── PDF阅读器.exe
    │   ├── 5-竞赛板芯片资料
    │   │   ├── 74HC_HCT573.pdf
    │   │   ├── 液晶控制器芯片资料
    │   │   │   ├── 液晶控制器说明.txt
    │   │   │   ├── 液晶控制器ILI9325.pdf
    │   │   │   ├── 液晶控制器ILI9328.pdf
    │   │   │   └── 液晶控制芯片uc8230s.pdf
    │   │   ├── AT24C02.pdf
    │   │   ├── STM32_CN.pdf
    │   │   ├── STM32_EN.pdf
    │   │   ├── stm32f103rbt6.pdf
    │   │   └── STM32F10xxx Cortex-M3 programming manual.pdf
    │   ├── 6-STM32固件库代码V3.5版
    │   │   ├── stm32f10x_stdperiph_lib_um.chm
    │   │   └── stm32f10x_stdperiph_lib.zip
    │   ├── 7-嵌入式竞赛板资料
    │   │   ├── CT117E电路原理图.pdf
    │   │   └── CT117E嵌入式竞赛板使用说明-V1.1.pdf
    │   ├── 8-液晶驱动参考例程
    │   │   ├── CT117E-LCD
    │   │   │   ├── Inc
    │   │   │   │   ├── fonts.H
    │   │   │   │   ├── lcd.h
    │   │   │   │   ├── stm32f10x_conf.h
    │   │   │   │   └── stm32f10x_it.h
    │   │   │   ├── Libraries
    │   │   │   │   ├── CMSIS
    │   │   │   │   │   ├── CM3
    │   │   │   │   │   │   ├── CoreSupport
    │   │   │   │   │   │   │   ├── core_cm3.c
    │   │   │   │   │   │   │   └── core_cm3.h
    │   │   │   │   │   │   └── DeviceSupport
    │   │   │   │   │   │       └── ST
    │   │   │   │   │   │           └── STM32F10x
    │   │   │   │   │   │               ├── Release_Notes.html
    │   │   │   │   │   │               ├── startup
    │   │   │   │   │   │               │   ├── arm
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_cl.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_hd.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_hd_vl.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_ld.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_ld_vl.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_md.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_md_vl.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_xl.s
    │   │   │   │   │   │               │   │   └── STM32F10x.s
    │   │   │   │   │   │               │   ├── gcc_ride7
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_cl.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_hd.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_hd_vl.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_ld.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_ld_vl.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_md.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_md_vl.s
    │   │   │   │   │   │               │   │   └── startup_stm32f10x_xl.s
    │   │   │   │   │   │               │   ├── iar
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_cl.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_hd.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_hd_vl.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_ld.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_ld_vl.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_md.s
    │   │   │   │   │   │               │   │   ├── startup_stm32f10x_md_vl.s
    │   │   │   │   │   │               │   │   └── startup_stm32f10x_xl.s
    │   │   │   │   │   │               │   └── TrueSTUDIO
    │   │   │   │   │   │               │       ├── startup_stm32f10x_cl.s
    │   │   │   │   │   │               │       ├── startup_stm32f10x_hd.s
    │   │   │   │   │   │               │       ├── startup_stm32f10x_hd_vl.s
    │   │   │   │   │   │               │       ├── startup_stm32f10x_ld.s
    │   │   │   │   │   │               │       ├── startup_stm32f10x_ld_vl.s
    │   │   │   │   │   │               │       ├── startup_stm32f10x_md.s
    │   │   │   │   │   │               │       ├── startup_stm32f10x_md_vl.s
    │   │   │   │   │   │               │       └── startup_stm32f10x_xl.s
    │   │   │   │   │   │               ├── stm32f10x.h
    │   │   │   │   │   │               ├── system_stm32f10x.c
    │   │   │   │   │   │               └── system_stm32f10x.h
    │   │   │   │   │   ├── CMSIS_changes.htm
    │   │   │   │   │   ├── CMSIS debug support.htm
    │   │   │   │   │   ├── Documentation
    │   │   │   │   │   │   └── CMSIS_Core.htm
    │   │   │   │   │   └── License.doc
    │   │   │   │   └── STM32F10x_StdPeriph_Driver
    │   │   │   │       ├── inc
    │   │   │   │       │   ├── misc.h
    │   │   │   │       │   ├── stm32f10x_adc.h
    │   │   │   │       │   ├── stm32f10x_bkp.h
    │   │   │   │       │   ├── stm32f10x_can.h
    │   │   │   │       │   ├── stm32f10x_cec.h
    │   │   │   │       │   ├── stm32f10x_conf.h
    │   │   │   │       │   ├── stm32f10x_crc.h
    │   │   │   │       │   ├── stm32f10x_dac.h
    │   │   │   │       │   ├── stm32f10x_dbgmcu.h
    │   │   │   │       │   ├── stm32f10x_dma.h
    │   │   │   │       │   ├── stm32f10x_exti.h
    │   │   │   │       │   ├── stm32f10x_flash.h
    │   │   │   │       │   ├── stm32f10x_fsmc.h
    │   │   │   │       │   ├── stm32f10x_gpio.h
    │   │   │   │       │   ├── stm32f10x_i2c.h
    │   │   │   │       │   ├── stm32f10x_iwdg.h
    │   │   │   │       │   ├── stm32f10x_pwr.h
    │   │   │   │       │   ├── stm32f10x_rcc.h
    │   │   │   │       │   ├── stm32f10x_rtc.h
    │   │   │   │       │   ├── stm32f10x_sdio.h
    │   │   │   │       │   ├── stm32f10x_spi.h
    │   │   │   │       │   ├── stm32f10x_tim.h
    │   │   │   │       │   ├── stm32f10x_usart.h
    │   │   │   │       │   └── stm32f10x_wwdg.h
    │   │   │   │       ├── Release_Notes.html
    │   │   │   │       └── src
    │   │   │   │           ├── misc.c
    │   │   │   │           ├── stm32f10x_adc.c
    │   │   │   │           ├── stm32f10x_bkp.c
    │   │   │   │           ├── stm32f10x_can.c
    │   │   │   │           ├── stm32f10x_cec.c
    │   │   │   │           ├── stm32f10x_crc.c
    │   │   │   │           ├── stm32f10x_dac.c
    │   │   │   │           ├── stm32f10x_dbgmcu.c
    │   │   │   │           ├── stm32f10x_dma.c
    │   │   │   │           ├── stm32f10x_exti.c
    │   │   │   │           ├── stm32f10x_flash.c
    │   │   │   │           ├── stm32f10x_fsmc.c
    │   │   │   │           ├── stm32f10x_gpio.c
    │   │   │   │           ├── stm32f10x_i2c.c
    │   │   │   │           ├── stm32f10x_iwdg.c
    │   │   │   │           ├── stm32f10x_pwr.c
    │   │   │   │           ├── stm32f10x_rcc.c
    │   │   │   │           ├── stm32f10x_rtc.c
    │   │   │   │           ├── stm32f10x_sdio.c
    │   │   │   │           ├── stm32f10x_spi.c
    │   │   │   │           ├── stm32f10x_tim.c
    │   │   │   │           ├── stm32f10x_usart.c
    │   │   │   │           └── stm32f10x_wwdg.c
    │   │   │   ├── Output
    │   │   │   │   ├── core_cm3.crf
    │   │   │   │   ├── core_cm3.d
    │   │   │   │   ├── core_cm3.o
    │   │   │   │   ├── CT117E-LCD.axf
    │   │   │   │   ├── CT117E-LCD.build_log.htm
    │   │   │   │   ├── CT117E-LCD.hex
    │   │   │   │   ├── CT117E-LCD.htm
    │   │   │   │   ├── CT117E-LCD.lnp
    │   │   │   │   ├── CT117E-LCD.plg
    │   │   │   │   ├── CT117E-LCD.sct
    │   │   │   │   ├── CT117E-LCD.tra
    │   │   │   │   ├── ExtDll.iex
    │   │   │   │   ├── lcd.crf
    │   │   │   │   ├── lcd.d
    │   │   │   │   ├── lcd.o
    │   │   │   │   ├── main.crf
    │   │   │   │   ├── main.d
    │   │   │   │   ├── main.o
    │   │   │   │   ├── startup_stm32f10x_md.d
    │   │   │   │   ├── startup_stm32f10x_md.o
    │   │   │   │   ├── stm32f10x_gpio.crf
    │   │   │   │   ├── stm32f10x_gpio.d
    │   │   │   │   ├── stm32f10x_gpio.o
    │   │   │   │   ├── stm32f10x_it.crf
    │   │   │   │   ├── stm32f10x_it.d
    │   │   │   │   ├── stm32f10x_it.o
    │   │   │   │   ├── stm32f10x_rcc.crf
    │   │   │   │   ├── stm32f10x_rcc.d
    │   │   │   │   ├── stm32f10x_rcc.o
    │   │   │   │   ├── system_stm32f10x.crf
    │   │   │   │   ├── system_stm32f10x.d
    │   │   │   │   └── system_stm32f10x.o
    │   │   │   ├── Project
    │   │   │   │   ├── CT117E-LCD.map
    │   │   │   │   ├── CT117E-LCD.plg
    │   │   │   │   ├── CT117E-LCD_Target 1.dep
    │   │   │   │   ├── CT117E-LCD.uvgui.Administrator
    │   │   │   │   ├── CT117E-LCD.uvgui_Administrator.bak
    │   │   │   │   ├── CT117E-LCD.uvgui.RD-01
    │   │   │   │   ├── CT117E-LCD.uvgui_RD-01.bak
    │   │   │   │   ├── CT117E-LCD.uvgui.z
    │   │   │   │   ├── CT117E-LCD.uvgui_z.bak
    │   │   │   │   ├── CT117E-LCD.uvgui.zPC
    │   │   │   │   ├── CT117E-LCD.uvgui_zPC.bak
    │   │   │   │   ├── CT117E-LCD.uvopt
    │   │   │   │   ├── CT117E-LCD_uvopt.bak
    │   │   │   │   ├── CT117E-LCD.uvproj
    │   │   │   │   ├── CT117E-LCD_uvproj.bak
    │   │   │   │   └── startup_stm32f10x_md.lst
    │   │   │   └── Sre
    │   │   │       ├── lcd.c
    │   │   │       ├── main.c
    │   │   │       └── stm32f10x_it.c
    │   │   ├── fonts.H
    │   │   ├── lcd.c
    │   │   └── lcd.h
    │   └── ReadMe！！!.txt
    └── README.MD

55 directories, 236 file
```
