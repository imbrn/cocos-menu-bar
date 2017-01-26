#include "menu_bar.h"
#include <cmath>

namespace menubar {

MenuBar::MenuBar(const Padding &padding, float items_gap):
      padding_(padding),
      items_gap_(items_gap) {
}

MenuBar *MenuBar::create(const Padding &padding, float items_gap) {
  MenuBar *obj = new MenuBar(padding ,items_gap);
  if (obj->init()) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return nullptr;
  }
}

bool MenuBar::init() {
  if (!cocos2d::ui::Widget::init()) {
    return false;
  }
  DoInit();
  return true;
}

void MenuBar::DoInit() {
  InitLeftItems();
  InitRightItems();
  SetDefaultSize();
}

void MenuBar::InitLeftItems() {
  left_items_ = ItemsBar::create(items_gap_);
  left_items_->setAnchorPoint({0, 0});
  addChild(left_items_, 1);
}

void MenuBar::InitRightItems() {
  right_items_ = ItemsBar::create(items_gap_);
  right_items_->setAnchorPoint({1, 0});
  addChild(right_items_, 1);
}

void MenuBar::SetDefaultSize() {
  auto director = cocos2d::Director::getInstance();
  auto visible_size = director->getVisibleSize();
  setAnchorPoint({0, 1});
  setPosition({0, visible_size.height});
  setContentSize({visible_size.width, 50});
}

void MenuBar::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  FitBackground();
  PositionLeftItems();
  PositionRightItems();
}

void MenuBar::PositionLeftItems() {
  left_items_->setContentSize({0, available_height()});
  float x = padding_.left;
  float y = padding_.bottom;
  left_items_->setPosition({x, y});
}

void MenuBar::PositionRightItems() {
  right_items_->setContentSize({0, available_height()});
  float x = getContentSize().width - padding_.right;
  float y = padding_.bottom;
  right_items_->setPosition({x, y});
}

float MenuBar::available_height() const {
  return getContentSize().height - padding_.top - padding_.bottom;
}

void MenuBar::set_background(cocos2d::ui::Widget *background) {
  RemoveBackground();
  background_ = background;
  AddBackground();
  FitBackground();
}

void MenuBar::set_background(const cocos2d::Color3B &color) {
  auto background = cocos2d::ui::Layout::create();
  background->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
  background->setBackGroundColor(color);
  set_background(background);
}

void MenuBar::RemoveBackground() {
  if (background_) {
    this->removeChild(background_);
    background_ = nullptr;
  }
}

void MenuBar::AddBackground() {
  if (background_) {
    this->addChild(background_);
  }
}

void MenuBar::FitBackground() {
  if (background_) {
    background_->setContentSize(getContentSize());
    background_->setAnchorPoint({0, 0});
    background_->setPosition({0, 0});
  }
}

void MenuBar::AddLeftComponent(cocos2d::ui::Widget *component, unsigned int index) {
  left_items_->AddComponent(component, index);
}

void MenuBar::AddRightComponent(cocos2d::ui::Widget *component, unsigned int index) {
  right_items_->AddComponent(component, index);
}

void MenuBar::RemoveAllComponents() {
  RemoveAllLeftComponents();
  RemoveAllRightComponents();
}

void MenuBar::RemoveAllLeftComponents() {
  left_items_->RemoveAllComponents();
}

void MenuBar::RemoveAllRightComponents() {
  right_items_->RemoveAllComponents();
}

}
