## 使用FMOD模仿qq变声效果

主要基于android studio3.5构建一个基本的Ndk工程

### 使用步骤
1.放入一个音频格式文件在sd卡根目录下，修改QQActivity里面path路径

2.编译cmakelists修改path_project为项目绝对路径编译

### 注意
1.调用音频播放需要放在子线程，参考MainActivity

2.MainActivity演示的是FMOF官方demo提供的代码，演示基本的播放功能

### 参考
https://www.jianshu.com/p/658752a83732
