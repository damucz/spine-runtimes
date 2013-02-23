#ifndef SPINE_REGIONATTACHMENT_H_
#define SPINE_REGIONATTACHMENT_H_

#include <spine/BaseRegionAttachment.h>
#include <IwGx.h>

namespace spine {

class Bone;
class AtlasRegion;

class RegionAttachment: public BaseRegionAttachment {
public:
  CIwFVec2 vertices[4];
	CIwFVec2 verticesUV[4];
  CIwColour verticesColor;      // same color for all the vertices
	CIwTexture *texture;

	RegionAttachment (AtlasRegion *region);

	virtual void updateWorldVertices (Bone *bone);
	virtual void draw (Slot *slot);
};

} /* namespace spine */
#endif /* SPINE_REGIONATTACHMENT_H_ */
