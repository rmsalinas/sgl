

#ifndef _SglDisplay_QT_H
#define _SglDisplay_QT_H

#include <memory>
#include "sgl_exports.h"
#include "sgldisplay.h"
namespace sgl{
class SglDisplay_QT_Internal;

class APP_SGLVIEWER_TOOLS_API SglDisplay_QT :public SglDisplay
{

public:
    SglDisplay_QT(std::shared_ptr<sgl::SceneDrawer> drawer,int w,int h,float f);

     virtual int display(bool needFullGUIInitialization);


private:

  SglDisplay_QT_Internal *_window_display;

};

}
#endif

