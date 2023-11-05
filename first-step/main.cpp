#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <cstdlib>

class KeyHandler : public OgreBites::InputListener {
  bool keyPressed(const OgreBites::KeyboardEvent& evt) override {
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
      Ogre::Root::getSingleton().queueEndRendering();
    }
    return true;
  }
};

int main(int /*argc*/, char* /*argv*/[]) {
  OgreBites::ApplicationContext ctx("FirstStep");
  ctx.initApp();

  auto root = ctx.getRoot();
  auto scnMgr = root->createSceneManager();

  auto shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scnMgr);

  auto light = scnMgr->createLight("MainLight");
  auto lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  lightNode->setPosition(0, 10, 15);
  lightNode->attachObject(light);

  auto camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  camNode->setPosition(0, 0, 15);
  camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

  auto cam = scnMgr->createCamera("MyCamera");
  cam->setNearClipDistance(5);
  cam->setAutoAspectRatio(true);
  camNode->attachObject(cam);

  ctx.getRenderWindow()->addViewport(cam);

  auto ent = scnMgr->createEntity("Sinbad.mesh");
  auto node = scnMgr->getRootSceneNode()->createChildSceneNode();
  node->attachObject(ent);

  KeyHandler keyHandler;
  ctx.addInputListener(&keyHandler);

  ctx.getRoot()->startRendering();
  ctx.closeApp();

  return EXIT_SUCCESS;
}