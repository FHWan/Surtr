这是我参加2024届robocom平安城市赛道使用的代码

下面是使用方法

cd ~/2024final/hz/ && conda activate paddle_new && python watch.py

进入conda虚拟环境并开始准备识别，需要先等待模型加载完毕再运行下面的程序，watch.py可以直接开启人群和大厦的识别，模型加载完成后终端会一共显示两个：准备识别巴拉巴拉

大概的逻辑就是等待文件夹内的图片出现，一旦出现就开始识别（因为那个车子的主控性能实在是太差了，这是我们想出的节省时间的办法，因为不可能一边走一边识别）

roslaunch final demo.launch

这个相当于设备初始化

roslaunch final mirobot.launch

机械臂初始化

python ~/robocom_ws/src/final/scripts/picture24.py

准备拍照，通过订阅指定的话题来确定拍照的时机，一共有三个：第一个大厦、人群、第二个大厦

rosrun final mirobot.py

这个是机械臂的使用，但是当时机械臂没用成功，只有物块的识别

rosrun final tracking2024.py

这是开始任务，我通过比赛的分段将其分为了0,1,2,3并还藏了一个4，因为当时在雷达导航出来的时候，弯道的巡线可能会过不去，所以设置了一个写死的，只要放的位置对的，就能走好

关于拍照识别，我在想了几个方案后敲定了现在这个按时间拍照的方案，性能好而且不容易出问题，除了就是要自己判断好时机改好代码
