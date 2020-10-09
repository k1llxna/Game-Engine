#ifndef GUIOBJECT_H
#define GUIOBJECT_H

class GuiObject {
public:
	virtual void Draw() = 0;
	virtual void FindContainingPoint() = 0;
};
#endif