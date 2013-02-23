#ifndef SPINE_SKELETON_H_
#define SPINE_SKELETON_H_

#include <spine/BaseSkeleton.h>
#include <IwGx.h>
#include <vector>

namespace spine {

class Skeleton: public BaseSkeleton {
public:
  std::vector<CIwFVec2> vertexArray;
  std::vector<CIwFVec2> vertexUVArray;
  std::vector<CIwColour> vertexColorArray;
	CIwTexture *texture; // BOZO - This is ugly. Support multiple textures?

	Skeleton (SkeletonData *skeletonData);

	virtual void draw () const;
};

} /* namespace spine */
#endif /* SPINE_SKELETON_H_ */
