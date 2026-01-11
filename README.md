# RCS Sentry Behavior Tree (Stable Release v1.0)

## 项目概述

这是一个基于ROS2和BehaviorTree.CPP开发的哨兵机器人行为树系统。

## 主要特性

### 🎯 目前的功能
- **智能巡逻**：机器人会在多个预设点之间随机巡逻
- **血量监控**：实时监控机器人血量状态
- **自动补给**：血量低于阈值时自动前往补给点
- **行为树架构**：基于BehaviorTree.CPP的可配置行为树

## 项目结构

```
├── config/                 # 配置文件
│   ├── config.yaml        # 巡逻点、补给点、血量阈值配置
│   └── sentry_bt.xml      # 行为树XML定义
├── src/
│   ├── bringup/           # ROS2启动包
│   └── sentry_bt/         # 行为树核心包
│       ├── include/sentry_bt/
│       │   ├── action_nodes/     # 动作节点定义
│       │   ├── condition_nodes/  # 条件节点定义
│       │   └── blackboard.hpp    # 黑板类定义
│       └── src/
│           ├── action_nodes/     # 动作节点实现
│           ├── condition_nodes/  # 条件节点实现
│           ├── blackboard.cpp    # 黑板实现
│           └── main.cpp          # 主程序入口
```

## 配置文件说明

### config.yaml
```yaml
patrol_points:          # 巡逻点列表
  - x: 1.0
    y: 1.0
  - x: 2.0
    y: 2.0
  # ... 更多巡逻点

supply_point:           # 补给点坐标
  x: 0.0
  y: 0.0

blood_threshold: 50     # 血量阈值
```

### sentry_bt.xml
```xml
<BehaviorTree ID="SentryMainTree">
      <Fallback name="MainFallback">
          <Sequence name="LowBloodSequence">
              <IsBloodLow/>
              <GotoSupply/>
          </Sequence>
          <Patrol/>
      </Fallback>
</BehaviorTree>
```

## 安装和使用

### 系统要求
- **ROS2版本**：Humble 或更高版本
- **依赖包**：
  - `ros-humble-navigation2`
  - `ros-humble-behaviortree-cpp-v3`
  - `yaml-cpp`

### 安装步骤

1. **克隆仓库**：
```bash
git clone https://github.com/IncrFunc/rcs_sentry_bt.git
cd rcs_sentry_bt
git checkout v1  # 切换到稳定版本
```

2. **编译项目**：
```bash
cd /path/to/workspace
colcon build --packages-select sentry_bt bringup
```

3. **设置环境**：
```bash
source install/setup.bash
```

## 运行指南

### 基本运行
```bash
# 运行行为树系统
ros2 launch bringup launch.py
```

### 完整系统运行
```bash
# 终端1：启动导航系统

# 终端2：运行哨兵行为树
ros2 launch bringup launch.py

# 终端3：发布血量数据（用于测试）
ros2 topic pub /sentry_blood std_msgs/msg/Int32 "data: 80" --rate 1
```

### 测试模式
如果没有完整的导航环境，系统会自动进入测试模式：
- 模拟所有导航行为
- 记录详细的执行日志
- 适合开发和功能验证

## 行为树架构

### 核心逻辑
```
Fallback (优先级选择)
  ├── Sequence (血量补给流程)
  │   ├── IsBloodLow (血量检查条件)
  │   └── GotoSupply (补给导航动作)
  └── Patrol (随机巡逻动作)
```

### 执行流程
1. **持续监控**：系统无限循环执行行为树
2. **状态评估**：
   - 血量 ≥ 阈值 → 执行巡逻任务
   - 血量 < 阈值 → 执行补给任务
3. **任务完成**：每次任务完成后重新评估状态

## 配置说明

### 巡逻点配置
在 `config/config.yaml` 中添加巡逻点：
```yaml
patrol_points:
  - x: 1.0
    y: 1.0
  - x: 2.0
    y: 2.0
  - x: 3.0
    y: 1.0
  - x: 2.0
    y: 0.0
```

### 补给点配置
```yaml
supply_point:
  x: 0.0
  y: 0.0
```

### 血量阈值
```yaml
blood_threshold: 50
```

## ROS2接口

### 订阅话题
- **`/sentry_blood`** (`std_msgs/Int32`)：血量数据输入

### 服务调用
- **`/navigate_to_pose`** (`nav2_msgs/NavigateToPose`)：导航服务

### 发布话题
- 导航状态反馈（通过nav2接口）

## 监控和调试


### 状态监控
```bash
# 查看血量话题
ros2 topic echo /sentry_blood

# 查看导航状态
ros2 topic echo /navigate_to_pose/_action/feedback
```

## 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件


## 致谢

感谢以下开源项目的支持：
- [ROS2](https://docs.ros.org/en/humble/)
- [BehaviorTree.CPP](https://www.behaviortree.dev/)
- [Navigation2](https://navigation.ros.org/)

---

**项目主页**: https://github.com/IncrFunc/rcs_sentry_bt  
**稳定分支**: `v1`  
**开发分支**: `dev`
