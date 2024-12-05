#ifndef OVERLAY_LAYER_H
#define OVERLAY_LAYER_H

#include "EngineCore.h"
#include "OverlayElement.h"

struct OverlayLayer {
    int zIndex;
    std::vector<OverlayElement> elements;

    OverlayLayer(int zIndex) : zIndex(zIndex) {}

    void addElement(const OverlayElement& element) { elements.push_back(element); }
};

#endif