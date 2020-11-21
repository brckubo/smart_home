# Smart_home
## 基于MQTT智能家居系统设计 
包括远程摄像头观测（推流）,环境温湿度（MQTT），远程开关，智能音箱（WU-KONG-ROBOT）,智能手环心率血氧检测，MQTT服务器搭建，ANDROID客户端查看设备。``**没有做安全效验,用户效验，智能配网等操作，需要自己去完善**``
### 服务端（arno_server）
    服务器采用ESC云服务器，系统为Ubuntu 20.04.1 LTS

**服务器搭建**

- ***Step1.*** 购买云服务器

>云服务购买参考：[腾讯云学生机购买链接](https://blog.csdn.net/weixin_46628200/article/details/107292935)

>服务器系统选择Ubuntu 20.04.1 LTS，设置服务器密码

- ***Step2.*** 安装 **MQTT** 服务器

>远程ssh连接软件选择 **finalshell** 

     Windows版下载地址:
     http://www.hostbuf.com/downloads/finalshell_install.exe
     其他版本下载： 
     http://www.hostbuf.com/t/988.html
>在云服务的控制台复制服务器公网IP,填入连接的用户名（一般默认为root）,密码为上面你设置的服务器密码
 
`连接到云服务器参考：`[Finalshell远程连接Linux服务器](https://blog.csdn.net/qq_44163269/article/details/107123402?utm_medium=distribute.pc_relevant.none-task-blog-OPENSEARCH-3.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-OPENSEARCH-3.control)

>MQTT服务器搭建，我们采用的是[EMQX](https://github.com/emqx/emqx)
      
      # 1.使用finalshell登录到云服务器
      
      # 2.安装docker
        apt install docker.io

      # 3.在docker运行emqx
        docker run -d --name emqx -p 1883:1883 -p 8083:8083 -p 8883:8883 -p 8084:8084 -p 18083:18083 emqx/emqx
>在云服务的控制台里面的防火墙规则开启端口1883(mqtt端口)，18083(mqtt后台管理，账号密码：admin/public）

- ***Step3.*** 安装 **Nginx RTMP** 服务器
>安装Nginx RTMP

`安装参考：`[rtmp流媒体服务器搭建](http://www.mamicode.com/info-detail-2640107.html)
>在云服务的控制台里面的防火墙规则开启端口80(nginx web端口)，1935(RTMP端口）
>在浏览器中输入服务器的IP地址，如果出现 `Welcome to Nginx!` 就成功了

### 远程开关（smart_switch）

- ***Step1.*** 准备元器件
>ESP8266 NodeMCU Lua V3 + usb传输线  *  1

>3脚共阳LED灯+单脚LED灯 * 1

>1K电阻数颗

- ***Step2.*** 电路连接
      
      



