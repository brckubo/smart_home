# Smart_home
## 基于MQTT智能家居系统设计 
包括远程摄像头观测（推流）,环境温湿度（MQTT），远程开关，智能音箱（WU-KONG-ROBOT）,智能手环心率血氧检测，MQTT服务器搭建，ANDROID客户端查看设备
### 服务端（arno_server）
    服务器采用ESC云服务器，系统为Ubuntu 20.04.1 LTS

**服务器搭建**

- ***Step1.*** 购买云服务器

>云服务购买参考：[腾讯云学生机购买链接](https://blog.csdn.net/weixin_46628200/article/details/107292935)

>服务器系统选择Ubuntu 20.04.1 LTS，设置服务器密码

- ***Step2.*** 连接到服务器

>远程ssh连接软件选择 **finalshell** ,

     Windows版下载地址:
     http://www.hostbuf.com/downloads/finalshell_install.exe
     其他版本下载： 
     http://www.hostbuf.com/t/988.html
>在云服务的控制台复制服务器公网IP,填入连接的用户名（一般默认为root）,密码为上面你设置的服务器密码
 
`连接到云服务器参考：`[Finalshell远程连接Linux服务器](https://blog.csdn.net/qq_44163269/article/details/107123402?utm_medium=distribute.pc_relevant.none-task-blog-OPENSEARCH-3.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-OPENSEARCH-3.control)

>MQTT服务器搭建，我们采用的是[EMQ](https://github.com/emqx/emqx)
      
      # 1.使用finalshell登录到云服务器
      # 2.下载EMQ源码包,在终端执行下面命令
      git clone -b v4.0.0 https://github.com/emqx/emqx-rel.git
      cd emqx-rel && make
      cd _build/emqx/rel/emqx && ./bin/emqx console 

      # ! 报错处理
      1.  /usr/bin/env: ‘escript’: No such file or directory 
          make: *** [Makefile:51: emqx] Error 127
      依次执行：
          wget http://erlang.org/download/otp_src_20.3.tar.gz
          tar xzf otp_src_20.3.tar.gz
          cd otp_src_20.3
          ./configure --prefix=/home/erlang   --without-javac  
          ln -s /home/erlang/bin/erl /usr/local/bin/erl
          export PATH=$PATH:/home/erlang/bin
          

      



