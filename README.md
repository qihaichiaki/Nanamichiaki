# Nanamichiaki
This is the learning game engine project Nanamichiaki Engine based on TheCherno's game engine project Hazel. YouTube channel: https://www.youtube.com/@TheCherno

## Learn  
### 入口点的添加 [24/8/9]  
* 创建了NNMCAK-dll、Sandbox-exe  
* 在NNMCAK中引用main函数，调用NNMCAK声明的CreateApplication，调用其中不可重写的Run方法，让引擎保持持续运行，通过在app中继承Application类，并且定义CreateApplication方法，达到入口点main在dll中的目的  

### [24/8/10]  
* 引入了第三方库spdlog作为引擎日志库的依赖  
* 引擎模块增加了LOG模块，区分引擎内部Core和外部引用应用App作为两份日志的输出  
* 首先使用NNMCAK::Log::Init() 初始化日志，使用类似NNMCAK_CORE_ERROR作为日志输出。日志等级：trace、info、warn、error、fatal  