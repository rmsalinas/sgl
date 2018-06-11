

#include "sgldisplay.h"
#include "sgldisplay_cv.h"

namespace sgl {
std::shared_ptr<SglDisplay> SglDisplay::create(std::shared_ptr<sgl::SceneDrawer> drawer,int w,int h,float f){
  std::shared_ptr<SglDisplay> disp;

  disp=std::make_shared<SglDisplay_CV>(drawer,w,h,f);
  disp->_sglDrawer=drawer;

  return disp;
}


void SglDisplay::zoom(float value){
    _scn.zoom(value);
}
void SglDisplay::rotate(float x,float z){
    _scn.rotate(x,z);
}
void SglDisplay::translate(float x,float y){
    _scn.translate(x,y);
}

void SglDisplay::setViewMatrix(sgl::Matrix44 vm){
    _scn.setViewMatrix(vm);
}


}

