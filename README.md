

# FishGame 项目说明

## 项目简介
FishGame 是一个基于 Qt 开发的捕鱼游戏项目，主要包含游戏界面、鱼类管理、炮台控制、商店系统等功能模块。游戏支持鼠标操作，包含多种鱼类对象和金币计数系统。

## 主要功能
- 多种鱼类动画与行为控制（clownfish, goldenfish, shark 等）
- 游戏界面交互（EasyView 类）
- 金币计数与持久化存储（QCoinCounter 类）
- 炮台等级管理（CannonManager 类）
- 商店购买系统（shop 类）

## 游戏核心类
- **EasyView**：主游戏界面，处理鼠标事件和游戏逻辑
- **QFish**：所有鱼类对象的基类，实现鱼类动画和绘制功能
- **QPixmapItem**：图形元素基类，用于管理游戏中的图像对象
- **CannonManager**：管理炮台等级和已购买关卡数据
- **QCoinCounter**：金币计数器，支持增减操作和数据持久化

## 游戏特色
- 支持多种鱼类对象，每种鱼类具有不同的行为模式
- 提供完整的金币管理系统，包含数据的加载和保存功能
- 游戏界面支持鼠标移动和点击事件
- 包含商店系统，可以购买不同等级的炮台

## 依赖环境
- Qt 6.8.1
- C++11 或更高版本
- QGraphicsView 框架

## 使用方法
1. 打开 Qt Creator
2. 加载项目 CMakeLists.txt
3. 选择合适的构建套件（建议使用 Desktop Qt 6.8.1 llvm_mingw64）
4. 构建并运行项目

## 项目结构
- `qfish/`: 鱼类对象实现
- `qpixmapitem/`: 图形元素基类
- `fish_illustration/`: 游戏中各种鱼类的示意图
- `image/`: 游戏资源图片
- `shop.cpp`: 商店界面实现
- `main.cpp`: 程序入口

## 版权信息
本项目使用 [MIT License](https://opensource.org/licenses/MIT) 开源协议（如未特别指定）。
