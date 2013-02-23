#include <iostream>
#include <spine-marm/RegionAttachment.h>
#include <spine-marm/Atlas.h>
#include <spine-marm/Skeleton.h>
#include <spine/Bone.h>
#include <spine/Slot.h>

namespace spine {

RegionAttachment::RegionAttachment (AtlasRegion *region) {
	texture = region->page->texture; // BOZO - Resolve attachment as late as possible?
	float u = region->x;
	float u2 = u + region->width;
	float v = region->y;
	float v2 = v + region->height;

  // normalize to 1.0f
  u /= texture->GetWidth();
  u2 /= texture->GetWidth();
  v /= texture->GetHeight();
  v2 /= texture->GetHeight();

	if (region->rotate) {
		verticesUV[1].x = u;
		verticesUV[1].y = v2;
		verticesUV[2].x = u;
		verticesUV[2].y = v;
		verticesUV[3].x = u2;
		verticesUV[3].y = v;
		verticesUV[0].x = u2;
		verticesUV[0].y = v2;
	} else {
		verticesUV[0].x = u;
		verticesUV[0].y = v2;
		verticesUV[1].x = u;
		verticesUV[1].y = v;
		verticesUV[2].x = u2;
		verticesUV[2].y = v;
		verticesUV[3].x = u2;
		verticesUV[3].y = v2;
	}
}

void RegionAttachment::draw (Slot *slot) {
	Skeleton* skeleton = (Skeleton*)slot->skeleton;

	uint8 r = (uint8)(skeleton->r * slot->r * 255);
	uint8 g = (uint8)(skeleton->g * slot->g * 255);
	uint8 b = (uint8)(skeleton->b * slot->b * 255);
	uint8 a = (uint8)(skeleton->a * slot->a * 255);
	verticesColor.Set(r, g, b, a);

	updateOffset(); // BOZO - Move to resolve()?
	updateWorldVertices(slot->bone);

	skeleton->texture = texture;
	skeleton->vertexArray.push_back(vertices[0]);
	skeleton->vertexArray.push_back(vertices[3]);
	skeleton->vertexArray.push_back(vertices[2]);
	skeleton->vertexArray.push_back(vertices[1]);
  skeleton->vertexUVArray.push_back(verticesUV[0]);
  skeleton->vertexUVArray.push_back(verticesUV[3]);
  skeleton->vertexUVArray.push_back(verticesUV[2]);
  skeleton->vertexUVArray.push_back(verticesUV[1]);
  skeleton->vertexColorArray.push_back(verticesColor);
}

void RegionAttachment::updateWorldVertices (spine::Bone *bone) {
	float x = bone->worldX;
	float y = bone->worldY;
	float m00 = bone->m00;
	float m01 = bone->m01;
	float m10 = bone->m10;
	float m11 = bone->m11;
	vertices[0].x = offset[0] * m00 + offset[1] * m01 + x;
	vertices[0].y = offset[0] * m10 + offset[1] * m11 + y;
	vertices[1].x = offset[2] * m00 + offset[3] * m01 + x;
	vertices[1].y = offset[2] * m10 + offset[3] * m11 + y;
	vertices[2].x = offset[4] * m00 + offset[5] * m01 + x;
	vertices[2].y = offset[4] * m10 + offset[5] * m11 + y;
	vertices[3].x = offset[6] * m00 + offset[7] * m01 + x;
	vertices[3].y = offset[6] * m10 + offset[7] * m11 + y;
}

} /* namespace spine */
