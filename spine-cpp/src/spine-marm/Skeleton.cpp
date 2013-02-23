#include <iostream>
#include <spine-marm/Skeleton.h>
#include <spine/SkeletonData.h>
#include <spine/Slot.h>
#include <spine/Attachment.h>
#include <IwGx.h>

namespace spine {

Skeleton::Skeleton (SkeletonData *skeletonData) :
				BaseSkeleton(skeletonData),
				vertexArray(skeletonData->bones.size() * 4),
        vertexUVArray(skeletonData->bones.size() * 4),
        vertexColorArray(skeletonData->bones.size()),
				texture(0)
{
}

void Skeleton::draw () const {
	const_cast<Skeleton*>(this)->vertexArray.clear();
  const_cast<Skeleton*>(this)->vertexUVArray.clear();
  const_cast<Skeleton*>(this)->vertexColorArray.clear();
	for (int i = 0, n = slots.size(); i < n; i++)
		if (slots[i]->attachment) slots[i]->attachment->draw(slots[i]);
	//target.draw(vertexArray, texture);

  int num_vertices = vertexArray.size();
  CIwFVec2 *uvs = texture ? IW_GX_ALLOC(CIwFVec2, num_vertices) : NULL;
  CIwSVec2 *verts = IW_GX_ALLOC(CIwSVec2, num_vertices);
  CIwColour *colors = IW_GX_ALLOC(CIwColour, num_vertices);

  IwTrace(XX, ("%d %d %d", vertexArray.size(), vertexUVArray.size(), vertexColorArray.size()));

  for (int i = 0; i < num_vertices; ++i)
  {
    uvs[i] = vertexUVArray[i];
    verts[i].x = (int)vertexArray[i].x;
    verts[i].y = (int)vertexArray[i].y;
    colors[i] = vertexColorArray[i>>2];     // divide by 4.f, same color for the four vertices
  }

  CIwMaterial* mat = IW_GX_ALLOC_MATERIAL();
  if (texture) {
    mat->SetTexture(texture);
  } else {
    mat->SetTexture(NULL);
  }
  mat->SetDepthWriteMode(CIwMaterial::DEPTH_WRITE_DISABLED);
  mat->SetAlphaMode(CIwMaterial::ALPHA_BLEND);
  IwGxSetMaterial(mat);		// can be cached to improve performance

  IwGxSetUVStream(uvs);
  IwGxSetVertStreamScreenSpace(verts, num_vertices);
  IwGxSetColStream(colors, num_vertices);
  IwGxSetNormStream(NULL);
  IwGxDrawPrims(IW_GX_QUAD_LIST, NULL, num_vertices);
}

} /* namespace spine */
