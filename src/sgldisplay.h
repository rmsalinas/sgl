

#ifndef _SglDisplay_H
#define _SglDisplay_H

#include <memory>
#include "sgl_exports.h"
#include "sgl.h"
namespace sgl{

class APP_SGLVIEWER_TOOLS_API SceneDrawer{
public:
    virtual void draw(Scene &scn)=0;
};


class APP_SGLVIEWER_TOOLS_API SglDisplay
{
protected:
    std::shared_ptr<SceneDrawer> _sglDrawer;
    Scene _scn;
public:

    static std::shared_ptr<SglDisplay> create(std::shared_ptr<SceneDrawer> drawer,int w,int h,float f);
    virtual int display( bool needFullGUIInitialization=true)=0;
    void zoom(float value);
    void rotate(float x,float z);
    void translate(float x,float y);
    void setViewMatrix(sgl::Matrix44 vm);

    Scene & getScene(){return _scn;}

};
}
#endif

