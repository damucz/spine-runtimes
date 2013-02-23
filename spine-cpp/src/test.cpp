#include <iostream>
#include <fstream>
#include <spine-marm/spine.h>
#include <IwGx.h>

using namespace std;
using namespace spine;

Atlas *atlas = NULL;
SkeletonData *skeletonData = NULL;
Skeleton *skeleton = NULL;
Animation *animation = NULL;
float animationTime = 0;
uint64 lastFrameTime = 0;

void init() {
  IwGxInit();

  try {
    ifstream atlasFile("spineboy.atlas");
    atlas = new Atlas(atlasFile);

    SkeletonJson skeletonJson(atlas);

    ifstream skeletonFile("spineboy-skeleton.json");
    skeletonData = skeletonJson.readSkeletonData(skeletonFile);

    ifstream animationFile("spineboy-walk.json");
    animation = skeletonJson.readAnimation(animationFile, skeletonData);

    skeleton = new Skeleton(skeletonData);
    skeleton->flipX = false;
    skeleton->flipY = false;
    skeleton->setToBindPose();
    skeleton->getRootBone()->x = 200;
    skeleton->getRootBone()->y = 420;
    skeleton->updateWorldTransform();
  } catch (exception &ex) {
    cout << ex.what() << endl << flush;
  }

  lastFrameTime = s3eTimerGetMs();
}

void release() {
  delete skeleton;
  delete skeletonData;
  delete animation;
  delete atlas;

  IwGxTerminate();
}

bool update() {
  float dt = (float)(s3eTimerGetMs() - lastFrameTime);
  lastFrameTime = s3eTimerGetMs();

  animationTime += dt / 1000.f;        // ms to s

  animation->apply(skeleton, animationTime, true);
  skeleton->updateWorldTransform();

  return true;
}

void draw() {
  IwGxSetColClear(0, 0, 0, 0);
  // Clear the screen
  IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
  // Draw screen space in the back so 3D sprites are visible
  IwGxSetScreenSpaceSlot(-1);


  ////////////
  skeleton->draw();

  //Iw2DFinishDrawing();

  // Flush IwGx
  IwGxFlush();

  // Display the rendered frame
  IwGxSwapBuffers();

  // Show the surface
  //	Iw2DSurfaceShow();
}

S3E_MAIN_DECL void IwMain() {

  init();

  // Main Game Loop
  while (!s3eDeviceCheckQuitRequest())
  {
    // Yield to the operating system
    s3eDeviceYield(0);

    // Prevent back-light to off state
    s3eDeviceBacklightOn();

    // Update the game
    if (!update())
      break;

    // Draw the scene
    draw();
  }

  release();

}
