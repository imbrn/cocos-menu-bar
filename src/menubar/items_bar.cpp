#include "items_bar.h"
#include <algorithm>

namespace menubar {

ItemsBar::ItemsBar(float items_gap): items_gap_(items_gap) {
}

ItemsBar *ItemsBar::create(float items_gap) {
  ItemsBar *obj = new ItemsBar(items_gap);
  if (obj->init()) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return nullptr;
  }
}

bool ItemsBar::init() {
  if (!cocos2d::ui::Widget::init())
    return false;
  DoInit();
  return true;
}

void ItemsBar::DoInit() {
  setAnchorPoint({0.5, 0.5});
}

void ItemsBar::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  Layout();
}

void ItemsBar::Layout() {
  float x = 0;
  for (auto component : components_)
    if (component && component->isVisible()) x = LayoutComponent(component, x);
  setContentSize({x - items_gap_, getContentSize().height});
}

float ItemsBar::LayoutComponent(cocos2d::ui::Widget *component, float x) {
  FitComponent(component);
  PositionComponent(component, x, 0);
  return component->getBoundingBox().getMaxX() + items_gap_;
}

void ItemsBar::FitComponent(cocos2d::ui::Widget *component) {
  auto scale = getContentSize().height / component->getContentSize().height;
  component->setScale(scale, scale);
}

void ItemsBar::PositionComponent(cocos2d::ui::Widget *component, float x, float y) {
  component->setAnchorPoint({0.5, 0.5});
  float component_x = (x + component->getBoundingBox().size.width / 2);
  float component_y = (y + component->getBoundingBox().size.height / 2);
  component->setPosition({component_x, component_y});
}

void ItemsBar::AddComponent(cocos2d::ui::Widget *component, int index) {
  if (!HasComponent(component)) {
    if (index != -1) AddComponentAtIndex(component, index);
    else AddComponentAtEnd(component);
    this->addChild(component);
    Layout();
  }
}

void ItemsBar::AddComponentAtIndex(cocos2d::ui::Widget *component, int index) {
  components_.insert(components_.begin() + index, component);
}

void ItemsBar::AddComponentAtEnd(cocos2d::ui::Widget *component) {
  components_.push_back(component);
}

void ItemsBar::RemoveAllComponents() {
  for (auto component : components_) {
    RemoveComponent(component);
  }
}

void ItemsBar::RemoveComponent(cocos2d::ui::Widget *component) {
  auto index = std::find(components_.begin(), components_.end(), component);
  if (index  != components_.end()) {
    components_.erase(index);
    this->removeChild(component);
    Layout();
  }
}

bool ItemsBar::HasComponent(cocos2d::ui::Widget *component) const {
  return std::find(components_.begin(), components_.end(), component) != components_.end();
}

}
