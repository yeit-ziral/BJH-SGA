#include "Framework.h"
#include "ModelClip.h"

ModelClip::ModelClip()
{

}

ModelClip::~ModelClip()
{
    for (pair<string, KeyFrame*> frame : keyFrames)
        delete frame.second;

    keyFrames.clear();
}

KeyFrame* ModelClip::GetKeyFrames(string name)
{
    if (keyFrames.count(name) == 0) // 안하면 알아서 name의 pair를 만들어서 unordered_map에 넣음
        return nullptr;

    return keyFrames[name];
}
