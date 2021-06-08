#ifndef CMAP_H
#define CMAP_H

#include "CRectangle.h"

extern CTexture Texture;

class CMap : public CRectangle {
public:
	void Render() {
		if (mEnabled) {
			CRectangle::Render(Texture, 0, 0, 0, 0);
		}
	}
};

#endif
