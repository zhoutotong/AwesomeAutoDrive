# AwesomeVehicle

## 主要属性

### 车辆对象、设备对象

|名称|含义|
|-:|:-|
|name|人机交互名称，便于阅读为准|
|tag|设备厂商名称或品牌信息|
|label|设备唯一标识，在同一个父设备下，这个标签是唯一的|
|type|设备类型标识，譬如：Camera|
|desc|描述字符串，暂时未加入|

公用接口

|名称|含义|
|-:|:-|
|setup|初始化资源|
|release|解除初始化，并销毁资源|
|start|启动设备|
|stop|关闭设备|

