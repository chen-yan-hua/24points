一、运行平台
>= Android 4.2.2（对应 API 版本17）

二、编译环境

IDE
-------------------------------
Eclipse IDE for Java Developers
Version: Oxygen.1a Release (4.7.1a)
Build id: 20171005-1200

插件
-------------------------------
ADT-23.0.6.zip
android-ndk-r17b-windows-x86.zip
android-ndk-r17b-windows-x86_64.zip
android-sdk_r24.0.2-windows.zip

三、实现说明

Android 呈现界面
JNI 调用 NDK 生成的 .so 库（实际运算逻辑）
对计算表达式进行穷举
将 24 点计算扩充到 20 到 26 点

四、运行界面

见文件 demo-1.jpg / demo-2.jpg
