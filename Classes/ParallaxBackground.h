#ifndef __PARALLAX_BACKGROUND_H__
#define __PARALLAX_BACKGROUND_H__

#include "cocos2d.h"

class ParallaxBackground : public cocos2d::ParallaxNode
{
private:
	bool isAddNewNode;
	int count;
	float posX;
	ParallaxBackground();
public:
	static ParallaxBackground* create();
	void updatePosition();
	virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags) override;
};

#endif // __PARALLAX_BACKGROUND_H__
