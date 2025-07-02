#include "cannonmanager.h"
#include <QSettings>

CannonManager::CannonManager() {

    loadPurchasedLevels();

}

 CannonManager* CannonManager::instance() {
    static CannonManager manager;
    return &manager;
}

// 读取本地存储的已购大炮等级
void CannonManager::loadPurchasedLevels() {
    //QSettings settings("MyGame", "Fishing");
    //​​访问方式​​：按下 Win + R，输入 regedit 打开注册表编辑器，按路径导航即可查看。
    //HKEY_CURRENT_USER\Software\MyGame\Fishing

    QSettings settings("MyGame", "Fishing");
    QVariant data = settings.value("cannons");
    if (data.isValid() && data.canConvert<QList<int>>()) {
        purchasedLevels.append(1);
        purchasedLevels = settings.value("cannons").value<QList<int>>();

    } else {
        purchasedLevels = {1}; // 默认解锁等级1
    }
}

// 检查是否拥有某等级大炮
bool CannonManager::hasLevel(int level) const {
    return purchasedLevels.contains(level);
}

// 购买大炮
void CannonManager::purchaseLevel(int level) {
    if (!purchasedLevels.contains(level)) {
        purchasedLevels.append(level);
       QSettings settings("MyGame", "Fishing");
       settings.setValue("cannons", QVariant::fromValue(purchasedLevels));
        settings.sync(); // 强制保存
        emit levelPurchased(level);
    }
}
