#ifndef MENUBAR_ITEMS_BAR_H
#define MENUBAR_ITEMS_BAR_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <vector>

namespace menubar {

///
/// ItemsBar class.
///
class ItemsBar: public cocos2d::ui::Widget {
protected:
  ItemsBar(float items_gap);

public:
  static ItemsBar *create(float items_gap = 16);
  virtual bool init() override;
  virtual void onSizeChanged() override;
  virtual ~ItemsBar() {}
  void AddComponent(cocos2d::ui::Widget *component, int index = -1);
  void RemoveComponent(cocos2d::ui::Widget *component);
  bool HasComponent(cocos2d::ui::Widget *component) const;

private:
  void DoInit();
  void Layout();
  void FitComponent(cocos2d::ui::Widget *component);
  void PositionComponent(cocos2d::ui::Widget *component, float x, float y);

  void AddComponentAtIndex(cocos2d::ui::Widget *component, int index);
  void AddComponentAtEnd(cocos2d::ui::Widget *component);

private:
  float items_gap_;
  std::vector<cocos2d::ui::Widget*> components_;
};

}

#endif
