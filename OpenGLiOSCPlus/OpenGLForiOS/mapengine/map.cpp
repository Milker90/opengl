//
//  map.c
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/14.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#include <stdio.h>
#include "map.h"
#include "MapImp.h"

void* wfCreateMap(void * context, int width, int height){
    MapImp * map = new MapImp(width, height, width, width);
    return map;
}

void wfDestroyMap(void *pMap){
    MapImp *map = (MapImp*)pMap;
    delete  map;
}

void  wfMapDraw(void *pMap){
    MapImp *map = (MapImp*)pMap;
    if (map){
        map->draw();
    }
}

void  wfMapSetArrowTexturePath(void *pMap, const char *path){
    MapImp *map = (MapImp*)pMap;
    if (map){
        map->setArrowTexturePath(path);
    }
}
