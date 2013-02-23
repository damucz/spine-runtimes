#include <spine-marm/Atlas.h>

namespace spine {

Atlas::Atlas (std::ifstream &file) {
	load(file);
}

Atlas::Atlas (std::istream &input) {
	load(input);
}

Atlas::Atlas (const std::string &text) {
	load(text);
}

Atlas::Atlas (const char *begin, const char *end) {
	load(begin, end);
}

BaseAtlasPage* Atlas::newAtlasPage (std::string name) {
	AtlasPage *page = new AtlasPage();
	page->texture = new CIwTexture();
	page->texture->LoadFromFile(name.c_str());
  page->texture->SetClamping(page->uWrap == mirroredRepeat || page->vWrap == mirroredRepeat);
  page->texture->SetMipMapping(false);
  page->texture->SetFiltering(true);
  page->texture->Upload();
	return page;
}

BaseAtlasRegion* Atlas::newAtlasRegion (BaseAtlasPage* page) {
	AtlasRegion *region = new AtlasRegion();
	region->page = reinterpret_cast<AtlasPage*>(page);
	return region;
}

AtlasRegion* Atlas::findRegion (const std::string &name) {
	return reinterpret_cast<AtlasRegion*>(BaseAtlas::findRegion(name));
}

} /* namespace spine */
